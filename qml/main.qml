import QtQuick 2.9
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.2
//import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0
import 'Training'
import Shared 1.0 //?
ApplicationWindow {
    visible: true
    id: window

    /////////////////////////////////////////////////////////
    property string errorMessage: deviceFinder.error
    property string infoMessage: deviceFinder.info
    property real messageHeight: msg.height
    property bool hasError: errorMessage != ""
    property bool hasInfo: infoMessage != ""

    Rectangle {
        id: msg
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 100 * sc
        color: hasError ? "#ba3f62" : "#3fba62"
        visible: hasError || hasInfo

        Text {
            id: error
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            minimumPixelSize: 5
            //font.pixelSize: GameSettings.smallFontSize
            fontSizeMode: Text.Fit
            color: "#ffffff"
            text: hasError ? errorMessage : infoMessage
        }
    }
    ////////////////////////////////////////////

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

    //    Image {
    //        anchors.fill: parent
    //        source: 'images/Splash.png'
    //        opacity: 1.0
    //        OpacityAnimator on opacity{
    //            from: 1; to: 0; running: true
    //        }
    //    }
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
            Rectangle {
                //splitter2
                opacity: 0.3
                x: 103 * sc;
                y: swipeView.height
                width: 544 * sc
                height: 2
            }
            RowLayout{
                //opacity: 0.3
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
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
                Image {
                    Layout.fillWidth: true
                    Layout.minimumHeight: 65 * sc
                    Layout.maximumHeight: 65 * sc
                    fillMode: Image.PreserveAspectFit
                    source:"images/bluetootch.png"
                }
                Battery{
                    id: rightBattery
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
                    width: 30 * sc
                    height: 30 * sc
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
                    // anchors.fill: parent
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

    Dialog{
        id: btDialog
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
            id:btDialogPage
            anchors.fill: parent
            background: Item {}
            header: Label{
                text: qsTr('FOUND DEVICES')
                color:'#28343e'
                font.pixelSize: 36 * sc
                height: 73 * sc
                Image {
                    width: 30 * sc
                    height: 30 * sc
                    anchors.top: parent.top
                    anchors.right: parent.right
                    source: "images/close.png"
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: btDialog.reject()
                }
            }
            Rectangle{
                anchors.fill: parent
                color:'#28343e'
                radius: 10 * sc

                Rectangle {
                    id: viewContainer
                    anchors.top: parent.top
                    //                    anchors.bottom:
                    // only BlueZ platform has address type selection
                    //                        connectionHandler.requiresAddressType ? addressTypeButton.top : searchButton.top
                    // anchors.topMargin: GameSettings.fieldMargin + messageHeight
                    // anchors.bottomMargin: GameSettings.fieldMargin
                    anchors.horizontalCenter: parent.horizontalCenter
                    // width: parent.width - GameSettings.fieldMargin*2
                    // color: GameSettings.viewColor
                    // radius: GameSettings.buttonRadius



                    ListView {
                        id: devices
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        //anchors.left: parent.left
                        //anchors.right: parent.right
                        //anchors.bottom: parent.bottom
                        //anchors.top: title.bottom
                        model: deviceFinder.devices
                        clip: true
                        delegate: Rectangle {
                            id: box
                            height: 100 * sc
                            width: parent.width
                            // color: index % 2 === 0 ? GameSettings.delegate1Color : GameSettings.delegate2Color

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    deviceFinder.connectToService(modelData.deviceAddress);
                                    app.showPage("Measure.qml")
                                }
                            }

                            Text {
                                id: device
                                // font.pixelSize: GameSettings.smallFontSize
                                text: modelData.deviceName
                                anchors.top: parent.top
                                anchors.topMargin: parent.height * 0.1
                                anchors.leftMargin: parent.height * 0.1
                                anchors.left: parent.left
                                // color: GameSettings.textColor
                            }

                            Text {
                                id: deviceAddress
                                // font.pixelSize: GameSettings.smallFontSize
                                text: modelData.deviceAddress
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: parent.height * 0.1
                                anchors.rightMargin: parent.height * 0.1
                                anchors.right: parent.right
                                // color: Qt.darker(GameSettings.textColor)
                            }
                        }
                    }
                }
            }
            footer: Button {
                id: searchButton
                Layout.fillWidth: true
                //anchors.horizontalCenter: parent.horizontalCenter
                //anchors.bottom: parent.bottom
                // anchors.bottomMargin: GameSettings.fieldMargin
                //width: viewContainer.width
                // height: GameSettings.fieldHeight
                enabled: !deviceFinder.scanning
                onClicked: deviceFinder.startSearch()
                text: qsTr("START SEARCH")
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

    //    Dialog{
    //        id: bt
    //        width: window.width
    //        height:window.height
    //        padding:  100 * sc
    //        modal: true
    //        standardButtons: Dialog.NoButton
    //        onAccepted: console.log("Ok clicked")
    //        onRejected: console.log("Cancel clicked")
    //        footer: Item {}
    //        contentItem: Item {}

    //        Rectangle {
    //            id: viewContainer
    //            anchors.top: parent.top
    //            anchors.bottom:
    //                // only BlueZ platform has address type selection
    //                connectionHandler.requiresAddressType ? addressTypeButton.top : searchButton.top
    //            // anchors.topMargin: GameSettings.fieldMargin + messageHeight
    //            // anchors.bottomMargin: GameSettings.fieldMargin
    //            anchors.horizontalCenter: parent.horizontalCenter
    //            // width: parent.width - GameSettings.fieldMargin*2
    //            // color: GameSettings.viewColor
    //            // radius: GameSettings.buttonRadius


    //            Text {
    //                id: title
    //                width: parent.width
    //                // height: GameSettings.fieldHeight
    //                horizontalAlignment: Text.AlignHCenter
    //                verticalAlignment: Text.AlignVCenter
    //                // color: GameSettings.textColor
    //                // font.pixelSize: GameSettings.mediumFontSize
    //                text: qsTr("FOUND DEVICES")

    //                // BottomLine {
    //                // height: 1;
    //                // width: parent.width
    //                // color: "#898989"
    //                // }
    //            }


    //            ListView {
    //                id: devices
    //                anchors.left: parent.left
    //                anchors.right: parent.right
    //                anchors.bottom: parent.bottom
    //                anchors.top: title.bottom
    //                model: deviceFinder.devices
    //                clip: true

    //                delegate: Rectangle {
    //                    id: box
    //                    // height:GameSettings.fieldHeight * 1.2
    //                    width: parent.width
    //                    // color: index % 2 === 0 ? GameSettings.delegate1Color : GameSettings.delegate2Color

    //                    MouseArea {
    //                        anchors.fill: parent
    //                        onClicked: {
    //                            deviceFinder.connectToService(modelData.deviceAddress);
    //                            app.showPage("Measure.qml")
    //                        }
    //                    }

    //                    Text {
    //                        id: device
    //                        // font.pixelSize: GameSettings.smallFontSize
    //                        text: modelData.deviceName
    //                        anchors.top: parent.top
    //                        anchors.topMargin: parent.height * 0.1
    //                        anchors.leftMargin: parent.height * 0.1
    //                        anchors.left: parent.left
    //                        // color: GameSettings.textColor
    //                    }

    //                    Text {
    //                        id: deviceAddress
    //                        // font.pixelSize: GameSettings.smallFontSize
    //                        text: modelData.deviceAddress
    //                        anchors.bottom: parent.bottom
    //                        anchors.bottomMargin: parent.height * 0.1
    //                        anchors.rightMargin: parent.height * 0.1
    //                        anchors.right: parent.right
    //                        // color: Qt.darker(GameSettings.textColor)
    //                    }
    //                }
    //            }
    //        }

    //        Button {

    //            id: addressTypeButton
    //            anchors.horizontalCenter: parent.horizontalCenter
    //            anchors.bottom: searchButton.top
    //            // anchors.bottomMargin: GameSettings.fieldMargin * 0.5
    //            width: viewContainer.width
    //            //height: GameSettings.fieldHeight
    //            visible: connectionHandler.requiresAddressType // only required on BlueZ
    //            state: "public"
    //            onClicked: state == "public" ? state = "random" : state = "public"

    //            states: [
    //                State {
    //                    name: "public"
    //                    PropertyChanges { target: addressTypeText; text: qsTr("Public Address") }
    //                    PropertyChanges { target: deviceHandler; addressType: AddressType.PublicAddress }
    //                },
    //                State {
    //                    name: "random"
    //                    PropertyChanges { target: addressTypeText; text: qsTr("Random Address") }
    //                    PropertyChanges { target: deviceHandler; addressType: AddressType.RandomAddress }
    //                }
    //            ]

    //            Text {
    //                id: addressTypeText
    //                anchors.centerIn: parent
    //                // font.pixelSize: GameSettings.tinyFontSize
    //                // color: GameSettings.textColor
    //            }
    //        }

    //        Button {
    //            id: searchButton
    //            anchors.horizontalCenter: parent.horizontalCenter
    //            anchors.bottom: parent.bottom
    //            // anchors.bottomMargin: GameSettings.fieldMargin
    //            width: viewContainer.width
    //            // height: GameSettings.fieldHeight
    //            enabled: !deviceFinder.scanning
    //            onClicked: deviceFinder.startSearch()

    //            Text {
    //                anchors.centerIn: parent
    //                // font.pixelSize: GameSettings.tinyFontSize
    //                text: qsTr("START SEARCH")
    //                // color: searchButton.enabled ? GameSettings.textColor : GameSettings.disabledTextColor
    //            }
    //        }
    //    }
}
