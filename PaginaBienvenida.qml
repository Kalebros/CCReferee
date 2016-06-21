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

import QtQuick 2.4
import QtQuick.Controls.Material 2.0

import Bardo.CCTorneo.TorneoData 1.0

PaginaBienvenidaForm {
    anchors.fill: parent

    carcasonneButton.onClicked: {
        console.log("Boton Carcasonne pulsado")
        stackPrincipal.pop()
        stackPrincipal.push("qrc:/NuevoTorneoPage.qml", {tipoTorneo: "Carcassonne" })
    }
    loadButton.onClicked: {
        console.log("Boton Load pulsado")
        stackPrincipal.pop()
        stackPrincipal.push("qrc:/PaginaCarga.qml")
    }
    catanButton.onClicked:
    {
        console.log("Boton Catan pulsado")
        stackPrincipal.pop()
        stackPrincipal.push("qrc:/NuevoTorneoPage.qml", {tipoTorneo: "Catan" })
    }

}
