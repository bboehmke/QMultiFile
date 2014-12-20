/**
 * @file QTarFileType.cpp
 *
 * This file is part of the QMultiFile Library
 *
 * Copyright (c) 2014 by Benjamin Böhmke
 *
 * The QMultiFile Library is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU Lesser General Public License as 
 * published by the Free Software Foundation; either version 3.0 of the License,
 * or (at your option) any later version.
 *
 * The QMultiFile Library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with the QMultiFile Library.
 * If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "QTarFileType.h"

#include <QFileInfo>

#include "../util/QTar.h"
#include "../util/QTarFile.h"

QTarFileType::QTarFileType(QMultiFileInfo& fileInfo) :
	QFileType(QStringList() << "tar", fileInfo), file(NULL) {
}

QTarFileType::~QTarFileType() {
	delete file;
}

bool QTarFileType::exist() const {
	// get informations about the archive
	QFileInfo archInfo(fileInfo.archivePath());

	// if the archive exit
	if (archInfo.isFile()) {
		// open the archive
		QTar tar(fileInfo.archivePath());

		// try to open the file
		if (tar.open(QTar::mdUntar)) {
			// if the file is in the archive -> it exist
			return tar.getFileNameList().contains(fileInfo.inArchivePath());
		}
	}
	return false;
}
bool QTarFileType::open(QIODevice::OpenMode mode) {
	// check if the file exist
	if (!exist()) {
		return false;
	}

	// create the file object
	file = new QTarFile(fileInfo.archivePath(), fileInfo.inArchivePath());

	// set the last open mode
	openMode = mode;

	// open the file
	return file->open(mode);
}
void QTarFileType::close() {
	if (!file) {
		file->close();
		delete file;
	}
}
bool QTarFileType::atEnd() const {
	return pos() >= size();
}
qint64 QTarFileType::bytesAvailable() const {
	return file->bytesAvailable();
}

bool QTarFileType::seek(qint64 position) {
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
qint64 QTarFileType::size() const {
	// check if file was opened
	if (!file) {
		return -1;
	}
	return dynamic_cast<QTarFile*>(file)->size();
}

qint64 QTarFileType::pos() const {
	// check if file was opened
	if (!file) {
		return -1;
	}
	return file->pos();
}

qint64 QTarFileType::read(char* data, qint64 maxSize) {
	// check if file was opened
	if (!file) {
		return -1;
	}
	return file->read(data, maxSize);
}

qint64 QTarFileType::write(const char* /*data*/, qint64 /*maxSize*/) {
	// check if file was opened
	if (!file) {
		return -1;
	}
	// not implemented
	return -1;
}
