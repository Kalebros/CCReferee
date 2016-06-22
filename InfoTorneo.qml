import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import Bardo.CCTorneo.TorneoData 1.0

InfoTorneoForm {

    property TorneoData infoTorneo


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

    tipoComboBox.onCurrentTextChanged: {
        infoTorneo.tipo=tipoComboBox.currentText
    }

    nombreField.onTextChanged: {
        infoTorneo.nombre=nombreField.text
    }

}
