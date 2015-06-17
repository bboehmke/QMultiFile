TEMPLATE = lib

TARGET  = QMultiFile
# no version number on windows
!win32:VERSION = 0.4.1

win32 {
	# Path to zlib and quazip
	LIBS += -L$$PWD/../libs/quazip/lib
	INCLUDEPATH += $$PWD/../libs/quazip/include
	INCLUDEPATH += $$PWD/../libs/zlib/include
	
	TARGET_EXT = .dll
}


include($$PWD/qmultifile.pri)

QT += core
QT -= gui

DESTDIR = ../

LIBS += -lquazip
