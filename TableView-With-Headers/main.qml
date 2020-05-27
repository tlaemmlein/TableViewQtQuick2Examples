import QtQuick 2.15
import QtQuick.Window 2.12
import TableModel 0.1
import QtQuick.Controls 2.15

ApplicationWindow {
    id: window
    visible: true
    width: 1024
    height: 800

    HorizontalHeaderView {
        id: horizontalHeader
        syncView: tableView
        anchors.left: tableView.left
        width: parent.width
        height: contentHeight
    }

    VerticalHeaderView {
        id: verticalHeader
        syncView: tableView
        anchors.top: tableView.top
        width: contentWidth
        height: parent.height
    }

    TableView {
        id: tableView
        anchors.fill: parent
        anchors.topMargin: horizontalHeader.height
        anchors.leftMargin: verticalHeader.width
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
}
