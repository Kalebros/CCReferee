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

    id: jugadoresComplexPage
    property string tipo

    StackView {
        id: jComplexStack
        anchors.fill: parent
        anchors.bottomMargin: barraBotones.height
        initialItem: JugadoresPage {
            id: jugadoresPageInicial
            tipo: jugadoresComplexPage.tipo
            width: jComplexStack.width
            height: jComplexStack.height
        }
    }

    BarraBotonesTorneo {
        id: barraBotones
        tipo: jugadoresComplexPage.tipo
        y: 577
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
                id: toolButton1
                iconA: "qrc:/images/add_person_amber.svg"
                iconB: "qrc:/images/add_person_lime.svg"
                tipo: jugadoresComplexPage.tipo
                onClicked: {
                    jugadoresPageInicial.state=""
                }
                checked: true
                ButtonGroup.group: bGroup
            }

            BottomButton {
                id: toolButton3
                iconA: "qrc:/images/check_person_amber.svg"
                iconB: "qrc:/images/check_person_lime.svg"
                ButtonGroup.group: bGroup
                tipo: jugadoresComplexPage.tipo
                onClicked: {
                    jugadoresPageInicial.state="checkJugador"
                }
            }

            BottomButton {
                id: toolButton2
                iconA: "qrc:/images/edit_person_amber.svg"
                iconB: "qrc:/images/edit_person_lime.svg"
                ButtonGroup.group: bGroup
                tipo: jugadoresComplexPage.tipo
                onClicked: {
                    jugadoresPageInicial.state="editJugador"
                }
            }
        }

    }

}
