////////////////////////////////////////////////////////////////////////////
///
/// CCReferee
/// Copyright @2016, Antonio Ramírez Marti
/// (morgulero@gmail.com)
///
/// This file is part of CCReferee.
///
/// CCReferee is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// CCReferee is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
///
////////////////////////////////////////////////////////////////////////////

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import Bardo.CCTorneo.TorneoData 1.0
import Bardo.CCTorneo.Database 1.0

JugadoresPageForm {

    id: jugadoresPage
    property string tipo

    Label {
        id: actionLabel
        height: 95
        text: qsTr("Añadir nuevo participante")
        color: tipo=="Catan" ? root.secondaryCatan : root.secondaryCarca
        visible: false
        wrapMode: Text.WordWrap
        anchors.top: parent.top
        anchors.topMargin: 45
        anchors.right: parent.right
        anchors.rightMargin: 66
        anchors.left: parent.left
        anchors.leftMargin: 8
        z: 1
        font.pointSize: 30
    }

    ListView {
        id: vistaEdit
        visible: true
        anchors.fill: parent
        anchors.topMargin: 40
        delegate: TextField {
            Material.accent: tipo=="Catan" ? Material.Amber : Material.Green
            width: vistaEdit.width-15
            x: 10
            text: nombre
            font.pointSize: font.pointSize+1
            onAccepted: {
                console.log("Nuevo nombre: "+text)
            }
        }
        model: modeloParticipantes
        header:Rectangle {
            width: parent.width
            height: 40
            color: Material.background
            Label {
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.top: parent.top
                anchors.topMargin: 4
                anchors.verticalCenter: parent.verticalCenter
                text: "Pulsa para editar"
                wrapMode: Text.WordWrap
                font.pointSize: 20
                color: tipo=="Catan" ? root.primaryCatan : root.primaryCarca
            }

            Rectangle {

                anchors.bottom: parent.bottom
                width: parent.width
                height: 1
                color: "transparent"
                border.color: tipo=="Catan" ? root.primaryCatan : root.primaryCarca
            }
        }
    }


    ListView {
        id: vistaCheck
        visible: false
        anchors.fill: parent
        anchors.topMargin: 40
        //        delegate: ItemDelegate {
        //            Material.accent: tipo=="Catan" ? Material.Amber : Material.Green
        //            width: vistaJugadores.width
        //            text: nombre
        //            onClicked: {
        //                console.log("Clicked on "+nombre)
        //            }
        //        }

        delegate: CheckDelegate {
            Material.accent: tipo=="Catan" ? Material.Amber : Material.Green
            width: vistaCheck.width
            text: nombre
            checked: checking
            onClicked: {
                Database.checkParticipante(idParticipante,!checking);
            }
        }
        model: modeloParticipantes
        header:Rectangle {
            width: parent.width
            height: 40
            color: Material.background
            Label {
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                text: "Nombre"
                color: tipo=="Catan" ? root.primaryCatan : root.primaryCarca
            }
            Label {
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                color: tipo=="Catan" ? root.primaryCatan : root.primaryCarca
                text: "Checking"
            }

            Rectangle {

                anchors.bottom: parent.bottom
                width: parent.width
                height: 1
                color: "transparent"
                border.color: tipo=="Catan" ? root.primaryCatan : root.primaryCarca
            }
        }
    }

    TextField {
        id: addField
        y: 321
        height: 40
        visible: false
        placeholderText: qsTr("Nombre del participante")
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 22
        anchors.left: parent.left
        anchors.leftMargin: 21
        Material.accent: tipo=="Catan" ? Material.Amber : Material.Green
    }

    Button {
        id: addButton
        text: qsTr("Añadir")
        visible: false
        anchors.right: parent.right
        anchors.rightMargin: 129
        anchors.left: parent.left
        anchors.leftMargin: 129
        anchors.top: addField.bottom
        anchors.topMargin: 15
    }
    states: [
        State {
            name: "addJugador"

            PropertyChanges {
                target: vistaCheck
                visible: false
            }

            PropertyChanges {
                target: actionLabel
                text: qsTr("Añadir nuevo participante")
                visible: true
            }

            PropertyChanges {
                target: addField
                text: qsTr("")
                visible: true
            }

            PropertyChanges {
                target: addButton
                visible: true
            }

            PropertyChanges {
                target: vistaEdit
                visible: false
            }
        },
        State {
            name: "checkJugador"

            PropertyChanges {
                target: vistaCheck
                visible: true
            }

            PropertyChanges {
                target: vistaEdit
                visible: false
            }
        }
    ]

}
