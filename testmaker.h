#ifndef _TEST_MAKER_H
#define _TEST_MAKER_H

#include <time.h>
#include <QLineEdit> // Для ::fromVariant
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

const int SIZE = 1024;
namespace uns {

	class ucQuestion { // Класс одной пары вопрос-ответ
	public:
		ucQuestion(QJsonObject json_obj);
		ucQuestion(QString que, QString ans);
		QJsonObject ToJsonObject();

		QString GetQuestion() const { return _que; }
		QString GetAnswer() const { return _ans; }
		u_int8_t GetFlag() const { return _flag; }
		void SetFlag(u_int8_t flag) { _flag = flag; }
	private:
		QString _que;
		QString _ans;
		u_int8_t _flag;
	};

	class ucDictionary { // Класс хранящий словарь
	public:
		void Init(QByteArray raw_file);
		void Clear();
		void AddElement(QString que, QString ans);
		void CleanFlags();
		QJsonObject ToJsonObject();
		QByteArray ToByteArray();

		int GetLength() const { return _dict.size(); }
		QString GetQuestion(int index) const { return _dict.at(index).GetQuestion(); }
		QString GetAnswer(int index) const { return _dict.at(index).GetAnswer(); }
		u_int8_t GetFlag(int index) const { return _dict.at(index).GetFlag(); }
		void SetFlag(int index, u_int8_t flag) { _dict[index].SetFlag(flag); }
	private:
		QList<ucQuestion> _dict;
	};

	class ucTestMaker {
	private:
		ucDictionary            _data;       // Класс хранящий все имеющиеся слова
		int                     _counter;    // Количество выведеных строк
		int                     index;       // Номер текущей строки
		QFile                   file;        // Подключаемый файл
        bool                    _fileIsOpen; // Флаг открытого файла
        QString                 _filename;   // Будем хранить имя открытого файла, чтобы можно было сохранить изменения

	public:
		                        ucTestMaker();
		void                    ClearTest();
		int                     OpenFile( const char filename[] );
		bool                    ReadFile();
		void                    Init();
		int                     NewWord();
		int                     MixNewWord();
		QString                 GetQuestion() const { return _data.GetQuestion(index); };
		QString                 GetAnswer() const { return _data.GetAnswer(index); };
		int                     GetCounter() { return _counter; }
		int                     GetLength() const { return _data.GetLength(); }
		char                    GetFlag() { return _data.GetFlag(index); }
		bool                    FileIsOpen() { return _fileIsOpen; }
		                        ~ucTestMaker();
	};

}

#endif // !_TEST_MAKER_H
