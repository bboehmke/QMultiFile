/**
 * @file QFileType.cpp
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
 
#include "QFileType.h"

QFileType::QFileType(QStringList extensions, QMultiFileInfo& fileInfo) :
	fileInfo(fileInfo), fileExtensions(extensions) {

}

QFileType::~QFileType() {
}


QStringList QFileType::getExtensions() const {
	return fileExtensions;
}
