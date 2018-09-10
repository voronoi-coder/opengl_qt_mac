//
// Created by zhaojunhe on 2018/6/21.
//
#pragma once

#include <QWidget>
#include "helper.hpp"

class Window:public QWidget{
    Q_OBJECT
public:
    Window();

private:
    Helper helper;
};
