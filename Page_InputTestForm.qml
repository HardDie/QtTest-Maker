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
            height: 400
        }
        TextRectangle {
            height: 100
            readOnly_val: false
        }

        MyButton { mylabel: "Next"
            onClicked: { guiWorker.nextTestStep() } }
        MyButton { mylabel: "Main Menu"
            onClicked: { stack_view.pop() } }
    }
}
