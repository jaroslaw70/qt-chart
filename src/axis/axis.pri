#Subdirectiores are defined here, because qt creator doesn't handle nested include(foo.pri) chains very well.

INCLUDEPATH += $$PWD \
    $$PWD/valueaxis \
    $$PWD/barcategoryaxis \
    $$PWD/categoryaxis \
    $$PWD/datetimeaxis

DEPENDPATH += $$PWD \
    $$PWD/valueaxis \
    $$PWD/barcategoryaxis \
    $$PWD/categoryaxis \
    $$PWD/datetimeaxis

SOURCES += \
    $$PWD/chartaxis.cpp \
    $$PWD/qabstractaxis.cpp \
    $$PWD/valueaxis/chartvalueaxisx.cpp \
    $$PWD/valueaxis/chartvalueaxisy.cpp \
    $$PWD/valueaxis/qvalueaxis.cpp \
    $$PWD/barcategoryaxis/chartbarcategoryaxisx.cpp \
    $$PWD/barcategoryaxis/chartbarcategoryaxisy.cpp \
    $$PWD/barcategoryaxis/qbarcategoryaxis.cpp \
    $$PWD/categoryaxis/chartcategoryaxisx.cpp \
    $$PWD/categoryaxis/chartcategoryaxisy.cpp \
    $$PWD/categoryaxis/qcategoryaxis.cpp \
    $$PWD/datetimeaxis/chartdatetimeaxisx.cpp \
    $$PWD/datetimeaxis/chartdatetimeaxisy.cpp \
    $$PWD/datetimeaxis/qdatetimeaxis.cpp

PRIVATE_HEADERS += \
    $$PWD/chartaxis_p.h \
    $$PWD/qabstractaxis_p.h \
    $$PWD/valueaxis/chartvalueaxisx_p.h \
    $$PWD/valueaxis/chartvalueaxisy_p.h \
    $$PWD/valueaxis/qvalueaxis_p.h \
    $$PWD/barcategoryaxis/chartbarcategoryaxisx_p.h \
    $$PWD/barcategoryaxis/chartbarcategoryaxisy_p.h \
    $$PWD/barcategoryaxis/qbarcategoryaxis_p.h \
    $$PWD/categoryaxis/chartcategoryaxisx_p.h \
    $$PWD/categoryaxis/chartcategoryaxisy_p.h \
    $$PWD/categoryaxis/qcategoryaxis_p.h \
    $$PWD/datetimeaxis/chartdatetimeaxisx_p.h \
    $$PWD/datetimeaxis/chartdatetimeaxisy_p.h \
    $$PWD/datetimeaxis/qdatetimeaxis_p.h

PUBLIC_HEADERS += \
    $$PWD/qabstractaxis.h \
    $$PWD/valueaxis/qvalueaxis.h \
    $$PWD/barcategoryaxis/qbarcategoryaxis.h \
    $$PWD/categoryaxis/qcategoryaxis.h \
    $$PWD/datetimeaxis/qdatetimeaxis.h
