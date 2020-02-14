import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Button {
	property string mylabel: "Unknown"
	Layout.fillHeight: true
	Layout.fillWidth: true
	Text {
		text: qsTr(mylabel)
		color: "black"
		anchors.centerIn: parent
		font.pixelSize: Qt.application.font.pixelSize
	}
}
