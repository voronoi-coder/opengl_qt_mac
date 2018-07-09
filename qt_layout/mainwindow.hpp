//
// Created by zhaojunhe on 2018/7/9.
//
#include <QMainWindow>

class GLWidget;

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow();

    ~MainWindow();

private:
    GLWidget *widgets[4];
};
