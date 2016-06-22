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
    id: tPage
    property TorneoData infoTorneo

    property var listaNombres: ["Información del torneo","Participantes"]

    anchors.fill: parent

    header: Rectangle {
        id: rHead
        color: infoTorneo.tipo=="Catan" ? "orangered"  : "steelblue"
        height: 70
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
            Material.accent: infoTorneo.tipo=="Catan" ? Material.Amber : Material.Lime
            width: parent.width
            height: 20
            currentIndex: torneoSwipe.currentIndex
            background: Rectangle {
                x:0
                y:0
                width: barraBotones.availableWidth
                height:botonA.height
                color: infoTorneo.tipo=="Catan" ? "orangered" : "steelblue"
            }

            TabButton {
                id: botonA
                background: Rectangle {
                    color: rHead.color
                    border.color: "transparent"
                    Image {
                        id: iconTabA
                        height: 30
                        width: 30
                        source: botonA.checked ? "qrc:/images/ic_descriptionWhite_48px.svg" : "qrc:/images/ic_description_48px.svg"
                        opacity:  botonA.checked ? 1 : 0.7
                        smooth: true
                        antialiasing: true
                        anchors.centerIn: parent
                    }
                }
            }
            TabButton {
                id: botonB
                Material.accent: "white"
                background: Rectangle {
                    color: rHead.color
                    border.color: "transparent"
                    Image {
                        id: iconTabB
                        height: 30
                        width: 30
                        source: botonB.checked ? "qrc:/images/ic_groupWhite_48px.svg" : "qrc:/images/ic_group_48px.svg"
                        opacity:  botonB.checked ? 1 : 0.7
                        smooth: true
                        antialiasing: true
                        anchors.centerIn: parent
                    }
                }
            }
            TabButton {
                id: botonC
                Material.accent: "white"
                text: "SegundoBoton"
                background: Rectangle {
                    color: rHead.color
                    border.color: "transparent"
                }
            }

            TabButton {
                id: botonD
                Material.accent: "white"
                text: "SegundoBoton"
                background: Rectangle {
                    color: rHead.color
                    border.color: "transparent"
                }
            }

        }
    }

    SwipeView {
        id: torneoSwipe
        anchors.fill: parent
        currentIndex: barraBotones.currentIndex

        InfoTorneo {
            id: infoTorneoPage
            infoTorneo: tPage.infoTorneo

            Binding {
                target: tPage
                property: infoTorneo
                value: infoTorneoPage.infoTorneo
            }
        }

        JugadoresPage {
            id: jugadoresPage
            tipo: infoTorneo.tipo
        }

    }

    Component.onCompleted: {
        console.log("INFO TORNEO: "+infoTorneo.nombre)
    }

}
