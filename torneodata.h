#ifndef TORNEODATA_H
#define TORNEODATA_H

#include <QObject>

class TorneoData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString nombre READ nombre WRITE setNombre NOTIFY nombreChanged)
    Q_PROPERTY(QString tipo READ tipo WRITE setTipo NOTIFY tipoChanged)
public:
    explicit TorneoData(QObject *parent = 0);

    QString nombre() const
    { return _nombre; }

    QString tipo() const
    { return _tipo; }

signals:

    void nombreChanged(QString n);
    void tipoChanged(QString t);

public slots:

    void setNombre(QString n);
    void setTipo(QString t);

private:

    QString _nombre;
    QString _tipo;
};

#endif // TORNEODATA_H
