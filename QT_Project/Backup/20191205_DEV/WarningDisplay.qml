import QtQuick 2.4

WarningDisplayForm
{
    function errorMessageReceivedToDisplay(objectName, errorText)
    {
 //       console.log("warning received")
        warningTextText = objectName + ",\n " + errorText
        clicknotify.running = true
        warningTextHorizontalAlignment = Text.AlignLeft
    }

    function errorCounterNumberToDisplay(errorCounterNumberText, errorCounterNumberValue)
    {
//        console.log("errorCounterNumberToDisplay: " + errorTotalNumberText)
        nbErrorCounterText = errorCounterNumberText + ": \t " + errorCounterNumberValue
        nbErrorCounterTextVisible = true
    }


    function noErrorToDisplay()
    {
//        console.log("warning received")
        warningTextText = "no warning"
        rectangleColor = "balck"
        nbErrorCounterTextVisible = false
        warningTextHorizontalAlignment = Text.AlignHCenter
    }

    SequentialAnimation on rectangleColor {
        id: clicknotify
        running: false


        ColorAnimation {
            from: "#a58107"
            to: "#ffffff"
            duration: 200
        }

        ColorAnimation {
            from: "#ffffff"
            to: "#a58107"
            duration: 200
        }
    }
}
