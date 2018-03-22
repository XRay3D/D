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

    background:Rectangle { color: '#181f25' }

    FontLoader { id: font1; source: '../fonts/HelveticaNeueCyr-Bold.ttf' }
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
    }

    Image {
        anchors.fill: parent
        source: 'images/Splash.png'
        opacity: 1.0
        OpacityAnimator on opacity{
            from: 1; to: 0; running: true
        }
    }
    ColumnLayout{
        opacity: 0.0
        OpacityAnimator on opacity{
            from: 0; to: 1; running: true
        }
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
                source:"images/background.png"
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
        Footer{
            Layout.minimumHeight:  148 * sc //0
            Layout.maximumHeight:  148 * sc //0
            Layout.fillWidth: true
        }
    }

    Shortcut {
        sequence: 'Esc'
        context: Qt.ApplicationShortcut
        onActivated: Qt.quit()
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

    Dialog{
        id: aboutDialog
        width: window.width
        height:window.height
        padding:  100 * sc
        modal: true
        standardButtons: Dialog.NoButton
        onAccepted: console.log("Ok clicked")
        onRejected: console.log("Cancel clicked")
        footer: Item {}
        contentItem: Item {}
        Page{
            id:aboutDialogPage
            anchors.fill: parent
            background: Item {}
            header: Label{
                text: qsTr('О продукте')
                color:'#28343e'
                font.pixelSize: 36 * sc
                height: 73 * sc
                Image {
                    anchors.top: parent.top
                    anchors.right: parent.right
                    id: name
                    source: "images/close.png"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: aboutDialog.reject()
                }
            }
            Rectangle{
                id: back
                anchors.fill: parent
                color:'#28343e'
                radius: 10 * sc
            }
            Flickable{
                anchors.fill: parent
                anchors.margins: 50*sc
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
                    text: ":1234567890
    Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
    Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
    Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt.
    Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem.
    Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.
    Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
    Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt.
    Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem."
                    font.pixelSize: 24 * sc
                }
            }
        }
        background: FastBlur{
            anchors.fill: parent
            transparentBorder: false
            source: window.contentItem
            radius: 32
            Rectangle{
                anchors.fill: parent
                opacity: 0.7
                color: "#dadada"
            }
        }
    }
}
