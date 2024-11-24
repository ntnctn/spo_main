#ifndef OPENFB2_H
#define OPENFB2_H
#include <QString>
#include <QXmlStreamReader>

class openfb2
{
public:
    openfb2(QObject *parent = 0);
    bool openFB2File(QString file, QString *book, QStringList *content);
};

#endif // OPENFB2_H
