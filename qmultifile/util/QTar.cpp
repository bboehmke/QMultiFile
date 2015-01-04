/**
 * @file QTar.cpp
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
#include "QTar.h"

#include <QFile>

QTar::QTar() : openMode(mdNotOpen), file(NULL) {

}

QTar::QTar(const QString& tarName) : openMode(mdNotOpen) {
	file = QSharedPointer<QIODevice>(new QFile(tarName));
}

QTar::QTar(QSharedPointer<QIODevice> ioDevice) :
		openMode(mdNotOpen), file(ioDevice) {
}

bool QTar::open(Mode mode) {
	if (file && mode == mdUntar) {
		openMode = mode;
		return file->open(QIODevice::ReadOnly);
	} else {
		return false;
	}
}

void QTar::close() {
	file->close();
}

QStringList QTar::getFileNameList() const {
	QStringList fileList;

	QListIterator<FileInfo> fileIt(getFileInfoList());
	while (fileIt.hasNext()) {
		fileList << fileIt.next().fileName;
	}

	return fileList;
}

QList<QTar::FileInfo> QTar::getFileInfoList() const {
	if (!file) {
		return QList<FileInfo>();
	}

	// close file if already open
	if (file->isOpen()) {
		file->close();
	}
	// open the file
	if (!file->open(QIODevice::ReadOnly)) {
		return QList<FileInfo>();
	}

	// prepare the info list
	QList<FileInfo> infoList;
	quint64 offset = 0;

	// read the header
	QByteArray header = file->read(512);
	// find all files
	while (!header.isEmpty()) {

		// break if the end of the tar is reached
		if (header.count('\0') == 512) {
			break;
		}

		// get file type
		int type = header.mid(156, 1).toInt(0, 8);
		// get file size
		quint64 size = header.mid(124, 12).toULongLong(0, 8);

		// get the informations
		if (type == 0) {
			FileInfo info;
			info.offset = offset + 512;
			info.fileName = QString(header.mid(0, 100));
			info.fileSize = size;

			// add info to list
			infoList << info;
		}

		// increase offset
		offset += 512; // header

		offset += size/512 * 512; // data
		file->read(size/512 * 512);
		if (size%512 != 0) { // round up
			file->read(512);
			offset += 512;
		}

		// read next header
		header = file->read(512);
	}

	// close the file
	file->close();

	// reopen the file
	if (openMode == mdUntar) {
		file->open(QIODevice::ReadOnly);
	}

	return infoList;
}
