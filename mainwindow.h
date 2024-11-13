#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextEdit>
#include <QFontDialog>
#include <QComboBox>
#include <QVBoxLayout>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();
    void changeFont();
    void changeTheme(int index);

private:
    Ui::MainWindow *ui;
    QTextEdit *textEdit;
    QPushButton *openButton;
    QPushButton *fontButton;
    QComboBox *themeComboBox;

    void setupUi();
};

#endif // MAINWINDOW_H
