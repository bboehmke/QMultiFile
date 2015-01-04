/**
 * @file QTarGzFileType.cpp
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
 
#include "QTarGzFileType.h"

#include <QFileInfo>

#include <quazip/quagzipfile.h>

#include "../util/QTar.h"
#include "../util/QTarFile.h"

QTarGzFileType::QTarGzFileType(QMultiFileInfo& fileInfo) :
	QFileType(QStringList() << "tar.gz" << "tgz", fileInfo), file(NULL) {
}

QTarGzFileType::~QTarGzFileType() {
	delete file;
}

bool QTarGzFileType::exist() const {
	// get informations about the archive
	QFileInfo archInfo(fileInfo.archivePath());

	// if the archive exit
	if (archInfo.isFile()) {
		// open the archive
		QTar tar(QSharedPointer<QIODevice>(new QuaGzipFile(fileInfo.archivePath())));

		// try to open the file
		if (tar.open(QTar::mdUntar)) {
			// if the file is in the archive -> it exist
			return tar.getFileNameList().contains(fileInfo.inArchivePath());
		}

	}
	return false;
}
bool QTarGzFileType::open(QIODevice::OpenMode mode) {
	// check if the file exist
	if (!exist()) {
		return false;
	}

	// create the file object
	file = new QTarFile(new QuaGzipFile(fileInfo.archivePath()), fileInfo.inArchivePath());

	// set the last open mode
	openMode = mode;

	// open the file
	return file->open(mode);
}
void QTarGzFileType::close() {
	if (!file) {
		file->close();
		delete file;
	}
}
bool QTarGzFileType::atEnd() const {
	return pos() >= size();
}
qint64 QTarGzFileType::bytesAvailable() const {
	return file->bytesAvailable();
}

bool QTarGzFileType::seek(qint64 position) {
	// check if file was opened
	if (!file) {
		return false;
	}

	return file->seek(position);
}
qint64 QTarGzFileType::size() const {
	// check if file was opened
	if (!file) {
		return -1;
	}
	return dynamic_cast<QTarFile*>(file)->size();
}

qint64 QTarGzFileType::pos() const {
	// check if file was opened
	if (!file) {
		return -1;
	}
	return file->pos();
}

qint64 QTarGzFileType::read(char* data, qint64 maxSize) {
	// check if file was opened
	if (!file) {
		return -1;
	}
	return file->read(data, maxSize);
}

qint64 QTarGzFileType::write(const char* /*data*/, qint64 /*maxSize*/) {
	// check if file was opened
	if (!file) {
		return -1;
	}
	// not implemented
	return -1;
}
