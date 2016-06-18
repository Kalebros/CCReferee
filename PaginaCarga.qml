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

PaginaCargaForm {

    id: paginaCarga
    anchors.fill: parent
    labelColor: "steelblue"

    vistaTorneos.model: ListModel {

        ListElement {
            nombre: "Jornadas Lúdicas Andaluzas 2016"
            tipo: "Carcassonne"
        }
        ListElement {
            nombre: "Jornadas Lúdicas Andaluzas 2016"
            tipo: "Catan"
        }
        ListElement {
            nombre: "Ficzone 2016"
            tipo: "Carcasonne"
        }
        ListElement {
            nombre: "Ficzone 2016"
            tipo: "Catan"
        }
        ListElement {
            nombre: "Jornadas Lúdicas Andaluzas 2016"
            tipo: "Carcassonne"
        }
        ListElement {
            nombre: "Jornadas Lúdicas Andaluzas 2016"
            tipo: "Catan"
        }
        ListElement {
            nombre: "Ficzone 2016"
            tipo: "Carcasonne"
        }
        ListElement {
            nombre: "Ficzone 2016"
            tipo: "Catan"
        }
        ListElement {
            nombre: "Jornadas Lúdicas Andaluzas 2016"
            tipo: "Carcassonne"
        }
        ListElement {
            nombre: "Jornadas Lúdicas Andaluzas 2016"
            tipo: "Catan"
        }
        ListElement {
            nombre: "Ficzone 2016"
            tipo: "Carcasonne"
        }
        ListElement {
            nombre: "Ficzone 2016"
            tipo: "Catan"
        }
        ListElement {
            nombre: "Jornadas Lúdicas Andaluzas 2016"
            tipo: "Carcassonne"
        }
        ListElement {
            nombre: "Jornadas Lúdicas Andaluzas 2016"
            tipo: "Catan"
        }
        ListElement {
            nombre: "Ficzone 2016"
            tipo: "Carcasonne"
        }
        ListElement {
            nombre: "Ficzone 2016"
            tipo: "Catan"
        }
        ListElement {
            nombre: "Jornadas Lúdicas Andaluzas 2016"
            tipo: "Carcassonne"
        }
        ListElement {
            nombre: "Jornadas Lúdicas Andaluzas 2016"
            tipo: "Catan"
        }
        ListElement {
            nombre: "Ficzone 2016"
            tipo: "Carcasonne"
        }
        ListElement {
            nombre: "Ficzone 2016"
            tipo: "Catan"
        }
    }

    vistaTorneos.delegate: TorneoDelegate {}

    cancelButton.onClicked: {
        stackPrincipal.pop()
        stackPrincipal.push("qrc:/PaginaBienvenida.qml")
    }
}
