include($$PWD/fileTypes/fileTypes.pri)
include($$PWD/util/util.pri)

# public API
INSTALL_HEADERS += \
                $$PWD/QMultiFileInfo.h \
                $$PWD/QMultiFile.h

# private API
HEADERS += \
                $${INSTALL_HEADERS} \
                $$PWD/QFileType.h \
                $$PWD/QFileFactory.h

SOURCES += \
                $$PWD/QMultiFileInfo.cpp \
                $$PWD/QMultiFile.cpp \
                $$PWD/QFileType.cpp \
                $$PWD/QFileFactory.cpp

