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

    Q_PROPERTY(int estimacionMesas READ estimacionMesas NOTIFY changedEstimacion)
    Q_PROPERTY(int numeroMesas READ numeroMesas NOTIFY changedNumeroMesas)
    Q_PROPERTY(int minimoJugadores READ minimoJugadores NOTIFY changedMinimoJugadores)
    Q_PROPERTY(bool ready READ isReady NOTIFY changedReady)

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

    int estimacionMesas() const;
    int numeroMesas() const;
    int minimoJugadores() const;
    bool isReady() const;

signals:

    void changedEstimacion(int n);
    void changedNumeroMesas(int n);
    void changedMinimoJugadores(int n);
    void changedReady(bool t);

public slots:

private:
    explicit RefereeDatabase(QObject *parent = 0);

    static RefereeDatabase *_instance;
    static QString currentVersion;


    QSqlDatabase _db;
    int _currentTorneo;
    TorneoData *_currentTorneoData;
    TorneoModel *_torneos;
    ParticipantesModel *_participantes;

    void updateToNextVersion();
    QString checkDatabaseVersion() const;

private slots:

    void updateEstimacionMesas(int n);
    void updateNumeroMesas(int n);
};

#endif // REFEREEDATABASE_H
