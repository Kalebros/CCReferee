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
    property string texto
    property string numero

    id: marcador
    implicitHeight: textLabel.height + numberLabel.height + 5
    implicitWidth: textLabel.width
    Label {
        id: textLabel
        x:0
        y:0
        text: texto
        font.pointSize: 15
    }
    Label {
        id: numberLabel
        anchors.horizontalCenter: marcador.horizontalCenter
        anchors.top: textLabel.bottom
        anchors.topMargin: 5
        text: numero
        font.pointSize: 25

    }

}
