#ifndef LIBRARYBOOK_H
#define LIBRARYBOOK_H
#include <QString>
#include <QXmlStreamReader>

class librarybook
{
public:
    librarybook();
   // void addBook(QString file, QString *book, QStringList *content);

private:
    QString bookTitle;
    QString bookAuthor;
    QList<QJsonObject> books;

};

#endif // LIBRARYBOOK_H
