import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import QtQuick.Layouts 1.0

Item {
    id: item1
    width: 358
    height: 642
    property alias tipoComboBox: comboBox1
    property alias nombreField: textField1
    property string tipo

    ColumnLayout {
        id: tipoColumn
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.top: textField1.bottom
        anchors.topMargin: 23

        Label {
            id: label2
            text: qsTr("Tipo de torneo")
            Layout.preferredHeight: 31
            Layout.preferredWidth: 175
            font.pointSize: 15
            color: tipo=="Catan" ? root.primaryCatan : root.primaryCarca
        }

        ComboBox {
            id: comboBox1
            Layout.preferredHeight: 40
            Layout.preferredWidth: 298
            Material.accent: tipo=="Catan" ? Material.Amber : Material.Green
        }
    }

    TextField {
        id: textField1
        height: 44
        text: qsTr("Text Field")
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 30
        font.pointSize: 15
        anchors.top: parent.top
        anchors.topMargin: 89
        Layout.preferredHeight: 40
        Layout.preferredWidth: 297
        placeholderText: "Nombre del torneo"
        Material.accent: tipo=="Catan" ? Material.Amber : Material.Green
    }

    ColumnLayout {
        id: columnParticipantes
        x: 30
        y: 243
        width: 310
        height: 86

        Label {
            id: label1
            text: qsTr("Participantes")
            Layout.preferredHeight: 21
            Layout.preferredWidth: 104
            font.pointSize: 15
            color: infoTorneo.tipo=="Catan" ? root.primaryCatan : root.primaryCarca
        }

        RowLayout {
            spacing: 20

            MarcadorParticipantes {
                id: marcadorMinimo
                numero: "8"
                texto: "Minimo"
            }

            MarcadorParticipantes {
                id: marcadorActuales
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                numero: "0"
                texto: "Actuales"
            }

            MarcadorParticipantes {
                id: marcadorChecked
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                numero: "0"
                texto: "Checked"
            }
        }
    }

    ColumnLayout {
        x: 24
        y: 360
        width: 298
        height: 86

        Label {
            id: labelEstimacion
            color: infoTorneo.tipo=="Catan" ? root.primaryCatan : root.primaryCarca
            text: qsTr("Estimacion de mesas")
            font.pointSize: 15
            Layout.preferredHeight: 21
            Layout.preferredWidth: 176
        }

        RowLayout {
            Layout.preferredHeight: 60
            Layout.preferredWidth: 286

            MarcadorParticipantes {
                id: marcadorActuales1
                texto: "Previstas"
                numero: "0"
            }

            MarcadorParticipantes {
                id: marcadorChecked1
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                texto: "Reales"
                numero: "0"
            }
            spacing: 30
        }
    }

}
