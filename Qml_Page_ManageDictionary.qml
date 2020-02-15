import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
	ColumnLayout {
		id: dict_manage_column
		width: parent.width * 0.7
		height: parent.height * 0.9
		anchors.centerIn: parent
		spacing: 2

		Rectangle {
			width: parent.width
			height: parent.height * 0.7
			border.color: "#C9CACA"
			border.width: 3
			radius: 10

			ListView {
				id: listView
				clip: true
				focus: true
				anchors.centerIn: parent
				width: parent.width - 20
				height: parent.height - 20
				currentIndex: -1

				MouseArea {
					anchors.fill: parent
					onClicked: {
						listView.currentIndex = listView.indexAt(mouseX, mouseY)
					}
				}

				highlight: Rectangle {
					border.width: 2
					border.color: "#C9CACA"
					radius: 3
				}

				model: ListModel {
				}

				delegate: Item {
					width: parent.width
					height: 20
					Text {
						width: parent.width
						text: model.question + " - " + model.answer
					}
				}

			}
		}

		RowLayout {
			Layout.fillHeight: true
			width: parent.width
			height: parent.height * 0.05

			Rectangle {
				Layout.fillWidth: true
				Layout.fillHeight: true
				border.color: "#C9CACA"
				border.width: 3
				radius: 10

				Qml_InputField {
					id: inputQuestion
					mytext: ""
				}
			}
			Rectangle {
				Layout.fillWidth: true
				Layout.fillHeight: true
				border.color: "#C9CACA"
				border.width: 3
				radius: 10

				Qml_InputField {
					id: inputAnswer
					mytext: ""
				}
			}
		}
		Qml_MyButton {
			mylabel: "Add"
			onClicked: {
				if (inputQuestion.mytext != "" && inputAnswer.mytext != "") {
					guiWorker.dictionaryAddItem(inputQuestion.mytext, inputAnswer.mytext)
					listView.model.append({question: inputQuestion.mytext, answer: inputAnswer.mytext})
					inputQuestion.mytext = ""
					inputAnswer.mytext = ""
				}
			}
		}
		RowLayout {
			Qml_MyButton {
				mylabel: "Edit"
				onClicked: {
					inputQuestion.mytext = listView.model.get(listView.currentIndex).question
					inputAnswer.mytext = listView.model.get(listView.currentIndex).answer
					guiWorker.dictionaryDeleteItem(listView.currentIndex)
					listView.model.remove(listView.currentIndex, 1)
					listView.currentIndex = -1
				}
			}
			Qml_MyButton {
				mylabel: "Delete"
				onClicked: {
					listView.model.remove(listView.currentIndex, 1)
					guiWorker.dictionaryDeleteItem(listView.currentIndex)
				}
			}
		}
		Qml_MyButton {
			mylabel: "Save to file"
			onClicked: {
			}
		}
		Qml_MyButton {
			mylabel: "Main Menu"
			onClicked: {
				stack_view.pop()
			}
		}
	}

	Connections {
		target: guiWorker
		onQmlAddItemToList: {
			listView.model.append({question: _question, answer: _answer})
		}
	}
}
