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
		ucQuestion( QJsonObject json_obj );     // Создание обьекта при помощи данных из файлы
		ucQuestion( QString que, QString ans ); // Создание обьекта при помощи данных из формы
		QJsonObject ToJsonObject();             // Формат экспорта в файл

		QString  GetQuestion() const { return _que; }
		QString  GetAnswer()   const { return _ans; }
		u_int8_t GetFlag()     const { return _flag; }

		void     SetFlag( u_int8_t flag ) { _flag = flag; }
	private:
		QString _que;
		QString _ans;
		u_int8_t _flag;
	};

	class ucDictionary { // Класс хранящий словарь
	public:
		bool Init( QByteArray raw_file ); // Инициализация словаря из файла
		void Clear(); // Полная очистка словаря
		void AddElement( QString que, QString ans ); // Добавление обьекта из формы
		void CleanFlags(); // Очищает флаги на всех обьектах
		QJsonObject ToJsonObject(); // Фомирует данные для экспорта в файл
		QByteArray ToByteArray(); // Преобразует из Json обьекта в бинарный файл

		int      GetLength()              const { return _dict.size(); }
		QString  GetQuestion( int index ) const { return _dict.at( index ).GetQuestion(); }
		QString  GetAnswer( int index )   const { return _dict.at( index ).GetAnswer(); }
		u_int8_t GetFlag( int index )     const { return _dict.at( index ).GetFlag(); }

		void     SetFlag( int index, u_int8_t flag ) { _dict[index].SetFlag( flag ); }

		void     DeleteElement( int index ) { _dict.removeAt( index ); }
	private:
		QList<ucQuestion> _dict;
	};

}

#endif
