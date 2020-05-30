import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import ProcessModel 0.1
import SortFilterTableModel 0.1
import QtQuick.Controls 2.4
import Qt.labs.qmlmodels 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 1024
    height: 800
    //title: qsTr("05-TableView-DelegateChooser")

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
            id: headerRepeater
            model: table.model.columnCount()
            SortableColumnHeading {
                initialWidth: Math.min(600, table.model.columnWidth(index)); height: parent.height
                text: table.model.headerData(index, Qt.Horizontal)
                initialSortOrder: table.model.initialSortOrder(index)
                onSorting: {
                    for (var i = 0; i < headerRepeater.model; ++i)
                        if (i !== index)
                            headerRepeater.itemAt(i).stopSorting()
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
        columnWidthProvider: function(column) { return headerRepeater.itemAt(column).width }

        delegate: DelegateChooser {
            role: "type"
            DelegateChoice {
                roleValue: "readonly"
                Rectangle {
                    color: "grey"
                    implicitHeight: readonlyText.implicitHeight
                    Text {
                        id: readonlyText
                        text: model.display
                        width: parent.width
                        elide: Text.ElideRight
                        font.preferShaping: false
                    }
                }
            }
            DelegateChoice {
                roleValue: "id"
                Rectangle {
                    color: "yellow"
                    implicitHeight: idText.implicitHeight
                    Text {
                        id: idText
                        text: model.display
                        width: parent.width
                        elide: Text.ElideRight
                        font.preferShaping: false
                    }
                }
            }
            DelegateChoice {
                roleValue: "string"
                Rectangle {
                    color: "#0048BA"
                    implicitHeight: stringText.implicitHeight *1.5

                    Text {
                        id: stringText
                        color: "white"
                        text: model.display
                        width: parent.width
                        elide: Text.ElideRight
                        font.preferShaping: false
                    }
                }
            }
            DelegateChoice {
                Rectangle {
                    color: "#EEE"
                    implicitHeight: defaultText.implicitHeight
                    Text {
                        id: defaultText
                        text: model.display
                        width: parent.width
                        elide: Text.ElideRight
                        horizontalAlignment: Text.AlignRight
                        font.preferShaping: false
                    }
                }
            }
        }
        ScrollBar.horizontal: ScrollBar { }
        ScrollBar.vertical: ScrollBar { }
    }
    Shortcut { sequence: StandardKey.Quit; onActivated: Qt.quit() }
}
