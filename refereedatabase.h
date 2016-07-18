#ifndef REFEREEDATABASE_H
#define REFEREEDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileInfo>

#include "torneodata.h"
#include "torneomodel.h"
#include "participantedata.h"
#include "participantesmodel.h"

/*!
 * @class RefereeDatabase
 *
 * Base de datos empleada en CCReferee, basada en SQLite
 * Signleton
 *
 */
class RefereeDatabase : public QObject
{
    Q_OBJECT

public:

    static RefereeDatabase *instance();

    Q_INVOKABLE TorneoData *getTorneo(int id);
    Q_INVOKABLE TorneoModel *getTorneoModel();
    Q_INVOKABLE ParticipantesModel *getParticipantesModel();

    Q_INVOKABLE void updateTorneoData(int id,QString nombre,QString tipo);
    Q_INVOKABLE int addTorneo(QString nombre, QString tipo);
    Q_INVOKABLE void setCurrentTorneo(int idTorneo);
    Q_INVOKABLE void checkParticipante(int idParticipante,bool check);
    Q_INVOKABLE void addParticipante(QString nombre);

    void updateParticipante(int idParticipante,ParticipanteData *data);


signals:


public slots:

private:
    explicit RefereeDatabase(QObject *parent = 0);

    static RefereeDatabase *_instance;
    static QString currentVersion;


    QSqlDatabase _db;
    int _currentTorneo;
    TorneoModel *_torneos;
    ParticipantesModel *_participantes;

    void updateToNextVersion();
    QString checkDatabaseVersion() const;
};

#endif // REFEREEDATABASE_H
