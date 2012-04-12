!include(config.pri) {
    error('Missing config.pri')
}

TEMPLATE = subdirs
SUBDIRS = src qmlplugin examples demos test

local_build:{
    message('Configured for local build against local libs...')
    message('You can run "make" to build qchart library, examples and demos...')
} else {
    message('Running build aginst system libs...')
    message('Bulding only charts library...')
    message('You can run "make install" to build and install charts.')
    message('Afterwards you can run "cd examples; qmake ; make " to build examples.')
    message('Run qmake CONFIG+=local_build' to build everything at once.)
    SUBDIRS = src
}

CONFIG += ordered
QMAKE_CXXFLAGS += -g -Wall
unix:QMAKE_DISTCLEAN += -r build bin include lib doc/html 
win32:QMAKE_DISTCLEAN += /Q /s build bin include lib doc\\html

# install feature file
feature.path = $$[QT_INSTALL_DATA]/mkspecs/features
feature.files = $$PWD/features/qtcommercialchart.prf
INSTALLS += feature

docs.target = docs
win32:{
    docs.commands = qdoc3 $$CHART_BUILD_DOC_DIR\\qcharts.qdocconf
}else{
    docs.commands = qdoc3 $$CHART_BUILD_DOC_DIR/qcharts.qdocconf
}
docs.depends = FORCE
QMAKE_EXTRA_TARGETS += docs

