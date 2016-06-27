////////////////////////////////////////////////////////////////////////////
///
/// CCReferee
/// Copyright @2016, Antonio Ramírez Marti
/// (morgulero@gmail.com)
///
/// This file is part of CCReferee.
///
/// CCReferee is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// CCReferee is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
///
////////////////////////////////////////////////////////////////////////////

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QColor>

#include "torneodata.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<TorneoData>("Bardo.CCTorneo.TorneoData",1,0,"TorneoData");
    QQmlApplicationEngine engine;

    QQmlContext *contexto=engine.rootContext();
    contexto->setProperty("primaryCatanColor",QColor("orange"));
    contexto->setProperty("primaryCarcassonneColor",QColor("steelblue"));
    contexto->setProperty("secondaryCatanColor",QColor("#FFC107")); //Material.Amber
    contexto->setProperty("secondaryCarcasssonneColor",QColor("#CDDC39")); //Material.Lime
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
