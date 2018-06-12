import QtGraphicalEffects 1.0
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    background: Item {}
    property ListView listView: listView
    property string trainingData: ''
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

    function share(index){
        trainingData = 'Тренировка №'+ myModel.getId(index) + ' от ' + myModel.getDate(index) + '\r\n'
                + qsTr('Тип тренировки: ') + (myModel.getType(index) ? qsTr('Коньковый  ход') : qsTr('Классический ход')) + '\r\n'
                + qsTr('Без стимуляции: ') +myModel.getTimeWithoutStimulation(index) + '\r\n'
                + qsTr('C стимуляцией: ') + myModel.getTimeWithStimulation(index) + '\r\n'
                + qsTr('Отдых: ') + myModel.getTimeRest(index) + '\r\n'
                + qsTr('Время стимуляции: ') +  myModel.getTimeStimulation(index) + '\r\n'
                + qsTr('Средняя амплитуда стимуляции: ') + myModel.getAvgStimulationAmplitude(index) + qsTr('В\r\n')
                + qsTr('Средняя длина шага: ') + myModel.getAvgStepLength(index) + qsTr('м\r\n')
                + qsTr('Средняя частота движений: ') + myModel.getAvgStepFrequency(index) + qsTr('ш/с\r\n')
                + qsTr('Средняя скорость без стимуляции: ') + myModel.getAvgSpeedWithoutStimulation(index) + qsTr('м/с\r\n')
                + qsTr('Средняя скорость со стимуляцией: ') + myModel.getAvgSpeedWithStimulation(index) + qsTr('м/с\r\n')
                + qsTr('Общая дистанция: ') + myModel.getTotalDistance(index) + qsTr('м\r\n')
                + qsTr('Дистанция в режиме стимуляции: ') + myModel.getTotalStimulationDistance(index) + qsTr('м\r\n')
        shareUtils.share(trainingData,'')//"Qt","")
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
                    background: Item {}
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
//                    ListView.onRemove: SequentialAnimation {
//                        PropertyAction {
//                            target: swipeDelegate
//                            property: "ListView.delayRemove"
//                            value: true
//                        }
//                        NumberAnimation {
//                            target: swipeDelegate
//                            property: "height"
//                            to: 0
//                            easing.type: Easing.InOutQuad
//                        }
//                        PropertyAction {
//                            target: swipeDelegate
//                            property: "ListView.delayRemove"
//                            value: false
//                        }
//                    }
                    swipe.right: Label {
                        id: deleteLabel
                        opacity: -swipeDelegate.swipe.position
                        text: qsTr("Удалить")
                        color: "white"
                        font: swipeDelegate.font
                        verticalAlignment: Label.AlignVCenter
                        padding: 12 * sc
                        height: parent.height
                        anchors.right: parent.right
                        //SwipeDelegate.onClicked: deleteItem(index)
                        background: Rectangle {
                            color: deleteLabel.SwipeDelegate.pressed ? Qt.darker("#f44336", 1.1) : "#f44336"
                            radius: 10 * sc
                        }
                        MouseArea{
                            anchors.fill: parent
                            enabled: deleteLabel.opacity > 0.9
                            onClicked: {
                                //deleteItem(index)
                                listView.currentIndex = index
                                dialogDelete.open()
                            }
                            onPressed: feedback.on(20)
                        }

                        //shareUtils.share("Qt","")

                    }
                    swipe.left: Label {
                        id: shareLabel
                        opacity: swipeDelegate.swipe.position
                        text: qsTr("Поделится")
                        color: "white"
                        font: swipeDelegate.font
                        verticalAlignment: Label.AlignVCenter
                        padding: 12 * sc
                        height: parent.height
                        anchors.left: parent.left
                        //SwipeDelegate.onClicked: deleteItem(index)
                        background: Rectangle {
                            color: shareLabel.SwipeDelegate.pressed ? Qt.darker("#4CAF50", 1.1) : "#4CAF50"
                            radius: 10 * sc
                        }
                        MouseArea{
                            anchors.fill: parent
                            enabled: shareLabel.opacity > 0.9
                            onClicked: {
                                share(index)
                            }
                            onPressed: feedback.on(20)
                        }
                    }
                    onClicked: {
                        listView.currentIndex = index
                        stack.push(contents)
                    }
                    onPressed: feedback.on(20)
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
                onPressed: feedback.on(20)
            }
        }
        onAccepted: {
            console.log('Ok clicked')
            deleteItem(listView.currentIndex)
        }
    }
}
