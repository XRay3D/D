import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

Page {
    id: page

    Settings{
        property alias vbrch: vibro.checked
    }

    background: Item{}

    font.family: 'HelveticaNeueCyr'
    font.pixelSize: 36 * sc
    font.bold: true

    header: Label{
        height: 110 * sc
        width: parent.width
        color: 'white'
        font.capitalization: Font.AllUppercase
        font.pixelSize: 36 * sc
        font.weight: Font.Black
        text: qsTr('Настройки')
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    ColumnLayout{
        anchors.fill: parent
        anchors.leftMargin: 103 * sc
        anchors.rightMargin: 103 * sc
        anchors.bottomMargin: 55 * sc
        Label {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: 'white'
            padding: 6 * sc
            text: 'Соединение'
            verticalAlignment: Text.AlignVCenter
            Image{
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 30 * sc
                source: 'images/bt.png'
                width: 33* sc
                height: 65* sc
                fillMode: Image.PreserveAspectFit
            }
            MouseArea{
                anchors.fill: parent
                onClicked: btDialog.open()
                onPressed: vibration.on(10)
            }
            enabled: trainingPage.state == 'Stopped' || !deviceHandler.alive
            opacity: enabled ? 1.0 : 0.3
        }
        Rectangle{
            Layout.fillWidth: true
            Layout.maximumHeight: 2
            Layout.minimumHeight: 2
            opacity: 0.3
        }
        ListButton{
            text: 'Задержка импульса'
            enabled: deviceHandler.alive
            Layout.fillWidth: true
            Layout.fillHeight: true
            Component.onCompleted: {
                var i = 0
                for(i = 0; i < 11; ++i){
                    model.append({'name': (i * 10) + qsTr('мс')});
                }
                currentIndex = 0
            }
            onValueChanged: delayChanged(value)
            //enabled: false
        }
        Rectangle{
            Layout.fillWidth: true
            Layout.maximumHeight: 2
            Layout.minimumHeight: 2
            opacity: 0.3
        }
        SwButton{
            id: vibro
            text: 'Вибрация'
            Layout.fillWidth: true
            Layout.fillHeight: true
            onCheckedChanged: vibration.enabled = checked
        }
        Rectangle{
            Layout.fillWidth: true
            Layout.maximumHeight: 2
            Layout.minimumHeight: 2
            opacity: 0.0//0.3
        }
        SwButton{
            text: 'Пуш-уведомления'
            Layout.fillWidth: true
            Layout.fillHeight: true
            enabled: false
            opacity: 0.0
        }

        Rectangle{
            Layout.fillWidth: true
            Layout.maximumHeight: 2
            Layout.minimumHeight: 2
            opacity: 0.0//0.3
        }
        SwButton{
            text: 'Звук'
            Layout.fillWidth: true
            Layout.fillHeight: true
            enabled: false
            opacity: 0.0
        }

        Rectangle{
            Layout.fillWidth: true
            Layout.maximumHeight: 2
            Layout.minimumHeight: 2
            opacity: 0.0//0.3
        }
        SwButton{
            text: 'Голосовое управление'
            Layout.fillWidth: true
            Layout.fillHeight: true
            enabled: false
            opacity: 0.0
        }
        Rectangle{
            Layout.fillWidth: true
            Layout.maximumHeight: 2
            Layout.minimumHeight: 2
            opacity: 0.0//0.3
        }
        ListButton{
            text: 'Язык'
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: ListModel {
                ListElement { name: 'РУС' }
                ListElement { name: 'ENG' }
            }
            enabled: false
            opacity: 0.0
        }
        Rectangle{
            Layout.fillWidth: true
            Layout.maximumHeight: 2
            Layout.minimumHeight: 2
            opacity: 0.3
        }
        Label{
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: 'white'
            padding: 6 * sc
            text: 'О продукте'
            verticalAlignment: Text.AlignVCenter
            MouseArea{
                anchors.fill: parent
                onClicked: aboutDialog.open()
                onPressed: vibration.on(10)
            }
        }
    }
}
