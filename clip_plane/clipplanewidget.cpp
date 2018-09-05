//
// Created by zhaojunhe on 2018/9/4.
//

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QVector3D>
#include <set>
#include <iostream>
#include "clipplanewidget.hpp"
#include "../loadshader/LoadShader.hpp"

ClipPlaneWidget::ClipPlaneWidget(QWidget *parent) : QOpenGLWidget(parent) {}

ClipPlaneWidget::~ClipPlaneWidget() {}

void ClipPlaneWidget::initializeGL() {
    loadObject();

    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER,   "/Users/junhe/Documents/OpenGL/opengl_qt_mac/clip_plane/clip_plane_vs.glsl"},
            {GL_FRAGMENT_SHADER, "/Users/junhe/Documents/OpenGL/opengl_qt_mac/clip_plane/clip_plane_fs.glsl"},
            {GL_NONE}
    };

    program = LoadShaders(shaders);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, objectVectexs.size() * sizeof(float), objectVectexs.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    glGenBuffers(1, &normal_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, normal_vbo);
    glBufferData(GL_ARRAY_BUFFER, objectNormals.size() * sizeof(float), objectNormals.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    mvpmatrixLoc = glGetUniformLocation(program, "u_mvpmatrix");
    mmatrixLoc = glGetUniformLocation(program, "u_mmatrix");
    lightposLoc = glGetUniformLocation(program, "u_light_pos");
    cameraLoc = glGetUniformLocation(program, "u_camera");
    clipplaneLoc = glGetUniformLocation(program, "u_clip_plane");

    glClearColor(0.3, 0.3, 0.3, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    std::cout << __FUNCTION__ << std::endl;
}

void ClipPlaneWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    float aspect = (float) w / (float) h;

    // must set to identity.
    projMatrx.setToIdentity();
    projMatrx.frustum(-aspect, aspect, -1, 1, 2, 100);

    viewMatrx.setToIdentity();
    viewMatrx.lookAt({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f});

    modelMatrx.setToIdentity();
    modelMatrx.translate(0, -2.0f, -25.0f);

    std::cout << __FUNCTION__ << " w, h " << w << " " << h << std::endl;
}

void ClipPlaneWidget::paintGL() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    lightPos = {40, 10, 20};
    cameraPos = {0.0f, 0.0f, 0.0f};
    clip_plane = {0.0f, 0.0f, 0.0f, 1.0};

    glUseProgram(program);

    glUniformMatrix4fv(mvpmatrixLoc, 1, GL_FALSE, (projMatrx * viewMatrx * modelMatrx).data());
    glUniformMatrix4fv(mmatrixLoc, 1, GL_FALSE, modelMatrx.data());
    glUniform3fv(lightposLoc, 1, lightPos.data());
    glUniform3fv(cameraLoc, 1, cameraPos.data());
    glUniform4fv(clipplaneLoc, 1, clip_plane.data());

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, objectVectexs.size() / 3);
}

void ClipPlaneWidget::keyPressEvent(QKeyEvent *event) {
}

void ClipPlaneWidget::loadObject() {

    std::vector<float> v_vertex;
    std::vector<uint16_t> indexs;

    std::map<uint16_t, std::set<std::array<float, 3>>> normal_map;

    QFile myobject("/Users/junhe/Documents/OpenGL/opengl_qt_mac/clip_plane/ch.obj");
    if (!myobject.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "route don't open.";
        return;
    }
    QTextStream in(&myobject);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(QRegExp("[ ]+"));

        if (parts[0].trimmed() == "v") {
            v_vertex.push_back(parts[1].toFloat());
            v_vertex.push_back(parts[2].toFloat());
            v_vertex.push_back(parts[3].toFloat());
        } else if (parts[0].trimmed() == "f") {
            uint16_t index[3];
            index[0] = parts[1].split(QRegExp("/"))[0].toInt() - 1;

            QVector3D firstPoint(v_vertex[3 * index[0]], v_vertex[3 * index[0] + 1], v_vertex[3 * index[0] + 2]);

            objectVectexs.push_back(firstPoint.x());
            objectVectexs.push_back(firstPoint.y());
            objectVectexs.push_back(firstPoint.z());


            index[1] = parts[2].split(QRegExp("/"))[0].toInt() - 1;
            QVector3D secPoint(v_vertex[3 * index[1]], v_vertex[3 * index[1] + 1], v_vertex[3 * index[1] + 2]);

            objectVectexs.push_back(secPoint.x());
            objectVectexs.push_back(secPoint.y());
            objectVectexs.push_back(secPoint.z());

            index[2] = parts[3].split(QRegExp("/"))[0].toInt() - 1;
            QVector3D thirdPoint(v_vertex[3 * index[2]], v_vertex[3 * index[2] + 1], v_vertex[3 * index[2] + 2]);
            objectVectexs.push_back(thirdPoint.x());
            objectVectexs.push_back(thirdPoint.y());
            objectVectexs.push_back(thirdPoint.z());

            indexs.push_back(index[0]);
            indexs.push_back(index[1]);
            indexs.push_back(index[2]);

            QVector3D normal = QVector3D::crossProduct(secPoint - firstPoint, thirdPoint - firstPoint);

            for (uint16_t idx:index) {
                normal_map[idx].insert({normal.x(), normal.y(), normal.z()});
            }
        }
    }

    myobject.close();

    objectNormals.reserve(indexs.size() * 3);
    for (int i:indexs) {
        QVector3D averageNormal(0, 0, 0);
        for (auto norm : normal_map[i]) {
            QVector3D vec(norm[0], norm[1], norm[2]);
            averageNormal += vec;
        }

        averageNormal.normalize();

        objectNormals.push_back(averageNormal.x());
        objectNormals.push_back(averageNormal.y());
        objectNormals.push_back(averageNormal.z());
    }

    std::cout << __FUNCTION__ << std::endl;

}
