import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle {
    property string mylabel: "Unknown"
    x: (parent.width * 0.6) + (parent.width * 0.4 / 2) - 20
    y: parent.height - (parent.height * 0.8) - (parent.height * 0.2 / 2) - 30
    // Workaround, change background color as in material design
    color: "#FAFAFA"
    Text {
        text: qsTr(mylabel)
        font.pointSize: 17
        renderType: Text.NativeRendering
    }
}
