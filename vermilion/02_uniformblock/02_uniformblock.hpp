//
// Created by zhaojunhe on 2018/7/18.
//

#pragma once

#include <QOpenGLWidget>

class QOpenGLShaderProgram;

class GLWidget : public QOpenGLWidget {
public:
    explicit GLWidget(QWidget *parent = 0);

    ~GLWidget();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

private:
    GLuint vShader;
    GLuint fShader;

};
