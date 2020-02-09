#include <QDebug>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

#include "jsonparser.h"

JsonParser::JsonParser() {}

QList< struct Question >
JsonParser::ParseJsonToQuestionsList( QByteArray rawFile ) {
	QList< Question > list;

	if ( rawFile.length() == 0 ) {
		qDebug() << "ERROR: File is empty!";
		return QList< Question >();
	}

	QJsonDocument jsonDocument = QJsonDocument::fromJson( rawFile );
	if ( jsonDocument.isNull() ) {
		qDebug() << "ERROR: Can't parse file!";
		return QList< Question >();
	}

	QJsonObject jsonFile = jsonDocument.object();
	QJsonArray  jsonArray = jsonFile.value( "dictionary" ).toArray();
	foreach ( QJsonValue json_val, jsonArray ) {
		QJsonObject jsonElement = json_val.toObject();
		Question    question;
		question._answer = jsonElement.value( "ans" ).toString();
		question._question = jsonElement.value( "que" ).toString();
		list.append( question );
	}

	return list;
}

QByteArray JsonParser::FormatJsonFileFromQuestionList(
    const QList< struct Question > &list ) {
	if ( list.length() == 0 ) {
		qDebug() << "ERROR: Empty list!";
		return QByteArray();
	}

	QJsonObject jsonRoot;
	QJsonArray  jsonArray;
	foreach ( struct Question question, list ) {
		QJsonObject jsonVal;
		jsonVal.insert( "ans",
		                QJsonValue::fromVariant( question._answer ) );
		jsonVal.insert( "que",
		                QJsonValue::fromVariant( question._question ) );
		jsonArray.append( jsonVal );
	}
	jsonRoot.insert( "dictionary", jsonArray );
	return QJsonDocument( jsonRoot ).toJson();
}
