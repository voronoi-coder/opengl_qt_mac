//
// Created by zhaojunhe on 2018/6/22.
//
#pragma once

#include <QWidget>

class QSlider;
class QPushButton;

class GLWidget;
class MainWindow;

class Window : public QWidget
{
Q_OBJECT

public:
    Window(MainWindow *mw);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void dockUndock();

private:
    QSlider *createSlider();

    GLWidget *glWidget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
    QPushButton *dockBtn;
    MainWindow *mainWindow;
};

