#include "torneomodel.h"

TorneoModel::TorneoModel(QObject *parent) : QAbstractItemModel(parent)
{

}

QHash<int,QByteArray> TorneoModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[NombreRole]="nombre";
    roles[TipoRole]="tipo";
    roles[IDRole]="internalID";

    return roles;
}

int TorneoModel::rowCount(const QModelIndex &parent) const
{
    return _listaTorneos.count();
}

int TorneoModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

Qt::ItemFlags TorneoModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return QAbstractItemModel::flags(index);

    return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
}

QVariant TorneoModel::data(const QModelIndex &index, int role) const
{
    QVariant res;
    if(!index.isValid())
        return res;

    switch(role) {
    case Qt::DisplayRole:
        res=_listaTorneos.at(index.row())->nombre();
        break;
    case Qt::EditRole:
        res=_listaTorneos.at(index.row())->nombre();
        break;
    case NombreRole:
        res=_listaTorneos.at(index.row())->nombre();
        break;
    case TipoRole:
        res=_listaTorneos.at(index.row())->tipo();
        break;
    case IDRole:
        res=_listaTorneos.at(index.row())->internalID();
        break;
    default:
        break;
    }

    return res;
}

bool TorneoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;

    switch(role) {
    case Qt::DisplayRole:
        _listaTorneos[index.row()]->setNombre(value.toString());
        emit dataChanged(index,index);
        break;
    case Qt::EditRole:
        _listaTorneos[index.row()]->setNombre(value.toString());
        emit dataChanged(index,index);
        break;
    case NombreRole:
        _listaTorneos[index.row()]->setNombre(value.toString());
        emit dataChanged(index,index);
        break;
    case TipoRole:
        _listaTorneos[index.row()]->setTipo(value.toString());
        emit dataChanged(index,index);
        break;
    case IDRole:
        _listaTorneos[index.row()]->setInternalID(value.toInt());
        emit dataChanged(index,index);
        break;
    default:
        break;
    }

    return true;
}

void TorneoModel::updateTorneo(int id, QString nombre, QString tipo)
{
    bool found=false;
    for(int i=0;i<_listaTorneos.count() && !found;i++) {
        if(_listaTorneos[i]->internalID()==id) {
            _listaTorneos[i]->setNombre(nombre);
            _listaTorneos[i]->setTipo(tipo);
            QModelIndex currentIndex=this->index(i,0,QModelIndex());
            emit dataChanged(currentIndex,currentIndex);
            found=true;
        }
    }
}

void TorneoModel::addTorneo(TorneoData *torneo)
{
    beginInsertRows(QModelIndex(),_listaTorneos.count(),_listaTorneos.count());
    _listaTorneos.append(torneo);
    endInsertRows();
}

QModelIndex TorneoModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row,column);
}

QModelIndex TorneoModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

void TorneoModel::setListaTorneos(QList<TorneoData*> listado)
{
    beginResetModel();
    if(!_listaTorneos.empty())
        foreach(TorneoData *torneo,_listaTorneos)
            delete torneo;
    _listaTorneos=listado;
    endResetModel();
}
