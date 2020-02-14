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

			Flickable {
				id: flick
				width: parent.width
				height: parent.height
				contentWidth: debug_edit.paintedWidth
				contentHeight: debug_edit.paintedHeight
				clip: true

				function ensureVisible(r)
				{
					if (contentX >= r.x)
						contentX = r.x;
					else if (contentX + width <= r.x + r.width)
						contentX = r.x + r.width - width;
					if (contentY >= r.y)
						contentY = r.y;
					else if (contentY + height <= r.y + r.height)
						contentY = r.y + r.height - height;
				}

				TextEdit {
					id: debug_edit
					width: flick.width
					focus: true
					wrapMode: TextEdit.Wrap
					onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)
				}
			}
		}

		MyButton {
			mylabel: "Main Menu"
			onClicked: {
				stack_view.pop()
			}
		}
		MyButton {
			mylabel: "Exit"
			onClicked: {
				testGuiApp.close()
			}
		}

	}

	Connections {
		target: debugPage
		onQmlPrintDebug: {
			debug_edit.text = text
		}
	}
}
