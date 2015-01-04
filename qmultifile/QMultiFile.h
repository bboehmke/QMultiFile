/**
 * @file QMultiFile.h
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
 
#ifndef QMULTIFILE_H_
#define QMULTIFILE_H_

#include <QIODevice>
#include <QString>
#include <QSharedPointer>

#include "QMultiFileInfo.h"

class QFileType;
class QFileFactory;

/**
 * @class QMultiFile
 * @brief Class to handle multiple file types
 *
 * The 'QMultiFile' class can be used as replacement for 'QFile'.
 *
 */
class QMultiFile : public QIODevice {
	Q_OBJECT
	public:
		/**
		 * @brief Construct the file
		 * @param fileInfo Information about the file
		 */
		QMultiFile(QMultiFileInfo& fileInfo);
		/**
		 * @brief Construct the file
		 * @param name Path to the file
		 */
		QMultiFile(QString name);
		~QMultiFile();

		/**
		 * @brief Check if the file exist
		 * @return True if the file exist
		 */
		bool exist() const;

		/**
		 * @brief Open the file in the given mode
		 * @param mode Open mode
		 * @return True if success
		 */
		bool open(OpenMode mode);
		/**
		 * @brief Close the device
		 */
		void close();

		/**
		 * @brief Check if the current read/write position is at the end
		 * @return True if position is at the end
		 */
		bool atEnd() const;
		/**
		 * @brief Amount of available bytes for reading
		 * @return Available bytes
		 */
		qint64 bytesAvailable() const;

		/**
		 * @brief Set the read/write position to the given point
		 * @param position Position to set the 'cursor'
		 * @return True if success
		 */
		bool seek(qint64 position);

		/**
		 * @brief Get the size of the file
		 * @return Size in bytes
		 */
		qint64 size() const;


		/**
		 * @brief Returns the Version information of this library
		 * @return Version info
		 */
		static QString getVersionInfo();

	protected:
		/**
		 * @brief Reads data from the IO object
		 * @param data Pointer where the data should be written to
		 * @param maxSize Maximum read bytes
		 * @return Amount of read bytes
		 */
		qint64 readData(char* data, qint64 maxSize);

		/**
		 * @brief Writes data to the IO object
		 * @param data Date to write
		 * @param maxSize Maximum bytes to write
		 * @return Written bytes
		 */
		qint64 writeData(const char* data, qint64 maxSize);

	private:
		/**
		 * @brief Handle of the IO file
		 */
		QFileType* fileHandle;


		/**
		 * @brief Creates the file type factory
		 */
		static void initFileTypeFactory();

		/**
		 * @brief Instance of the file type factory
		 */
		static QSharedPointer<QFileFactory> fileFactory;
};

#endif /* QMULTIFILE_H_ */
