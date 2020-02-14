import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
	property string mylabel: "Unknown"
	Layout.fillHeight: true
	Layout.fillWidth: true
	height: 37
	// Workaround, change background color as in material design
	color: "#FAFAFA"
	Text {
		width: parent.width
		height: 40
		text: qsTr(mylabel)
		font.bold: true
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		font.pointSize: 18
		anchors.centerIn: parent
	}
}
