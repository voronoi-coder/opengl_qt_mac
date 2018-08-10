//
// Created by zhaojunhe on 2018/8/10.
//

#pragma once

#include <QOpenGLWidget>
#include "../vbm/vbm.hpp"

class ShadowMapGLWidget : public QOpenGLWidget {
public:
    ShadowMapGLWidget(QWidget *parent = 0);

    ~ShadowMapGLWidget();

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    GLuint render_light_prog;

    struct {
        GLint model_view_projection_matrix;
    } render_light_uniforms;

    GLuint render_scene_prog;

    struct {
        GLint model_matrix;
        GLint view_matrix;
        GLint projection_matrix;
        GLint shadow_matrix;
        GLint light_position;
        GLint material_ambient;
        GLint material_diffuse;
        GLint material_specular;
        GLint material_specular_power;
    } render_scene_uniforms;

    GLuint depth_fbo;
    GLuint  depth_texture;

    GLuint  ground_vao;
    GLuint  ground_vbo;

    VBObject object;

    float aspect;
    GLint current_width;
    GLint current_height;

private:
    void DrawScene(bool depth_only = false);

};
