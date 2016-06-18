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


Component {
    Item {
        id: delegate
        x: 10
        y: 10
        width: vistaJugadores.width - 50
        height: labelNombre.height+30
        Column {
            id: column
            spacing: 5
            Label {
                id: labelNombre
                text: nombre
                font.pointSize: 13
                horizontalAlignment: Text.AlignHCenter
            }
            Rectangle {
                id: lastBorder
                height: 1
                color: "slategrey"
                width: delegate.width
            }
        }

    }
}
