import QtQuick 2.9
import QtQuick.Controls 2.2
//import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

ToolBar{
    id: footer
    background: Rectangle{
        id: back
        color: '#252525'
    }
    RowLayout{
        id: row
        anchors.fill: parent
        RadioButton {
            id: b1
            checked: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            indicator: Item {
                anchors.centerIn: parent
                Image{
                    id: image1
                    anchors.centerIn: parent
                    source: trainingType ? "images/type2.png" : "images/type1.png"
                    width:200 * sc
                    height:85 * sc
                    fillMode: Image.PreserveAspectFit
                }
                Colorize {
                    id: colorize1
                    opacity: 0
                    anchors.fill: image1
                    source: image1
                    lightness: -0.85
                    saturation: 0.0
                }
                Glow {
                    id: glow1
                    anchors.fill: colorize1
                     samples: 6 * sc
                    color: "white"
                    source: colorize1
                }

            }

            onCheckedChanged: {
                image1.visible = b1.checked
                glow1.visible = !b1.checked
                if(b1.checked)pageIndex = 0
            }
            states: State {
                when: b1.pressed
                PropertyChanges { target: b1.indicator; scale: 0.8}
            }
            transitions: Transition {
                NumberAnimation { properties: "scale"; easing.type: Easing.InOutQuad; duration: 150  }
            }
        }
        RadioButton{
            id: b2
            //opacity: 0
            Layout.fillHeight: true
            Layout.fillWidth: true
            indicator: Item {
                anchors.centerIn: parent
                Image{
                    id: image2
                    anchors.centerIn: parent
                    source:"images/statictics.png"
                    width:97 * sc
                    height:82 * sc
                }
                Colorize {
                    id: colorize2
                    opacity: 0
                    anchors.fill: image2
                    source: image2
                    lightness: -0.85
                    saturation: 0.0
                }
                Glow {
                    id: glow2
                    anchors.fill: colorize2
                     samples: 6 * sc
                    color: "white"
                    source: colorize2
                }
            }
            onCheckedChanged: {
                image2.visible = b2.checked
                glow2.visible = !b2.checked
                if(b2.checked)pageIndex = 1
            }
            states: State {
                when: b2.pressed
                PropertyChanges { target: b2.indicator; scale: 0.8}
            }
            transitions: Transition {
                NumberAnimation { properties: "scale"; easing.type: Easing.InOutQuad; duration: 150  }
            }
        }
        RadioButton{
            id: b3
            //opacity: 0
            Layout.fillHeight: true
            Layout.fillWidth: true
            indicator: Item {
                anchors.centerIn: parent
                Image{
                    id: image3
                    anchors.centerIn: parent
                    source:"images/settings.png"
                    width:84 * sc
                    height:85 * sc
                }
                Colorize {
                    id: colorize3
                    opacity: 0
                    anchors.fill: image3
                    source: image3
                    lightness: -0.85
                    saturation: 0.0
                }
                Glow {
                    id: glow3
                    anchors.fill: colorize3
                     samples: 6 * sc
                    color: "white"
                    source: colorize3
                }
            }
            onCheckedChanged: {
                image3.visible = b3.checked
                glow3.visible = !b3.checked
                if(b3.checked)pageIndex = 2
            }
            states: State {
                when: b3.pressed
                PropertyChanges { target: b3.indicator; scale: 0.8}
            }
            transitions: Transition {
                NumberAnimation { properties: "scale"; easing.type: Easing.InOutQuad; duration: 150  }
            }
        }
    }
    Component.onCompleted: {
        b2.checked = true
        b3.checked = true
        b1.checked = true
    }
}
