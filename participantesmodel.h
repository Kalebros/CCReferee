#ifndef PARTICIPANTESMODEL_H
#define PARTICIPANTESMODEL_H

#include <QObject>

#include <QAbstractListModel>
#include "participantedata.h"

class ParticipantesModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum ParticipanteRoles
    {
        IDParticipanteRole=Qt::UserRole+1,
        IDTorneoRole,
        NombreRole,
        CheckedRole
    };

    explicit ParticipantesModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent) const;
    QHash<int,QByteArray> roleNames() const;

    void setListaParticipantes(QList<ParticipanteData*> lista);

signals:

public slots:

private:

    QList<ParticipanteData*> _listaParticipantes;
};

#endif // PARTICIPANTESMODEL_H
