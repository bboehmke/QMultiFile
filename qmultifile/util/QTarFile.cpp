/**
 * @file QTarFile.cpp
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
#include "QTarFile.h"

#include <QFile>

#include "QTar.h"

QTarFile::QTarFile() : file(NULL), offset(0), fileSize(0) {
}

QTarFile::QTarFile(const QString tarName, const QString& fileName) :
		file(NULL), fileName(fileName), offset(0), fileSize(0) {

	file = QSharedPointer<QIODevice>(new QFile(tarName));
}

QTarFile::QTarFile(QIODevice* ioDevice, const QString& fileName) :
				file(QSharedPointer<QIODevice>(ioDevice)),
				fileName(fileName), offset(0), fileSize(0) {
}


bool QTarFile::open(OpenMode mode) {
	if (file && mode == QIODevice::ReadOnly) {
		// open the tar file
		QTar tar(file);

		// find the file
		QListIterator<QTar::FileInfo> fileIt(tar.getFileInfoList());
		while (fileIt.hasNext()) {
			QTar::FileInfo info = fileIt.next();

			if (info.fileName == fileName) {
				// save the offset and the file size
				offset = info.offset;
				fileSize = info.fileSize;

				QIODevice::open(QIODevice::ReadOnly);
				if (!file->open(QIODevice::ReadOnly)) {
					return false;
				}
				// skip unneeded bytes
				file->read(offset);
				return true;
			}
		}
		tar.close();
	}
	return false;
}

void QTarFile::close() {
	if (file) {
		file->close();
	}
}

bool QTarFile::atEnd() const {
	if (file) {
		return bytesAvailable() <= 0;
	} else {
		return true;
	}
}

qint64 QTarFile::bytesAvailable() const {
	if (file) {
		return size() - pos();
	} else {
		return 0;
	}
}

bool QTarFile::seek(qint64 position) {
	if (file) {
		// max seek pos = end of the file
		if (position > fileSize) {
			position = fileSize;
		}

		// if sequential device there is no seek and it must be done manually
		if (file->isSequential()) {
			// if the requested pos is before the actual one reopen the device
			if (pos() > position) {
				file->close();
				if (!file->open(QIODevice::ReadOnly)) {
					return false;
				}
				// skip unneeded bytes
				file->read(offset + position);

			} else {
				// skip unneeded bytes
				file->read(position - pos());
			}

			QIODevice::seek(position);
			return true;

		} else {
			QIODevice::seek(position);
			file->seek(offset + position);
			return true;
		}
	} else {
		return true;
	}
}

qint64 QTarFile::size() const {
	if (file) {
		return fileSize;
	} else {
		return 0;
	}
}

qint64 QTarFile::readData(char* data, qint64 maxSize) {
	if (file) {
		// check for file end
		qint64 size = maxSize;
		if (size > bytesAvailable()) {
			size = bytesAvailable();
		}
		return file->read(data, size);
	} else {
		return -1;
	}
}

qint64 QTarFile::writeData(const char* data, qint64 maxSize) {
	if (file) {
		return file->write(data, maxSize);
	} else {
		return -1;
	}
}
