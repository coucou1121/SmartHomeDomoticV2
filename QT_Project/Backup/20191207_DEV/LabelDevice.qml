import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

Label
{    
    id: label
    width: 200
    height: 50
    color:  Material.color(Material.Purple)
    text: "Text"
    clip: true
    rotation: 0
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
    font.bold: false
    font.pointSize: 22
}
