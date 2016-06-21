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

import "qrc:/torneoCreacion.js" as ScriptTorneo

NuevoTorneoPageForm {
    property string tipoTorneo: "Carcassonne"
    anchors.fill: parent

    torneoField.validator: RegExpValidator{ regExp: /.*\S.*/ }
    Component.onCompleted: {
        //Actualizar el color dependiendo del tipo de torneo
        if(tipoTorneo=="Carcassonne") {
            torneoField.color="steelblue"
            torneoLabel.color="steelblue"
            torneoLabel.text="Carcassonne"
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
            var torneoData=Qt.createQmlObject('import Bardo.CCTorneo.TorneoData 1.0; TorneoData {nombre: ""; tipo: "Catan"}',
                                              root,"infoTorneo1")
            torneoData.nombre=torneoField.text
            torneoData.tipo=tipoTorneo
            stackPrincipal.pop()
            stackPrincipal.push("qrc:/TorneoPage.qml",{"infoTorneo": torneoData})
        }
    }
}
