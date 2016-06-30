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

#include "refereedatabase.h"
#include <QDebug>

RefereeDatabase *RefereeDatabase::_instance=0;

RefereeDatabase *RefereeDatabase::instance()
{
    if(!_instance)
        _instance=new RefereeDatabase(0);

    return _instance;
}

RefereeDatabase::RefereeDatabase(QObject *parent) : QObject(parent)
{
    //Crear la base de datos
    _db=QSqlDatabase::addDatabase("QSQLITE");

    _db.setDatabaseName(QStringLiteral("ccreferee.db"));

    QFileInfo dPath("ccreferee.db");

    bool needToBuild=!dPath.exists();

    _db.open();

    if(needToBuild) {
        QSqlQuery query(_db);

        query.exec("CREATE TABLE IF NOT EXISTS Metadata ("
                   "databaseVersion TEXT NOT NULL"
                   ")");

        query.exec("CREATE TABLE IF NOT EXISTS Torneo ("
                   "idTorneo INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "nombre TEXT NOT NULL, "
                   "tipo INTEGER NOT NULL DEFAULT 0"
                   ")");

        query.exec("CREATE TABLE IF NOT EXISTS Participante ("
                   "idParticipante INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "idTorneo INTEGER NOT NULL, "
                   "nombre TEXT NO NULL, "
                   "checked INTEGER NOT NULL DEFAULT 0, "
                   "FOREIGN KEY(idTorneo) REFERENCES Torneo(idTorneo)"
                   ")");
    }
    _torneos=0;
}

TorneoData *RefereeDatabase::getTorneo(int id)
{
    TorneoData *data=new TorneoData(this);

    data->setNombre("Mi Torneo de prueba");
    data->setTipo("Catan");

    return data;
}

TorneoModel *RefereeDatabase::getTorneoModel()
{
    if(_torneos)
        return _torneos;

    _torneos=new TorneoModel(this);

    QList<TorneoData*> listaTorneos;
    {
        QSqlQuery query(_db);

        query.exec("SELECT idTorneo,nombre,tipo FROM Torneo");

        while(query.next()) {
            TorneoData *torneo=new TorneoData(this);
            torneo->setInternalID(query.value(0).toInt());
            torneo->setNombre(query.value(1).toString());
            torneo->setTipo(query.value(2).toString());
            listaTorneos.append(torneo);
        }
    }

    _torneos->setListaTorneos(listaTorneos);

    return _torneos;
}

void RefereeDatabase::updateTorneoData(int id, QString nombre, QString tipo)
{
    {
        QSqlQuery query(_db);
        query.prepare("UPDATE Torneo SET nombre=:nombre,tipo=:tipo WHERE idTorneo=:id");
        query.bindValue(":nombre",nombre);
        query.bindValue(":tipo",tipo);
        query.bindValue(":id",id);
        qDebug() << "ID: "<<id<<" NOMBRE: "<<nombre<<" TIPO: "<<tipo;

        if(!query.exec())
            qDebug() << "ERROR EN updateTorneoData: "<<query.lastError().text();
    }
    _torneos->updateTorneo(id,nombre,tipo);
}
