import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    Label_IndexText {
        id: test_index
    }

    ColumnLayout {
        id: test_column
        width: parent.width * 0.6
        height: parent.height * 0.8
        anchors.centerIn: parent
        spacing: 2

        TextRectangle {
            id: test_output
            height: 800
        }

        MyButton { mylabel: "Next"
            onClicked: { guiWorker.buttonTestNext() } }
        MyButton { mylabel: "Main Menu"
            onClicked: { stack_view.pop() } }
    }

    Connections {
        target: guiWorker
        onQmlSetTestString: {
            test_output.text_val = text
            test_index.mylabel = index
        }
    }
}
