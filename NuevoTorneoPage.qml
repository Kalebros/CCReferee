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

NuevoTorneoPageForm {
    property string tipoTorneo: "Carcasonne"
    anchors.fill: parent

    torneoField.validator: RegExpValidator{ regExp: /.*\S.*/ }
    Component.onCompleted: {
        //Actualizar el color dependiendo del tipo de torneo
        if(tipoTorneo=="Carcasonne") {
            torneoField.color="steelblue"
            torneoLabel.color="steelblue"
            torneoLabel.text="Carcasonne"
        }
        if(tipoTorneo=="Catan") {
            torneoField.color="orange"
            torneoLabel.color="orange"
            torneoLabel.text="Catan"
        }
        readyButton.enabled=false
    }

    cancelButton.onClicked: {
        stackPrincipal.pop()
    }

    torneoField.onAcceptableInputChanged: {
        if(torneoField.acceptableInput)
            readyButton.enabled=true
        else readyButton.enabled=false
    }

    readyButton.onClicked: {
        if(torneoField.text) {
            stackPrincipal.pop()
            stackPrincipal.push("qrc:/TorneoPage.qml",{"infoTorneo.nombre": torneoField.text, "infoTorneo.tipo":tipoTorneo})
        }
    }
}
