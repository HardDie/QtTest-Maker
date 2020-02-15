import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
	property string mylabel: "Unknown"

	Layout.fillHeight: true
	Layout.fillWidth: true
	height: 37
	color: "transparent"

	Text {
		anchors.centerIn: parent
		text: qsTr(mylabel)
		font.pointSize: 17
	}
}
