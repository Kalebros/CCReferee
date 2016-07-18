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

import QtQuick.Layouts 1.0

InfoTorneoForm {
    id: infoTorneoForm1

    property TorneoData infoTorneo
    property bool isDataChanged: false


    nombreField.text: infoTorneo.nombre
    tipo: infoTorneo.tipo

    tipoComboBox.model: ListModel {

        ListElement {
            tipo: "Catan"
        }

        ListElement {
            tipo: "Carcassonne"
        }
    }

    tipoComboBox.currentIndex: infoTorneo.tipo=="Catan" ? 0 : 1
    marcadorActuales.color: tipo=="Catan" ? root.secondaryCatan : root.secondaryCarca
    marcadorActuales.limite: 8
    marcadorChecked.color: tipo=="Catan" ? root.secondaryCatan : root.secondaryCarca
    marcadorChecked.limite: 8
    marcadorActuales.numero: modeloParticipantes.numeroParticipantes
    marcadorChecked.numero: modeloParticipantes.participantesCheck
    marcadorPrevistas.limite: 1
    marcadorPrevistas.color: tipo=="Catan" ? root.secondaryCatan : root.secondaryCarca
    marcadorReales.color: tipo=="Catan" ? root.secondaryCatan : root.secondaryCarca
    marcadorReales.limite: 1
    marcadorPrevistas.numero: Database.estimacionMesas
    marcadorReales.numero: Database.numeroMesas

    tipoComboBox.onCurrentTextChanged: {
        infoTorneo.tipo=tipoComboBox.currentText
        isDataChanged=true
    }

    nombreField.onTextChanged: {
        infoTorneo.nombre=nombreField.text
        isDataChanged=true
    }

    ScrollBar.vertical: ScrollBar {}
    ScrollBar.horizontal: ScrollBar {}

    Component.onDestruction: {
        if(isDataChanged)
            Database.updateTorneoData(infoTorneo.internalID,infoTorneo.nombre,infoTorneo.tipo)
    }
}
