//
// Created by zhaojunhe on 2018/7/9.
//

#include <QToolButton>

class Button : public QToolButton
{
Q_OBJECT

public:
    explicit Button(const QString &text, QWidget *parent = 0);

    QSize sizeHint() const override;
};
