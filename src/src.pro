!include( ../common.pri ):error( Couldn't find the common.pri file! )
TARGET = QtCommercialChart
DESTDIR = $$CHART_BUILD_LIB_DIR
TEMPLATE = lib
QT += core \
    gui
CONFIG += debug_and_release
CONFIG(debug, debug|release):TARGET = QtCommercialChartd
SOURCES += \
    barchart/bar.cpp \
    barchart/barlabel.cpp \
    barchart/barchartmodel.cpp \
    barchart/separator.cpp \
    barchart/qbarset.cpp \
    barchart/qbarcategory.cpp \
    barchart/qbarchartseries.cpp \
    barchart/qpercentbarchartseries.cpp \
    barchart/qstackedbarchartseries.cpp \
    barchart/barpresenterbase.cpp \
    barchart/barpresenter.cpp \
    barchart/stackedbarpresenter.cpp \
    barchart/percentbarpresenter.cpp \
    linechart/linechartanimationitem.cpp \
    linechart/linechartitem.cpp \
    linechart/qlinechartseries.cpp \
    qchart.cpp \
    axisitem.cpp \
    qchartview.cpp \
    qchartseries.cpp \
    qchartaxis.cpp \
    charttheme.cpp \
    chartdataset.cpp \
    chartpresenter.cpp \
    domain.cpp
PRIVATE_HEADERS += linechart/linechartitem_p.h \
    linechart/linechartanimationitem_p.h \
    barchart/barlabel_p.h \
    barchart/bar_p.h \
    barchart/separator_p.h \
    barchart/barchartmodel_p.h \
    barchart/barpresenter.h \
    barchart/stackedbarpresenter.h \
    barchart/percentbarpresenter.h \
    barchart/barpresenterbase.h \
    axisitem_p.h \
    chartitem_p.h \
    charttheme_p.h \
    chartdataset_p.h \
    chartpresenter_p.h \
    domain_p.h
PUBLIC_HEADERS += linechart/qlinechartseries.h \
    barchart/qbarchartseries.h \
    barchart/qstackedbarchartseries.h \
    barchart/qpercentbarchartseries.h \
    barchart/barpresenter.h \
    barchart/qstackedbarchartseries.h \
    barchart/stackedbarpresenter.h \
    barchart/qpercentbarchartseries.h \
    barchart/percentbarpresenter.h \
    barchart/barpresenterbase.h \
    barchart/qbarset.h \
    barchart/qbarcategory.h \
    qchartseries.h \
    qchart.h \
    qchartglobal.h \
    qchartview.h \
    qchartaxis.h
    
include(piechart/piechart.pri)
include(scatterseries/scatter.pri)

THEMES += themes/chartthemeicy_p.h \
    themes/chartthemegrayscale_p.h \
    themes/chartthemescientific_p.h \
    themes/chartthemevanilla_p.h
HEADERS += $$PUBLIC_HEADERS
HEADERS += $$PRIVATE_HEADERS
HEADERS += $$THEMES
INCLUDEPATH += linechart \
    barchart \
    themes \
    .
OBJECTS_DIR = $$CHART_BUILD_DIR/lib
MOC_DIR = $$CHART_BUILD_DIR/lib
UI_DIR = $$CHART_BUILD_DIR/lib
RCC_DIR = $$CHART_BUILD_DIR/lib
DEFINES += QTCOMMERCIALCHART_LIBRARY
public_headers.path = $$[QT_INSTALL_HEADERS]/QtCommercialChart
public_headers.files = $$PUBLIC_HEADERS
target.path = $$[QT_INSTALL_LIBS]
INSTALLS += target \
    public_headers
install_build_public_headers.name = bild_public_headers
install_build_public_headers.output = $$CHART_BUILD_PUBLIC_HEADER_DIR/${QMAKE_FILE_BASE}.h
install_build_public_headers.input = PUBLIC_HEADERS
install_build_public_headers.commands = $$QMAKE_COPY \
    ${QMAKE_FILE_NAME} \
    $$CHART_BUILD_PUBLIC_HEADER_DIR
install_build_public_headers.CONFIG += target_predeps \
    no_link
install_build_private_headers.name = bild_private_headers
install_build_private_headers.output = $$CHART_BUILD_PRIVATE_HEADER_DIR/${QMAKE_FILE_BASE}.h
install_build_private_headers.input = PRIVATE_HEADERS
install_build_private_headers.commands = $$QMAKE_COPY \
    ${QMAKE_FILE_NAME} \
    $$CHART_BUILD_PRIVATE_HEADER_DIR
install_build_private_headers.CONFIG += target_predeps \
    no_link
QMAKE_EXTRA_COMPILERS += install_build_public_headers install_build_private_headers
chartversion.target = qchartversion_p.h
chartversion.commands = @echo \
    "build_time" \
    > \
    $$chartversion.target;
chartversion.depends = $$HEADERS \
    $$SOURCES
PRE_TARGETDEPS += qchartversion_p.h
QMAKE_CLEAN += qchartversion_p.h
QMAKE_EXTRA_TARGETS += chartversion
unix:QMAKE_DISTCLEAN += -r \
    $$CHART_BUILD_HEADER_DIR \
    $$CHART_BUILD_LIB_DIR
win32:QMAKE_DISTCLEAN += /Q \
    $$CHART_BUILD_HEADER_DIR \
    $$CHART_BUILD_LIB_DIR

