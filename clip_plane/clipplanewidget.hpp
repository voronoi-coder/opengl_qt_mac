//
// Created by zhaojunhe on 2018/9/4.
//
#pragma once

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <array>

class ClipPlaneWidget : public QOpenGLWidget {
public:
    ClipPlaneWidget(QWidget *parent = 0);

    ~ClipPlaneWidget();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    void loadObject();

    std::vector<float> objectVectexs;
    std::vector<float> objectNormals;

    GLint program;
    GLuint vbo;
    GLuint normal_vbo;
    GLuint vao;
    GLint mvpmatrixLoc;
    GLint mmatrixLoc;
    GLint lightposLoc;
    GLint cameraLoc;
    GLint clipplaneLoc;

    QMatrix4x4 modelMatrx;
    QMatrix4x4 viewMatrx;
    QMatrix4x4 projMatrx;

    std::array<float, 3> cameraPos;
    std::array<float, 3> lightPos;
    std::array<float, 4> clip_plane;
};

