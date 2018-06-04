import QtGraphicalEffects 1.0
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    background: Item {}
    property ListView listView: listView

    Component {
        id: contents
        Stats {}
    }

    function showLastTraining(){
        stackView.pop(initialItem)
        listView.currentIndex = 0
        listView.currentIndex = myModel.count() - 1
        stack.push(contents)
    }

    function deleteItem(index){
        myModel.updateModel()
        database.removeRecord(myModel.getId(index))
        myModel.updateModel();  // Обновляем модель данных
    }


    StackView{
        id: stack
        anchors.fill: parent
        Component.onCompleted: stackView = stack
        initialItem: Page {
            id: initialItem
            background: Item{}
            header: Label{
                height: 110 * sc
                width: parent.width
                color: 'white'
                font.capitalization: Font.AllUppercase
                font.pixelSize: 36 * sc
                font.weight: Font.Black
                text: qsTr('Журнал тренировок')
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            ListView {
                id: listView
                anchors.fill: parent
                anchors.leftMargin: 100 * sc
                anchors.rightMargin: 100 * sc
                clip: true
                model: myModel
                delegate: SwipeDelegate {
                    id: swipeDelegate
                    text: '№'+ myModel.getId(index) + date.toLocaleString(locale, ' — d.MM.yyyy — hh:mm')
                    height: 93 * sc
                    width: parent.width
                    font.pixelSize: 28 * sc
                    contentItem: Text {
                        text: swipeDelegate.text
                        font: swipeDelegate.font
                        //color: swipeDelegate.enabled ? (control.down ? "#17a81a" : "#21be2b") : "#bdbebf"
                        color: 'white'
                        elide: Text.ElideRight
                        verticalAlignment: Text.AlignVCenter
                        Behavior on x {
                            enabled: !swipeDelegate.down
                            NumberAnimation {
                                easing.type: Easing.InOutCubic
                                duration: 400
                            }
                        }
                        Image {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                            anchors.rightMargin: /*100*/10 * sc
                            height: 58 * sc
                            width: 97 * sc
                            fillMode: Image.PreserveAspectFit
                            source: type ? 'images/type2.png' : 'images/type1.png'
                        }
                    }
                    background: Item {}
                    ListView.onRemove: SequentialAnimation {
                        PropertyAction {
                            target: swipeDelegate
                            property: "ListView.delayRemove"
                            value: true
                        }
                        NumberAnimation {
                            target: swipeDelegate
                            property: "height"
                            to: 0
                            easing.type: Easing.InOutQuad
                        }
                        PropertyAction {
                            target: swipeDelegate
                            property: "ListView.delayRemove"
                            value: false
                        }
                    }
                    swipe.right: Label {
                        opacity: -swipeDelegate.swipe.position
                        id: deleteLabel
                        text: qsTr("Удалить")
                        color: "white"
                        font: swipeDelegate.font
                        verticalAlignment: Label.AlignVCenter
                        padding: 12 * sc
                        height: parent.height
                        anchors.right: parent.right
                        //SwipeDelegate.onClicked: deleteItem(index)
                        background: Rectangle {
                            color: deleteLabel.SwipeDelegate.pressed ? Qt.darker("tomato", 1.1) : "tomato"
                            radius: 10 * sc
                        }
                        MouseArea{
                            anchors.fill: parent
                            enabled: -swipeDelegate.swipe.position > 0.9
                            onClicked: deleteItem(index)
                            onPressed: vibration.on(10)
                        }
                    }
                    onClicked: {
                        listView.currentIndex = index
                        stack.push(contents)
                    }
                    onPressed: vibration.on(10)
//                    states: State {
//                        when: pressed
//                        PropertyChanges { target: swipeDelegate; scale: 0.9}
//                    }
//                    transitions: Transition {
//                        NumberAnimation { properties: 'scale'; easing.type: Easing.InOutQuad; duration: 150 }
//                    }
                }
                ScrollBar.vertical: ScrollBar {}
                remove: Transition {
                    ParallelAnimation {
                        NumberAnimation { property: 'opacity'; to: 0; duration: 1000 }
                        NumberAnimation { properties: 'x,y'; to: 100; duration: 1000 }
                    }
                }
            }
        }
        pushEnter: Transition { PropertyAnimation { property: 'opacity'; from: 0; to:1; duration: 200; } }
        pushExit: Transition { PropertyAnimation { property: 'opacity'; from: 1; to:0; duration: 200; } }
        popEnter: Transition { PropertyAnimation { property: 'opacity'; from: 0; to:1; duration: 200 } }
        popExit: Transition { PropertyAnimation { property: 'opacity'; from: 1; to:0; duration: 200 } }
    }
}
