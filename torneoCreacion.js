var torneo

function createInfoTorneo(nombre,tipo,parent,idObject) {

    var resTorneo=Qt.createQmlObject('import Bardo.CCTorneo.TorneoData 1.0; TorneoData{nombre: ""; tipo: "Catan"}',
                                     parent,
                                     idObject)

    resTorneo.nombre=nombre
    resTorneo.tipo=tipo

    return resTorneo

}
