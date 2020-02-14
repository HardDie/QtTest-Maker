import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3

Item {
	ColumnLayout {
		width: parent.width * 0.6
		height: parent.height * 0.8
		anchors.centerIn: parent
		spacing: 2

		Qml_Label_AppName {
			mylabel: "TestMaker v1.2"
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
			}
		}
		Qml_MyButton {
			mylabel: "Open new file"
			onClicked: {
			}
		}
		Qml_MyButton {
			mylabel: "Exit"
			onClicked: {
				testGuiApp.close()
			}
		}

		MessageDialog {
			id: info
			icon: StandardIcon.Info
			text: "Some info"
			detailedText: "Long some info"
			standardButtons: StandardButton.Ok
		}
	}

	Connections {
		target: guiWorker
		onQmlShowMessage: {
			info.text = text
			info.detailedText = detailedText
			info.open()
		}
	}
}
