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

QString RefereeDatabase::currentVersion="1.0";

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

        query.exec("INSERT INTO Metadata(databaseVersion) VALUES('1.0')");
    }
    if(checkDatabaseVersion()!=RefereeDatabase::currentVersion)
        updateToNextVersion();
    _torneos=0;
    _participantes=0;
    _currentTorneo=-1;
}

QString RefereeDatabase::checkDatabaseVersion() const
{
    QString res;
    {
        QSqlQuery query(_db);
        query.exec("SELECT databaseVersion FROM Metadata");
        query.next();
        res=query.value(0).toString();
    }

    return res;
}

void RefereeDatabase::updateToNextVersion()
{
    //Update to version 1.0
    return;
}


TorneoData *RefereeDatabase::getTorneo(int id)
{
    TorneoData *data=0;

    if(_torneos) {
            data=_torneos->getTorneo(id);
    }
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

void RefereeDatabase::updateEstimacionMesas(int n)
{
    Q_UNUSED(n)
    emit changedEstimacion(estimacionMesas());
}

void RefereeDatabase::updateNumeroMesas(int n)
{
    Q_UNUSED(n)
    emit changedNumeroMesas(numeroMesas());
}

ParticipantesModel *RefereeDatabase::getParticipantesModel()
{
    if(_participantes)
        return _participantes;

    _participantes=new ParticipantesModel(this);

    //Conexiones
    connect(_participantes,SIGNAL(changedNumeroParticipantes(int)),this,SLOT(updateEstimacionMesas(int)));
    connect(_participantes,SIGNAL(changedParticipantesCheck(int)),this,SLOT(updateNumeroMesas(int)));

    if(_currentTorneo!=-1) {
        QList<ParticipanteData*> listaParticipantes;
        {
            QSqlQuery query(_db);

            query.prepare("SELECT idParticipante,idTorneo,nombre,checked "
                          "FROM Participante "
                          "WHERE idTorneo=:idTorneo");
            query.bindValue(":idTorneo",_currentTorneo);
            query.exec();

            while(query.next()) {
                ParticipanteData *participante=new ParticipanteData(this);
                participante->setIDParticipante(query.value(0).toInt());
                participante->setIDTorneo(query.value(1).toInt());
                participante->setNombre(query.value(2).toString());
                participante->setChecking(query.value(3).toBool());
                listaParticipantes.append(participante);
            }
        }
        _participantes->setListaParticipantes(listaParticipantes);
    }

    return _participantes;
}

void RefereeDatabase::setCurrentTorneo(int idTorneo)
{
    _currentTorneo=idTorneo;
    if(_participantes) {
        QList<ParticipanteData*> listaParticipantes;
        {
            QSqlQuery query(_db);

            query.prepare("SELECT idParticipante,idTorneo,nombre,checked "
                          "FROM Participante "
                          "WHERE idTorneo=:idTorneo");
            query.bindValue(":idTorneo",_currentTorneo);
            query.exec();

            while(query.next()) {
                ParticipanteData *participante=new ParticipanteData(this);
                participante->setIDParticipante(query.value(0).toInt());
                participante->setIDTorneo(query.value(1).toInt());
                participante->setNombre(query.value(2).toString());
                participante->setChecking(query.value(3).toBool());
                listaParticipantes.append(participante);
            }
        }
        _participantes->setListaParticipantes(listaParticipantes);
    }
}

void RefereeDatabase::updateTorneoData(int id, QString nombre, QString tipo)
{
    {
        QSqlQuery query(_db);
        _db.transaction();
        query.prepare("UPDATE Torneo SET nombre=:nombre,tipo=:tipo WHERE idTorneo=:id");
        query.bindValue(":nombre",nombre);
        query.bindValue(":tipo",tipo);
        query.bindValue(":id",id);
        if(query.exec())
            _db.commit();
        else {
            _db.rollback();
            return;
        }
    }
    if(_torneos)
        _torneos->updateTorneo(id,nombre,tipo);
}

int RefereeDatabase::addTorneo(QString nombre, QString tipo)
{
    int nuevaID=-1;
    {
        QSqlQuery query(_db);
        _db.transaction();
        query.prepare("INSERT INTO Torneo(nombre,tipo) "
                      "VALUES(:nombre,:tipo)");
        query.bindValue(":nombre",nombre);
        query.bindValue(":tipo",tipo);
        if(query.exec()) {
            query.exec("SELECT last_insert_rowid()");
            query.next();
            nuevaID=query.value(0).toInt();
            _db.commit();
        }
        else {
            _db.rollback();
            return nuevaID;
        }
    }

    if(_torneos) {
        TorneoData *nuevoTorneo=new TorneoData(this);
        nuevoTorneo->setInternalID(nuevaID);
        nuevoTorneo->setNombre(nombre);
        nuevoTorneo->setTipo(tipo);
        _torneos->addTorneo(nuevoTorneo);
    }

    return nuevaID;

}

void RefereeDatabase::updateParticipante(int idParticipante, ParticipanteData *data)
{
    {
        QSqlQuery query(_db);
        _db.transaction();
        query.prepare("UPDATE Participante "
                      "SET idTorneo=:idTorneo,nombre=:nombre,checked=:isCheck "
                      "WHERE idParticipante=:id");
        query.bindValue(":id",idParticipante);
        query.bindValue(":idTorneo",data->getIDTorneo());
        query.bindValue(":nombre",data->getNombre());
        query.bindValue(":isCheck",data->getChecking());

        if(!query.exec()) {
            _db.rollback();
        }
        else _db.commit();
    }
}

void RefereeDatabase::checkParticipante(int idParticipante,bool check)
{
    {
        QSqlQuery query(_db);
        _db.transaction();
        query.prepare("UPDATE Participante "
                      "SET checked=:check WHERE idParticipante=:id");
        query.bindValue(":id",idParticipante);
        query.bindValue(":check",check);
        if(!query.exec())
            _db.rollback();
        else _db.commit();
    }
}

int RefereeDatabase::estimacionMesas() const
{
    int nJugadores=_participantes->numeroParticipantes();
    if(nJugadores<8)
        return 0;
    if(!(nJugadores%4))
        return nJugadores/(int)4;
    else if(!((nJugadores-3)%4))
        return ((nJugadores-3)%4)+1;
    else if(!((nJugadores-6)%4))
        return ((nJugadores-6)%4)+2;
    else return ((nJugadores-9)%4)+3;
    return 0;
}

int RefereeDatabase::numeroMesas() const
{
    int nJugadores=_participantes->participantesCheck();
    if(nJugadores<8)
        return 0;
    if(!(nJugadores%4))
        return nJugadores/(int)4;
    else if(!((nJugadores-3)%4))
        return ((nJugadores-3)%4)+1;
    else if(!((nJugadores-6)%4))
        return ((nJugadores-6)%4)+2;
    else return ((nJugadores-9)%4)+3;
    return 0;
}

void RefereeDatabase::addParticipante(QString nombre)
{
    int idJugador;
    {
        QSqlQuery query(_db);
        _db.transaction();
        query.prepare("INSERT INTO Participante(idTorneo,nombre) "
                      "VALUES(:idTorneo,:nombre)");
        query.bindValue(":idTorneo",_currentTorneo);
        query.bindValue(":nombre",nombre);

        if(!query.exec())
            _db.rollback();
        else {
            _db.commit();
            query.exec("SELECT last_insert_rowid()");
            query.next();
            idJugador=query.value(0).toInt();
        }
    }
    ParticipanteData *nuevoParticipante=new ParticipanteData(this);
    nuevoParticipante->setIDParticipante(idJugador);
    nuevoParticipante->setNombre(nombre);
    nuevoParticipante->setChecking(false);
    nuevoParticipante->setIDTorneo(_currentTorneo);

    _participantes->addParticipante(nuevoParticipante);
}

