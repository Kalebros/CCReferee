import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    id: item1
    width: 358
    height: 642
    property alias tipoComboBox: comboBox1
    property alias nombreField: textField1

    RowLayout {
    }

    ColumnLayout {
        x: 30
        y: 93
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 150

        ColumnLayout {

            TextField {
                id: textField1
                text: qsTr("Text Field")
                Layout.preferredHeight: 40
                Layout.preferredWidth: 297
                placeholderText: "Nombre del torneo"
            }
        }

        ColumnLayout {

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
            }
        }
    }
}
