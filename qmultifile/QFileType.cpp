/**
 * @file QFileType.cpp
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
 
#include "QFileType.h"

QFileType::QFileType(QStringList extensions, QMultiFileInfo& fileInfo) :
	fileInfo(fileInfo), fileExtensions(extensions) {

}

QFileType::~QFileType() {
}


QStringList QFileType::getExtensions() const {
	return fileExtensions;
}
