import QtQuick 2.9
import QtQuick.Templates 2.2 as T
import QtQuick.Controls 2.2

Button {
    id: control

    background:Rectangle{
        anchors.fill: control
        color: enabled ? (control.pressed ? 'darkgray' : 'red') : 'gray'
        radius: 10 * sc
    }
    onPressed: feedback.on(20)
}
