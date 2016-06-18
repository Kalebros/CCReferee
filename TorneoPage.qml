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

TorneoPageForm {

    property alias infoTorneo: infoTorneo
    property string rutaIcono: infoTorneo.tipo=="Catan" ? "qrc:/images/players_orange.png" : "qrc:/images/players_blue.png"

    anchors.fill: parent
    TorneoData {
        id: infoTorneo
    }

    header: Rectangle {
        id: rHead
        color: infoTorneo.tipo=="Catan" ? "orange" : "steelblue"
        height: 50
        Row {
            x:10
            y:0
            anchors.verticalCenter: rHead.verticalCenter
            anchors.horizontalCenter: rHead.horizontalCenters
            spacing: 10
            TransparentButton {
                id: backButton
                source: "qrc:/images/white_arrow.png"
                height: 30
                width: 30
                anchors.verticalCenter: tNameLabel.verticalCenter
                onClicked: {
                    stackPrincipal.pop()
                    stackPrincipal.push("qrc:/PaginaBienvenida.qml")
                }
            }

            Label {
                id: tNameLabel
                text: infoTorneo.nombre
                color: "white"
                width: (rHead.width / 5) * 4
                font.pointSize: 20
                elide: Text.ElideRight
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        TabBar {
            id: barraBotones
            anchors.top: rHead.bottom
            Material.accent: infoTorneo.tipo=="Catan" ? Material.Indigo : Material.Amber
            width: parent.width
            height: 40
            currentIndex: torneoSwipe.currentIndex
            TabButton {
                id: botonA
                background: Rectangle {
                    color: botonA.checked ? "white" : rHead.color
                    Image {
                        id: iconTab
                        source: botonA.checked ?  rutaIcono : "qrc:/images/players.png"
                        smooth: true
                        antialiasing: true
                        anchors.centerIn: parent
                    }
                }
            }
            TabButton {
                id: botonB
                Material.accent: "white"
                text: "SegundoBoton"
                background: Rectangle {
                    color: botonB.checked ? "white" : rHead.color
                }
            }
        }
    }

    SwipeView {
        id: torneoSwipe
        anchors.fill: parent
        currentIndex: barraBotones.currentIndex

        JugadoresPage {
            id: jugadoresPage
            tipo: infoTorneo.tipo
        }
        Page {
            id: pruebaPage
        }

    }

}
