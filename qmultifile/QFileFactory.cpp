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
    // get archive extension
    QString extension = fileInfo.getArchiveExtension();

    // if the extension is on the alias list replace it
    if (aliasList.contains(extension)) {
        extension = aliasList[extension];
    }

	// search for the name of the extension
	QMap<QString, QSharedPointer<QFileCreator> >::iterator it
			= fileList.find(extension);

	// check if extension was found
	if (it == fileList.end()) {
		return new QPlainFileType(fileInfo);
	}

	// create the instance of the file class
	return it.value()->create(fileInfo);
}

void QFileFactory::addArchiveAlias(QString archiveExt, QString alias) {
    aliasList[alias] = archiveExt;
}