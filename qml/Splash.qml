import QtQuick 2.9

Item {
 Image {
 anchors.fill: parent
 source: "Splash_images/background.png"
 fillMode: Image.PreserveAspectCrop
 }
 Image {
 anchors.horizontalCenter: parent.horizontalCenter
 y: 918 * sc
 height: 67 * sc
 width: 347 * sc
 source: "Splash_images/dems.png"
 }
 Image {
 anchors.horizontalCenter: parent.horizontalCenter
 y: 121 * sc
 height: 206 * sc
 width: 354 * sc
 source: "Splash_images/roc.png"
 }
 Text {
 anchors.horizontalCenter: parent.horizontalCenter
 y: 1187 * sc
 color: 'white'
 //font.family: 'HelveticaNeueCyr'
 font.pointSize: 19 * sc
 font.weight: Font.Black
 opacity: 0.8
 text: qsTr("Loading...")
 }
 Text {
 anchors.horizontalCenter: parent.horizontalCenter
 y: 1010* sc
 color: 'white'
 font.capitalization: Font.AllUppercase
 //font.family: 'HelveticaNeueCyr'
 font.pointSize: 15 * sc
 font.weight: Font.Black
 opacity: 0.7
 text: qsTr("Электромиостимуляция")
 }
}


