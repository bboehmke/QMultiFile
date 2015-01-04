/**
 * @file QPlainFileType.cpp
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
 
#include "QPlainFileType.h"

#include <QFile>
#include <QFileInfo>

QPlainFileType::QPlainFileType(QMultiFileInfo& fileInfo) :
	QFileType(QStringList() << "", fileInfo) {
	
	file = new QFile(fileInfo.filePath());
}


QPlainFileType::~QPlainFileType() {
	delete file;
}

bool QPlainFileType::exist() const {
	return QFileInfo(fileInfo.filePath()).isFile();
}

bool QPlainFileType::open(QIODevice::OpenMode mode) {
	return file->open(mode);
}

void QPlainFileType::close() {
	file->close();
}

bool QPlainFileType::atEnd() const {
	return file->atEnd();
}

qint64 QPlainFileType::bytesAvailable() const {
	return file->bytesAvailable();
}

bool QPlainFileType::seek(qint64 position) {
	return file->seek(position);
}

qint64 QPlainFileType::size() const {
	return file->size();
}

qint64 QPlainFileType::pos() const {
	return file->pos();
}

qint64 QPlainFileType::read(char* data, qint64 maxSize) {
	return file->read(data, maxSize);
}

qint64 QPlainFileType::write(const char* data, qint64 maxSize) {
	return file->write(data, maxSize);
}
