import QtQuick 2.2

Rectangle{
    color: "#515151"
    border.width: 1
    gradient: Gradient {
            GradientStop { position: 0.0; color: "#8E8E8E" }
            GradientStop { position: 1.0; color: "#313131" }
        }
    height:20
    width: parent.width
    Text {
        text: styleData.value
        anchors.centerIn:parent
        color:"white"
        font.family: "黑体"
        font.pointSize: 12
    }
}
