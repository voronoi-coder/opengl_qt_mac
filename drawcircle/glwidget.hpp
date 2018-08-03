//
// Created by zhaojunhe on 2018/7/31.
//
#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

class QOpenGLShaderProgram;


class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions{
public:
    explicit GLWidget(QWidget *parent = 0);

    ~GLWidget();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    QOpenGLShaderProgram *program;
    QOpenGLBuffer vbo;
    QOpenGLBuffer *ibo;

    float aspect;

    int m_matrixLoc;
    int u_scale_with_map;
    int u_pitch_with_map;
    int u_extrude_scale;
    int u_camera_to_center_distance;
    int u_color;
    int u_radius;
    int u_blur;
    int u_opacity;
    int u_stroke_color;
    int u_stroke_width;
    int u_stroke_opacity;
};
