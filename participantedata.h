#ifndef PARTICIPANTEDATA_H
#define PARTICIPANTEDATA_H

#include <QObject>

class ParticipanteData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int idParticipante READ getIDParticipante WRITE setIDParticipante NOTIFY changeIDParticipante)
    Q_PROPERTY(int idTorneo READ getIDTorneo WRITE setIDTorneo NOTIFY changeIDTorneo)
    Q_PROPERTY(QString nombre READ getNombre WRITE setNombre NOTIFY changeNombre)
    Q_PROPERTY(bool checking READ getChecking WRITE setChecking NOTIFY changeChecking)
public:
    explicit ParticipanteData(QObject *parent = 0);

    int getIDParticipante() const
    { return _idParticipante; }

    int getIDTorneo() const
    { return _idTorneo; }

    QString getNombre() const
    { return _nombre; }

    bool getChecking() const
    { return _isChecked; }

signals:

    void changeIDParticipante(int id);
    void changeIDTorneo(int id);
    void changeNombre(QString nombre);
    void changeChecking(bool check);

public slots:

    void setIDParticipante(int id);
    void setIDTorneo(int id);
    void setNombre(QString nombre);
    void setChecking(bool check);

private:

    int _idParticipante;
    int _idTorneo;
    QString _nombre;
    bool _isChecked;
};

#endif // PARTICIPANTEDATA_H
