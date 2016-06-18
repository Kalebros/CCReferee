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

Item {
    id: item1
    width: 358
    height: 642
    property alias readyButton: readyButton
    property alias cancelButton: cancelButton
    property alias torneoField: torneoField
    property alias torneoLabel: tipoTorneoLabel

    Label {
        id: tipoTorneoLabel
        x: 8
        y: 8
        width: 284
        height: 59
        text: qsTr("TIPO TORNEO")
        font.pointSize: 30
    }

    TextField {
        id: torneoField
        x: 79
        y: 150
        width: 313
        height: 40
        text: qsTr("")
        anchors.verticalCenterOffset: -30
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        placeholderText: "Nombre del torneo"
    }

    Button {
        id: cancelButton
        x: 129
        y: 579
        width: 100
        text: qsTr("Cancelar")
        anchors.horizontalCenterOffset: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 23
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Button {
        id: readyButton
        x: 129
        y: 336
        width: 100
        text: qsTr("Listo")
        anchors.verticalCenterOffset: 49
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
