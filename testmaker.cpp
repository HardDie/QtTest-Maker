#include "testmaker.h"

namespace uns {
	/*
	* Name: ucTestMaker
	* Description: Конструктор
	*/
	ucTestMaker::ucTestMaker() {
		_counter = 0;
		_index = -1;
		_fileIsOpen = false;
		_filename = "";
	}

	/*
	* Name: ClearTest
	* Description: Очищает тест
	*/
	void ucTestMaker::ClearTest() {
		_data.Clear();
		_counter = 0;
		_index = -1;
	}

	/*
	* Name: CheckFile
	* Description: Проверяет доступен ли файл
	*/
	int ucTestMaker::CheckFile( QString filename ) {
		file.setFileName( filename );
		if ( !file.open( QIODevice::ReadOnly ) ) {
			return -1;
		}
		file.close();
		return 0;
	}

	/*
	* Name: ReadFile
	* Description: Считывает все строки из файла, в случае если из файла считалась хотя бы одно строка, возвращается true
	*/
	bool ucTestMaker::ReadFile( QString filename ) {
		file.setFileName( filename );
		file.open( QIODevice::ReadOnly );
		QString data = file.readAll();
		file.close();
		if ( !_data.Init( data.toUtf8() ) ) {
			_filename = "";
			_fileIsOpen = false;
		}
		_filename = filename;
		_fileIsOpen = true;
		return _fileIsOpen;
	}

	/*
	* Name: SaveFile
	* Description: Все тесты сохраняются в файл, в случае удачной записи вернется true
	*/
	bool ucTestMaker::SaveFile() {
		if ( _fileIsOpen && _filename != "" ) {
			file.setFileName( _filename );
			if ( !file.open( QIODevice::WriteOnly ) ) {
				_filename = "";
				return false;
			}
			file.write( _data.ToByteArray() );
			file.close();
		} else {
			return false;
		}
		return true;
	}

	/*
	* Name: Init
	* Description: Сбрасывает все флаги слов
	*/
	void ucTestMaker::Init() {
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
		while ( _data.GetFlag( _index = rand() % _data.GetLength() ) == 3 || _data.GetFlag( _index ) == 4 );
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

	ucTestMaker::~ucTestMaker() {
		_data.Clear();
	}

	/*
	* Name: ucQuestion
	* Description: Конструктор для обьекта вопроса, на вход подается
	* json обеьект
	*/
	ucQuestion::ucQuestion(QJsonObject json_obj) {
		_que = json_obj.value("que").toString();
		_ans = json_obj.value("ans").toString();
	}

	/*
	* Name: ucQuestion
	* Description: Конструктор для обьекта вопроса, на вход подается две строки
	* вопрос и ответ
	*/
	ucQuestion::ucQuestion(QString que, QString ans) {
		_que = que;
		_ans = ans;
	}

	/*
	* Name: ToJsonObject
	* Description: Собирает обект в json обьект и возвращает
	*/
	QJsonObject ucQuestion::ToJsonObject() {
		QJsonObject json_obj;
		json_obj.insert("que", QJsonValue::fromVariant(_que));
		json_obj.insert("ans", QJsonValue::fromVariant(_ans));
		return json_obj;
	}

	/*
	* Name: Init
	* Description: Парсит считанный json файл в обекты вопросов,
	* на вход подается бинарный считаный файл
	*/
	bool ucDictionary::Init(QByteArray raw_file) {
		QJsonDocument json_doc = QJsonDocument::fromJson(raw_file);
		if (json_doc.isNull()) {
			return false;
		}
		QJsonObject json_file = json_doc.object();
		QJsonArray json_dict = json_file.value("dictionary").toArray();
		foreach (QJsonValue json_val, json_dict) {
			QJsonObject json_el = json_val.toObject();
			_dict.append(ucQuestion(json_el));
		}
		return true;
	}

	/*
	* Name: Clear
	* Description: Очищает все обьекты
	*/
	void ucDictionary::Clear() {
		_dict.clear();
	}

	/*
	* Name: AddElement
	* Description: Позволяет в базу добавить обьект,
	* на вход подается две строки вопрос и ответ
	*/
	void ucDictionary::AddElement(QString que, QString ans) {
		_dict.append(ucQuestion(que, ans));
	}

	/*
	* Name: CleanFlags
	* Description: Проходится по массиву обьектов и выставляет
	* флаги в значение 0
	*/
	void ucDictionary::CleanFlags() {
		for (int j = 0; j < _dict.size(); j++) {
			_dict[j].SetFlag(0);
		}
	}

	/*
	* Name: ToJsonObject
	* Description: Преобразует все обьекты в один json обьект
	*/
	QJsonObject ucDictionary::ToJsonObject() {
		QJsonObject json_obj;
		QJsonArray json_arr;
		foreach (ucQuestion que_str, _dict) {
			json_arr.append(que_str.ToJsonObject());
		}
		json_obj.insert("dictionary", json_arr);
		return json_obj;
	}

	/*
	* Name: ToByteArray
	* Description: Дерево содержащееся в json обьекте преобразуется
	* в бинарный файл, для последующей записи в файл
	*/
	QByteArray ucDictionary::ToByteArray() {
		return QJsonDocument(ToJsonObject()).toJson();
	}
}
