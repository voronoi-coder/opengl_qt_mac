//
// Created by zhaojunhe on 2018/7/13.
//

#include <QtWidgets>

#include "mainwindow.hpp"
#include "previewform.hpp"

MainWindow::MainWindow()
{
    textEdit = new QPlainTextEdit;
    textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
    setCentralWidget(textEdit);

    findCodecs();

    previewForm = new PreviewForm(this);
    previewForm->setCodecList(codecs);

    createMenus();

    setWindowTitle(tr("Codecs"));

    const QRect screenGeometry = QApplication::desktop()->screenGeometry(this);
    resize(screenGeometry.width() / 2, screenGeometry.height() * 2 / 3);
}

void MainWindow::open()
{
    const QString fileName = QFileDialog::getOpenFileName(this);
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("Codecs"),
                             tr("Cannot read file %1:\n%2")
                                     .arg(QDir::toNativeSeparators(fileName),
                                          file.errorString()));
        return;
    }

    const QByteArray data = file.readAll();

    previewForm->setWindowTitle(tr("Choose Encoding for %1").arg(QFileInfo(fileName).fileName()));
    previewForm->setEncodedData(data);
    if (previewForm->exec())
        textEdit->setPlainText(previewForm->decodedString());
}

void MainWindow::save()
{
    const QAction *action = qobject_cast<const QAction *>(sender());
    const QByteArray codecName = action->data().toByteArray();
    const QString title = tr("Save As (%1)").arg(QLatin1String(codecName));

    QString fileName = QFileDialog::getSaveFileName(this, title);
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Codecs"),
                             tr("Cannot write file %1:\n%2")
                                     .arg(QDir::toNativeSeparators(fileName),
                                          file.errorString()));
        return;
    }

    QTextStream out(&file);
    out.setCodec(codecName.constData());
    out << textEdit->toPlainText();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Codecs"),
                       tr("The <b>Codecs</b> example demonstrates how to read and write "
                                  "files using various encodings."));
}

void MainWindow::aboutToShowSaveAsMenu()
{
    QString currentText = textEdit->toPlainText();

            foreach (QAction *action, saveAsActs) {
            QByteArray codecName = action->data().toByteArray();
            QTextCodec *codec = QTextCodec::codecForName(codecName);
            action->setVisible(codec && codec->canEncode(currentText));
        }
}

void MainWindow::findCodecs()
{
    QMap<QString, QTextCodec *> codecMap;
    QRegularExpression iso8859RegExp("^ISO[- ]8859-([0-9]+).*$");
    QRegularExpressionMatch match;

            foreach (int mib, QTextCodec::availableMibs()) {
            QTextCodec *codec = QTextCodec::codecForMib(mib);

            QString sortKey = codec->name().toUpper();
            int rank;

            if (sortKey.startsWith(QLatin1String("UTF-8"))) {
                rank = 1;
            } else if (sortKey.startsWith(QLatin1String("UTF-16"))) {
                rank = 2;
            } else if ((match = iso8859RegExp.match(sortKey)).hasMatch()) {
                if (match.captured(1).size() == 1)
                    rank = 3;
                else
                    rank = 4;
            } else {
                rank = 5;
            }
            sortKey.prepend(QLatin1Char('0' + rank));

            codecMap.insert(sortKey, codec);
        }
    codecs = codecMap.values();
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *openAct =
            fileMenu->addAction(tr("&Open..."), this, &MainWindow::open);
    openAct->setShortcuts(QKeySequence::Open);

    QMenu *saveAsMenu = fileMenu->addMenu(tr("&Save As"));
    connect(saveAsMenu, &QMenu::aboutToShow,
            this, &MainWindow::aboutToShowSaveAsMenu);
            foreach (const QTextCodec *codec, codecs) {
            const QByteArray name = codec->name();
            QAction *action = saveAsMenu->addAction(tr("%1...").arg(QLatin1String(name)));
            action->setData(QVariant(name));
            connect(action, &QAction::triggered, this, &MainWindow::save);
            saveAsActs.append(action);
        }

    fileMenu->addSeparator();
    QAction *exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);

    menuBar()->addSeparator();

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
}