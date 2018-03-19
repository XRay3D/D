import QtQuick 2.9
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.2
//import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0
import 'Training'

ApplicationWindow {
    visible: true
    id: window

    FontLoader { id: font1; source: "../fonts/HelveticaNeueCyr-Bold.ttf" }
    FontLoader { id: font2; source: '../fonts/HelveticaNeueCyr-Heavy.ttf' }
    FontLoader { id: font3; source: '../fonts/HelveticaNeueCyr-Light.ttf' }
    FontLoader { id: font4; source: '../fonts/HelveticaNeueCyr-Medium.ttf' }
    FontLoader { id: font5; source: '../fonts/HelveticaNeueCyr-Roman.ttf' }
    FontLoader { id: font6; source: '../fonts/HelveticaNeueCyr-Thin.ttf' }

    font.family: 'HelveticaNeueCyr'

    Connections {
        target: GUI
        onBack: {
            console.log("back")
            if(stackView.depth === 2)
                stackView.pop()
        }
    }

    //flags: Qt.FramelessWindowHint // Отключаем обрамление окна

    width: 750 * 0.7
    height: (1334 - 36) * 0.7
    property double sc: width / 750
    property bool trainingType: false
    property int pageIndex: 0
    property StackView stackView

    Settings {
        id: settings
        property alias x: window.x
        property alias y: window.y
        property string style: "Material"
        property bool type

    }

    Component.onDestruction: {
        console.log('onDestruction')
        settings.type = trainingType
    }

    Component.onCompleted: {
        console.log('onCompleted')
        trainingType = settings.type
    }

    background:Rectangle{
        color: 'black'
    }

    Item {
        id: mf
        anchors.fill: parent
        Image {
            anchors.fill: parent
            id :image
            source:"images/background.png"
        }
        opacity: 0.0
        OpacityAnimator on opacity{
            from: 0; to: 1; running: true
        }
        SwipeView {
            //            Component.onCompleted: {
            //                currentIndex = 2
            //            }
            id: swipeView
            width: parent.width
            height: 925 * sc
            currentIndex: pageIndex
            interactive: false
            TrainingPage { id: trainingPage }
            Journal { id: journal }
            AppSettings { id: appSettings }
        }
        Item {
            anchors.fill: parent
            anchors.topMargin: swipeView.height
            Image {
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                //battery
                opacity: 0.3
                width:456 * sc
                height:33 * sc
                source:"images/battery.png"
            }
            Image {
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                //bluetootch
                opacity: 0.3
                width:33 * sc
                height:65 * sc
                source:"images/bluetootch.png"
            }
            Rectangle {
                //splitter2
                opacity: 0.3
                x:103 * sc;
                width: 544 * sc
                height: 2
            }
        }
    }

    // Loader {
    //     id: loader
    //     anchors.fill: parent
    //     sourceComponent: MainForm/*Splash*/{
    //     }
    // }
    // Timer{
    // interval: 100; running: true; repeat: false
    // onTriggered:{
    // loader.setSource('MainForm.qml')
    // window.header.visible = true
    // window.footer.visible = true
    // }
    // }

    Shortcut {
        sequence: 'Esc'
        context: Qt.ApplicationShortcut
        onActivated: Qt.quit()
    }

    header: Header{
        // visible: false
        height: 130 * sc //0
        //        states: State {
        //            when: visible
        //            PropertyChanges { target: window.header; height: 130 * sc }
        //        }
        //        transitions: Transition {
        //            NumberAnimation { properties: "height"; easing.type: Easing.InOutQuad }
        //        }
    }

    footer: Footer{
        // visible: false
        height: 148 * sc// 0
        //        states: State {
        //            when: visible
        //            PropertyChanges { target: window.footer; height: 148 * sc }
        //        }
        //        transitions: Transition {
        //            NumberAnimation { properties: "height"; easing.type: Easing.InOutQuad }
        //        }
    }

    DropShadow {
        anchors.fill: footer
        verticalOffset: 0
        radius: 8.0
        samples: 17
        color: "#80000000"
        source: footer
    }
    DropShadow {
        anchors.fill: header
        verticalOffset: 0
        radius: 8.0
        samples: 17
        color: "#80000000"
        source: header
    }

    // Dialog {
    // width: window.width-100
    // height: window.height-100
    // x: 50
    // //background: Rectangle{color: 'transparent'}
    // id: dialog
    // modal: true
    // standardButtons: Dialog.Ok
    // ColumnLayout {
    // anchors.fill: parent
    // CheckBox { text: qsTr("E-mail") }
    // CheckBox { text: qsTr("Calendar") }
    // CheckBox { text: qsTr("Contacts") }
    // }
    // }

    Keys.onReleased: {
        console.log(event.key,'key')
        event.accepted = true
        if (event.key === Qt.Key_Back) {
            console.log("Back button captured - wunderbar !")
            event.accepted = true
        }
    }
    Dialog{
        x: 100 * sc
        width: parent.width - 200 * sc
        height:parent.height
        id: aboutDialog
        //        ScrollView {
        //            width: 200
        //            height: 200
        //            clip: true
        //            ScrollBar.horizontal.interactive: true
        //                  ScrollBar.vertical.interactive: true
        //            Label {
        //                text: "ABC"
        //                font.pixelSize: 224
        //            }
        //        }
        header:Label{}
        Flickable{
            anchors.fill: parent
            clip: true

            contentHeight: label.height
            ScrollBar.vertical: ScrollBar { }

            flickableDirection: Flickable.VerticalFlick


            Label {
                id: label
                //                anchors.fill: parent
                width: parent.width
                color: 'white'
                wrapMode: Text.WordWrap
                text:
                    ":1234567890
Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt.
Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem."
                font.pixelSize: 24 * sc
            }
        }
        title: qsTr("About")
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: console.log("Ok clicked")
        onRejected: console.log("Cancel clicked")
        contentItem: Item{}
        footer: Item{}
        background: Rectangle{
            color: '#28343e'
        }
    }
}
