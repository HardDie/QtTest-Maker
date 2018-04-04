#ifndef _TEST_MAKER_H
#define _TEST_MAKER_H

#include <time.h>
#include <QLineEdit> // Для ::fromVariant
#include <QFile>
#include <QList>
#include "json_classes.h"

namespace uns {

	class ucTestMaker {
	private:
		ucDictionary            _data;       // Класс хранящий все имеющиеся слова
		int                     _counter;    // Количество выведеных строк
		int                     _index;      // Номер текущей строки
		QFile                   file;        // Подключаемый файл
        bool                    _fileIsOpen; // Флаг открытого файла
        QString                 _filename;   // Будем хранить имя открытого файла, чтобы можно было сохранить изменения

	public:
		                        ucTestMaker();
		void                    ClearTest();
		int                     CheckFile( QString filename );
		bool                    ReadFile( QString filename );
		bool                    SaveFile();
		void                    Init();
		int                     NewWord();
		int                     MixNewWord();
		void                    AddNewQue( QString que, QString ans ) { _data.AddElement( que, ans ); }

		int                     GetCounter()             const { return _counter; }
		int                     GetLength()              const { return _data.GetLength(); }
		char                    GetFlag()                const { return _data.GetFlag( _index ); }
		bool                    FileIsOpen()             const { return _fileIsOpen; }
		QString                 GetQuestion( int index = -1 ) const;
		QString                 GetAnswer( int index = -1 )   const;

		void                    DeleteQue( int index ) { _data.DeleteElement( index ); }
		void                    ForceSetFile( QString filename ) { _filename = filename; _fileIsOpen = true; };
		                        ~ucTestMaker();
	};

}

#endif // !_TEST_MAKER_H
