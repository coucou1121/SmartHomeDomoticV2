import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

Rectangle
{
    id: rectangle

  width: 980
  height: 800
  color: "#222222"
  clip: true
  property alias title: label.text


  Label
  {
      id: label
      color: "#ffffff"
      text: ""
      anchors.right: parent.right
      anchors.left: parent.left
      horizontalAlignment: Text.AlignHCenter
      font.pixelSize: 24
  }
}

/*##^## Designer {
    D{i:1;anchors_x:0;anchors_y:0}
}
 ##^##*/
