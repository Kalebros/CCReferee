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

#include "torneodata.h"

TorneoData::TorneoData(QObject *parent) : QObject(parent)
{
    _nombre=QString();
    _tipo=QString();
    _internalID=-1;
}

void TorneoData::setNombre(QString n)
{
    _nombre=n;
    emit nombreChanged(_nombre);
}

void TorneoData::setTipo(QString t)
{
    _tipo=t;
    emit tipoChanged(_tipo);
    if(_tipo=="Catan")
        emit changedMinimoJugadores(12);
    else emit changedMinimoJugadores(8);
}

void TorneoData::setInternalID(int id)
{
    _internalID=id;
    emit internalIDChanged(_internalID);
}

int TorneoData::minimoJugadores() const
{
    if(_tipo=="Catan")
        return 12;
    else return 8;
}
