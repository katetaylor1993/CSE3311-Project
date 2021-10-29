import QtQuick 2.15
import QtQuick.Window 2.15

/*
  ******************** HEEEY!! LOOK HERE!! ********************
  BEFORE YOU START:
    1. Are you on your own branch on git? Current branch should
        NOT be "main"
    2. Keep things looking neat and uniform
    3. I may put more stuff here so check back after pull
  */

Window {

    // These are configuration items for this window.
    property int strt_height: 480
    property int strt_width: 640
    property int padding: 10
    property string padding_color: "#ffffff"
    property string bg_color: "#f1f1f1"
    property string font: "Calibri"
    //enable ("black") or disable ("transparent") grid lines for development
    property string borderColor: "black"

    id: mainWindow
    width: strt_width
    height: strt_height
    minimumHeight: 300
    minimumWidth: 500
    color: padding_color
    visible: true
    title: qsTr("Hello World")

    // This makes it so mainWindow.width and mainWindow.height (just above)
    // can be referenced by these names in any qml
    property alias w_width: mainWindow.width
    property alias w_height: mainWindow.height

    Rectangle
    {
        // this is the login screen.
        id: canvas
        x: padding
        y: padding
        height: w_height - (2*padding)
        width: w_width - (2*padding)
        color: bg_color
        Grid
        {
            // breaks the inner window in half
            id: canvasGrid
            rows: 1
            columns: 2
            Rectangle
            {
                // left side with some text
                height: canvas.height
                width: canvas.width/canvasGrid.columns
                color: "transparent"
                border.color: borderColor
                border.width: 1
                Text
                {
                    id: loginPrompt
                    height: canvas.height
                    width: canvas.width/canvasGrid.columns
                    font.pointSize: 30
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                    text: qsTr("Welcome! \nPlease log in.")
                }
            }

            Rectangle
            {
                //right side has all the input boxes, buttons and links
                id: canvas_1
                color: "transparent"
                height: canvas.height
                width: canvas.width/canvasGrid.columns
                Grid
                {
                    columns: 1
                    rows: 7
                    Rectangle {}
                    Rectangle {
                        height: 40
                        width: canvas_1.width
                        Text
                        {
                            font.pointSize: 15
                            horizontalAlignment: Text.AlignHCenter
                            text: qsTr("Login email:")
                        }
                    }
                    Rectangle {
                        height: 40
                        width: canvas_1.width
                        TextInput
                        {
                            height:15
                        }
                    }
                    Rectangle {}
                    Rectangle {}
                    Rectangle {}
                    Rectangle {}
                }

            }
        }
    }

}

