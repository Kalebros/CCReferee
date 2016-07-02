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

    property string tipo
    vistaJugadores.topMargin: 40

    vistaJugadores.model: modeloParticipantes

    vistaJugadores.delegate: CheckDelegate {
        Material.accent: tipo=="Catan" ? Material.Amber : Material.Green
        width: vistaJugadores.width
        text: nombre
        checked: checking
        onClicked: {
            Database.checkParticipante(idParticipante,!checking);
        }
    }
    vistaJugadores.header: Rectangle {
        width: parent.width
        height: 40
        color: "white"
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
    barraBotones.tipo: tipo

}
