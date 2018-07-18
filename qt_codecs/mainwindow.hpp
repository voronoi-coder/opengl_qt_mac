//
// Created by zhaojunhe on 2018/7/13.
//
#include <QList>
#include <QMainWindow>

class QAction;
class QTextCodec;
class QPlainTextEdit;

class PreviewForm;

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow();

private slots:
    void open();
    void save();
    void about();
    void aboutToShowSaveAsMenu();

private:
    void findCodecs();
    void createMenus();

    QList<QAction *> saveAsActs;
    QPlainTextEdit *textEdit;
    PreviewForm *previewForm;
    QList<QTextCodec *> codecs;
};
