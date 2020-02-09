import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

ApplicationWindow {
    id: testGuiApp
    visible: true
    width: 1024
    height: 768
    title: qsTr("TestMaker")

    StackView {
        id: stack_view
        anchors.fill: parent
        initialItem: main_menu
    }

    Component {
        id: main_menu
        Page_MainMenu {}
    }

    Component {
        id: test_menu
        Page_TestForm {}
    }

    Component {
        id: type_test_menu
        Page_InputTestForm {}
    }

    Connections {
        target: guiWorker
        onQmlReturnToMainMenu: {
            stack_view.pop()
        }
    }
}

////            Switch {
////                id: myswitch
////                text: "Wi-Fi" + " = " + myswitch.position
////                checked: true
////            }
//}
