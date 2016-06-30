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
