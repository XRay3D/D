import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Page {

    property int type: myModel.getData(listView.currentIndex,'type')
    property string date: myModel.getData(listView.currentIndex,'date').toLocaleString(locale, 'd.MM.yyyy — hh:mm')
    property string timeWithStimulation: myModel.getData(listView.currentIndex,'timeWithStimulation').toLocaleTimeString(locale, 'hh:mm')
    property string timeWithoutStimulation: myModel.getData(listView.currentIndex,'timeWithoutStimulation').toLocaleTimeString(locale, 'hh:mm')
    property string timePause: myModel.getData(listView.currentIndex,'timePause').toLocaleString(locale,'hh:mm')
    property int avgStimulationAmplitude: myModel.getData(listView.currentIndex,'avgStimulationAmplitude')
    property int avgStepLength: myModel.getData(listView.currentIndex,'avgStepLength')
    property int avgStepFrequency: myModel.getData(listView.currentIndex,'avgStepFrequency')
    property int avgSpeedWithoutStimulation: myModel.getData(listView.currentIndex,'avgSpeedWithoutStimulation')
    property int avgSpeedWithStimulation: myModel.getData(listView.currentIndex,'avgSpeedWithStimulation')
    property int totalDistance: myModel.getData(listView.currentIndex,'totalDistance')
    property int totalStimulationDistance: myModel.getData(listView.currentIndex,'totalStimulationDistance')

    MouseArea{
        id: area
        anchors.fill: parent
        onClicked: {
            if(stack.depth > 1) stack.pop()
        }
    }

    GridLayout{
        anchors.fill: parent
        anchors.leftMargin: 103 * sc
        anchors.rightMargin: 103 * sc
        columns: 3
        columnSpacing: 0
        rowSpacing: 0
        Item {
            Layout.fillWidth: true
            Layout.minimumHeight: 160 * sc
            Layout.maximumHeight: 160 * sc
            Layout.columnSpan: 3
            Label{
                height: 110 * sc
                width: parent.width
                color: 'white'
                font.capitalization: Font.AllUppercase
                font.pixelSize: 36 * sc
                font.weight: Font.Black
                text: qsTr('ТРЕНИРОВКА №') + (listView.currentIndex + 1)
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y: 90 * sc
                color: 'white'
                font.pixelSize: 45 * sc
                text: date
            }
        }
        Rectangle {//line
            Layout.fillWidth: true
            height: 2
            Layout.columnSpan: 3
            opacity: 0.3
        }
        Item {
            Layout.fillWidth: true
            Layout.minimumHeight: 155 * sc
            Layout.maximumHeight: 155 * sc
            Layout.columnSpan: 3
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:10 * sc
                color: 'white'
                font.pixelSize: 24 * sc
                text: type ? qsTr('Коньковый  ход') : qsTr('Классический ход')
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:35 * sc
                color: 'white'
                font.pixelSize: 90 * sc
                text: timeWithStimulation
            }
        }
        Rectangle {//line
            Layout.fillWidth: true
            height: 2
            Layout.columnSpan: 3
            opacity: 0.3
        }
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y: 8 * sc
                color: 'white'
                font.pixelSize: 24 * sc
                text: qsTr('Без стимуляции')
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:38 * sc
                color: 'white'
                font.pixelSize: 60 * sc
                text: timeWithoutStimulation
            }
        }
        Rectangle {//line
            width: 2
            Layout.fillHeight: true
            opacity: 0.3
        }
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:8 * sc
                color: 'white'
                font.pixelSize: 24 * sc
                text: qsTr('Режим стимуляции')
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:38 * sc
                color: 'white'
                font.pixelSize: 60 * sc
                text: timeWithStimulation
            }
        }
        Rectangle {//line
            Layout.fillWidth: true
            height: 2
            Layout.columnSpan: 3
            opacity: 0.3
        }
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:8 * sc
                color: 'white'
                font.pixelSize: 24 * sc
                text: qsTr('Отдых')
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:38 * sc
                color: 'white'
                font.pixelSize: 60 * sc
                text: timePause
            }
        }
        Rectangle {//line
            width: 2
            Layout.fillHeight: true
            opacity: 0.3
        }
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:8 * sc
                color: 'white'
                font.pixelSize: 24 * sc
                text: qsTr('Стимуляция')
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:38 * sc
                color: 'white'
                font.pixelSize: 60 * sc
                text: timeWithStimulation
            }
        }
        Rectangle {//line
            Layout.fillWidth: true
            height: 2
            Layout.columnSpan: 3
            opacity: 0.3
        }
        Item {
            Layout.fillWidth: true
            Layout.minimumHeight: 370 * sc
            Layout.maximumHeight: 370 * sc
            Layout.columnSpan: 3
            RowLayout{
                anchors.fill: parent
                anchors.topMargin: 20 * sc
                anchors.bottomMargin: 20 * sc
                ColumnLayout{
                    id: column0
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    property var texts: [
                        qsTr('Средняя амплитуда стимуляции'),
                        qsTr('Средняя длина шага'),
                        qsTr('Средняя частота движений'),
                        qsTr('Средняя скорость без стимуляции'),
                        qsTr('Средняя скорость со стимуляцией'),
                        qsTr('Общая дистанция'),
                        qsTr('Дистанция в режиме стимуляции')
                    ]
                    Repeater{
                        model: 7
                        Text {
                            Layout.fillHeight: true
                            color: 'white'
                            font.pixelSize: 24 * sc
                            text: column0.texts[index]
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
                ColumnLayout{
                    id: column1
                    Layout.fillHeight: true
                    property var values: [
                        avgStimulationAmplitude,
                        avgStepLength,
                        avgStepFrequency,
                        avgSpeedWithoutStimulation,
                        avgSpeedWithStimulation,
                        totalDistance,
                        totalStimulationDistance
                    ]
                    Repeater{
                        model: 7
                        Text {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            color: 'white'
                            font.pixelSize: 24 * sc
                            text: column1.values[index]
                            font.bold: true
                            horizontalAlignment: Text.AlignRight
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
                ColumnLayout{
                    id: column2
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    property var texts: [
                        qsTr('В'),
                        qsTr('м'),
                        qsTr('ш/с'),
                        qsTr('м/с'),
                        qsTr('м/с'),
                        qsTr('м'),
                        qsTr('м')
                    ]
                    Repeater{
                        model: 7
                        Text {
                            Layout.fillHeight: true
                            color: 'white'
                            font.pixelSize: 24 * sc
                            text: column2.texts[index]
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
            }
        }
    }
}
