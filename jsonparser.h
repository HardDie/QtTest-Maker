#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QList>
#include <QString>

#include "global.h"

/**
 * Имеет две основых функции:
 * 1) Из json файла распарсить данные и получить список данных
 * 2) Из списка данных сформировать готовый для записи json файл
 */
class JsonParser
{
public:
    JsonParser();
    static QList<struct Question> ParseJsonToQuestionsList(QByteArray rawFile);
    static QByteArray FormatJsonFileFromQuestionList(const QList<struct Question> &list);
};

#endif // JSONPARSER_H
