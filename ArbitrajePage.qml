import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import QtQuick.Layouts 1.0
import Bardo.CCTorneo.TorneoData 1.0
import Bardo.CCTorneo.Database 1.0

ArbitrajePageForm {

    id: arbitrajePageForm1

    function checkState() {
        if(modeloParticipantes.participantesCheck >= torneo.minimoJugadores)
            state="State1"
        else state=""
    }

    Text {
        id: text1
        x: 8
        y: 212
        width: 342
        height: 35
        text: qsTr("No se cumple el mínimo de participantes.")
        anchors.verticalCenter: parent.verticalCenter
        wrapMode: Text.WordWrap
        font.pixelSize: 30
        color: torneo.tipo=="Catan" ? root.secondaryCatan : root.secondaryCarca
    }

    BarraBotonesTorneo {
        id: barraBotones
        tipo: torneo.tipo
        y: 577
        visible: false
        z: 1
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        ButtonGroup {
            id: bGroup
        }

        Row {
            x: 0
            y: 0
            spacing: 40
            anchors.horizontalCenter: parent.horizontalCenter

            BottomButton {
                id: tButton1
                z: 1
                iconA: "qrc:/images/circle-one-amber.svg"
                iconB: "qrc:/images/circle-one-lime.svg"
                tipo: torneo.tipo
                onClicked: {
                    console.log("CLICKED!")
                }
                checked: true
                ButtonGroup.group: bGroup
            }

            BottomButton {
                id: tButton2
                z: 2
                iconA: "qrc:/images/circle-two-amber.svg"
                iconB: "qrc:/images/circle-two-lime.svg"
                ButtonGroup.group: bGroup
                tipo: torneo.tipo
                onClicked: {
                    console.log("CLICKED!")
                }
            }

            BottomButton {
                id: tButton3
                z: 3
                iconA: "qrc:/images/circle-three-amber.svg"
                iconB: "qrc:/images/circle-three-lime.svg"
                ButtonGroup.group: bGroup
                tipo: torneo.tipo
                onClicked: {
                    console.log("CLICKED!")
                }
            }
        }

    }

    states: [
        State {
            name: "State1"

            PropertyChanges {
                target: text1
                visible: false
            }

            PropertyChanges {
                target: barraBotones
                visible: true
            }
        }
    ]

    Component.onCompleted: {
        checkState()
    }

    Connections {
        target: torneo
        onTipoChanged: {
            checkState()
        }
    }

    Connections {
        target: modeloParticipantes
        onParticipantesCheckChanged: {
            checkState()
        }
    }

}
