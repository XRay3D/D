import QtGraphicalEffects 1.0
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3

Page {
    background: Item{}
    //    property int type_
    //    property string date_
    //    property string timeWithStimulation_
    //    property string timeWithoutStimulation_
    //    property string timePause_
    //    property int avgStimulationAmplitude_
    //    property int avgStepLength_
    //    property int avgStepFrequency_
    //    property int avgSpeedWithoutStimulation_
    //    property int avgSpeedWithStimulation_
    //    property int totalDistance_
    //    property int totalStimulationDistance_
    function showLastTraining(){
        //                            dialogDelete.open()
        //        listView.currentIndex= listView.model.count - 1
        console.log('onClicked', myModel.count())
        //                            type_ = type
        //                            date_ = currentDate.toLocaleString(locale, 'd.MM.yyyy — hh:mm')
        //                            timeWithStimulation_ = timeWithStimulation.toLocaleTimeString(locale, 'hh:mm')
        //                            timeWithoutStimulation_ = timeWithoutStimulation.toLocaleTimeString(locale, 'hh:mm')
        //                            timePause_ = timePause.toLocaleString(locale,'hh:mm')
        //                            avgStimulationAmplitude_ = avgStimulationAmplitude
        //                            avgStepLength_ = avgStepLength
        //                            avgStepFrequency_ = avgStepFrequency
        //                            avgSpeedWithoutStimulation_ = avgSpeedWithoutStimulation
        //                            avgSpeedWithStimulation_ = avgSpeedWithStimulation
        //                            totalDistance_ = totalDistance
        //                            totalStimulationDistance_ = totalStimulationDistance
        stack.push(contents)
    }
    Component {
        id: contents
        Item {
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
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        y:22 * sc
                        color: 'white'
                        font.bold: true
                        font.weight: Font.Black
                        font.pixelSize: 35 * sc
                        text: qsTr('ТРЕНИРОВКА №') + (listView.currentIndex + 1)
                    }
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        y:76 * sc
                        color: 'white'
                        font.pixelSize: 45 * sc
                        text: date_
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
                        text: type_ ? qsTr('Коньковый  ход') : qsTr('Классический ход')
                    }
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        y:35 * sc
                        color: 'white'
                        font.pixelSize: 90 * sc
                        text: timeWithStimulation_
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
                        text: timeWithoutStimulation_
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
                        text: timeWithStimulation_
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
                        text: timePause_
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
                        text: timeWithStimulation_
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
                                avgStimulationAmplitude_,
                                avgStepLength_,
                                avgStepFrequency_ ,
                                avgSpeedWithoutStimulation_,
                                avgSpeedWithStimulation_,
                                totalDistance_,
                                totalStimulationDistance_
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
            MouseArea{
                id: area
                anchors.fill: parent
                onClicked: {
                    if(stack.depth > 1) stack.pop()
                }
            }
        }
    }
    StackView{
        id: stack
        anchors.fill: parent
        Component.onCompleted: stackView = stack
        initialItem: Page {
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
                MouseArea
                {
                    anchors.fill: parent
                    // Вносим новую запись в базу данных
                    onClicked: {
                        database.inserIntoTable()
                        myModel.updateModel() // И обновляем модель данных с новой записью
                    }
                }
            }
            ListView {
                id: listView
                anchors.fill: parent
                //anchors.topMargin: 85 * sc
                anchors.leftMargin: 103 * sc
                anchors.rightMargin: 103 * sc
                clip: true
                model: myModel//trainingModel
                delegate: Item {
                    id: delegate
                    height: 93 * sc
                    width: parent.width
                    property var locale: Qt.locale()
                    property date currentDate: date
                    Label {
                        anchors.fill: parent
                        color: 'white'
                        font.pixelSize: 24 * sc
                        verticalAlignment: Text.AlignVCenter
                        text: '№'+ (index + 1) + currentDate.toLocaleString(locale, ' — d.MM.yyyy — hh:mm')
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
                    MouseArea{
                        id: area
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            //                            dialogDelete.open()
                            console.log('onClicked', index)
                            listView.currentIndex = index
                            //                            type_ = type
                            //                            date_ = currentDate.toLocaleString(locale, 'd.MM.yyyy — hh:mm')
                            //                            timeWithStimulation_ = timeWithStimulation.toLocaleTimeString(locale, 'hh:mm')
                            //                            timeWithoutStimulation_ = timeWithoutStimulation.toLocaleTimeString(locale, 'hh:mm')
                            //                            timePause_ = timePause.toLocaleString(locale,'hh:mm')
                            //                            avgStimulationAmplitude_ = avgStimulationAmplitude
                            //                            avgStepLength_ = avgStepLength
                            //                            avgStepFrequency_ = avgStepFrequency
                            //                            avgSpeedWithoutStimulation_ = avgSpeedWithoutStimulation
                            //                            avgSpeedWithStimulation_ = avgSpeedWithStimulation
                            //                            totalDistance_ = totalDistance
                            //                            totalStimulationDistance_ = totalStimulationDistance
                            stack.push(contents)
                        }
                    }
                    states: State {
                        when: area.pressed
                        PropertyChanges { target: delegate; scale: 0.9}
                    }
                    transitions: Transition {
                        NumberAnimation { properties: 'scale'; easing.type: Easing.InOutQuad; duration: 150 }
                    }
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

    // Диалог подтверждения удаления строки из базы данных
    Dialog {
        id: dialogDelete
        title: 'Title'
        standardButtons: Dialog.Ok | Dialog.Cancel

        onRejected: console.log('Cancel clicked')
        onAccepted: {
            console.log('Ok clicked')
            database.removeRecord(myModel.getId(listView.currentIndex))
            myModel.updateModel();  // Обновляем модель данных
        }
    }
}
