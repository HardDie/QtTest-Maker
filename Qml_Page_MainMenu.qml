import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3

Item {
	ColumnLayout {
		width: parent.width * 0.7
		height: parent.height * 0.9
		anchors.centerIn: parent
		spacing: 2

		Qml_Label_AppName {
			mylabel: "TestMaker v1.3"
		}

		// Test modes
		Qml_MyButton {
			mylabel: "Question -> Answer"
			onClicked: {
				stack_view.push(test_menu)
				guiWorker.setTestModeQA()
			}
		}
		Qml_MyButton {
			mylabel: "Answer -> Question"
			onClicked: {
				stack_view.push(test_menu)
				guiWorker.setTestModeAQ()
			}
		}
		Qml_MyButton {
			mylabel: "Mix"
			onClicked: {
				stack_view.push(test_menu)
				guiWorker.setTestModeMix()
			}
		}

		// Type tests modes
		Qml_MyButton {
			mylabel: "Type Question -> Answer"
			onClicked: {
				stack_view.push(type_test_menu)
				guiWorker.setTestModeTypeQA()
			}
		}
		Qml_MyButton {
			mylabel: "Type Answer -> Question"
			onClicked: {
				stack_view.push(type_test_menu)
				guiWorker.setTestModeTypeAQ()
			}
		}
		Qml_MyButton {
			mylabel: "Type Mix"
			onClicked: {
				stack_view.push(type_test_menu)
				guiWorker.setTestModeTypeMix()
			}
		}

		// Manage buttons
		Qml_MyButton {
			mylabel: "Debug info"
			onClicked: {
				stack_view.push(debug_menu)
				debugPage.debugUpdate()
			}
		}
		Qml_MyButton {
			mylabel: "Manage dictionary"
			onClicked: {
				stack_view.push(dict_manage_menu)
				guiWorker.dictionaryFillList()
			}
		}
		Qml_MyButton {
			mylabel: "Open new file"
			onClicked: {
				fileDialog.open()
			}
		}
		Qml_MyButton {
			mylabel: "Exit"
			onClicked: {
				guiWorker.exitFromApp()
			}
		}
	}

	MessageDialog {
		id: info
		standardButtons: StandardButton.Ok
	}
	MessageDialog {
		id: exit_dialog
		standardButtons: StandardButton.No | StandardButton.Yes
		onYes: {
			testGuiApp.close()
		}
	}

	FileDialog {
		id: fileDialog
		title: "File Dialog"
		folder: shortcuts.home
		onAccepted: {
			guiWorker.openFile(fileUrl.toString())
		}
	}


	Connections {
		target: guiWorker
		onQmlShowMessage: {
			info.text = text
			info.detailedText = detailedText
			info.open()
		}
		onQmlShowExitMessage: {
			exit_dialog.text = text
			exit_dialog.detailedText = detailedText
			exit_dialog.open()
		}
		onQmlExitFromApp: {
			testGuiApp.close()
		}
	}
}
