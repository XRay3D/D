import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    property int value: 0
    Item {
        anchors.centerIn: parent
        height: 33 * sc
        width: 91 * sc
        Rectangle{
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            height: 15 * sc
            width: 8 * sc
            radius: 3 * sc
        }
        Rectangle{
            id: body
            anchors.fill: parent
            anchors.leftMargin: 9 * sc
            radius: 3 * sc
        }
        Rectangle{
            id: hole
            anchors.fill: parent
            color: '#161d23'
            anchors.leftMargin: 13 * sc
            anchors.rightMargin: 17 * sc
            anchors.topMargin: 4 * sc
            anchors.bottomMargin: 4 * sc
            radius: 2
        }
       Rectangle{
            opacity: 0.9
            anchors.fill: hole
            anchors.leftMargin: hole.width * ((100 - value) / 100)
            radius: hole.radius
            color: value > 15 ? 'white' : 'red'
        }
    }
}
