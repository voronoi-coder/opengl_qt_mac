#pragma once

#include <QOpenGLWidget>
#include "../../lib/vbm/vbm.hpp"

class InstancingWidget : public QOpenGLWidget {
Q_OBJECT
public:
    InstancingWidget(QWidget *parent = 0);

    ~InstancingWidget();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    GLuint program;
    GLuint weight_vbo;
    GLuint color_vbo;

    GLint modelMLoc;
    GLint projectionMLoc;

    float aspect;

    VBObject object;

    QTimer *timer;
};
