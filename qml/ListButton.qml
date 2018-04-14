import QtGraphicalEffects 1.0
import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Controls.impl 2.2
import QtQuick.Templates 2.2 as T

T.ComboBox {
    id: control

    baselineOffset: contentItem.y + contentItem.baselineOffset
    implicitHeight: Math.max(contentItem.implicitHeight, indicator.implicitHeight) + topPadding + bottomPadding
    implicitWidth: contentItem.implicitWidth + leftPadding + rightPadding

    padding: 6
    spacing: 6

    property string text: qsTr('Switch')

    property color color: 'white'

    model: ListModel {}

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.color// control.down ? 'red' : 'green'
        verticalAlignment: Text.AlignVCenter
        rightPadding: control.indicator.width + control.spacing
    }

    delegate: MenuItem {
        width: parent.width
        text: control.textRole ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole]) : modelData
        highlighted: control.highlightedIndex === index
        hoverEnabled: control.hoverEnabled
    }

    popup: T.Popup {
        width: control.width
        height: Math.min(contentItem.implicitHeight, control.Window.height - topMargin - bottomMargin)
        transformOrigin: Item.Top
        topMargin: 12
        bottomMargin: 12
        dim: true

        enter: Transition {
            NumberAnimation { property: 'scale'; from: 0.9; to: 1.0; easing.type: Easing.OutQuint; duration: 220 }
            NumberAnimation { property: 'opacity'; from: 0.0; to: 1.0; easing.type: Easing.OutCubic; duration: 150 }
        }

        exit: Transition {
            NumberAnimation { property: 'scale'; from: 1.0; to: 0.9; easing.type: Easing.OutQuint; duration: 220 }
            NumberAnimation { property: 'opacity'; from: 1.0; to: 0.0; easing.type: Easing.OutCubic; duration: 150 }
        }

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: control.model
            currentIndex: control.highlightedIndex
            highlightMoveDuration: 0
            T.ScrollIndicator.vertical: ScrollIndicator { }
            delegate: Label {
                id: delegate
                width: parent.width
                height: 70 * sc
                text: name
                color: control.color
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                states: State {
                    when: delegateMouseArea.pressed
                    PropertyChanges { target: delegate; scale: 0.9}
                }
                transitions: Transition {
                    NumberAnimation { properties: 'scale'; easing.type: Easing.InOutQuad; duration: 150 }
                }
                MouseArea {
                    id: delegateMouseArea
                    anchors.fill: parent
                    onClicked: {
                        control.currentIndex = index
                        control.popup.close()
                    }
                }
                Glow{
                    cached : true
                    opacity: delegateMouseArea.pressed? 1 : 0
                    anchors.fill: contentItem.delegate
                    radius: 8
                    samples: 17
                    color: 'white'
                    source: contentItem.delegate
                }
            }
        }

        background: Rectangle {
            id: back1
            radius: 10
            color: '#28343e'
        }
    }

    indicator: Item {
        anchors.right: control.right
        x: text ? (control.mirrored ? control.width - width - control.rightPadding : control.leftPadding) : control.leftPadding + (control.availableWidth - width) / 2
        y: control.topPadding + (control.availableHeight - height) / 2
        width: 98 * sc
        height: 60 * sc
        Rectangle {
            id: back
            color: control.enabled ? '#FFFFFF' : '#C0C0C0'
            anchors.margins: 1
            anchors.fill: parent
            radius: height / 2
        }
        SwipeView{
            id: list
            anchors.centerIn: parent
            anchors.fill: parent

            clip: true
            currentIndex: control.currentIndex
            focusPolicy : Qt.NoFocus
            height: 34 * sc
            hoverEnabled:false
            interactive: false
            orientation: Qt.Vertical
            wheelEnabled : false
            width: parent.width
            Repeater{
                model: control.model.count
                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    //                    height: 34 * sc
                    //                    width: (98 - height) * sc
                    text: control.model.get(index).name
                    font.pixelSize: 30 * sc
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }
        Image {
            anchors.fill: parent
            source:'images/frame.png'
        }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: popup.open()
    }
}
