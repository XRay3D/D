import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.settings 1.0
import '.'

Page {
    id: trainingSelection

    background: Item{}

    header: Label{
        height: 110 * sc
        width: parent.width
        color: 'white'
        font.capitalization: Font.AllUppercase
        font.pixelSize: 36 * sc
        font.weight: Font.Black
        text: qsTr('ВЫБОР СТИЛЯ')
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Image {
        id: icon

        anchors.horizontalCenter: parent.horizontalCenter
        height:416 * sc
        width:713 * sc

        opacity: 0.1
        source: trainingType ? 'images/icon2.png' : 'images/icon.png'
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: mid
        anchors.horizontalCenter: parent.horizontalCenter
        height:186 * sc
        width:413 * sc
        y: 454 * sc

        fillMode: Image.PreserveAspectFit
        source: trainingType ? 'images/mid2.png' : 'images/mid.png'
        Label {
            id: typeName
            anchors.fill: parent
            anchors.rightMargin: 145 * sc
            anchors.bottomMargin: 10 * sc
            color: 'white'
            font.capitalization: Font.AllUppercase
            font.italic: true
            font.pixelSize: 22 * sc
            font.weight: Font.Black
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: trainingType ? qsTr('Коньковый\nход') : qsTr('Классический\nход')
        }
    }

    Button {
        id: left
        height: 97 * sc
        width: 48 * sc
        x: 75 * sc
        y: 481 * sc
        contentItem: Item {}
        background: Image {
            anchors.fill: parent
            source:'images/left.png'
        }
        states: State {
            name: 'moved'; when: left.pressed
            PropertyChanges { target: left; x: (75 - 30) * sc }
        }
        transitions: Transition {
            NumberAnimation { properties: 'x'; easing.type: Easing.InOutQuad; duration: 150 }
        }
        onClicked: trainingType = !trainingType
    }

    Button {
        id: right
        height:97 * sc
        width:48 * sc
        x: 620 * sc
        y: 481 * sc
        contentItem: Item {}
        background: Image {
            anchors.fill: parent
            source:'images/right.png'
        }
        states: State {
            name: 'moved'; when: right.pressed
            PropertyChanges { target: right; x: (620 + 30) * sc }
        }
        transitions: Transition {
            NumberAnimation { properties: 'x'; easing.type: Easing.InOutQuad; duration: 150 }
        }
        onClicked: trainingType = !trainingType
    }
}
