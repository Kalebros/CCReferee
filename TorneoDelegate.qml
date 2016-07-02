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
import "qrc:/torneoCreacion.js" as ScriptCreacion

Component {
    id: torneoDelegate
    Item {
        id: torneo
        height: decoRect.height + lNombre.height + lTipo.height -15
        width: parent.width

        MouseArea {
            anchors.fill: parent
            onClicked:{
                var torneoData=Qt.createQmlObject('import Bardo.CCTorneo.TorneoData 1.0; TorneoData {nombre: ""; tipo: "Catan"}',
                                                  root,"infoTorneo1")
                torneoData.nombre=lNombre.text
                torneoData.tipo=lTipo.text
                torneoData.internalID=internalID
                Database.setCurrentTorneo(internalID)
                console.log(torneoData.nombre+", "+torneoData.tipo+", "+torneoData.internalID)
                stackPrincipal.pop()
                stackPrincipal.push("qrc:/TorneoPage.qml",{ "infoTorneo": torneoData});
            }
        }

        Row {
            padding: 10
            spacing: 10
            height: decoRect.height
            width: decoRect.width
            Rectangle {
                id: decoRect
                width: 40
                height: 40
                color: tipo=="Catan" ? "orange" : "steelblue"
            }
            Column {
                Label {
                    id: lNombre
                    text: nombre
                    font.pointSize: 15
                }
                Label {
                    id: lTipo
                    text: tipo
                    color: tipo=="Catan" ? "orange" : "steelblue"
                    font.pointSize: 12
                    font.italic: true
                }
                Rectangle {
                    height: 1
                    width: (vistaTorneos.width / 5) * 4
                    border.color: "slategrey"
                    color: "slategrey"
                    opacity: 0.5
                }
                spacing: 5
            }
        }
    }
}
