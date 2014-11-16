/**
 * @file test_main.cpp
 *
 * Copyright (c) 2014 by Benjamin Böhmke
 *
 */

#include <QDebug>

#include <qmultifile/QMultiFileInfo.h>
#include <qmultifile/QMultiFile.h>

#include <QStringList>


int main() {

	qDebug() << "------------------------------";
	qDebug() << QMultiFile::getVersionInfo();
	qDebug() << "------------------------------";

	QStringList files;

	files << "testFiles/dir2/df.txt";
	files << "testFiles/test.zip/dir2/df.txt";
	files << "testFiles/tst_[1-2].zip/dir2/df.txt";
	files << "testFiles/tst_[1-20].zip/dir2/df.txt";
	files << "testFiles/test.ext/test.zip/dir2/df.txt";

	QStringListIterator fileIt(files);

	while (fileIt.hasNext()) {
		QString f = fileIt.next();
		qDebug() << "########################################";
		qDebug() << f;
		qDebug() << "########################################";

		QMultiFileInfo info(f);
		qDebug() << ">>>QMultiFileInfo<<<";
		qDebug() << " baseName()            -> " << info.baseName();
		qDebug() << " fileName()            -> " << info.fileName();
		qDebug() << " filePath()            -> " << info.filePath();
		qDebug() << " archivePath()         -> " << info.archivePath();
		qDebug() << " inArchivePath()       -> " << info.inArchivePath();
		qDebug() << " path()                -> " << info.path();
		qDebug() << " wildcardFilePath()    -> " << info.wildcardFilePath();
		qDebug() << " wildcardPath()        -> " << info.wildcardPath();
		qDebug() << " wildcardArchivePath() -> " << info.wildcardArchivePath();
		qDebug() << " getArchiveExtension() -> " << info.getArchiveExtension();
		qDebug() << " isInArchive()         -> " << info.isInArchive();
		qDebug() << " exist()               -> " << info.exist();

		qDebug() << "";

		QMultiFile file(f);
		qDebug() << ">>>QMultiFile<<<";
		qDebug() << " size()           -> " << file.size();
		qDebug() << " open()           -> " << file.open(QIODevice::ReadOnly);
		qDebug() << " size()           -> " << file.size();
		qDebug() << " pos()            -> " << file.pos();
		qDebug() << " atEnd()          -> " << file.atEnd();
		qDebug() << " bytesAvailable() -> " << file.bytesAvailable();

		qDebug() << "----------------------------------------";
		qDebug() << " seek()           ->" << file.seek(32);
		qDebug() << " read()           ->" << file.read(10);

		qDebug() << " seek()           ->" << file.seek(32);
		qDebug() << " read()           ->" << file.read(10);
		qDebug() << "----------------------------------------";

		qDebug() << " pos()            -> " << file.pos();
		qDebug() << " atEnd()          -> " << file.atEnd();
		qDebug() << " bytesAvailable() -> " << file.bytesAvailable();

		file.close();

		qDebug() << "";
		qDebug() << "";


	}

	return 0;
}

