import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
	ColumnLayout {
		anchors.fill: parent
		anchors.centerIn: parent
		spacing: 2

		Rectangle {
			width: parent.width
			height: parent.height * 0.8

			Qml_InputField {
				id: debug_edit
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
		target: debugPage
		onQmlPrintDebug: {
			debug_edit.mytext = text
		}
	}
}
