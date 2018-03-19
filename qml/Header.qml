import QtQuick 2.9
import QtQuick.Controls 2.2
ToolBar {
    background: Rectangle{
        id: back
        color: '#252525'
    }
    Image {
        anchors.left: parent.left
        anchors.leftMargin: 30 * sc
        anchors.verticalCenter: parent.verticalCenter
        height:48 * sc
        opacity: 0.74
        source:"Header_images/dems.png"
        width:247 * sc
    }
    Image {
        anchors.rightMargin: 30 * sc
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        height:94 * sc
        source:"Header_images/roc.png"
        width:161 * sc
    }

    // Объявляем свойства, которые будут хранить позицию зажатия курсора мыши
    // Центральная область для перемещения окна приложения
    // Здесь уже потребуется использовать положение как по оси X, так и по оси Y
    property int previousX
    property int previousY
    MouseArea {
        // anchors {
        // top: topArea.bottom
        // bottom: bottomArea.top
        // left: leftArea.right
        // right: rightArea.left
        // }
        anchors.fill: parent

        onPressed: {
            previousX = mouseX
            previousY = mouseY
        }

        onMouseXChanged: {
            var dx = mouseX - previousX
            window.setX(window.x + dx)
        }

        onMouseYChanged: {
            var dy = mouseY - previousY
            window.setY(window.y + dy)
        }
    }
}
