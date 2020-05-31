import QtQuick 2.12

Rectangle {
    id: root
    color: "wheat"
    property int initialSortOrder: Qt.AscendingOrder
    property alias text: label.text
    property real initialWidth: 100
    signal sorting
    width: splitter.x + 6

    function setWidth(newWidth) {
        splitter.x = newWidth -6
    }

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
        anchors.margins: 8
        anchors.verticalCenter: parent.verticalCenter
        text: "^"
        visible: false
    }

    TapHandler { id: tap; onTapped: nextState() }

    Item {
        id: splitter
        x: root.initialWidth - 6
        width: 12
        height: parent.height
        DragHandler {
            yAxis.enabled: false
            onActiveChanged: {
                if (!active) {
                    if (splitter.x <= 5 ) {
                      splitter.x = 6
                    }
                    table.forceLayout()
                }
            }
        }
        Rectangle {
            anchors.fill: parent
            id: splitterRect
            color: "grey"
            visible: false
        }


        MouseArea {
            hoverEnabled: true
            anchors.fill: parent
            onEntered: splitterRect.visible = true
            onExited: splitterRect.visible = false
        }

    }


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
