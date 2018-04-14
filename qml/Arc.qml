import QtQuick 2.9
import QtQuick.Templates 2.2
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

Control {
    id: arc

    property int value: 0
    property double minValue: 0
    property double maxValue: 100
    property string suffix: ''
    property string name: ''

    Component.onCompleted: update()
    font.family: 'HelveticaNeueCyr'
    font.pixelSize: 26 * sc

    Label {
        id: max
        //font.family: 'HelveticaNeueCyr'
        anchors.right: arc.right
        anchors.top: arc.top
        color: 'white'
        height: arc.height / 5
        horizontalAlignment: Text.AlignRight
        text: maxValue + suffix
        verticalAlignment: Text.AlignBottom
        width: arc.height / 4
    }

    Label {
        id: min
        anchors.left: arc.left
        anchors.top: arc.top
        color: 'white'
        height: arc.height / 5
        horizontalAlignment: Text.AlignLeft
        text: minValue + suffix
        verticalAlignment: Text.AlignBottom
        width: arc.height / 4
    }

    Label {
        id: vt
        anchors.bottomMargin: arc.height * 0.2
        anchors.fill: arc
        color: 'white'
        font.pixelSize: 60 * sc
        font.weight: Font.ExtraLight
        horizontalAlignment: Text.AlignHCenter
        text: value + suffix
        verticalAlignment: Text.AlignBottom
    }

    Label {
        anchors.bottomMargin: arc.height * 0.05
        anchors.fill: arc
        color: 'white'
        opacity: 0.7
        horizontalAlignment: Text.AlignHCenter
        text: name
        verticalAlignment: Text.AlignBottom
    }

    Rb{
        anchors.right: arc.right
        y: arc.height / 1.7
        plus: true
        onClicked: {
            if (value < 10) ++value
            arc.update()
        }
    }

    Rb{
        anchors.left: arc.left
        y: arc.height / 1.7
        onClicked: {
            if (value) --value
            arc.update()
        }
    }

    function update(){
        mycanvas.requestPaint()
        vt.text = (value * maxValue) / 10 + suffix
    }

    property double w: width - height / 3.5
    property double h: height / 5
    property double a: w
    property double b: Math.sqrt(h * h + w * w / 4)
    property double radius: (a * b * b) / (2 * h * w)
    property double a1: -Math.PI / 2 - Math.acos((radius - h) / radius)
    property double a2: Math.PI - a1
    property double a3: (Math.acos((radius - h) / radius) * 2) / 10
    property double a4: a1 + (Math.acos((radius - h) / radius) * 2) / 10 * value
    property double l: 0
    property double cx: width / 2
    property double cy: radius + height / 5

    Slider{
        id: slider
        width: w * 1.1
        height: h * 1.6
        x: (parent.width - width) / 2
        y: h * 0.7
        from: 0
        to: 10
        opacity: 0.0
        onValueChanged: {
            parent.value = value
            arc.update()
        }
    }

    Canvas {
        anchors.fill: arc
        property int i: 0
        onPaint: {
            var ctx = getContext('2d');
            ctx.clearRect(0, 0, width, height)
            ctx.strokeStyle = '#5e6168' //Qt.rgba(0, 0, 0, 1);
            ctx.lineWidth = 15 * sc
            ctx.lineCap = 'round'
            ctx.beginPath()
            ctx.arc(cx, cy, radius, a2, a1, false)
            ctx.stroke()
            ctx.lineWidth = 5 * sc
            for(i = 0; i < 10; ++i){
                if(i == 0 || i == 5)
                    l = 40 * sc
                else
                    l = 20 * sc
                ctx.beginPath()
                ctx.moveTo(Math.cos(a1 + a3 * i) * radius + cx, Math.sin(a1 + a3 * i) * radius + cy)
                ctx.lineTo(Math.cos(a1 + a3 * i) * (radius + l) + cx, Math.sin(a1 + a3 * i) * (radius + l) + cy)
                ctx.stroke()
            }
            l = 40 * sc
            ctx.beginPath()
            ctx.moveTo(Math.cos(a2) * radius + cx, Math.sin(a2) * radius + cy)
            ctx.lineTo(Math.cos(a2) * (radius + l) + cx, Math.sin(a2) * (radius + l) + cy)
            ctx.stroke()
        }

    }

    Canvas {
        id: mycanvas
        anchors.fill: arc
        onPaint: {
            var ctx = getContext('2d');
            ctx.clearRect(0, 0, width, height)
            ctx.strokeStyle = 'white'
            ctx.lineWidth = 15 * sc
            ctx.lineCap = 'round'
            ctx.beginPath()
            ctx.arc(cx, cy, radius, a4, a1, true)
            ctx.stroke()

            //            var gradient = ctx.createLinearGradient(0, 0, 100, 100);
            //            gradient.addColorStop(0.3, Qt.rgba(1, 0, 0, 1));
            //            gradient.addColorStop(0.7, 'rgba(0, 255, 255, 1');
        }
    }

    LinearGradient {
        visible: parent.visible
        anchors.fill: parent
        start: Qt.point(0, height * 0.2)
        end: Qt.point(0, height * 0.5)
        source: mycanvas
        gradient: Gradient {
            GradientStop { position: 0.0; color: 'red' }
            GradientStop { position: 1.0; color: 'black' }
        }
    }

    Image {
        id: handle
        x: Math.cos(a4) * radius + cx - arc.height / 8
        y: Math.sin(a4) * radius + cy - arc.height / 8
        width: 61 * sc
        height: 61 * sc
        source: 'images/handle.png'
        states: State {
            when: slider.pressed
            PropertyChanges { target: handle; scale: 0.8}
        }
        transitions: Transition {
            NumberAnimation { properties: 'scale'; easing.type: Easing.InOutQuad }
        }
    }



    // InnerShadow {
    // anchors.fill: arc
    // radius: 1.5 * sc
    // samples: 4
    //// horizontalOffset: -3 * sc
    // verticalOffset: -3 * sc
    // color: '#1F0000'
    // source: mycanvas
    // }

    // InnerShadow {
    // opacity: 0.4
    // anchors.fill: arc
    // radius: 1.5 * sc
    // samples: 4
    //// horizontalOffset: 3 * sc
    // verticalOffset: 3 * sc
    // color: 'white'
    // source: mycanvas
    // }
}
