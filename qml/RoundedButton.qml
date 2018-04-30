import QtQuick 2.9
import QtQuick.Templates 2.2 as T
import QtQuick.Controls 2.2
//import QtQuick.Controls.impl 2.2

/*T.*/Button {
    id: control

    background:Rectangle{
        anchors.fill: control
        color: enabled ? (control.pressed ? 'darkgray' : 'red') : 'gray'
        radius: 30 + sc
    }

    //    //font: Theme.font

    //    enabled: false

    //    implicitWidth: Math.max(background ? background.implicitWidth : 0,
    //                                         contentItem.implicitWidth + leftPadding + rightPadding)
    //    implicitHeight: Math.max(background ? background.implicitHeight : 0,
    //                                          contentItem.implicitHeight + topPadding + bottomPadding)
    //    leftPadding: 4
    //    rightPadding: 4

    //    background: Rectangle {
    //        id: buttonBackground
    //        implicitWidth: 100
    //        implicitHeight: 40
    //        opacity: enabled ? 1 : 0.3
    //        border.color: 'red'
    //        border.width: 1
    //        radius: 2

    //        states: [
    //            State {
    //                name: "normal"
    //                when: !control.down
    //                PropertyChanges {
    //                    target: buttonBackground
    //                }
    //            },
    //            State {
    //                name: "down"
    //                when: control.down
    //                PropertyChanges {
    //                    target: buttonBackground
    //                    border.color: 'gray'
    //                }
    //            }
    //        ]
    //    }

    //    contentItem: Text {
    //        id: textItem
    //        text: control.text

    //        font: control.font
    //        opacity: enabled ? 1.0 : 0.3
    //        color: 'darkgreen'
    //        horizontalAlignment: Text.AlignHCenter
    //        verticalAlignment: Text.AlignVCenter
    //        elide: Text.ElideRight

    //        states: [
    //            State {
    //                name: "normal"
    //                when: !control.down
    //            },
    //            State {
    //                name: "down"
    //                when: control.down
    //                PropertyChanges {
    //                    target: textItem
    //                    color: 'green'
    //                }
    //            }
    //        ]
    //    }
}
