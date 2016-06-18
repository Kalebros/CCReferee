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

Item {
    id: item1
    width: 358
    height: 642
    property alias cancelButton: cancelButton
    property color labelColor: "#000000"
    property alias vistaTorneos: listView1

    ListView {
        id: listView1
        anchors.top: labelB.bottom
        anchors.topMargin: 6
        anchors.bottom: cancelButton.top
        anchors.bottomMargin: 39
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }

        ScrollBar.vertical: ScrollBar {}
    }

    Label {
        id: labelA
        x: 20
        y: 8
        width: 300
        height: 51
        color: parent.labelColor
        text: "Selecciona un"
        font.pointSize: 30
    }

    Label {
        id: labelB
        x: 20
        y: 48
        width: 300
        height: 51
        color: parent.labelColor
        text: "torneo"
        font.pointSize: 30
    }

    Button {
        id: cancelButton
        x: 97
        y: 558
        width: 166
        height: 40
        text: qsTr("Cancelar")
        anchors.horizontalCenterOffset: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 44
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
