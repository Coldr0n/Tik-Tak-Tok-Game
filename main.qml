import QtQuick
import QtQuick.Controls
import TikTakTok 1.0

Window {
id:root
    width: 366
    height: 640
    maximumWidth: width
    maximumHeight: height
    minimumWidth: width
    minimumHeight: height
    visible: true
    title: qsTr("Tik Tak Tok")
    property bool radioButton1 : true
    property bool radioButton2 : true

    function newGame()
    {
        loader.active = false
        loader.active = true
    }

    Loader {
        anchors.fill:parent
        id: loader
        sourceComponent: Item{
            anchors.fill:parent

            Game {
                id: game
                property bool playerWone:false
                property bool drawe:false
                property bool newGameVisible:true
                property bool beginningTexte:true
                property bool chooseCaracterVisible:false
                onDisplayCross: (x, y) => {
                                    const index = y*3+x
                                    const clickedArea = repeater.itemAt(index)
                                    clickedArea.areaVisible = false
                                    clickedArea.isCross = true

                                }

                onDisplayCircle: (x, y) => {
                                    const index = y*3+x
                                    const clickedArea = repeater.itemAt(index)
                                    clickedArea.areaVisible = false
                                    clickedArea.isCross = false

                                }

                onPlayerWon: (WINNER) => {



                                 const playerName = WINNER === 0 ? "Les croix" : "Les ronds"

                                 endGameText.text = playerName + " ont gagné !"

                                 playerWone = true

                             }

                onDraw: () => {

                           drawe = true

                           endGameText.text = "Match nul"
                       }

                onNewGame: () => {
                               chooseCaracterVisible = false

                               rectanglesAnimation.stop()

                           }

                onPlayerCounter: (PLAYER) => {
                               const playernumber = PLAYER === 0 ? "croix" : "ronds"
                               counter.text = "C'est aux " + playernumber + " de jouer"
                           }

                onColoriseSquare: (x, y) => {
                                      const index = y*3+x
                                      const clickedArea = repeater.itemAt(index)
                                      clickedArea.isColorised = true
                                }

                onBeginningText: ()  => {
                                     beginningTexte = false
                                 }

                onChooseCaracter: () => {
                                      chooseCaracterVisible = true
                                      newGameVisible = false
                                  }

            }




            Text{
                id: counter
                font.pointSize: 20
                text: "C'est aux croix de jouer"
            }


            Rectangle{
                width: counter.width
                height: counter.height
                color: "white"
                visible: game.playerWone || game.drawe
            }


            Grid {
                columns: 3
                spacing: 3
                id: grid
                visible: !game.newGameVisible && !game.chooseCaracterVisible
                anchors.top: counter.bottom
                RotationAnimation on rotation {
                    running: false
                    loops: 1
                    id: gridAnimation
                    from: 0
                    to: -360
                    duration: 400
                }


                Repeater{
                    model: 9
                    id: repeater
                    Rectangle{
                        id: rectangles
                        property bool isColorised: false
                        color: isColorised ? "#800000FF" : (mouseAreaaaaa.containsMouse ?"#80400090" : "white")
                        RotationAnimation on rotation {
                            running: false
                            loops: 2
                            id: rectanglesAnimation
                            from: 0
                            to: 360
                            duration: 500
                        }

                        Connections{
                            target: game
                            function onPlayerWoneChanged()
                            {
                                rectanglesAnimation.start()
                                gridAnimation.start()
                            }
                        }


                        width: 120; height: width
                        border.color: "black"; border.width: 4
                        property bool areaVisible: true
                        property bool isCross: true

                        MouseArea{
                            id: mouseAreaaaaa
                            visible: parent.areaVisible && !game.playerWone
                            property int posy: Math.floor(index/3)
                            property int posx: index%3
                            cursorShape: Qt.PointingHandCursor
                            hoverEnabled: true

                            anchors.fill: parent
                            onClicked:() => {
                                          game.place(posx, posy)
                                          game.beginningText()
                                      }
                            }
                        Image{
                            source: "file:black cross.png"
                            visible: !parent.areaVisible && parent.isCross
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                        }

                        Image{
                            source: "file:black circle.png"
                            visible: !parent.areaVisible && !parent.isCross
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }
                }

            }


            Rectangle
            {
                width: 330
                height: 200
                radius: 10
                anchors.horizontalCenter: grid.horizontalCenter
                anchors.top: grid.bottom
                anchors.topMargin: 20
                visible: game.drawe || game.playerWone
                onVisibleChanged:() => {
                                    if(visible){
                                        animation.start()
                                    }
                }

                gradient: Gradient{
                    GradientStop { position: 0.0; color: "midnightblue" }
                    GradientStop { position: 1.0; color: "darkred" }
                }

                Rectangle
                {
                    width: endGameText.width + 10
                    height: endGameText.height + 10
                    color: "white"
                    id: endGameTextRectangle
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 30
                    radius: 10
                    border.color: "black"
                    border.width: 3
                    RotationAnimation on rotation {
                            loops: 2
                            id: animation
                            from: 0
                            to: 360
                            duration: 300
                        }




                    Text{
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.leftMargin: 30
                        font.pointSize: 25
                        id: endGameText
                        color: "black"
                    }
                }

                Button
                {
                    text: "Menu principal"
                    anchors.top: endGameTextRectangle.bottom
                    anchors.topMargin: 30
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 200
                    height: 50
                    font.pointSize: 20
                    onClicked: () => {
                                   root.newGame()
                               }
                }
            }

            Rectangle
            {
                anchors.fill: parent
                visible: game.chooseCaracterVisible
                gradient: Gradient{
                    GradientStop { position: 0.0; color: "midnightblue" }
                    GradientStop { position: 1.0; color: "darkred" }
                }

                Rectangle{

                    id: chooseRectangle
                    width: 250
                    height: 200
                    radius: 15
                    border.color: "black"
                    border.width: 3
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter


                    Column
                    {
                        id: player1Column
                        anchors.top: chooseRectangle.top
                        anchors.topMargin: 20
                        spacing: 3
                        anchors.left: chooseRectangle.left
                        anchors.leftMargin: 20
                        width: chooseRectangle.width - 10
                        height: chooseRectangle.height / 2 -10

                        Text{
                            id: player1text
                            text: "Les croix sont le : "
                            font.pointSize: 16
                        }

                        RadioButton {
                            id :crossHuman
                            checked: radioButton1
                            text: "Joueur n° 1"
                            font.pointSize: 11
                            onCheckedChanged: () => {
                                                  radioButton1 = true
                                              }
                        }

                        RadioButton {
                            text: "L'ordinateur"
                            checked: !radioButton1
                            font.pointSize: 11
                            onCheckedChanged: () => {
                                                  radioButton1 = false
                                              }
                        }

                    }

                    Column
                    {
                        anchors.top: player1Column.bottom
                        anchors.left: chooseRectangle.left
                        anchors.leftMargin: 20
                        spacing: 3
                        id: player2Column
                        width: player1Column.width
                        height: player1Column.height

                        Text{
                            id: player2text
                            text: "Les ronds sont le :"
                            font.pointSize: 16
                        }

                        RadioButton {
                            id :circleHuman
                            checked: radioButton2
                            text: "Joueur n° 2"
                            font.pointSize: 11
                            onCheckedChanged: () => {
                                                  radioButton2 = true
                                              }
                        }

                        RadioButton {
                            text: "L'ordinateur"
                            checked: !radioButton2
                            font.pointSize: 11
                            onCheckedChanged: () => {
                                                  radioButton2 = false
                                              }
                        }

                    }
                }

                Button
                {
                    text: "Commencer la partie"
                    font.pointSize: 20
                    anchors.top: chooseRectangle.bottom
                    anchors.topMargin: 15
                    anchors.horizontalCenter: parent.horizontalCenter
                    onClicked: () => {
                                   game.startGame(crossHuman.checked, circleHuman.checked)
                               }
                }
            }


            Rectangle
            {
                anchors.fill: parent
                visible: game.newGameVisible
                gradient: Gradient{
                    GradientStop { position: 0.0; color: "midnightblue" }
                    GradientStop { position: 1.0; color: "darkred" }
                }
                Column
                {
                    anchors.fill: parent

                    Button
                    {
                        text: "Nouvelle partie"
                        font.pointSize: 20
                        width: 300
                        height: 50
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        onClicked: () => {
                                       game.chooseCaracter()
                                   }
                    }


                }

            }

            Rectangle
            {
                border.color: "black"
                visible: game.newGameVisible || game.chooseCaracterVisible
                border.width: 3
                width: 250
                anchors.top: parent.top
                anchors.topMargin: 30
                height: 100
                id: menu_top_rectangle
                color:"white"
                radius: 10
                anchors.horizontalCenter: parent.horizontalCenter

                Text
                {

                    text: "TIK TAK TOK"
                    font.pointSize: 30
                    anchors.verticalCenter: menu_top_rectangle.verticalCenter
                    anchors.horizontalCenter: menu_top_rectangle.horizontalCenter
                }
            }
        }
    }
}

