import QtQuick 2.2

 Rectangle
 {
     id:content
     width: 500
     height: 500
     color:"white"

     property int current: 0
     function setCurrent(curIndex)
     {
         content.children[curIndex].state="active"
         content.children[current].state="hide"
         current = curIndex
     }

     MainWidget
     {
         Rectangle
         {
             anchors.fill: parent
             anchors.margins: 50
             color:"#99FF0000"
             Text
             {
                 font.pointSize: 50
                 font.family: "微软雅黑"
                 color:"#FFFFFF"
                 anchors.centerIn: parent
                 text:"十步杀一人"
             }
         }
     }
     MainWidget
     {
         Rectangle
         {
             anchors.fill: parent
             anchors.margins: 50
             color:"#BB00FF00"
             Text
             {
                 font.pointSize: 100
                 font.family: "微软雅黑"
                 color:"#FFFFFF"
                 anchors.centerIn: parent
                 text:"，"
             }
         }
     }
     MainWidget
     {
         Rectangle
         {
             anchors.fill: parent
             anchors.margins: 50
             color:"#990000FF"
             Text
             {
                 font.pointSize: 50
                 font.family: "微软雅黑"
                 color:"#FFFFFF"
                 anchors.centerIn: parent
                 text:"千里不留行"
             }
         }
     }
     MainWidget
     {
         Rectangle
         {
             anchors.fill: parent
             anchors.margins: 50
             color:"#FFFF9900"
             Text
             {
                 font.pointSize: 50
                 font.family: "微软雅黑"
                 color:"#FFFFFF"
                 anchors.centerIn: parent
                 text:"。"
             }
         }
     }
     MainWidget
     {
         Rectangle
         {
             anchors.fill: parent
             anchors.margins: 50
             color:"#FF00FFFF"
             Text
             {
                 font.pointSize: 50
                 font.family: "微软雅黑"
                 color:"#FFFFFF"
                 anchors.centerIn: parent
                 text:"事了拂衣去"
             }
         }
     }
     MainWidget
     {
         Rectangle
         {
             anchors.fill: parent
             anchors.margins: 50
             color:"#99FF00FF"
             Text
             {
                 font.pointSize: 50
                 font.family: "微软雅黑"
                 color:"#FFFFFF"
                 anchors.centerIn: parent
                 text:"，"
             }
         }
     }
     MainWidget
     {
         Rectangle
         {
             anchors.fill: parent
             anchors.margins: 50
             color:"#FFC0C0C0"
             Text
             {
                 font.pointSize: 50
                 font.family: "微软雅黑"
                 color:"#FFFFFF"
                 anchors.centerIn: parent
                 text:"深藏功与名。"
             }
         }
     }
 }
