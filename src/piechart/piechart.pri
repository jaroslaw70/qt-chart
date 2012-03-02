INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/qpieseries.cpp \
    $$PWD/pieslice.cpp \
    $$PWD/piepresenter.cpp \
    $$PWD/qpieslice.cpp

PRIVATE_HEADERS += \
    $$PWD/piepresenter_p.h \
    $$PWD/pieslice_p.h \

PUBLIC_HEADERS += \
    $$PWD/qpieseries.h \
    $$PWD/qpieslice.h
