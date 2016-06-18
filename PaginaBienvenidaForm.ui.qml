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
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.0

Item {
    id: item1
    width: 358
    height: 642
    property alias catanButton: catanButton
    property alias carcasonneButton: carcasonneButton
    property alias loadButton: loadButton


    Label {
        id: label1
        x: 41
        width: 276
        height: 55
        text: qsTr("CCReferee")
        anchors.horizontalCenterOffset: 0
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 35
        horizontalAlignment: Text.AlignHCenter
    }

    Column {
        x: 83
        y: 241
        anchors.verticalCenterOffset: 30
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 15

        Button {
            id: loadButton
            width: 291
            height: 60
            text: qsTr("Cargar torneo")
        }

        Button {
            id: carcasonneButton
            width: 291
            height: 60
            text: qsTr("Nuevo torneo de Carcasonne")
        }

        Button {
            id: catanButton
            width: 291
            height: 60
            text: qsTr("Nuevo torneo de Catan")
        }
    }

}
