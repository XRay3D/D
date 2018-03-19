import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Page {
    id: training
    property bool isRuning: false
    //property int type: 0
    background: Item{}

    StackView{
        id: stackView
        width: parent.width
        height: 768 * sc
        initialItem: Selection { id: initialItem }
        pushEnter: Transition { PropertyAnimation { property: "opacity"; from: 0; to:1; duration: 200; } }
        pushExit: Transition { PropertyAnimation { property: "opacity"; from: 1; to:0; duration: 200; } }
        popEnter: Transition { PropertyAnimation { property: "opacity"; from: 0; to:1; duration: 200 } }
        popExit: Transition { PropertyAnimation { property: "opacity"; from: 1; to:0; duration: 200 } }
    }

    Rectangle {
        id: splitter2
        anchors.horizontalCenter: parent.horizontalCenter
        opacity: 0.3
        y: 768 * sc
        width: 544 * sc
        height: 2
    }

    Button {
        id: btnPulse
        visible: isRuning
        opacity: 0.0
        width: 116 * sc
        height: 116 * sc
        x: parent.width / 2 - width / 2
        y: 790 * sc
        Layout.alignment: Qt.AlignHCenter
        background: Image {
            source:"images/pulse.png"
            anchors.fill: parent
        }
        states: State {
            when: btnPulse.pressed
            PropertyChanges { target: btnPulse.background; scale: 0.8}
        }
        transitions: Transition {
            NumberAnimation { properties: "scale"; easing.type: Easing.InOutQuad; duration: 150  }
        }
        OpacityAnimator on opacity { from: 0; to: 1; running: isRuning; easing.type: Easing.InExpo}
    }

    Button {
        id: btnStartStop
        width: 116 * sc
        height: 116 * sc
        x: parent.width / 2 - width / 2
        y:790 * sc

        background: Image {
            source: isRuning ? "images/stop.png" : "images/play.png"
            anchors.fill: parent
        }

        onClicked: {
            if(!isRuning){
                isRuning = !isRuning
                // trainingLoader.setSource('TrainingControl.qml')
                stackView.push('Control.qml')
            }else{
                if(stackView.depth == 2)
                    stackView.push('Stats.qml')
                else{
                    stackView.pop(initialItem)
                    isRuning = false
                    btnPulse.opacity = 0.0
                }
            }
        }

        states: State {
            when: btnStartStop.pressed
            PropertyChanges { target: btnStartStop.background; scale: 0.8}
        }

        transitions: Transition {
            NumberAnimation { properties: "scale"; easing.type: Easing.InOutQuad; duration: 150  }
        }
    }

    property int k: 80 * sc

    states: State {
        name: "moved"; when: isRuning
        PropertyChanges { target: btnStartStop; x: training.width / 2 - btnStartStop.width - k }
        PropertyChanges { target: btnPulse; x: training.width / 2 + k }
    }

    transitions: Transition {
        NumberAnimation { properties: "x"; easing.type: Easing.InOutQuad; duration: 150  }
    }

//    DropShadow {
//        anchors.fill: btnPulse
//        verticalOffset: 8
//        radius: 8.0
//        samples: 17
//        color: 'red'//"#80000000"
//        source: btnPulse
//    }

//    DropShadow {
//        anchors.fill: btnStartStop
//        verticalOffset: 8
//        radius: 8.0
//        samples: 17
//        color: 'red'//"#80000000"
//        source: btnStartStop
//    }
}
