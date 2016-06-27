import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import Bardo.CCTorneo.TorneoData 1.0

InfoTorneoBForm {
    property TorneoData infoTorneo

    Flickable {
        id: flickableRoot
        anchors.fill: parent
        focus: true

        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0

        contentWidth: 400
        contentHeight: 400

        TextField {
            id: textField1
            x: 46
            y: 46
            width: 286
            height: 40
            text: infoTorneo.nombre
            font.pointSize: 12
            placeholderText: "Nombre del torneo"
            Material.accent: infoTorneo.tipo=="Catan" ? Material.Amber : Material.Lime
        }

        Label {
            id: label1
            x: 46
            y: 103
            width: 81
            height: 23
            text: "Juego"
            font.pointSize: 15
        }

        ComboBox {
            id: juegoComboBox
            x: 46
            y: 132
            width: 286
            height: 40
            model: ListModel {
                ListElement {
                    name: "Catan"
                }
                ListElement {
                    name: "Carcassonne"
                }
            }
            currentIndex: infoTorneo.tipo=="Catan" ? 0 : 1
            onCurrentTextChanged: {
                infoTorneo.tipo=currentText
            }
        }

        ScrollBar.vertical: ScrollBar {}
        ScrollBar.horizontal: ScrollBar {}

    }
}
