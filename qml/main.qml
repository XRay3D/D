import QtQuick 2.9
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

//import Shared 1.0 //?

ApplicationWindow {
    visible: true
    id: window
    width: 750 * 0.7
    height: (1334 - 36) * 0.7
    property double sc: width / 750
    property Footer tabBar: tabBar
    property Journal journal: journal
    property FastBlur fastBlur: fastBlur

    FontLoader { id: font1; source: '../fonts/HelveticaNeueCyr-Bold.ttf' }
    FontLoader { id: font2; source: '../fonts/HelveticaNeueCyr-Heavy.ttf' }
    FontLoader { id: font3; source: '../fonts/HelveticaNeueCyr-Light.ttf' }
    FontLoader { id: font4; source: '../fonts/HelveticaNeueCyr-Medium.ttf' }
    FontLoader { id: font5; source: '../fonts/HelveticaNeueCyr-Roman.ttf' }
    FontLoader { id: font6; source: '../fonts/HelveticaNeueCyr-Thin.ttf' }

    /////////////////////////////////////////////////////////

    property string errorMessage: deviceFinder.error
    property bool hasError: errorMessage != ''
    property string infoMessage: deviceFinder.info
    property bool hasInfo: infoMessage != ''
    
    /////////////////////////////////////////////////////////

    property int pageIndex: 0
    property StackView stackView

    font.family: 'HelveticaNeueCyr'
    font.pixelSize: 30 * sc

    background:Rectangle { color: '#181f25' }


    Connections {
        target: GUI
        onBack: {
            console.log('back')
            if(stackView.depth === 2)
                stackView.pop()
        }
    }
    
    Connections {
        target: deviceHandler
        onAliveChanged: {
            console.log('onAliveChanged')
        }
    }

    Shortcut {
        sequence: 'F4'
        context: Qt.ApplicationShortcut
        onActivated: Qt.quit()
    }

    Settings {
        id: settings
        property alias x: window.x
        property alias y: window.y
    }

    ColumnLayout{
        opacity: 0.0
        OpacityAnimator on opacity { from: 0; to: 1; running: true}
        anchors.fill: parent
        spacing: 0
        Header{
            Layout.minimumHeight:  130 * sc //0
            Layout.maximumHeight:  130 * sc //0
            Layout.fillWidth: true
        }
        Item {
            Layout.fillWidth: true
            Layout.fillHeight:  true
            Image {
                anchors.fill: parent
                id :image
                source:'images/background.png'
            }
            SwipeView {
                id: swipeView
                width: parent.width
                height: 925 * sc
                currentIndex: pageIndex
                interactive: false
                TrainingPage { id: trainingPage }
                Journal { id: journal }
                AppSettings { id: appSettings }
            }
            Rectangle { //splitter2
                opacity: 0.3
                x: 103 * sc;
                y: swipeView.height
                width: 544 * sc
                height: 2
            }
            RowLayout{
                opacity: deviceHandler.alive === true ? 1.0 : 0.3
                anchors.fill: parent
                anchors.topMargin: swipeView.height
                anchors.leftMargin: 103 * sc
                anchors.rightMargin: 103 * sc
                Label{
                    Layout.minimumWidth: 140 * sc
                    Layout.maximumWidth: 140 * sc
                    Layout.fillHeight: true
                    text: leftBattery.value + '%'
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: 'white'
                    font.pixelSize: 24 * sc
                }
                Battery{
                    id: leftBattery
                    value: deviceHandler.batteryLeft
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
                Image {
                    Layout.fillWidth: true
                    Layout.minimumHeight: 65 * sc
                    Layout.maximumHeight: 65 * sc
                    fillMode: Image.PreserveAspectFit
                    source:'images/bluetootch.png'
                }
                Battery{
                    id: rightBattery
                    value: deviceHandler.batteryRight
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    rotation: 180
                }
                Label{
                    Layout.minimumWidth: 140 * sc
                    Layout.maximumWidth: 140 * sc
                    Layout.fillHeight: true
                    text: rightBattery.value + '%'
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: 'white'
                    font.pixelSize: 24 * sc
                }
            }
        }
        Footer{
            id: tabBar
            Layout.minimumHeight:  148 * sc //0
            Layout.maximumHeight:  148 * sc //0
            Layout.fillWidth: true
        }
    }


    overlay.modal: FastBlur{
        anchors.fill: parent
        transparentBorder: false
        source: window.contentItem
        radius: 32
        Rectangle{
            anchors.fill: parent
            opacity: 0.7
        }
        Behavior on opacity { NumberAnimation { duration: 200 } }
    }
    overlay.modeless: FastBlur{
        anchors.fill: parent
        transparentBorder: false
        source: window.contentItem
        radius: 32
        Behavior on opacity { NumberAnimation { duration: 200 } }
    }

    // Диалог справки
    MyDialog {
        id: aboutDialog
        caption: qsTr('О продукте')
        Flickable{
            anchors.fill: parent
            anchors.margins: 50 * sc
            clip: true
            contentHeight: label.height
            ScrollBar.vertical: ScrollBar { }
            flickableDirection: Flickable.VerticalFlick
            Label {
                id: label
                // anchors.fill: parent
                width: parent.width
                color: 'white'
                wrapMode: Text.WordWrap
                text: ':1234567890
       Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
       Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
       Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt.
       Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem.
       Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
       Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
       Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt.
       Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem.'
                font.pixelSize: 24 * sc
            }
        }
    }
    // Диалог установки соединения
    MyDialog{
        id: btDialog
        caption: qsTr('Соединение')
        ListView {
            id: devices
            anchors.fill: parent
            anchors.margins: 50 * sc
            anchors.bottomMargin: 100 * sc
            model: deviceFinder.devices
            clip: true
            delegate: BorderImage {
                height: 100 * sc
                width: parent.width
                source: 'images/frame.png'
                border {
                    left: 30
                    right: 30
                    top: 30
                    bottom: 30
                }
                horizontalTileMode: BorderImage.Repeat
                verticalTileMode: BorderImage.Stretch
                //color: index % 2 === 0 ? '#100000' : '#200000'
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        deviceFinder.connectToService(modelData.deviceAddress);
                        console.log(modelData.deviceAddress)
                        btDialog.accept()
                    }
                }
                Label {
                    text: modelData.deviceName
                    anchors.top: parent.top
                    anchors.topMargin: 15 * sc
                    anchors.leftMargin: 15 * sc
                    anchors.left: parent.left
                    color: 'white'
                }
                Label {
                    text: modelData.deviceAddress
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 15 * sc
                    anchors.rightMargin: 15 * sc
                    anchors.right: parent.right
                    color: 'white'
                }
            }
        }
        onOpened: {
            if(!deviceFinder.scanning)
                deviceFinder.startSearch()
        }
        //        footer: Item{
        //            width: parent.width;
        //            height: 150 * sc
        //            RoundedButton {
        //                anchors.fill: parent
        //                anchors.margins: 20 * sc
        //                height: 50 * sc
        //                enabled: !deviceFinder.scanning
        //                onClicked: deviceFinder.startSearch()
        //                text: qsTr('START SEARCH')
        //            }
        //        }
    }
    // Диалог подтверждения удаления тренировки из базы данных
    MyDialog {
        id: dialogDelete
        caption: 'Удаление'
        Label{
            anchors.fill: parent
            anchors.margins: 50 * sc
            height: 110 * sc
            width: parent.width
            color: 'white'
            font.capitalization: Font.AllUppercase
            font.pixelSize: 36 * sc
            font.weight: Font.Black
            wrapMode: Text.WordWrap
            text: qsTr('Вы действительно хотите удалить тренировку?')
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        footer: Item{
            width: parent.width;
            height: 100 * sc
            Button {
                anchors.fill: parent
                anchors.margins: 20 * sc
                height: 50 * sc
                enabled: !deviceFinder.scanning
                onClicked: dialogDelete.accept()
                text: qsTr('Да')
            }
        }
        onAccepted: {
            console.log('Ok clicked')
            myModel.updateModel()
            database.removeRecord(myModel.getId(journal.listView.currentIndex))
            myModel.updateModel();  // Обновляем модель данных
        }
    }
    // Для отладки BT соединения
    Rectangle {
        id: msg
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 130 * sc
        color: hasError ? '#BA3F62' : '#3FBA62'
        visible: hasError || hasInfo
        Label {
            id: error
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            fontSizeMode: Text.Fit
            color: '#ffffff'
            text: hasError ? errorMessage : infoMessage
        }
    }
}
