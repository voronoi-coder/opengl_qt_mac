//
// Created by zhaojunhe on 2018/7/13.
//

#include <QDialog>

class QComboBox;
class QDialogButtonBox;
class QLabel;
class QPlainTextEdit;
class QPushButton;
class QTabWidget;
class QTextCodec;

class PreviewForm : public QDialog {
Q_OBJECT
public:
    explicit PreviewForm(QWidget *parent = nullptr);

    void setCodecList(const QList<QTextCodec *> &list);
    void setEncodedData(const QByteArray &data);
    QString decodedString() const { return decodedStr; }

private slots:
    void updateTextEdit();

private:
    void reset();

    QByteArray encodedData;
    QString decodedStr;

    QPushButton *okButton;
    QTabWidget *tabWidget;
    QComboBox *encodingComboBox;
    QPlainTextEdit *textEdit;
    QPlainTextEdit *hexDumpEdit;
    QLabel *statusLabel;
};
