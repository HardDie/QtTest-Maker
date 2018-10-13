import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    property bool readOnly_val: true
    property string text_val: ""
    height: 100
    Layout.fillHeight: true
    Layout.fillWidth: true
    // Workaround, change background color as in material design
    color: "#FAFAFA"
    border.color: "#C9CACA"
    border.width: 3
    radius: 10
    TextInput {
        id: input
        anchors.fill: parent
        anchors.margins: 10
        font.pixelSize: Qt.application.font.pixelSize * 1.6
        wrapMode: TextInput.Wrap
        maximumLength: 200
        readOnly: readOnly_val
        text: text_val
    }
}
