#ifndef _TEST_MAKER_H
#define _TEST_MAKER_H

#include <QFile>
#include <time.h>
#include <string.h>
#include <QVector>
#include <QDebug>
#include <QMessageBox>

const int SIZE = 1024;
namespace uns {

	struct usData_t {	// Структура одного объекта
		char *	string;
		char	flag;
	};

	class ucTestMaker {
	private:
		QVector< usData_t >	data;		// Вектор данных
		int					counter;	// Количество выведеных строк
		int					index;		// Номер текущей строки
		QFile				file;		// Подключаемый файл

	public:
								ucTestMaker();
		void					ClearTest();
		int						OpenFile( const char filename[] );
		void					ReadFile();
		void					AddQuestion();
		void					Init();
		int						NewWord();
		int						MixNewWord();
		const	char	*		GetQuestion();
		const	char	*		GetAnswer();
		int						GetCounter() { return counter; }
		int						GetLength() { return data.size(); }
		char					GetFlag() { return data[index].flag; }
								~ucTestMaker();
	};

}

#endif // !_TEST_MAKER_H
