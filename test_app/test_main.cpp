/**
 * @file test_main.cpp
 *
 * This file is part of the QMultiFile Library
 *
 * Copyright (c) 2014 - 2015 by Benjamin Böhmke
 *
 * The QMultiFile Library is free software; you can redistribute it and/or
 * modify it under the terms of the MIT License.
 *
 * This software is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the LICENSE file for more details.
 */

#include <QDebug>

#include <qmultifile/QMultiFileInfo.h>
#include <qmultifile/QMultiFile.h>

#include <QStringList>


int main() {

	qDebug() << "------------------------------";
	qDebug() << QMultiFile::getVersionInfo();
	qDebug() << "------------------------------";
	QMultiFile::addArchiveAlias("zip", "zippy");

	QStringList files;

	files << "testFiles/dir2/df.txt";
	files << "testFiles/test.zip/dir2/df.txt";
	files << "testFiles/test.bla.zip/dir2/df.txt";
	files << "testFiles/test.zippy/dir2/df.txt";
	files << "testFiles/test.tar/dir2/df.txt";
	files << "testFiles/test.tar.gz/dir2/df.txt";
	files << "testFiles/tst_[1-2].zip/dir2/df.txt";
	files << "testFiles/tst_[1-20].zip/dir2/df.txt";
	files << "testFiles/test.ext/test.zip/dir2/df.txt";
    files << "testFiles/test.zip/dir2/../dir2/df.txt";

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
		qDebug() << " absoluteFilePath()    -> " << info.absoluteFilePath();
		qDebug() << " absolutePath()        -> " << info.absolutePath();
		qDebug() << " wildcardFilePath()    -> " << info.wildcardFilePath();
		qDebug() << " wildcardPath()        -> " << info.wildcardPath();
		qDebug() << " wildcardArchivePath() -> " << info.wildcardArchivePath();
		qDebug() << " getArchiveExtension() -> " << info.getArchiveExtension();
		qDebug() << " isInArchive()         -> " << info.isInArchive();
		qDebug() << " exist()               -> " << info.exist();
		qDebug() << " exists()              -> " << info.exists();

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
		qDebug() << " seek(32)         ->" << file.seek(32);
		qDebug() << " read(10)         ->" << file.read(10);

		qDebug() << " seek(32)         ->" << file.seek(32);
		qDebug() << " read(10)         ->" << file.read(10);
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

