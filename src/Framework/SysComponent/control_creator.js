
function createLabel(text, parent) {
    return Qt.createQmlObject('import QtQuick 2.0; \
                        import QtQuick.Controls 1.4; \
                        Label { \
                            x:1; \
                            width:parent.width-1; \
                            height:parent.height; \
                            elide: Text.ElideLeft; \
                            verticalAlignment:Text.AlignVCenter; \
                            function setValue(value) { \
                                text = String(value); \
                            } \
                            text:"'+ text + '"}', parent, "label");
}



function createCombobox(id, text, parent) {
    return Qt.createQmlObject('import QtQuick 2.0; \
                        import QtQuick.Controls 1.4; \
                        ComboBox { \
                            anchors.fill: parent; \
                            property var itemName: "'+ id +'"; \
                            onActivated: { \
                                root.itemChanged(itemName, index); \
                            } \
                            function setValue(value) { \
                            } \
                        }', parent, "combobox");
}

function createIntSpinbox(id, value, parent) {
    return Qt.createQmlObject('import QtQuick 2.0; \
                        import QtQuick.Controls 1.4; \
                        SpinBox { \
                            anchors.fill: parent; \
                            minimumValue: -2147483648; \
                            maximumValue: 2147483647; \
                            value:'+ parseInt(value) + '; \
                            property var itemName: "'+ id +'"; \
                            onEditingFinished: { \
                                root.itemChanged(itemName, value); \
                            } \
                            function setValue(value) { \
                                value = Number(value); \
                            } \
                        }', parent, "intspinbox");
}

function createFloatSpinbox(id, value, parent) {
    return Qt.createQmlObject('import QtQuick 2.0; \
                        import QtQuick.Controls 1.4; \
                        SpinBox { \
                            anchors.fill: parent; \
                            minimumValue: -2147483648; \
                            maximumValue: 2147483647; \
                            decimals: 6; \
                            value:'+ parseFloat(value) + '; \
                            property var itemName: "'+ id +'"; \
                            onEditingFinished: { \
                                root.itemChanged(itemName, value); \
                            } \
                            function setValue(value) { \
                                value = Number(value); \
                            } \
                        }', parent, "floatspinbox");
}

function createLineEdit(id, text, parent) {
    return Qt.createQmlObject('import QtQuick 2.0; \
                            import QtQuick.Controls 1.4; \
                            TextField { \
                                anchors.fill: parent; \
                                text:"'+ text + '"; \
                                property var itemName: "'+ id +'"; \
                                onEditingFinished: { \
                                    root.itemChanged(itemName, text); \
                                } \
                                function setValue(value) { \
                                    text = String(value); \
                                } \
                            }', parent, "textedit");
}

function createDelegateControl(json, parent) {
    var item
    if (json.type == 'label')
    {
        item = createLabel(json.value, parent)
    }
    else if (json.type == 'textEdit')
    {
        item = createLineEdit(json.id, json.value, parent)
    }
    else if (json.type == 'enum')
    {
        item = createCombobox(json.id, json.value, parent)
        var text = json.value
        var currIndex = text.shift()
        item.model = text
        item.currentIndex = currIndex
    }
    else if (json.type == 'int')
    {
        item = createIntSpinbox(json.id, json.value, parent)
    }
    else if (json.type == 'double')
    {
        item = createFloatSpinbox(json.id, json.value, parent)
    }

    return item
}

function createItem(row, column, parent) {
    var prop = root.propjson[row]
    if (column == 0) {
        createLabel(prop.name, parent)
    }
    else if (column == 1) {
        root.createdItems.push(createDelegateControl(prop, parent))
    }
}

