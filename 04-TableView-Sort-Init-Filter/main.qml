import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import ProcessModel 0.1
import SortFilterTableModel 0.1
import QtQuick.Controls 2.4

ApplicationWindow {
    id: window
    visible: true
    width: 1024
    height: 800
    title: qsTr("04-TableView-Sort-Init-Filter")

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            anchors.rightMargin: 6
            Switch {
                id: cbUpdate
                checked: true
                text: qsTr("Update every")
            }
            SpinBox {
                id: sbUpdate
                from: 1
                to: 60
                value: 2
                enabled: cbUpdate.checked
            }
            Label {
                text: "sec"
            }
            Item {
                Layout.fillWidth: true
            }
            TextField {
                id: tfFilter
                implicitWidth: parent.width / 4
                onTextEdited: table.contentY = 0
            }
        }
    }
    Row {
        id: header
        width: table.contentWidth
        height: cbUpdate.height
        x: -table.contentX
        z: 1
        spacing: 4
        Repeater {
            id: peter
            model: table.model.columnCount()
            SortableColumnHeading {
                width: Math.min(600, table.model.columnWidth(index)); height: parent.height
                text: table.model.headerData(index, Qt.Horizontal)
                initialSortOrder: table.model.initialSortOrder(index)
                onSorting: {
                    for (var i = 0; i < peter.model; ++i)
                        if (i != index)
                            peter.itemAt(i).stopSorting()
                    table.model.sort(index, state == "up" ? Qt.AscendingOrder : Qt.DescendingOrder)
                }
            }
        }
    }
    TableView {
        id: table
        anchors.fill: parent
        anchors.topMargin: header.height
        columnSpacing: 4; rowSpacing: 4
        model: SortFilterTableModel {
            filterText: tfFilter.text
        }
        Timer {
            interval: sbUpdate.value * 1000
            repeat: true
            running: cbUpdate.checked
            onTriggered: table.model.processModel.update()
        }
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
