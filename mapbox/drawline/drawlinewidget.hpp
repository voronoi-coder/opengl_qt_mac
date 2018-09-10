//
// Created by zhaojunhe on 2018/8/24.
//
#pragma once

#include <QOpenGLWidget>
#include <array>
#include <QVector2D>
#include <cmath>

enum class LineCapType : uint8_t {
    Round,
    Butt,
    Spuare
};

enum class LineJoinType : uint8_t {
    Miter,
    Bevel,
    Round,
    FakeRound,
    FlipBevel
};

class DrawLineGLWidget : public QOpenGLWidget {
public:
    DrawLineGLWidget(QWidget *parent = 0);

    ~DrawLineGLWidget();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    void buildLine(const std::vector<QPoint> coordinates, LineCapType cap = LineCapType::Butt);
    void addCurrentVertex(const QPoint &currentCoordinate, double &distance, const QVector2D &normal, double endLeft, double endRight, bool round);

private:
    static const int8_t extrudeScale = 63;

    struct LineLayoutVertex {
        LineLayoutVertex(QPoint p, QVector2D e, std::array<bool, 2> t, int8_t dir, int32_t linesofar = 0)
                : a_pos({static_cast<int16_t>(p.x() * 2 | t[0]), static_cast<int16_t>(p.y() * 2 | t[1])}),
                  a_data({static_cast<uint8_t>(::round(extrudeScale * e.x()) + 128), // maximum miter length is 2.
                          static_cast<uint8_t>(::round(extrudeScale * e.y()) + 128),
                          static_cast<uint8_t>(((dir == 0 ? 0 : (dir < 0 ? -1 : 1)) + 1) | ((linesofar & 0x3F) << 2)),
                          static_cast<uint8_t>(linesofar >> 6)}) {}

        std::array<short, 2> a_pos;
        std::array<unsigned char, 4> a_data;
    };

    GLenum polygonMode = GL_FILL;

    std::vector<LineLayoutVertex> vertexs;
    std::vector<uint16_t> indexs;

    std::vector<std::array<short, 2>> lineVertexs;
    std::vector<uint16_t> lineIndexs;

    float m_miter_limit = 2.f;
    float m_round_limit = 1.f;

    std::ptrdiff_t e1;
    std::ptrdiff_t e2;
    std::ptrdiff_t e3;

    GLuint program;
    GLuint vbo;
    GLuint vao;
    GLuint ibo;

    GLuint centerLineProgram;
    GLuint centerLineVbo;
    GLuint centerLineVao;
    GLuint centerLineIbo;

    GLint centerLineColorLoc;
    GLint centerLineMatrixLoc;

    GLint matrixLoc;
    GLint colorLoc;
    GLint widthLoc;

    float aspect;
};
