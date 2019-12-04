import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0

import io.qt.GlobalEnumerate 1.0

PageBackground {

    id: lightAndFan
    width: 980
    height: 800
    title: "light And Fan"

    LightAndFan {
        id: lightAndFan1
        x: 126
        y: 117
        width: 244
        height: 102
    }
}
