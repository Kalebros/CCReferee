#include "participantesmodel.h"
#include "refereedatabase.h"


ParticipantesModel::ParticipantesModel(QObject *parent) : QAbstractListModel(parent)
{
    _listaParticipantes=QList<ParticipanteData*>();
}

QHash<int,QByteArray> ParticipantesModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[IDParticipanteRole]="idParticipante";
    roles[IDTorneoRole]="idTorneo";
    roles[NombreRole]="nombre";
    roles[CheckedRole]="checking";

    return roles;
}

Qt::ItemFlags ParticipantesModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return QAbstractListModel::flags(index);

    return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
}

int ParticipantesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return _listaParticipantes.count();
}

QVariant ParticipantesModel::data(const QModelIndex &index, int role) const
{
    QVariant res;
    if(!index.isValid() || index.row()>=_listaParticipantes.count())
        return res;

    switch(role) {
    case Qt::DisplayRole:
        res=_listaParticipantes.at(index.row())->getNombre();
        break;
    case Qt::EditRole:
        res=_listaParticipantes.at(index.row())->getNombre();
        break;
    case IDParticipanteRole:
        res=_listaParticipantes.at(index.row())->getIDParticipante();
        break;
    case IDTorneoRole:
        res=_listaParticipantes.at(index.row())->getIDTorneo();
        break;
    case NombreRole:
        res=_listaParticipantes.at(index.row())->getNombre();
        break;
    case CheckedRole:
        res=_listaParticipantes.at(index.row())->getChecking();
        break;
    default:
        break;
    }

    return res;
}

bool ParticipantesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid() || index.row()>=_listaParticipantes.count())
        return false;

    switch(role) {
    case Qt::EditRole:
        _listaParticipantes[index.row()]->setNombre(value.toString());
        break;
    case IDParticipanteRole:
        _listaParticipantes[index.row()]->setIDParticipante(value.toInt());
        break;
    case IDTorneoRole:
        _listaParticipantes[index.row()]->setIDTorneo(value.toInt());
        break;
    case NombreRole:
        _listaParticipantes[index.row()]->setNombre(value.toString());
        break;
    case CheckedRole:
        _listaParticipantes[index.row()]->setChecking(value.toBool());
        break;
    default:
        break;
    }

    RefereeDatabase::instance()->updateParticipante(_listaParticipantes[index.row()]->getIDParticipante(),_listaParticipantes[index.row()]);
    emit dataChanged(index,index);

    return true;
}

void ParticipantesModel::setListaParticipantes(QList<ParticipanteData*> lista)
{
    beginResetModel();
    foreach(ParticipanteData *data,_listaParticipantes)
        delete data;
    _listaParticipantes.clear();
    _listaParticipantes=lista;
    endResetModel();
}
