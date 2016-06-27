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
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0


ApplicationWindow {
    id: root
    visible: true
    width: 358
    height: 642

    title: qsTr("CCReferee")

    property color primaryCatan: "orangered"
    property color secondaryCatan: "#FFC107" //Material.Amber
    property color primaryCarca: "steelblue"
    property color secondaryCarca: "#CDDC39" //Material.Lime


    StackView {
        id: stackPrincipal
        anchors.fill: parent
        initialItem: PaginaBienvenida {
            id: paginaInicial
        }
    }

}
