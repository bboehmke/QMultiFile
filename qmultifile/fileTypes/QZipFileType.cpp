/**
 * @file QZipFileType.cpp
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
 
#include "QZipFileType.h"

#include <QFileInfo>

#include <quazip/quazip.h>
#include <quazip/quazipfile.h>

QZipFileType::QZipFileType(QMultiFileInfo& fileInfo) :
	QFileType(QStringList() << "zip", fileInfo), file(NULL) {
}

QZipFileType::~QZipFileType() {
	delete file;
}

bool QZipFileType::exist() const {
	// get informations about the archive
	QFileInfo archInfo(fileInfo.archivePath());

	// if the archive exit
	if (archInfo.isFile()) {
		// open the archive
		QuaZip zip(fileInfo.archivePath());

		// try to open the file
		if (zip.open(QuaZip::mdUnzip)) {
			// if the file is in the archive -> it exist
			return zip.getFileNameList().contains(fileInfo.inArchivePath());
		}
	}
	return false;
}
bool QZipFileType::open(QIODevice::OpenMode mode) {
	// check if the file exist
	if (!exist()) {
		return false;
	}

	// create the file object
	file = new QuaZipFile(fileInfo.archivePath(), fileInfo.inArchivePath());

	// set the last open mode
	openMode = mode;

	// open the file
	return file->open(mode);
}
void QZipFileType::close() {
	if (!file) {
		file->close();
		delete file;
	}
}
bool QZipFileType::atEnd() const {
	return pos() >= size();
}
qint64 QZipFileType::bytesAvailable() const {
	return file->bytesAvailable();
}

bool QZipFileType::seek(qint64 position) {
	// check if file was opened
	if (!file) {
		return false;
	}

	// check if the position is valid
	if (position >= size()) {
		return false;
	}
	// if the position is in front of the actual position
	if (position < pos()) {
		// the file must be closed
		close();

		// and reopened
		if (!open(openMode)) {
			return false;
		}

		// then all bytes until the position are dropped
		file->read(position);
	} else {

		// drop all bytes before the position
		file->read(position-pos());
	}
	return true;
}
qint64 QZipFileType::size() const {
	// check if file was opened
	if (!file) {
		return -1;
	}
	return dynamic_cast<QuaZipFile*>(file)->usize();
}

qint64 QZipFileType::pos() const {
	// check if file was opened
	if (!file) {
		return -1;
	}
	return file->pos();
}

qint64 QZipFileType::read(char* data, qint64 maxSize) {
	// check if file was opened
	if (!file) {
		return -1;
	}
	return file->read(data, maxSize);
}

qint64 QZipFileType::write(const char* /*data*/, qint64 /*maxSize*/) {
	// check if file was opened
	if (!file) {
		return -1;
	}
	// not implemented
	return -1;
}
