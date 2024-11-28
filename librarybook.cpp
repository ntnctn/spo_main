#include "librarybook.h"


// класс для взаимодействия с джисонами



librarybook::librarybook() {}

bool loadFB2(const QString& filePath, QString& error) {
    QFile f(filePath);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        error = "Не удалось открыть файл";
        return false;
    }

    QXmlStreamReader sr(&f);
    QString title, authorLastName, authorFirstName;

    while (!sr.atEnd()) {
        if (sr.hasError()) {
            error = sr.errorString();
            return false;
        }

        if (sr.isStartElement()) {
            if (sr.name().toString() == "book-title") {
                sr.readNext(); //поиск названия книги
                if (sr.text().toString().isEmpty()){
                    error = "Название книги не найдено";
                    return false;
                }
                title = sr.text().toString().trimmed();
            } else if (sr.name().toString() == "last-name") {
                sr.readNext(); //поиск фамилии автора
                if (sr.text().toString().isEmpty()){
                    error = "Фамилия автора не найдена";
                    return false;
                }
                authorLastName = sr.text().toString().trimmed();
            } else if (sr.name().toString() == "first-name") {
                sr.readNext(); //поиск имени автора
                if (sr.text().toString().isEmpty()){
                    error = "Имя автора не найдено";
                    return false;
                }
                authorFirstName = sr.text().toString().trimmed();
            }
        }
        sr.readNext();
    }

    if (title.isEmpty() || authorLastName.isEmpty()) {
        error = "Не удалось извлечь название или автора";
        return false;
    }

    bookTitle = title;
    bookAuthor = authorLastName + (authorFirstName.isEmpty() ? "" : ", " + authorFirstName);
    return true;
}

void saveToJson(const QString& jsonFilePath) {
    QFile jsonFile(jsonFilePath);
    if (jsonFile.exists()){
        loadBooksFromJson(jsonFilePath); //load existing data
    }

    QJsonObject bookObject;

    bookObject["title"] = bookTitle;
    bookObject["author"] = bookAuthor;

    QJsonArray bookArray;
    for (const QJsonObject& obj : books){
        bookArray.append(obj);
    }
    bookArray.append(bookObject);

    QJsonObject mainObject;
    mainObject["books"] = bookArray;

    QJsonDocument jsonDoc(mainObject);
    if (!jsonFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось открыть файл для записи");
        return;
    }
    jsonFile.write(jsonDoc.toJson(QJsonDocument::Compact));
    jsonFile.close();
}

void loadBooksFromJson(const QString& jsonFilePath){
    books.clear();
    QFile loadFile(jsonFilePath);
    if (!loadFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //Handle error - file might not exist yet, that's ok
        return;
    }
    QByteArray jsonData = loadFile.readAll();
    loadFile.close();
    QJsonDocument loadDoc = QJsonDocument::fromJson(jsonData);

    if (!loadDoc.isNull() && loadDoc.isObject()){
        if (loadDoc.object().contains("books")){
            QJsonArray arr = loadDoc.object()["books"].toArray();
            for (const QJsonValue & value : arr){
                books.append(value.toObject());
            }
        }
    }

}

QJsonArray getBooks() const {
    return QJsonArray::fromVariantList(books); // Convert QList to QJsonArray
}








// питон код реги
//     reg_genre = '<genre>(.+)</genre>'
//     reg_title = '<book-title>(.+)</book-title>'
//     reg_last_name = '<last-name>(.+)</last-name>'
//     reg_first_name = 'first-name>(.+)</first-name>'


//строка сравнивается с регуляркой если содержит - добавляем в переменную











// QFile f(file);

// if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
// {
//     qDebug() << "файл не открыт";
//     return false;
// }


// QXmlStreamReader sr(&f);


// while( !sr.atEnd() )
// {

//     if(sr.name().toString() == "text-author" ) // автор текстта
//     {
//         book->append( "<p align=\"justify\" style=\"margin-left:45px;\">" );
//         break;
//     }

// }
