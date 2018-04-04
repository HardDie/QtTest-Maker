#ifndef _JSON_CLASSES_H
#define _JSON_CLASSES_H

#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QByteArray>
#include <QList>

namespace uns {

	class ucQuestion { // Класс одной пары вопрос-ответ
	public:
		QString _que;
		QString _ans;
		u_int8_t _flag;

		ucQuestion( QJsonObject json_obj );     // Создание обьекта при помощи данных из файлы
		ucQuestion( QString que, QString ans ); // Создание обьекта при помощи данных из формы
		QJsonObject ToJsonObject();             // Формат экспорта в файл
	};

	class ucDictionary { // Класс хранящий словарь
	public:
		bool Init( QByteArray raw_file ); // Инициализация словаря из файла
		void CleanFlags(); // Очищает флаги на всех обьектах
		QJsonObject ToJsonObject(); // Фомирует данные для экспорта в файл
		QByteArray ToByteArray(); // Преобразует из Json обьекта в бинарный файл

		int      GetLength()              const { return _dict.size(); }
		QString  GetQuestion( int index ) const { return _dict.at( index )._que; }
		QString  GetAnswer( int index )   const { return _dict.at( index )._ans; }
		u_int8_t GetFlag( int index )     const { return _dict.at( index )._flag; }

		void     SetFlag( int index, u_int8_t flag ) { _dict[index]._flag = flag; }

		void     AddElement( QString que, QString ans ) { _dict.append( ucQuestion( que, ans ) ); }
		void     DeleteElement( int index ) { _dict.removeAt( index ); }
		void     Clear() { _dict.clear(); }
	private:
		QList<ucQuestion> _dict;
	};

}

#endif
