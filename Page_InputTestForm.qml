import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
	Label_IndexText {
		id: type_test_index
	}

	ColumnLayout {
		width: parent.width * 0.6
		height: parent.height * 0.8
		anchors.centerIn: parent
		spacing: 2

		TextRectangle {
			id: type_test_output
			height: 400
		}
		TextRectangle {
			id: type_test_input
			height: 100
			readOnly_val: false
		}

		MyButton {
			mylabel: "Check"
			onClicked: {
				guiWorker.buttonTestTypeCheck(type_test_input.text_val)
			}
		}
		MyButton {
			mylabel: "Skip"
			onClicked: {
				guiWorker.buttonTestTypeSkip()
			}
		}
		MyButton {
			mylabel: "Main Menu"
			onClicked: {
				stack_view.pop()
			}
		}
	}

	Connections {
		target: guiWorker
		onQmlSetTypeTestString: {
			type_test_output.text_val = text
			type_test_index.mylabel = index
			type_test_input.text_val = ""
		}
	}
}
