/**
 * @file QFileFactory.cpp
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
 
#include "QFileFactory.h"

#include "fileTypes/QPlainFileType.h"

QFileType* QFileFactory::create(QMultiFileInfo& fileInfo) {

	// search for the name of the extension
	QMap<QString, QSharedPointer<QFileCreator> >::iterator it
			= fileList.find(fileInfo.getArchiveExtension());

	// check if extension was found
	if (it == fileList.end()) {
		return new QPlainFileType(fileInfo);
	}

	// create the instance of the file class
	return it.value()->create(fileInfo);
}
