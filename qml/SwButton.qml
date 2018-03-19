import QtQuick 2.9
import QtQuick.Templates 2.2 as T
import QtQuick.Controls 2.2
import QtQuick.Controls.impl 2.2

T.Switch {
    id: control

    baselineOffset: contentItem.y + contentItem.baselineOffset

    implicitHeight: Math.max(contentItem.implicitHeight, indicator.implicitHeight) + topPadding + bottomPadding
    implicitWidth: contentItem.implicitWidth + leftPadding + rightPadding

    padding: 6 * sc
    spacing: 6 * sc

    property color color: 'white'

    text: qsTr("Switch")

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.color// control.down ? 'red' : 'green'
        verticalAlignment: Text.AlignVCenter
        rightPadding: control.indicator.width + control.spacing
    }

    indicator: Item {
        anchors.right: control.right
        x: text ? (control.mirrored ? control.width - width - control.rightPadding : control.leftPadding) : control.leftPadding + (control.availableWidth - width) * 0.5
        y: control.topPadding + (control.availableHeight - height) * 0.5
        width: 98 * sc
        height: 60 * sc
        Rectangle {
            id: back
            color: control.checked ? "#ffffff" : "#697178"
            anchors.margins: 1
            anchors.fill: parent
            radius: height * 0.5
            //ColorAnimation on color{ duration: 2000 }
        }
        Image {
            anchors.fill: parent
            source:"ListBox_images/frame.png"
        }
        Image {
            source:"SwButton_images/indicator.png"
            x: Math.max(6 * sc, Math.min(parent.width - width, control.visualPosition * parent.width - (width / 2))) - 3 * sc
            y: (parent.height - height) * 0.5 + 1 * sc
            width: 55 * sc
            height: 55 * sc
            Behavior on x {
                enabled: !control.down
                SmoothedAnimation { velocity: 200 }
            }
        }
    }
}
