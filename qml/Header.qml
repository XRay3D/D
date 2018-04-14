import QtQuick 2.9
import QtQuick.Controls 2.2
ToolBar {
    background: Rectangle{
        id: back
        color: '#252525'
    }
    Image {
        anchors.left: parent.left
        anchors.leftMargin: 30 * sc
        anchors.verticalCenter: parent.verticalCenter
        height:48 * sc
        opacity: 0.74
        source:'images/dems.png'
        width:247 * sc
    }
    Image {
        anchors.rightMargin: 30 * sc
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        height:94 * sc
        source:'images/roc.png'
        width:161 * sc
    }
}
