import QtQuick 2.12
import QtQuick.Window 2.12
import TableModel 0.1
import QtQuick.Controls 2.0

ApplicationWindow {
    id: window
    visible: true
    width: 1024
    height: 800
    title: qsTr("01-TableView-Simple-Different-Cols")

    TableView {
        anchors.fill: parent
        columnSpacing: 4; rowSpacing: 4
        model: _TableModel
        delegate: Rectangle {
            color: "#EEE"
            implicitWidth: Math.max(60, text.implicitWidth)
            implicitHeight: text.implicitHeight
            Text {
                id: text
                text: model.display
                width: parent.width
                elide: Text.ElideRight
                font.preferShaping: false
            }
        }
        Shortcut { sequence: StandardKey.Quit; onActivated: Qt.quit() }
    }

}
