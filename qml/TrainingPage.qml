import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page{
    id: trainingPage
    property bool isRuning: false
    property int k: 80 * sc

    background: Item{}

    state: training.state //init state is 'Stopped'

    StackView{
        id: stackView
        width: parent.width
        height: 768 * sc
        initialItem: Selection { id: initialItem }
        pushEnter: Transition { PropertyAnimation { property: 'opacity'; from: 0; to:1; duration: 200; } }
        pushExit: Transition { PropertyAnimation { property: 'opacity'; from: 1; to:0; duration: 200; } }
        popEnter: Transition { PropertyAnimation { property: 'opacity'; from: 0; to:1; duration: 200 } }
        popExit: Transition { PropertyAnimation { property: 'opacity'; from: 1; to:0; duration: 200 } }
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
        id: btnPulseStop
        opacity: 0.0
        width: 116 * sc
        height: 116 * sc
        x: parent.width / 2 - width / 2
        y: 790 * sc
        Layout.alignment: Qt.AlignHCenter
        background: Image {
            id: btnPulseStopImage
            anchors.fill: parent
        }
        states: State { when: btnPulseStop.pressed; PropertyChanges { target: btnPulseStop.background; scale: 0.8} }
        transitions: Transition { NumberAnimation { properties: 'scale'; easing.type: Easing.InOutQuad; duration: 150 } }
        onClicked: {
            if(trainingPage.state == 'Running'){
                deviceHandler.impulse()
            }
            else if(trainingPage.state == 'Paused'){
                training.stop()
                journal.showLastTraining()
                tabBar.selectTab(2)
                stackView.pop(initialItem)
            }
        }
    }

    Button {
        id: btnStartPause
        width: 116 * sc
        height: 116 * sc
        x: parent.width / 2 - width / 2
        y: 790 * sc
        background: Image {
            id: btnStartPauseImage
            anchors.fill: parent
        }
        states: State { when: btnStartPause.pressed; PropertyChanges { target: btnStartPause.background; scale: 0.8} }
        transitions: Transition { NumberAnimation { properties: 'scale'; easing.type: Easing.InOutQuad; duration: 150 } }
        onClicked: {
            if(trainingPage.state == 'Stopped'){
                if(!deviceHandler.alive)//! return
                    btDialog.open()
                else{
                    stackView.push('DemsControl.qml')
                    training.start()
                }
            }
            else if(trainingPage.state == 'Running'){
                training.pause()
            }
            else if(trainingPage.state == 'Paused'){
                training.resume()
            }
        }
    }

    states: [
        State {
            name: 'Stopped'
            PropertyChanges { target: btnStartPauseImage; source: 'images/play.png' }
            PropertyChanges { target: btnPulseStopImage; source: 'images/pulse.png' }
        },
        State {
            name: 'Running'
            PropertyChanges { target: btnStartPauseImage; source: 'images/pause.png' }
            PropertyChanges { target: btnPulseStopImage; source: 'images/pulse.png' }
            PropertyChanges { target: btnStartPause; x: trainingPage.width / 2 - btnStartPause.width - k }
            PropertyChanges { target: btnPulseStop; x: trainingPage.width / 2 + k }
        },
        State {
            name: 'Paused'
            PropertyChanges { target: btnStartPauseImage; source: 'images/play.png' }
            PropertyChanges { target: btnPulseStopImage; source: 'images/stop.png' }
            PropertyChanges { target: btnStartPause; x: trainingPage.width / 2 - btnStartPause.width - k }
            PropertyChanges { target: btnPulseStop; x: trainingPage.width / 2 + k }
        }
    ]

    transitions: [
        Transition {
            from: 'Stopped'; to: 'Running'
            NumberAnimation { target: btnPulseStop; properties: 'x'; easing.type: Easing.InOutQuad; duration: 150 }
            NumberAnimation { target: btnStartPause; properties: 'x'; easing.type: Easing.InOutQuad; duration: 150 }
            PropertyAnimation { target: btnPulseStop; property: 'opacity'; from: 0; to: 1; duration: 150 }
        },
        Transition {
            from: 'Paused'; to: 'Stopped'
            PropertyAnimation { target: btnPulseStop; property: 'opacity'; from: 1; to: 0; duration: 0 }
        }
    ]
}
