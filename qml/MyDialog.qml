import QtQuick 2.9
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

Dialog{
    id: dialog
    property string caption: ''

    x: 120 * sc
    y: 120 * sc
    width: window.width - 240 * sc
    height:window.height - 240 * sc

    modal: true
    padding: 0

    standardButtons: Dialog.NoButton

    header: Label{
        text: caption
        color:'#28343e'
        font.pixelSize: 36 * sc
        height: 73 * sc
        Image {
            width: 30 * sc
            height: 30 * sc
            anchors.top: parent.top
            anchors.right: parent.right
            id: name
            source: 'images/close.png'
        }
        MouseArea{
            anchors.fill: parent
            onClicked: reject()
        }
    }

    background: Item {}

    contentItem:  Rectangle{
        id: contentItemRectangle
        anchors.fill: parent
        anchors.topMargin: header.height
        color:'#28343e'
        radius: 30 * sc
    }

    enter: Transition {
        NumberAnimation { property: 'scale'; from: 0.9; to: 1.0; easing.type: Easing.OutQuint; duration: 220 }
        NumberAnimation { property: 'opacity'; from: 0.0; to: 1.0; easing.type: Easing.OutCubic; duration: 150 }
    }

    exit: Transition {
        NumberAnimation { property: 'scale'; from: 1.0; to: 0.9; easing.type: Easing.OutQuint; duration: 220 }
        NumberAnimation { property: 'opacity'; from: 1.0; to: 0.0; easing.type: Easing.OutCubic; duration: 150 }
    }
}
