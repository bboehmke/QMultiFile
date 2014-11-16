/**
 * @file QMultiFileInfo.cpp
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
	// replace \ with /
	file.replace("\\", "/");

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
			archiveExtension = rx.cap(3);

			// set the file path
			path_file = file.mid(pos + rx.matchedLength());

			// build the wildcard paths
			QStringList pathList = getArchivePath(path_wildcardArchive);

			// if nothing was build we may have no wildcard
			if (pathList.isEmpty()) {
				path_archive = path_wildcardArchive;

				// give this file info to the multifile
				fileExist = QMultiFile(*this).exist();

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
	return path.left(path.lastIndexOf("/"));
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
	return path.left(path.lastIndexOf("/"));
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
