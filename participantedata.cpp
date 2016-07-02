#include "participantedata.h"

ParticipanteData::ParticipanteData(QObject *parent) : QObject(parent)
{
    _idTorneo=_idParticipante=-1;
    _isChecked=false;
    _nombre=QString();
}

void ParticipanteData::setIDParticipante(int id)
{
    _idParticipante=id;
    emit changeIDParticipante(_idParticipante);
}

void ParticipanteData::setIDTorneo(int id)
{
    _idTorneo=id;
    emit changeIDTorneo(_idTorneo);
}

void ParticipanteData::setNombre(QString nombre)
{
    _nombre=nombre;
    emit changeNombre(_nombre);
}

void ParticipanteData::setChecking(bool check)
{
    _isChecked=check;
    emit changeChecking(_isChecked);
}
