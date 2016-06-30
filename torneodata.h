#ifndef TORNEODATA_H
#define TORNEODATA_H

#include <QObject>

class TorneoData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString nombre READ nombre WRITE setNombre NOTIFY nombreChanged)
    Q_PROPERTY(QString tipo READ tipo WRITE setTipo NOTIFY tipoChanged)
    Q_PROPERTY(int internalID READ internalID WRITE setInternalID NOTIFY internalIDChanged)
public:
    explicit TorneoData(QObject *parent = 0);

    QString nombre() const
    { return _nombre; }

    QString tipo() const
    { return _tipo; }

    int internalID() const
    { return _internalID; }


signals:

    void nombreChanged(QString n);
    void tipoChanged(QString t);
    void internalIDChanged(int id);

public slots:

    void setNombre(QString n);
    void setTipo(QString t);
    void setInternalID(int id);

private:

    QString _nombre;
    QString _tipo;
    int _internalID;
};

#endif // TORNEODATA_H
