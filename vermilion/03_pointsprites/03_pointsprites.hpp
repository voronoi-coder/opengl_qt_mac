//
// Created by zhaojunhe on 2018/9/18.
//
#pragma once

#include <QOpenGLWidget>

class PointSpritesWidget : public QOpenGLWidget {
Q_OBJECT
public:
    PointSpritesWidget(QWidget *parent = 0);

    ~PointSpritesWidget();

protected:
    void initializeGL() override;

    void resizeGL(int width, int height) override;

    void paintGL() override;

private:
    GLuint sprite_texture;
    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLint model_matrix_loc;
    GLint projection_matrix_loc;

    float aspect;

    QTimer *timer;
};
