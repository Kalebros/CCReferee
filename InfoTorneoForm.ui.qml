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
        x: 30
        anchors.top: textField1.bottom
        anchors.topMargin: 23
        anchors.horizontalCenterOffset: 5
        anchors.horizontalCenter: parent.horizontalCenter

        Label {
            id: label2
            text: qsTr("Tipo de torneo")
            Layout.preferredHeight: 31
            Layout.preferredWidth: 175
            font.pointSize: 12
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
        x: 30
        width: 298
        height: 40
        text: qsTr("Text Field")
        anchors.horizontalCenterOffset: 5
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 89
        Layout.preferredHeight: 40
        Layout.preferredWidth: 297
        placeholderText: "Nombre del torneo"
        Material.accent: tipo=="Catan" ? Material.Amber : Material.Green
    }
}
