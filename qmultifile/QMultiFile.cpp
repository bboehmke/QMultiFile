/**
 * @file QMultiFile.cpp
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
 
#include "QMultiFile.h"
#include "QMultiFileInfo.h"
#include "QMultiFileConfig.h"

#include "QFileFactory.h"
#include "QFileType.h"

#include "fileTypes/QZipFileType.h"
#include "fileTypes/QPlainFileType.h"
#include "fileTypes/QTarFileType.h"
#include "fileTypes/QTarGzFileType.h"

// prepare the factory
QSharedPointer<QFileFactory> QMultiFile::fileFactory =
		QSharedPointer<QFileFactory>();

QMultiFile::QMultiFile(QMultiFileInfo& fileInfo) {
	// init the factory
	QMultiFile::initFileTypeFactory();

	fileHandle = QMultiFile::fileFactory->create(fileInfo);
}

QMultiFile::QMultiFile(QString name) {
	// init the factory
	QMultiFile::initFileTypeFactory();

	QMultiFileInfo info(name);
	fileHandle = QMultiFile::fileFactory->create(info);
}
QMultiFile::~QMultiFile() {
	delete fileHandle;
}

bool QMultiFile::exist() const {
	return fileHandle->exist();
}

bool QMultiFile::open(OpenMode mode) {
	QIODevice::open(mode);
	return fileHandle->open(mode);
}

void QMultiFile::close() {
	fileHandle->close();
}


bool QMultiFile::atEnd() const {
	return bytesAvailable() <= 0;
}

qint64 QMultiFile::bytesAvailable() const {
	return size() - pos();
}

bool QMultiFile::seek(qint64 position) {
	QIODevice::seek(position);
	return fileHandle->seek(position);
}

qint64 QMultiFile::size() const {
	return fileHandle->size();
}


QString QMultiFile::getVersionInfo() {
	// convert version
	QString version = QString("%1.%2.%3")
						.arg((quint8)((CFG::VERSION>>16) & 0xFF))
						.arg((quint8)((CFG::VERSION>>8)  & 0xFF))
						.arg((quint8)((CFG::VERSION   )  & 0xFF));

	return QString("QMultiFile Library - Version: %1 - Build: "__DATE__" "__TIME__).arg(version);
}

qint64 QMultiFile::readData(char* data, qint64 maxSize) {
	return fileHandle->read(data, maxSize);
}

qint64 QMultiFile::writeData(const char* data, qint64 maxSize) {
	return fileHandle->write(data, maxSize);
}

void QMultiFile::initFileTypeFactory() {
	// if the factory not exist
	if (!QMultiFile::fileFactory) {
		// create the factory
		QMultiFile::fileFactory =
				QSharedPointer<QFileFactory>(new QFileFactory());

		// register the files
		QMultiFile::fileFactory->registerFile<QZipFileType>();
		QMultiFile::fileFactory->registerFile<QPlainFileType>();
		QMultiFile::fileFactory->registerFile<QTarFileType>();
		QMultiFile::fileFactory->registerFile<QTarGzFileType>();
	}
}
