#ifndef REFEREEDATABASE_H
#define REFEREEDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileInfo>

#include "torneodata.h"
#include "torneomodel.h"

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
    Q_PROPERTY(int valorDedicado READ getValorDedicado WRITE setValorDedicado NOTIFY valorDedicadoChange)
public:

    static RefereeDatabase *instance();

    int getValorDedicado() const
    { return _vDedicado; }

    Q_INVOKABLE TorneoData *getTorneo(int id);
    Q_INVOKABLE TorneoModel *getTorneoModel();

    Q_INVOKABLE void updateTorneoData(int id,QString nombre,QString tipo);

signals:

    void valorDedicadoChange(int v);

public slots:

    void setValorDedicado(int v)
    {
        _vDedicado=v;
        emit valorDedicadoChange(_vDedicado);
    }

private:

    explicit RefereeDatabase(QObject *parent = 0);

    static RefereeDatabase *_instance;

    QSqlDatabase _db;
    int _vDedicado;
    TorneoModel *_torneos;
};

#endif // REFEREEDATABASE_H
