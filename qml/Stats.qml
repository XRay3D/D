import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Page {
    GridLayout{
        anchors.fill: parent
        anchors.leftMargin: 103 * sc
        anchors.rightMargin: 103 * sc
        columns: 3
        columnSpacing: 0
        rowSpacing: 0
        Item {
            Layout.fillWidth: true
            Layout.minimumHeight: 175 * sc
            Layout.maximumHeight: 175 * sc
            Layout.columnSpan: 3
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:23 * sc
                color: 'white'
                font.pixelSize: 24 * sc
                text: qsTr('Общее время')
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                y:55 * sc
                color: 'white'
                font.pixelSize: 90 * sc
                text: '01:20:39'
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
                text: '43:15'
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
                text: '37:24'
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
                text: '01:13:32'
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
                text: '07:13'
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
            Layout.minimumHeight: 365 * sc
            Layout.maximumHeight: 365 * sc
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
                        3.3,
                        5.5,
                        2.5,
                        4.2,
                        4.6,
                        5000,
                        1500
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
