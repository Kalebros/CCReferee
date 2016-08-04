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

QString RefereeDatabase::currentVersion="1.4";

RefereeDatabase *RefereeDatabase::_instance=0;

RefereeDatabase *RefereeDatabase::instance()
{
    if(!_instance)
        _instance=new RefereeDatabase(0);

    return _instance;
}

RefereeDatabase::RefereeDatabase(QObject *parent) : QObject(parent)
{
    //Preparar reloj
    begining=std::chrono::high_resolution_clock::now();

    //Crear la base de datos
    _db=QSqlDatabase::addDatabase("QSQLITE");

    _db.setDatabaseName(QStringLiteral("ccreferee.db"));

    QFileInfo dPath("ccreferee.db");

    bool needToBuild=!dPath.exists();

    _db.open();

    if(needToBuild) {
        QSqlQuery query(_db);

        //Hay que usar transacciones para mayor seguridad

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

        query.exec("CREATE TABLE IF NOT EXISTS Ronda "
                      "("
                      "idRonda INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "idTorneo INTEGER NOT NULL, "
                      "nombreRonda TEXT NOT NULL DEFAULT 'Primera Ronda', "
                      "FOREIGN KEY(idTorneo) REFERENCES Torneo(idTorneo) "
                      ")");
        query.exec("CREATE TABLE IF NOT EXISTS Mesa "
                   "("
                   "idMesa INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "idRonda INTEGER NOT NULL, "
                   "nombreMesa TEXT NOT NULL, "
                   "FOREIGN KEY(idRonda) REFERENCES Ronda(idRonda) "
                   ")");
        query.exec("CREATE TABLE IF NOT EXISTS Mesa "
                   "("
                   "idMesa INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "idRonda INTEGER NOT NULL, "
                   "nombreMesa TEXT NOT NULL, "
                   "FOREIGN KEY(idRonda) REFERENCES Ronda(idRonda) "
                   ")");

        query.exec("CREATE TABLE IF NOT EXISTS JugadorParticipaEnMesa "
                   "("
                   "idJugador INTEGER NOT NULL, "
                   "idMesa INTEGER NOT NULL, "
                   "puntuacionReal INTEGER NOT NULL DEFAULT 0, "
                   "puntuacionGeneral INTEGER NOT NULL DEFAULT 0, "
                   "puntuacionCorregida INTEGER NOT NULL DEFAULT 0, "
                   "FOREIGN KEY(idJugador) REFERENCES Jugador(idJugador), "
                   "FOREIGN KEY(idMesa) REFERENCES Mesa(idMesa), "
                   "PRIMARY KEY (idJugador,idMesa)"
                   ")");

        query.exec("CREATE VIEW IF NOT EXISTS VistaPrimeraRonda as "
                   "SELECT r.idTorneo as idTorneo,m.nombreMesa as mesa,p.idParticipante as idParticipante, "
                   "p.nombre as nombre,jpm.puntuacionReal as puntuacionReal, jpm.puntuacionGeneral as puntuacionGeneral, "
                   "jpm.puntuacionCorregida as puntuacionCorregida "
                   "from Participante as p, jugadorparticipaenmesa as jpm,Mesa as m,Ronda as r "
                   "WHERE p.idParticipante=jpm.idJugador and m.idMesa=jpm.idMesa and m.idRonda=r.idRonda "
                   "and r.nombreRonda='Primera ronda' order by mesa");

        query.exec("CREATE VIEW IF NOT EXISTS VistaSegundaRonda as "
                   "SELECT r.idTorneo as idTorneo,m.nombreMesa as mesa,p.idParticipante as idParticipante, "
                   "p.nombre as nombre,jpm.puntuacionReal as puntuacionReal, jpm.puntuacionGeneral as puntuacionGeneral, "
                   "jpm.puntuacionCorregida as puntuacionCorregida "
                   "from Participante as p, jugadorparticipaenmesa as jpm,Mesa as m,Ronda as r "
                   "WHERE p.idParticipante=jpm.idJugador and m.idMesa=jpm.idMesa and m.idRonda=r.idRonda "
                   "and r.nombreRonda='Segunda ronda' order by mesa");

        query.exec("CREATE VIEW IF NOT EXISTS VistaTerceraRonda as "
                   "SELECT r.idTorneo as idTorneo,m.nombreMesa as mesa,p.idParticipante as idParticipante, "
                   "p.nombre as nombre,jpm.puntuacionReal as puntuacionReal, jpm.puntuacionGeneral as puntuacionGeneral, "
                   "jpm.puntuacionCorregida as puntuacionCorregida "
                   "from Participante as p, jugadorparticipaenmesa as jpm,Mesa as m,Ronda as r "
                   "WHERE p.idParticipante=jpm.idJugador and m.idMesa=jpm.idMesa and m.idRonda=r.idRonda "
                   "and r.nombreRonda='Tercera ronda' order by mesa");

        query.exec("CREATE VIEW IF NOT EXISTS VistaSemifinalRonda as "
                   "SELECT r.idTorneo as idTorneo,m.nombreMesa as mesa,p.idParticipante as idParticipante, "
                   "p.nombre as nombre,jpm.puntuacionReal as puntuacionReal, jpm.puntuacionGeneral as puntuacionGeneral, "
                   "jpm.puntuacionCorregida as puntuacionCorregida "
                   "from Participante as p, jugadorparticipaenmesa as jpm,Mesa as m,Ronda as r "
                   "WHERE p.idParticipante=jpm.idJugador and m.idMesa=jpm.idMesa and m.idRonda=r.idRonda "
                   "and r.nombreRonda='Semifinal' order by mesa");

        query.exec("CREATE VIEW IF NOT EXISTS VistaFinalRonda as "
                   "SELECT r.idTorneo as idTorneo,m.nombreMesa as mesa,p.idParticipante as idParticipante, "
                   "p.nombre as nombre,jpm.puntuacionReal as puntuacionReal, jpm.puntuacionGeneral as puntuacionGeneral, "
                   "jpm.puntuacionCorregida as puntuacionCorregida "
                   "from Participante as p, jugadorparticipaenmesa as jpm,Mesa as m,Ronda as r "
                   "WHERE p.idParticipante=jpm.idJugador and m.idMesa=jpm.idMesa and m.idRonda=r.idRonda "
                   "and r.nombreRonda='Final' order by mesa");

        query.exec("INSERT INTO Metadata(databaseVersion) VALUES('1.4')");
    }
    if(checkDatabaseVersion()!=RefereeDatabase::currentVersion)
        updateToNextVersion();
    _torneos=0;
    _participantes=0;
    _currentTorneoData=0;
    _currentTorneo=-1;

    //Preparar reloj
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
    QString dbVersion=checkDatabaseVersion();
    //Update de 1.0 a 1.1
    if(dbVersion==QStringLiteral("1.0"))
    {
        //Más seguro utilizando transacciones,
        //para refactorizar más adelante
        QSqlQuery query(_db);
        query.exec("CREATE TABLE IF NOT EXISTS Ronda "
                      "("
                      "idRonda INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "idTorneo INTEGER NOT NULL, "
                      "nombreRonda TEXT NOT NULL DEFAULT 'Primera Ronda', "
                      "FOREIGN KEY(idTorneo) REFERENCES Torneo(idTorneo) "
                      ")");
        query.exec("CREATE TABLE IF NOT EXISTS Mesa "
                   "("
                   "idMesa INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "idRonda INTEGER NOT NULL, "
                   "nombreMesa TEXT NOT NULL, "
                   "FOREIGN KEY(idRonda) REFERENCES Ronda(idRonda) "
                   ")");
        query.exec("CREATE TABLE IF NOT EXISTS Mesa "
                   "("
                   "idMesa INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "idRonda INTEGER NOT NULL, "
                   "nombreMesa TEXT NOT NULL, "
                   "FOREIGN KEY(idRonda) REFERENCES Ronda(idRonda) "
                   ")");
        query.exec("UPDATE Metadata SET databaseVersion='1.1' "
                   "WHERE databaseVersion='1.0'");
        dbVersion=QStringLiteral("1.1");
    }
    if(dbVersion==QStringLiteral("1.1"))
    {
        QSqlQuery query(_db);
        query.exec("CREATE TABLE IF NOT EXISTS JugadorParticipaEnMesa "
                   "("
                   "idJugador INTEGER NOT NULL, "
                   "idMesa INTEGER NOT NULL, "
                   "puntuacionReal INTEGER NOT NULL DEFAULT 0, "
                   "puntuacionGeneral INTEGER NOT NULL DEFAULT 0, "
                   "FOREIGN KEY(idJugador) REFERENCES Jugador(idJugador), "
                   "FOREIGN KEY(idMesa) REFERENCES Mesa(idMesa), "
                   "PRIMARY KEY (idJugador,idMesa)"
                   ")");
        query.exec("UPDATE Metadata SET databaseVersion='1.2' "
                   "WHERE databaseVersion='1.1'");
        dbVersion==QStringLiteral("1.2");
    }
    if(dbVersion==QStringLiteral("1.2"))
    {
        QSqlQuery query(_db);
        query.exec("ALTER TABLE JugadorParticipaEnMesa "
                   "ADD COLUMN puntuacionCorregida INTEGER NOT NULL DEFAULT 0");
        query.exec("UPDATE Metadata SET databaseVersion='1.3' "
                   "WHERE databaseVersion='1.2'");
        dbVersion=QStringLiteral("1.3");
    }
    if(dbVersion==QStringLiteral("1.3")) {
        QSqlQuery query(_db);
        query.exec("CREATE VIEW IF NOT EXISTS VistaPrimeraRonda as "
                   "SELECT r.idTorneo as idTorneo,m.nombreMesa as mesa,p.idParticipante as idParticipante, "
                   "p.nombre as nombre,jpm.puntuacionReal as puntuacionReal, jpm.puntuacionGeneral as puntuacionGeneral, "
                   "jpm.puntuacionCorregida as puntuacionCorregida "
                   "from Participante as p, jugadorparticipaenmesa as jpm,Mesa as m,Ronda as r "
                   "WHERE p.idParticipante=jpm.idJugador and m.idMesa=jpm.idMesa and m.idRonda=r.idRonda "
                   "and r.nombreRonda='Primera ronda' order by mesa");

        query.exec("CREATE VIEW IF NOT EXISTS VistaSegundaRonda as "
                   "SELECT r.idTorneo as idTorneo,m.nombreMesa as mesa,p.idParticipante as idParticipante, "
                   "p.nombre as nombre,jpm.puntuacionReal as puntuacionReal, jpm.puntuacionGeneral as puntuacionGeneral, "
                   "jpm.puntuacionCorregida as puntuacionCorregida "
                   "from Participante as p, jugadorparticipaenmesa as jpm,Mesa as m,Ronda as r "
                   "WHERE p.idParticipante=jpm.idJugador and m.idMesa=jpm.idMesa and m.idRonda=r.idRonda "
                   "and r.nombreRonda='Segunda ronda' order by mesa");

        query.exec("CREATE VIEW IF NOT EXISTS VistaTerceraRonda as "
                   "SELECT r.idTorneo as idTorneo,m.nombreMesa as mesa,p.idParticipante as idParticipante, "
                   "p.nombre as nombre,jpm.puntuacionReal as puntuacionReal, jpm.puntuacionGeneral as puntuacionGeneral, "
                   "jpm.puntuacionCorregida as puntuacionCorregida "
                   "from Participante as p, jugadorparticipaenmesa as jpm,Mesa as m,Ronda as r "
                   "WHERE p.idParticipante=jpm.idJugador and m.idMesa=jpm.idMesa and m.idRonda=r.idRonda "
                   "and r.nombreRonda='Tercera ronda' order by mesa");

        query.exec("CREATE VIEW IF NOT EXISTS VistaSemifinalRonda as "
                   "SELECT r.idTorneo as idTorneo,m.nombreMesa as mesa,p.idParticipante as idParticipante, "
                   "p.nombre as nombre,jpm.puntuacionReal as puntuacionReal, jpm.puntuacionGeneral as puntuacionGeneral, "
                   "jpm.puntuacionCorregida as puntuacionCorregida "
                   "from Participante as p, jugadorparticipaenmesa as jpm,Mesa as m,Ronda as r "
                   "WHERE p.idParticipante=jpm.idJugador and m.idMesa=jpm.idMesa and m.idRonda=r.idRonda "
                   "and r.nombreRonda='Semifinal' order by mesa");

        query.exec("CREATE VIEW IF NOT EXISTS VistaFinalRonda as "
                   "SELECT r.idTorneo as idTorneo,m.nombreMesa as mesa,p.idParticipante as idParticipante, "
                   "p.nombre as nombre,jpm.puntuacionReal as puntuacionReal, jpm.puntuacionGeneral as puntuacionGeneral, "
                   "jpm.puntuacionCorregida as puntuacionCorregida "
                   "from Participante as p, jugadorparticipaenmesa as jpm,Mesa as m,Ronda as r "
                   "WHERE p.idParticipante=jpm.idJugador and m.idMesa=jpm.idMesa and m.idRonda=r.idRonda "
                   "and r.nombreRonda='Final' order by mesa");

        query.exec("UPDATE Metadata SET databaseVersion='1.4' "
                   "WHERE databaseVersion='1.3'");
        dbVersion=QStringLiteral("1.4");
    }
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

int RefereeDatabase::minimoJugadores() const
{
   if(!_currentTorneoData)
       return -1;
   if(_currentTorneoData->tipo()=="Catan")
       return 12;
   else return 8;
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
    _currentTorneoData=getTorneo(idTorneo);
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
        if(_currentTorneoData->tipo()=="Catan")
            emit changedMinimoJugadores(12);
        else emit changedMinimoJugadores(8);
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
    int res=0;
    int nJugadores=_participantes->numeroParticipantes();
    if(nJugadores<8)
        return res;
    if(!(nJugadores%4))
        res= nJugadores/(int)4;
    else if(!((nJugadores-3)%4))
        res= ((nJugadores-3)/4)+1;
    else if(!((nJugadores-6)%4))
        res= ((nJugadores-6)/4)+2;
    else res= ((nJugadores-9)/4)+3;
    return res;
}

int RefereeDatabase::numeroMesas() const
{
    int nJugadores=_participantes->participantesCheck();
    if(nJugadores<8)
        return 0;
    if(!(nJugadores%4))
        return nJugadores/(int)4;
    else if(!((nJugadores-3)%4))
        return ((nJugadores-3)/4)+1;
    else if(!((nJugadores-6)%4))
        return ((nJugadores-6)/4)+2;
    else return ((nJugadores-9)/4)+3;
    return 0;
}

bool RefereeDatabase::isReady() const
{
    if(_participantes->participantesCheck()>=_currentTorneoData->minimoJugadores())
        return true;
    else return false;
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

void RefereeDatabase::generateRepartoRondaInicial()
{
    if(!_currentTorneoData || !_participantes)
        return;

    if(_participantes->participantesCheck() < _currentTorneoData->minimoJugadores())
        return;

    int numJugadores=_participantes->participantesCheck();
    int mesasCuatro=0,mesasTres=0;

    //Seguro se puede refactorizar el codigo siguiente
    if(!(numJugadores%4))
        mesasCuatro=numJugadores/4;
    else {
        numJugadores-=3;
        mesasTres++;
        if(!(numJugadores%4))
            mesasCuatro=numJugadores/4;
        else {
            numJugadores-=3;
            mesasTres++;
            if(!(numJugadores%4))
                mesasCuatro=numJugadores/4;
            else {
                numJugadores-=3;
                mesasTres++;
                mesasCuatro=numJugadores/4;
            }
        }
    }

    QList<ParticipanteData*> listado=_participantes->getListaParticipantes();

    QList<ParticipanteData*> listadoCheck;

    for(int i=0;i<listado.count();i++) {
        if(listado.at(i)->getChecking())
            listadoCheck.append(listado[i]);
    }

    QVector<int> nPart=repartoMesa(listadoCheck.count());

    //Realizar el reparto dentro de la base de datos

    int idRonda=addRondaToTorneo(_currentTorneo,QStringLiteral("Primera ronda"));
    for(int i=0;i<mesasCuatro;i++){
        int idMesa=addMesaToRonda(idRonda,QStringLiteral("Mesa ")+QString::number(i));
        for(int j=0+(4*i);j<4+(i*4);j++) {
            addParticipanteToMesa(idMesa,listadoCheck.at(nPart.at(j)));
        }
    }

    for(int i=0;i<mesasTres;i++) {
        int idMesa=addMesaToRonda(idRonda,QStringLiteral("Mesa ")+QString::number(i+mesasCuatro));
        for(int j=(mesasCuatro*4)+(3*i);j<((mesasCuatro*4)+3)+(3*i);j++) {
            addParticipanteToMesa(idMesa,listadoCheck.at(nPart.at(j)));
        }
    }
}

int RefereeDatabase::addRondaToTorneo(int torneo, QString ronda)
{
    int res=-1;
    if(!_db.isOpen())
        return res;

    QSqlQuery query(_db);
    _db.transaction();
    query.prepare("INSERT INTO Ronda(idTorneo,nombreRonda) "
                  "VALUES(:torneo,:nombre)");
    query.bindValue(":torneo",torneo);
    query.bindValue(":nombre",ronda);
    if(query.exec()) {
        query.exec("SELECT last_insert_rowid()");
        query.next();
        res=query.value(0).toInt();
        _db.commit();
    }
    else _db.rollback();

    return res;
}

void RefereeDatabase::clearRondaTorneo(int torneo, QString ronda)
{
    if(!_db.isOpen())
        return;

    QSqlQuery query(_db);
    _db.transaction();
    query.prepare("delete from JugadorParticipaEnMesa where idMesa in ( "
                  "select idMesa from Mesa, ronda where mesa.idRonda=Ronda.idRonda and Ronda.nombreRonda=:ronda and idTorneo=:torneo)");
    query.bindValue(":torneo",torneo);
    query.bindValue(":ronda",ronda);
    if(!query.exec()) {
        _db.rollback();
        return;
    }
    query.prepare("delete from Mesa where idMesa in ("
                  "select idMesa from Mesa,Ronda where mesa.idRonda=Ronda.idRonda and Ronda.nombreRonda=:ronda "
                  "and Ronda.idTorneo=:torneo)");
    query.bindValue(":torneo",torneo);
    query.bindValue(":ronda",ronda);
    if(!query.exec()) {
        _db.rollback();
        return;
    }
    query.prepare("delete from ronda where idRonda in ("
                  "select idRonda from Ronda where Ronda.nombreRonda=:ronda "
                  "and ronda.idTorneo=:torneo");
    query.bindValue(":torneo",torneo);
    query.bindValue(":ronda",ronda);
    if(!query.exec()) {
        _db.rollback();
        return;
    }
    _db.commit();
    return;
}

int RefereeDatabase::addMesaToRonda(int ronda, QString mesa)
{
    int res=-1;
    if(!_db.isOpen())
        return res;

    QSqlQuery query(_db);
    _db.transaction();
    query.prepare("INSERT INTO Mesa(idRonda,nombreMesa) "
                  "VALUES(:ronda,:mesa)");
    query.bindValue(":ronda",ronda);
    query.bindValue(":mesa",mesa);
    if(query.exec()) {
        query.exec("SELECT last_insert_rowid()");
        query.next();
        res=query.value(0).toInt();
        _db.commit();
    }
    else _db.rollback();
    return res;
}

void RefereeDatabase::addParticipanteToMesa(int mesa, const ParticipanteData *participante)
{
    if(!_db.isOpen())
        return;

    QSqlQuery query(_db);
    _db.transaction();
    query.prepare("INSERT INTO JugadorParticipaEnMesa(idMesa,idJugador) "
                  "VALUES(:mesa,:id)");
    query.bindValue(":mesa",mesa);
    query.bindValue(":id",participante->getIDParticipante());
    if(!query.exec())
        _db.rollback();
    else _db.commit();

    return;
}

QVector<int> RefereeDatabase::repartoMesa(int numReparto)
{
    std::chrono::high_resolution_clock::duration d=begining-std::chrono::high_resolution_clock::now();
    unsigned seed=d.count();
    generadorRand.seed(seed);
    std::uniform_int_distribution<int> distribucion(0,numReparto-1);
    QVector<int> nPart;
    int currentIndex=0;
    for(int j=0;j<numReparto;j++) {
        int nAsignado=distribucion(generadorRand);
        bool repeat=true;
        while(repeat) {
            bool partialCheck=false;
            for(int k=0;k<currentIndex && !partialCheck;k++) {
                if(nAsignado==nPart[k]
                        and !partialCheck)
                    partialCheck=true;
            }
            if(partialCheck) nAsignado=distribucion(generadorRand);
            else repeat=false;
        }
        nPart.append(nAsignado);
        currentIndex++;
    }
    return nPart;
}
