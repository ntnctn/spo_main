import QtQuick 2.15
import QtQuick.Controls 2.15
import QtWebEngine 1.1

ApplicationWindow {
    visible: true
    width: 1024  // Увеличиваем ширину окна
    height: 768  // Увеличиваем высоту окна
    title: "Читалка"

    Column {
        anchors.fill: parent
        spacing: 10

        Button {
            text: "Открыть файл"
            onClicked: {
                fileDialog.open()
            }
        }

        // Элемент для отображения PDF
        WebEngineView {
            id: webView
            anchors.fill: parent
            visible: false  // Скрываем его по умолчанию
        }

        // Текстовое поле для отображения содержимого текстовых файлов
        TextEdit {
            id: textEdit
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            readOnly: true
            visible: false  // Скрываем его по умолчанию
        }

        Dialog {
            id: fileDialog
            title: "Выберите файл"
            nameFilters: ["Text files (*.txt)", "PDF files (*.pdf)", "All files (*)"]
            onAccepted: {
                var file = fileDialog.fileUrl
                loadFile(file)
            }
        }
    }

    function loadFile(fileUrl) {
        var extension = fileUrl.split('.').pop().toLowerCase()

        if (extension === "txt") {
            loadTextFile(fileUrl)
        } else if (extension === "pdf") {
            loadPdfFile(fileUrl)
        } else {
            textEdit.text = "Неподдерживаемый формат файла."
        }
    }

    function loadTextFile(fileUrl) {
        var xhr = new XMLHttpRequest()
        xhr.open("GET", fileUrl, true)
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status === 200) {
                    textEdit.text = xhr.responseText
                    textEdit.visible = true
                    webView.visible = false
                } else {
                    textEdit.text = "Ошибка при загрузке файла."
                }
            }
        }
        xhr.send()
    }

    function loadPdfFile(fileUrl) {
        webView.url = fileUrl  // Загружаем PDF-файл в WebEngineView
        webView.visible = true
        textEdit.visible = false  // Скрываем текстовое поле
    }
}
