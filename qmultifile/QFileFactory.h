/**
 * @file QFileFactory.h
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
 
#ifndef QFILEFACTORY_H_
#define QFILEFACTORY_H_

#include <QString>
#include <QSharedPointer>
#include <QMap>
#include <QStringList>

#include "QFileType.h"
#include "QMultiFileInfo.h"


/**
 * @class QFileCreator
 * @brief Base class for the GenericFileCreator
 */
class QFileCreator {
	public:
		virtual ~QFileCreator() {}

		/**
		 * @brief Creates a new instance of this class
		 * @param fileInfo Information about the file
		 * @return The created file
		 */
		virtual QFileType* create(QMultiFileInfo& fileInfo) = 0;
};

/**
 * @class QGenericFileCreator
 * @brief Class for the creation of a new instance of <em>T</em>
 */
template<class T>
class QGenericFileCreator: public QFileCreator {
	public:
		~QGenericFileCreator() {}

		/**
		 * @brief Creates a new instance of this class
		 * @param fileInfo Information about the file
		 * @return The created file
		 */
		QFileType* create(QMultiFileInfo& fileInfo) {
			return new T(fileInfo);
		}
};

/**
 * @class QFileFactory
 * @brief Class providing the interface to the FileFactory
 */
class QFileFactory {
	public:
		/**
		 * @brief Register a new File
		 * @tparam The File-class to register
		 */
		template<class T>
		void registerFile() {
			QSharedPointer<QFileCreator> fc(new QGenericFileCreator<T>);

			// create an empty file info
			QMultiFileInfo info;

			// add all file extensions of this file to the list
			QStringListIterator extIt(T(info).getExtensions());
			while (extIt.hasNext()) {
				fileList[extIt.next()] = fc;
			}

		}

		/**
		 * @brief Creates a new instance from the given file path
		 * @param fileInfo Information about the file
		 * @return The created file
		 */
		QFileType* create(QMultiFileInfo& fileInfo);

	private:
		/**
		 * @brief List with all registered files
		 */
		QMap<QString, QSharedPointer<QFileCreator> > fileList;
};




#endif /* QFILEFACTORY_H_ */
