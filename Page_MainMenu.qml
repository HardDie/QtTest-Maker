import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    ColumnLayout {
        width: parent.width * 0.6
        height: parent.height * 0.8
        anchors.centerIn: parent
        spacing: 2

        Label_AppName {
            mylabel: "TestMaker v1.2"
        }

        MyButton { mylabel: "Question -> Answer"
            onClicked: { stack_view.push(test_menu); guiWorker.setTestModeQA() } }
        MyButton { mylabel: "Answer -> Question"
            onClicked: { stack_view.push(test_menu); guiWorker.setTestModeAQ() } }
        MyButton { mylabel: "Mix"
            onClicked: { stack_view.push(test_menu); guiWorker.setTestModeMix() } }

        MyButton { mylabel: "Type Question -> Answer"
            onClicked: { stack_view.push(type_test_menu); guiWorker.setTestModeTypeQA() } }
        MyButton { mylabel: "Type Answer -> Question"
            onClicked: { stack_view.push(type_test_menu); guiWorker.setTestModeTypeAQ() } }
        MyButton { mylabel: "Type Mix"
            onClicked: { stack_view.push(type_test_menu); guiWorker.setTestModeTypeMix() } }

        MyButton { mylabel: "Manage dictionary" }
        MyButton { mylabel: "Open new file" }
        MyButton { mylabel: "Exit"
            onClicked: { testGuiApp.close() } }
    }
}