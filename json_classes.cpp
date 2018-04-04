#include "json_classes.h"

namespace uns {
	/* -------------------- Object -------------------- */
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
		json_obj.insert("ans", QJsonValue::fromVariant(_ans));
		json_obj.insert("que", QJsonValue::fromVariant(_que));
		return json_obj;
	}

	/* -------------------- Dictionary -------------------- */
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
