import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0

PageBackground {
    id: lightAndFansView
    width: 1480
    height: 800
    title: "lights and fans"

    GridLayout {
        columnSpacing: 0
        rowSpacing: 0
        anchors.rightMargin: 30
        anchors.leftMargin: 30
        anchors.bottomMargin: 30
        anchors.topMargin: 30
        anchors.fill: parent
        rows: 2
        columns: 2

        Frame {
            id: frameLoftMaster
            height: 300
            Layout.maximumWidth: 700
            Layout.minimumWidth: 700
            Layout.maximumHeight: 280
            Layout.minimumHeight: 280
            rightPadding: 10
            leftPadding: 10
            bottomPadding: 10
            topPadding: 10
            Layout.preferredHeight: 280
            Layout.preferredWidth: 700

            LabelDevice {
                id: labelDeviceLoft
                x: 0
                y: -11
                text: "Combles"
                horizontalAlignment: Text.AlignLeft
                anchors.right: parent.right
                anchors.rightMargin: 354
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.top
                anchors.bottomMargin: -25
                anchors.top: parent.top
                anchors.topMargin: -10
            }

            Frame {
                id: frameLoft
                height: 200
                anchors.topMargin: 30
                anchors.fill: parent
                leftPadding: 1
                rightPadding: 1
                bottomPadding: 1
                topPadding: 1

                Rectangle {
                    id: rectangleBackgroundLoft
                    color: "#3d3d3d"
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                }

                PushButtonLight {
                    id: pushButtonLightLoft
                    x: 242
                    y: 21
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightStep30
                    x: 338
                    y: 103
                    width: 80
                    height: 80
                    antialiasing: true
                }

            }

        }

        Frame {
            id: frame1erMaster
            height: 300
            Layout.maximumHeight: 280
            Layout.minimumHeight: 280
            Layout.maximumWidth: 700
            Layout.minimumWidth: 700
            rightPadding: 10
            bottomPadding: 10
            leftPadding: 10
            topPadding: 10
            Layout.preferredHeight: 280
            Layout.preferredWidth: 700

            Frame {
                id: frame1er
                x: 4
                y: 30
                width: 676
                height: 200
                rightPadding: 1
                bottomPadding: 1
                leftPadding: 1
                topPadding: 1
                enabled: true
                antialiasing: false
                Rectangle {
                    id: rectangleBackground1er
                    color: "#3d3d3d"
                    anchors.fill: parent
                    border.width: 0
                }

                PushButtonLight {
                    id: pushButtonLightRoomNordWest
                    x: 13
                    y: 11
                    width: 71
                    height: 80
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightRoomNordEst
                    x: 13
                    y: 109
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightOffice
                    x: 151
                    y: 58
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightSDB
                    x: 253
                    y: 11
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonFan {
                    id: pushButtonFanSDB1er
                    x: 406
                    y: 11
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightStep21
                    x: 296
                    y: 106
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightRoomEstNorth
                    x: 570
                    y: 16
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightRoomEstSouth
                    x: 529
                    y: 113
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightStep20
                    x: 411
                    y: 118
                    width: 80
                    height: 80
                    antialiasing: true
                }

                Rectangle {
                    id: rectangle20
                    x: 0
                    y: 93
                    width: 140
                    height: 10
                    color: "#ffffff"
                }

                Rectangle {
                    id: rectangle21
                    x: 130
                    y: 0
                    width: 10
                    height: 47
                    color: "#ffffff"
                }

                Rectangle {
                    id: rectangle22
                    x: 130
                    y: 149
                    width: 10
                    height: 49
                    color: "#ffffff"
                }

                Rectangle {
                    id: rectangle23
                    x: 237
                    y: -1
                    width: 10
                    height: 104
                    color: "#ffffff"
                }

                Rectangle {
                    id: rectangle24
                    x: 237
                    y: 149
                    width: 10
                    height: 49
                    color: "#ffffff"
                }

                Rectangle {
                    id: rectangle25
                    x: 237
                    y: 93
                    width: 132
                    height: 10
                    color: "#ffffff"
                }

                Rectangle {
                    id: rectangle26
                    x: 492
                    y: -1
                    width: 10
                    height: 104
                    color: "#ffffff"
                }

                Rectangle {
                    id: rectangle27
                    x: 438
                    y: 97
                    width: 64
                    height: 10
                    color: "#ffffff"
                }

                Rectangle {
                    id: rectangle28
                    x: 497
                    y: 149
                    width: 10
                    height: 49
                    color: "#ffffff"
                }
            }

            LabelDevice {
                id: labelDevice1er
                text: "1er"
                horizontalAlignment: Text.AlignLeft
                anchors.bottom: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottomMargin: -25
                anchors.leftMargin: 4
                anchors.topMargin: -10
                anchors.rightMargin: 350
            }
        }

        Frame {
            id: frameRezInfMaster
            Layout.preferredHeight: 423
            Layout.preferredWidth: 700

            Frame {
                id: frameRezInf
                x: 0
                y: 82
                width: 672
                height: 197
                Rectangle {
                    id: rectangleBackgroundRezInf
                    x: 0
                    color: "#3d3d3d"
                    anchors.rightMargin: -11
                    anchors.leftMargin: -11
                    anchors.bottomMargin: -11
                    anchors.topMargin: -11
                    anchors.fill: parent
                }

                Frame {
                    id: frame
                    x: -12
                    y: 185
                    width: 246
                    height: 127

                    Rectangle {
                        id: rectangleBackgroundRezSup2
                        color: "#3d3d3d"
                        anchors.rightMargin: -11
                        anchors.leftMargin: -11
                        anchors.bottomMargin: -11
                        anchors.topMargin: -11
                        anchors.fill: parent
                    }
                }

                PushButtonLight {
                    id: pushButtonLightSPA
                    x: 0
                    y: 48
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightHomeCinema
                    x: 114
                    y: 53
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightElectricity
                    x: 312
                    y: 13
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightHeatering
                    x: 555
                    y: 53
                    width: 80
                    height: 80
                    scale: 1
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightStep01
                    x: 387
                    y: 94
                    width: 80
                    height: 80
                    antialiasing: true
                }

                Rectangle {
                    id: rectangle15
                    x: 225
                    y: -12
                    width: 10
                    height: 105
                    color: "#ffffff"
                }

                Rectangle {
                    id: rectangle17
                    x: 487
                    y: -12
                    width: 10
                    height: 75
                    color: "#ffffff"
                }

                Rectangle {
                    id: rectangle19
                    x: 487
                    y: 119
                    width: 10
                    height: 63
                    color: "#ffffff"
                }

                PushButtonLight {
                    id: pushButtonLightGarage
                    x: 59
                    y: 214
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightEntrySouthOut
                    x: 284
                    y: 190
                    width: 80
                    height: 80
                    antialiasing: true
                }

            }

            LabelDevice {
                id: labelDeviceRezSup
                x: 4
                y: -4
                text: "Rez sup"
                horizontalAlignment: Text.AlignLeft
                anchors.bottom: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottomMargin: -25
                anchors.leftMargin: 4
                anchors.topMargin: -10
                anchors.rightMargin: 350
            }
        }

        Frame {
            id: frameRezSupMaster
            rightPadding: 120
            bottomPadding: 12
            leftPadding: 12
            topPadding: 12
            Layout.preferredHeight: 423
            Layout.preferredWidth: 700

            Frame {
                id: frameRezSup
                anchors.top: parent.top
                anchors.topMargin: 82
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 120
                anchors.right: parent.right
                anchors.rightMargin: -104
                anchors.left: parent.left
                anchors.leftMargin: 0
                Rectangle {
                    id: rectangleBackgroundRezSup
                    color: "#3d3d3d"
                    anchors.rightMargin: -11
                    anchors.leftMargin: -11
                    anchors.bottomMargin: -10
                    anchors.topMargin: -11
                    anchors.fill: parent
                }

                Frame {
                    id: frameTerasse
                    x: -12
                    y: 185
                    width: 246
                    height: 127
                    antialiasing: false

                    Rectangle {
                        id: rectangleBackgroundRezSup1
                        color: "#3d3d3d"
                        anchors.rightMargin: -11
                        anchors.leftMargin: -11
                        anchors.bottomMargin: -11
                        anchors.topMargin: -11
                        anchors.fill: parent
                    }
                }

                PushButtonLight {
                    id: pushButtonLightSaloonTV
                    x: 0
                    y: 27
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightKitchenCook
                    x: 92
                    y: 99
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightKitchenFridge
                    x: 124
                    y: 1
                    width: 80
                    height: 80
                }

                PushButtonLight {
                    id: pushButtonLightSDBRezSup
                    x: 486
                    y: -7
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonFan {
                    id: pushButtonFanSDBRezSup
                    x: 573
                    y: -7
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightStep10
                    x: 367
                    y: 99
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightEntry
                    x: 281
                    y: 40
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightRoomEstSouth1
                    x: 546
                    y: 99
                    width: 80
                    height: 80
                    antialiasing: true
                }

                Rectangle {
                    id: rectangle10
                    x: 224
                    y: -12
                    width: 10
                    height: 105
                    color: "#ffffff"
                }

                Rectangle {
                    id: rectangle11
                    x: 224
                    y: 139
                    width: 10
                    height: 46
                    color: "#ffffff"
                }

                Rectangle {
                    id: rectangle12
                    x: 471
                    y: -12
                    width: 10
                    height: 105
                    color: "#ffffff"
                }

                Rectangle {
                    id: rectangle13
                    x: 574
                    y: 83
                    width: 85
                    height: 10
                    color: "#ffffff"
                }

                Rectangle {
                    id: rectangle14
                    x: 471
                    y: 139
                    width: 10
                    height: 46
                    color: "#ffffff"
                }

                PushButtonLight {
                    id: pushButtonLightEntryNortheOut
                    x: 292
                    y: -96
                    width: 80
                    height: 80
                    antialiasing: true
                }

                PushButtonLight {
                    id: pushButtonLightTerrasse
                    x: 68
                    y: 210
                    width: 80
                    height: 80
                    antialiasing: true
                }
            }

            LabelDevice {
                id: labelDeviceRezInf
                x: 4
                y: -4
                text: "Rez inf"
                horizontalAlignment: Text.AlignLeft
                anchors.bottom: parent.top
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.leftMargin: 4
                anchors.bottomMargin: -25
                anchors.rightMargin: 350
                anchors.topMargin: -10
            }
        }



    }
}

/*##^## Designer {
    D{i:86;anchors_x:0;anchors_y:"-41"}D{i:60;anchors_height:142;anchors_width:620;anchors_x:31;anchors_y:27}
D{i:1;anchors_height:200;anchors_width:676;anchors_x:0;anchors_y:26}D{i:66;anchors_height:123;anchors_width:642;anchors_x:18;anchors_y:37}
D{i:65;anchors_height:200;anchors_width:676;anchors_x:2;anchors_y:30}D{i:87;anchors_x:0;anchors_y:"-41"}
D{i:63;anchors_height:189;anchors_width:663;anchors_x:0;anchors_y:"-6"}D{i:85;anchors_height:78;anchors_width:196;anchors_x:0;anchors_y:7}
D{i:36;anchors_height:197;anchors_width:672;anchors_x:"-11";anchors_y:83}D{i:89;anchors_x:0;anchors_y:"-41"}
D{i:62;anchors_height:197;anchors_width:672;anchors_x:0;anchors_y:"-7"}D{i:64;anchors_height:92;anchors_width:233;anchors_x:0;anchors_y:"-7"}
D{i:22;anchors_height:197;anchors_width:672;anchors_x:0;anchors_y:82}D{i:88;anchors_x:0;anchors_y:"-41"}
D{i:59;anchors_x:37;anchors_y:76}
}
 ##^##*/
