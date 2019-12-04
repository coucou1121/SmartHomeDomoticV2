import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Styles 1.2

PageBackground
{
    width: 200
    height: 100

    MultiButton {
        id: multiButton
        x: 0
        y: 53
        width: 96
        height: 44
        Material.color: Material.Orange


   }

    Button {
        id: button
        anchors.rightMargin: 104
        anchors.bottomMargin: 53
        anchors.fill: parent
        background : "green"

        onClicked:
        {
            logo.visible = logo.visible == true ? false : true
        }

        Image {
            id: logo
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            source: "Picture/lightBulbOff.png"
        }

        style: ButtonStyle {
                    background: Item {
                        Canvas {
                            anchors.fill: parent

                            onPaint: {
                                var ctx = getContext("2d");
                                ctx.reset();

                                ctx.beginPath();
                                ctx.lineWidth = height * 0.1;
                                ctx.roundedRect(ctx.lineWidth / 2, ctx.lineWidth / 2,
                                    width - ctx.lineWidth, height - ctx.lineWidth, button.radius, button.radius);
                                ctx.strokeStyle = "grey";
                                ctx.stroke();
                                ctx.fillStyle = "#00c0f5";
                                ctx.fill();
                            }
                        }
                    }

                    label: Label {
                        text: button.text
                        color: "white"
                        font.pixelSize: button.height * 0.5
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
    }


}

/*##^## Designer {
    D{i:3;anchors_height:65;anchors_width:63;anchors_x:48;anchors_y:0}D{i:2;anchors_height:52;anchors_width:119;anchors_x:22;anchors_y:24}
}
 ##^##*/
