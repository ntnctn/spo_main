#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Text Files (*.txt);;All Files (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            textEdit->setPlainText(in.readAll());
            file.close();
        }
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
