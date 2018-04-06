#include "testmaker.h"

namespace uns {
	ucTestMaker::ucTestMaker() {
		_counter = 0;
		_index = -1;
		_fileIsOpen = false;
		_filename = "";
	}

	ucTestMaker::~ucTestMaker() {
		_data.Clear();
	}

	/*
	* Name: CheckFile
	* Description: Проверяет доступен ли файл
	*/
	int ucTestMaker::CheckFile( QString filename ) {
		_file.setFileName( filename );
		if ( !_file.open( QIODevice::ReadOnly ) ) {
			return -1;
		}
		_file.close();
		return 0;
	}

	/*
	* Name: ReadFile
	* Description: Считывает все строки из файла, в случае если из файла
	* считалась хотя бы одно строка, возвращается true
	*/
	bool ucTestMaker::ReadFile( QString filename ) {
		_file.setFileName( filename );
		_file.open( QIODevice::ReadOnly );
		QString data = _file.readAll();
		_file.close();
		if ( !_data.Init( data.toUtf8() ) ) {
			_filename = "";
			_fileIsOpen = false;
		}
		_filename = filename;
		_fileIsOpen = true;
		return _fileIsOpen;
	}

	/*
	* Name: InitEmptyFile
	* Description: Инициализирует пустой файл после его создания и записывает
	* минимальные данные
	*/
	void ucTestMaker::InitEmptyFile( QString filename ) {
		_fileIsOpen = true;
		_filename = filename;
		SaveFile();
		ClearTest();
	}

	/*
	* Name: SaveFile
	* Description: Все тесты сохраняются в файл, в случае удачной записи вернется
	* true
	*/
	bool ucTestMaker::SaveFile() {
		if ( _fileIsOpen && _filename != "" ) {
			_file.setFileName( _filename );
			if ( !_file.open( QIODevice::WriteOnly ) ) {
				_filename = "";
				return false;
			}
			_file.write( _data.ToByteArray() );
			_file.close();
		} else {
			return false;
		}
		return true;
	}

	/*
	* Name: ClearTest
	* Description: Очищает тест
	*/
	void ucTestMaker::ClearTest() {
		_data.Clear();
		_counter = 0;
		_index = -1;
		_fileIsOpen = false;
		_filename = "";
	}

	/*
	* Name: ClearFlags
	* Description: Сбрасывает все флаги слов
	*/
	void ucTestMaker::ClearFlags() {
		srand( ( unsigned int ) time( NULL ) );
		_data.CleanFlags();
		_counter = 0;
	}

	/*
	* Name: NewWord
	* Description: Выбирает новое слово для вопроса
	*/
	int ucTestMaker::NewWord() {
		if ( _counter == _data.GetLength() ) {
			return 1;
		}
		while ( _data.GetFlag( _index = rand() % _data.GetLength() ) == 1 );
		_data.SetFlag( _index, 1 );
		_counter++;
		return 0;
	}

	/*
	* Name: MixNewWord
	* Description: Выбирает новое слово для вопроса с учетом двух вопросов
	*/
	int ucTestMaker::MixNewWord() {
		if ( _counter == ( 2 * _data.GetLength() ) ) {
			return 1;
		}
		while ( _data.GetFlag( _index = rand() % _data.GetLength() ) == 3 ||
		        _data.GetFlag( _index ) == 4 );
		if ( _data.GetFlag( _index ) == 0 ) {
			_data.SetFlag( _index, rand() % 2 + 1 );
		} else if ( _data.GetFlag( _index ) == 1 ) {
			_data.SetFlag( _index, 3 );
		} else if ( _data.GetFlag( _index ) == 2 ) {
			_data.SetFlag( _index, 4 );
		}
		_counter++;
		return 0;
	}

	/*
	* Name: GetQuestion
	* Description: Если на вход подан индекс, то вернется вопрос под этим номером
	* иначе вернется вопрос под выбранным внутри индексом
	*/
	QString ucTestMaker::GetQuestion( int index ) const {
		if ( index >= 0 ) {
			return _data.GetQuestion( index );
		} else {
			return _data.GetQuestion( _index );
		}
	}

	/*
	* Name: GetAnswer
	* Description: Если на вход подан индекс, то вернется ответ под этим номером
	* иначе вернется ответ под выбранным внутри индексом
	*/
	QString ucTestMaker::GetAnswer( int index ) const {
		if ( index >= 0 ) {
			return _data.GetAnswer( index );
		} else {
			return _data.GetAnswer( _index );
		}
	}

}
