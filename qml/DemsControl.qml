import QtQuick 2.9
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

Item {
    opacity: 0.0
    OpacityAnimator on opacity{
        from: 0; to: 1; running: true
    }

    Settings{
        property alias p: power.value
        property alias d: duration.value
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        y:23 * sc
        color: 'white'
        font.pixelSize: 24 * sc
        text: qsTr('Общее время')
    }

    Text {
        id: time
        anchors.horizontalCenter: parent.horizontalCenter
        y:55 * sc
        color: 'white'
        font.pixelSize: 90 * sc
        text: training.totalTime //'00:35:48'
    }

    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        opacity: 0.3
        y: 175 * sc
        width: 544 * sc
        height: 2
    }

    Text {
        id: splitter1
        anchors.horizontalCenter: parent.horizontalCenter
        opacity: 0.3
        y:190 * sc
        color: 'white'
        font.capitalization: Font.AllUppercase
        font.pixelSize: 36 * sc
        text: qsTr('настройки импульса')
    }

    property real k: 1 / 2.5

    ColumnLayout{
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 155 * sc
        anchors.top: splitter1.bottom
        anchors.bottom: parent.bottom
        Arc{
            id: power
            Layout.fillWidth: true
            Layout.maximumHeight : width * k
            Layout.minimumHeight : width * k
            Layout.preferredHeight : width * k
            minValue : 0
            maxValue: 100
            suffix: '%'
            name: qsTr('Мощность')
            onValueChanged: {
                //deviceHandler.setVoltage(value * 10)
                powerChanged(value * 10)
            }
        }
        Arc{
            id: duration
            Layout.fillWidth: true
            Layout.maximumHeight : width * k
            Layout.minimumHeight : width * k
            Layout.preferredHeight : width * k
            minValue: 0
            maxValue: 500
            suffix: qsTr('мc')
            name: qsTr('Продолжительность')
            onValueChanged: {
                //deviceHandler.setDuration(value * 50)
                durationChanged(value * 50)
            }
        }
    }
}
