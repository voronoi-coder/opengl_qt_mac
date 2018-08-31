//
// Created by zhaojunhe on 2018/8/24.
//

#include <QMatrix4x4>
#include <QKeyEvent>
#include "drawlinewidget.hpp"
#include "optional.hpp"
#include "../loadshader/LoadShader.hpp"


DrawLineGLWidget::DrawLineGLWidget(QWidget *parent) : QOpenGLWidget(parent) {

}

DrawLineGLWidget::~DrawLineGLWidget() {

}

void DrawLineGLWidget::initializeGL() {
    ShaderInfo light_shaders[] = {
            {GL_VERTEX_SHADER,   "/Users/junhe/Documents/OpenGL/opengl_qt_mac/drawline/line_vs.glsl"},
            {GL_FRAGMENT_SHADER, "/Users/junhe/Documents/OpenGL/opengl_qt_mac/drawline/line_fs.glsl"},
            {GL_NONE}
    };

    program = LoadShaders(light_shaders);

    std::vector<QPoint> line;
    line.push_back({0, 0});
    line.push_back({0, 1});
    line.push_back({1, 1});
    line.push_back({1, 0});

    buildLine(line);

    // buildline
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexs.size() * sizeof(LineLayoutVertex), vertexs.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexs.size() * sizeof(uint16_t), indexs.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 2, GL_UNSIGNED_SHORT, GL_FALSE, sizeof(LineLayoutVertex), (void *) 0);
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(LineLayoutVertex),
                          (void *) offsetof(LineLayoutVertex, a_data));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    matrixLoc = glGetUniformLocation(program, "u_matrix");
    colorLoc = glGetUniformLocation(program, "u_color");
    widthLoc = glGetUniformLocation(program, "u_width");
}

void DrawLineGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    aspect = float(w) / float(h);
}

void DrawLineGLWidget::paintGL() {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    glUseProgram(program);

    QMatrix4x4 projM;
    projM.setToIdentity();
    projM.perspective(45.0f, aspect, 1.0f, 500.0f);
    QMatrix4x4 modelM;
    modelM.setToIdentity();
    modelM.translate(.0f, 0.0f, -10.0f);

    GLfloat color[4] = {1.0f, 0.0f, 0.0f, 1.0f};

    glUniformMatrix4fv(matrixLoc, 1, GL_FALSE, (projM * modelM).data());
    glUniform4fv(colorLoc, 1, color);
    glUniform1f(widthLoc, 0.5f);

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLES, indexs.size(), GL_UNSIGNED_SHORT, nullptr);
}

const float SHARP_CORNER_OFFSET = 15.0f;
const float COS_HALF_SHARP_CORNER = std::cos(75.0 / 2.0 * (M_PI / 180.0));

// The number of bits that is used to store the line distance in the buffer.
const int LINE_DISTANCE_BUFFER_BITS = 14;

// We don't have enough bits for the line distance as we'd like to have, so
// use this value to scale the line distance (in tile units) down to a smaller
// value. This lets us store longer distances while sacrificing precision.
const float LINE_DISTANCE_SCALE = 1.0 / 2.0;

// The maximum line distance, in tile units, that fits in the buffer.
const float MAX_LINE_DISTANCE = std::pow(2, LINE_DISTANCE_BUFFER_BITS) / LINE_DISTANCE_SCALE;

QVector2D perp(const QVector2D &v) {
    return QVector2D(-v.y(), v.x());
}

