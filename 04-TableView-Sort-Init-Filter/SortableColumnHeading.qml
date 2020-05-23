import QtQuick 2.12

Rectangle {
    id: root
    color: "wheat"
    property int initialSortOrder: Qt.AscendingOrder
    property alias text: label.text
    signal sorting

    function stopSorting() {
        state = ""
    }

    Text {
        id: label
        anchors.verticalCenter: parent.verticalCenter
        x: 4
        width: parent.width - 4
        text: table.model.headerData(index, Qt.Horizontal)
    }

    Text {
        id: upDownIndicator
        anchors.right: parent.right
        anchors.margins: 4
        anchors.verticalCenter: parent.verticalCenter
        text: "^"
        visible: false
    }

    TapHandler { id: tap; onTapped: nextState() }

    function nextState() {
        if (state == "")
            state = (initialSortOrder == Qt.DescendingOrder ? "down" : "up")
        else if (state == "up")
            state = "down"
        else
            state = "up"
        root.sorting()
    }
    states: [
        State {
            name: "up"
            PropertyChanges { target: upDownIndicator; visible: true; rotation: 0 }
            PropertyChanges { target: root; color: "orange" }
        },
        State {
            name: "down"
            PropertyChanges { target: upDownIndicator; visible: true; rotation: 180 }
            PropertyChanges { target: root; color: "orange" }
        }
    ]
}
