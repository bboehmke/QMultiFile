/**
 * @file QMultiFileInfo.cpp
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
#include "QMultiFileInfo.h"

#include <QRegExp>
#include <QFileInfo>
#include <QString>
#include <QStringList>

#include <QDebug>

#include "QMultiFile.h"

QMultiFileInfo::QMultiFileInfo() : fileExist(false) {

}
QMultiFileInfo::QMultiFileInfo(QString file) : fileExist(false) {
	file = normalizeFilePath(file);

	// prepare the req exp
	QRegExp rx("([^\\.]*)(\\.)([^\\/]*)(\\/)");
	int pos = 0;
	QString handledPath;

	// search in the path
	while ((pos = rx.indexIn(file, pos)) != -1) {
		// build the path
		path_wildcardArchive = handledPath + rx.cap(1) + "." + rx.cap(3);

		// check if there is an archive
		if (checkIfArchive(path_wildcardArchive)) {
			// set extension
			archiveExtension = rx.cap(3).toLower();
			// set the file path
			path_file = file.mid(pos + rx.matchedLength());
			// build the wildcard paths
			QStringList pathList = getArchivePath(path_wildcardArchive);

			// if nothing was build we may have no wildcard
			if (pathList.isEmpty()) {
				path_archive = path_wildcardArchive;

				// check if the file exist
				fileExist = QMultiFile(*this).exist();

				// if the file not exist try to remove dummy "."
				while (!fileExist && archiveExtension.contains(".")) {
					// remove content before dummy "."
					archiveExtension = archiveExtension.mid(archiveExtension.indexOf(".")+1).toLower();
					fileExist = QMultiFile(*this).exist();
				}

			} else {
				// build the iterator
				QStringListIterator pathListIt(pathList);
				while (pathListIt.hasNext()) {
					QString path = pathListIt.next();

					// check the path
					if (QMultiFile(path + "/" + path_file).exist()) {
						fileExist = true;
						path_archive = path;
						break;
					}
				}


			}
			return;

		// if not
		} else {
			// add the archive path to the handled path
			handledPath += rx.cap(0);
		}

		pos += rx.matchedLength();
	}

	// check if this is a plain file
	if (archiveExtension.isEmpty()) {
		path_file = file;

		fileExist = QMultiFile(*this).exist();
	}

}

QString QMultiFileInfo::baseName() const {
	QString file = fileName();
	return file.left(file.indexOf("."));
}

QString QMultiFileInfo::fileName() const {
	return path_file.right(path_file.length() - path_file.lastIndexOf("/") - 1);
}

QString QMultiFileInfo::absoluteFilePath() const {
    if (path_archive.isEmpty()) {
        return QFileInfo(path_file).absoluteFilePath();
    } else {
        return QFileInfo(path_wildcardArchive).absoluteFilePath() + "/" + path_file;
    }
}
QString QMultiFileInfo::absolutePath() const {
    QString path = absoluteFilePath();
    // if path not exist return empty string
    if (!path.contains("/")) {
        return "";
    } else {
        return path.left(path.lastIndexOf("/"));
    }
}

QString QMultiFileInfo::filePath() const {
	if (path_archive.isEmpty()) {
		return path_file;
	} else {
		return path_archive + "/" + path_file;
	}
}

QString QMultiFileInfo::archivePath() const {
	return path_archive;
}

QString QMultiFileInfo::inArchivePath() const {
	return path_file;
}

QString QMultiFileInfo::path() const {
	QString path = filePath();
	// if path not exist return empty string
	if (!path.contains("/")) {
		return "";
	} else {
		return path.left(path.lastIndexOf("/"));
	}
}

QString QMultiFileInfo::wildcardFilePath() const {
	if (path_archive.isEmpty()) {
		return path_file;
	} else {
		return path_wildcardArchive + "/" + path_file;
	}
}
QString QMultiFileInfo::wildcardPath() const {
	QString path = wildcardFilePath();
	// if path not exist return empty string
	if (!path.contains("/")) {
		return "";
	} else {
		return path.left(path.lastIndexOf("/"));
	}
}
QString QMultiFileInfo::wildcardArchivePath() const {
	return path_wildcardArchive;
}

QString QMultiFileInfo::getArchiveExtension() const {
	return archiveExtension;
}

bool QMultiFileInfo::isInArchive() const {
	return archiveExtension != "";
}

bool QMultiFileInfo::exist() const {
    return fileExist;
}
bool QMultiFileInfo::exists() const {
    return fileExist;
}

bool QMultiFileInfo::checkIfArchive(QString path) {
	QStringList pathList = getArchivePath(path);

	// if there are paths in the list
	if (pathList.size() > 0) {
		QStringListIterator pathListIt(pathList);

		// check if one archive is valid
		while (pathListIt.hasNext()) {
			if (QFileInfo(pathListIt.next()).isFile()) {
				return true;
			}
		}

	// if the path list is empty
	} else {
		// try the path direct
		return QFileInfo(path).isFile();
	}
	return false;
}

QStringList QMultiFileInfo::getArchivePath(QString path) {
	QRegExp rx("([^\\[]*)(\\[)([^\\]]*)(\\])(.*)");

	// if wildcard was found
	if (rx.indexIn(path) != -1) {
		// get pre and post path
		QString pre = rx.cap(1);
		QString post = rx.cap(5);

		QStringList pathList;

		// split the wildcard at the separator
		QStringListIterator wildcardIt(rx.cap(3).split(","));
		while (wildcardIt.hasNext()) {
			// split ranges
			QStringList wildcard = wildcardIt.next().split("-");

			if (wildcard.size() < 2) {
				int a = wildcard.at(0).toInt();

				// build the path
				pathList.append(QString("%1%2%3").arg(pre).arg(a).arg(post));
			} else {
				int a = wildcard.at(0).toInt();
				int b = wildcard.at(1).toInt();

				// ensure that a is smaller than b
				if (b < a) {
					int c = a;
					a = b;
					b = c;
				}

				// build the paths
				for (int i = a; i <= b; ++i) {
					pathList.append(QString("%1%2%3").arg(pre).arg(i).arg(post));
				}
			}

		}

		return pathList;

	} else {
		return QStringList();
	}
}


QString QMultiFileInfo::normalizeFilePath(QString path) {
	// replace \ with /
	path.replace("\\", "/");

	// prepare new path
	int counter = 0;
	QStringList newPath;

	// iterate string from back to front
	QStringListIterator it(path.split("/"));
	it.toBack();
	while (it.hasPrevious()) {
		QString part = it.previous();

		if (part == "..") {
			++counter;
		} else {
			if (counter > 0) {
				--counter;
			} else {
				newPath.insert(0, part);
			}
		}
	}

	// add leading ".."
	while (counter > 0) {
		newPath.insert(0, "..");
		--counter;
	}

	// join path
	return newPath.join("/");
}