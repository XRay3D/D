import QtQuick 2.9
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0


AbstractButton{//+
    height: 68 * sc
    width: 68 * sc
    //hoverEnabled: true
    property bool plus: false

    background: Image {
        id: background
        anchors.centerIn: parent
        height: parent.height
        width: height
        source: plus ? 'images/plus.png' : 'images/minus.png'
    }

    states: State { when: pressed; PropertyChanges { target: background; scale: 0.8} }
    transitions: Transition { NumberAnimation { properties: 'scale'; easing.type: Easing.InOutQuad; duration: 50 } }
    contentItem: Item{}
}