void DrawLineGLWidget::buildLine(const std::vector<QPoint> coordinates) {
    const std::size_t len = [&coordinates] {
        std::size_t l = coordinates.size();
        while (l >= 2 && coordinates[l - 1] == coordinates[l - 2]) {
            l--;
        }
        return l;
    }();

    const std::size_t first = [&coordinates, &len] {
        std::size_t i = 0;
        while (i < len - 1 && coordinates[i] == coordinates[i + 1]) {
            i++;
        }
        return i;
    }();

    if (len < 2)return;

    const LineJoinType joinType = LineJoinType::Miter;
    const float miterLimit = joinType == LineJoinType::Bevel ? 1.05f : m_miter_limit;

    const QPoint firstCoordinate = coordinates[first];
    const LineCapType beginCap = LineCapType::Butt;
    const LineCapType endCap = LineCapType::Butt;

    double distance = 0;
    bool startOfLine = true;

    optional<QPoint> currentCoordinate;
    optional<QPoint> prevCoordinate;
    optional<QPoint> nextCoordinate;
    optional<QVector2D> prevNormal;
    optional<QVector2D> nextNormal;

    e1 = e2 = e3 = -1;

    for (std::size_t i = first; i < len; ++i) {
        if (i + 1 < len) {
            nextCoordinate = coordinates[i + 1];
        } else {
            nextCoordinate = {};
        }

        if (nextCoordinate && coordinates[i] == *nextCoordinate) {
            continue;
        }

        if (nextNormal) {
            prevNormal = nextNormal;
        }
        if (currentCoordinate) {
            prevCoordinate = *currentCoordinate;
        }

        currentCoordinate = coordinates[i];

        nextNormal = nextCoordinate ? perp(QVector2D(*nextCoordinate - *currentCoordinate).normalized()) : prevNormal;

        if (!prevNormal) {
            prevNormal = *nextNormal;
        }

        QVector2D joinNormal = *prevNormal + *nextNormal;
        if (joinNormal.x() != 0 || joinNormal.y() != 0) {
            joinNormal.normalize();
        }

        const double cosHalfAngle = joinNormal.x() * nextNormal->x() + joinNormal.y() * nextNormal->y();
        const double miterLength = cosHalfAngle != 0 ? 1 / cosHalfAngle : std::numeric_limits<double>::infinity();
        const bool isSharpCorner = cosHalfAngle < COS_HALF_SHARP_CORNER && prevCoordinate && nextCoordinate;

        const bool middleVertex = prevCoordinate && nextCoordinate;
        const LineJoinType currentJoin = joinType;
        const LineCapType currentCap = nextCoordinate ? beginCap : endCap;
        // Calculate how far along the line the currentVertex is
        if (prevCoordinate)
            distance += QVector2D(*currentCoordinate - *prevCoordinate).length();

        if (!middleVertex && currentCap == LineCapType::Butt) {
            if (nextCoordinate) {
                addCurrentVertex(*currentCoordinate, distance, *nextNormal, 0, 0, false);
            } else {
                addCurrentVertex(*currentCoordinate, distance, *prevNormal, 0, 0, false);
            }
        } else if (middleVertex && currentJoin == LineJoinType::Miter) {
            joinNormal = joinNormal * miterLength;
            addCurrentVertex(*currentCoordinate, distance, joinNormal, 0, 0, false);
        }

    }
}

void DrawLineGLWidget::addCurrentVertex(const QPoint &currentCoordinate, double &distance, const QVector2D &normal,
                                        double endLeft, double endRight, bool round) {
    QVector2D extrude = normal;
    if (endLeft) {
        extrude = extrude - (perp(extrude) * endLeft);
    }

    vertexs.push_back(
            LineLayoutVertex(currentCoordinate, extrude, {round, false}, endLeft, distance * LINE_DISTANCE_SCALE));
    e3 = vertexs.size() - 1;
    if (e1 >= 0 && e2 >= 0) {
        indexs.push_back(e1);
        indexs.push_back(e2);
        indexs.push_back(e3);
    }
    e1 = e2;
    e2 = e3;

    extrude = normal * -1.0;
    if (endRight) {
        extrude = extrude - (perp(normal) * endRight);
    }

    vertexs.push_back(
            LineLayoutVertex(currentCoordinate, extrude, {round, true}, -endRight, distance * LINE_DISTANCE_SCALE));
    e3 = vertexs.size() - 1;
    if (e1 >= 0 && e2 >= 0) {
        indexs.push_back(e1);
        indexs.push_back(e2);
        indexs.push_back(e3);
    }
    e1 = e2;
    e2 = e3;

    // There is a maximum "distance along the line" that we can store in the buffers.
    // When we get close to the distance, reset it to zero and add the vertex again with
    // a distance of zero. The max distance is determined by the number of bits we allocate
    // to `linesofar`.
    if (distance > MAX_LINE_DISTANCE / 2.0f) {
        distance = 0;
        addCurrentVertex(currentCoordinate, distance, normal, endLeft, endRight, round);
    }
}

void DrawLineGLWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_M: {
            polygonMode = (polygonMode == GL_FILL) ? GL_LINE : GL_FILL;
            update();
        }
            break;
    }
}























