#ifndef TORNEOMODEL_H
#define TORNEOMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QList>

#include "torneodata.h"

class TorneoModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit TorneoModel(QObject *parent = 0);

    enum TorneoRoles
    {
        NombreRole=Qt::UserRole+1,
        TipoRole,
        IDRole
    };
    Q_ENUM(TorneoRoles)

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QHash<int,QByteArray> roleNames() const;
    void setListaTorneos(QList<TorneoData*> listado);
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    void updateTorneo(int id,QString nombre,QString tipo);
    void addTorneo(TorneoData *torneo);

signals:

public slots:

private:

    QList<TorneoData*> _listaTorneos;

};

#endif // TORNEOMODEL_H
