import QtQuick 2.12
import QtQuick.Window 2.12
import TableModel 0.1
import QtQuick.Controls 2.0

ApplicationWindow {
    id: window
    visible: true
    width: 1024
    height: 800
    title: qsTr("02-TableView-ColumnWidth-Headings")

    Rectangle {
        anchors.fill: parent
        Row {
            id: header
            width: table.contentWidth
            height: 40
            x: -table.contentX
            z: 1
            spacing: 4
            Repeater {
                model: table.model.columnCount()
                Rectangle {
                    width: table.model.columnWidth(index); height: parent.height
                    color: "orange"

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        x: 4
                        width: parent.width - 4
                        text: table.model.headerData(index, Qt.Horizontal)
                    }
                }
            }
        }
        TableView {
            id: table
            anchors.fill: parent
            anchors.topMargin: header.height
            columnSpacing: 4; rowSpacing: 4
            model: _TableModel
            columnWidthProvider: function(column) { return Math.min(600, model.columnWidth(column)) }

            delegate: Rectangle {
                color: "#EEE"
                implicitHeight: text.implicitHeight
                Text {
                    id: text
                    text: model.display
                    width: parent.width
                    elide: column == 49 ? Text.ElideLeft : Text.ElideRight
                    font.preferShaping: false
                }
            }

            ScrollBar.horizontal: ScrollBar { }
            ScrollBar.vertical: ScrollBar { }
        }
        Shortcut { sequence: StandardKey.Quit; onActivated: Qt.quit() }
    }
}
