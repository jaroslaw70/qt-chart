TARGET = qtcommercialchartqml2
QT += quick qml widgets
IMPORT_INSTALL_PATH = $$[QT_INSTALL_QML]
DEFINES += CHARTS_FOR_QUICK2

!include(../declarative/declarative.pri) {
    error( "Couldn't find the declarative.pri file!" )
}
qmldir.files += plugins.qmltypes
TARGETPATH = QtCommercial.Chart
QMAKE_MOC_OPTIONS += -Muri=$$TARGETPATH
