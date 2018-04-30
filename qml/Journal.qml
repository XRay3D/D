import QtGraphicalEffects 1.0
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    background: Item{}
    property ListView listView: listView

    Component {
        id: contents
        Stats{
        }
    }

    function showLastTraining(){
        if(!debug){//debug
            stackView.pop(initialItem)
            listView.currentIndex = 0
            listView.currentIndex = myModel.count() - 1
        }
        stack.push(contents)
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
                model: myModel
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
                        text: '№'+ myModel.getId(index)/*(index + 1)*/+ currentDate.toLocaleString(locale, ' — d.MM.yyyy — hh:mm')
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
                        property bool skip: true
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: {
                            if(skip){
                                listView.currentIndex = index
                                stack.push(contents)
                            }
                            skip = true
                        }
                        Timer{
                            id: timer
                            interval: 250; running: area.pressed; repeat: false
                            onTriggered:{
                                area.skip = false
                                dialogDelete.open()
                            }
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
}
