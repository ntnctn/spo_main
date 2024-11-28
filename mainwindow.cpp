#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "openfb2.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    setupUi();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupUi() {
    this->setWindowTitle("Читалка");

    textEdit = new QTextEdit(this);
    openButton = new QPushButton("Открыть файл", this);
    fontButton = new QPushButton("Изменить шрифт", this);

    themeComboBox = new QComboBox(this);
    themeComboBox->addItem("Светлая");
    themeComboBox->addItem("Темная");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(openButton);
    layout->addWidget(fontButton);
    layout->addWidget(themeComboBox);
    layout->addWidget(textEdit);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(openButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(fontButton, &QPushButton::clicked, this, &MainWindow::changeFont);
    connect(themeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::changeTheme);
}

void MainWindow::openFile() {
    QString name = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Text Files (*.txt);;All Files (*)");
    if (!name.isEmpty()) {

        QString text;
        QStringList content;

        if(name.endsWith(".fb2"))
        {
            openfb2 otf;
            otf.openFB2File(name, &text, &content);

            textEdit->setText(text);
           // ui->textBrowser->verticalScrollBar()->setValue(0);

        }
        else{

            QFile file(name);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                textEdit->setPlainText(in.readAll());
                file.close();
            }

        }



    }
    else{
        //файл пустой -> ошибка


    }
}

void MainWindow::changeFont() {
    bool ok;
    QFont font = QFontDialog::getFont(&ok, textEdit->font(), this);
    if (ok) {
        textEdit->setFont(font);
    }
}

void MainWindow::changeTheme(int index) {
    if (index == 0) { // Светлая тема
        qApp->setStyle("Fusion");
        qApp->setPalette(QPalette(QPalette::Light));
    } else { // Темная тема
        qApp->setStyle("Fusion");
        qApp->setPalette(QPalette(QPalette::Dark));
    }
}
