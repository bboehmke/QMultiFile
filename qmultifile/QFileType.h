/**
 * @file QFileType.h
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
 
#ifndef QFILETYPE_H_
#define QFILETYPE_H_

#include <QIODevice>
#include <QString>
#include <QStringList>

#include "QMultiFileInfo.h"

/**
 * @class QFileType
 * @brief Base class for all file types
 */
class QFileType {
	public:
		/**
		 * @brief Construct the file
		 * @param extensions Extensions that are supported by this file type
		 * @param fileInfo Information about the file
		 */
		QFileType(QStringList extensions, QMultiFileInfo& fileInfo);
		virtual ~QFileType();

		/**
		 * @brief Get the list with supported extensions
		 * @return List with file extensions
		 */
		QStringList getExtensions() const;

		/**
		 * @brief Check if the file exist
		 * @return True if the file exist
		 */
		virtual bool exist() const = 0;
		/**
		 * @brief Open the file in the given mode
		 * @param mode Open mode
		 * @return True if success
		 */
		virtual bool open(QIODevice::OpenMode mode) = 0;

		/**
		 * @brief Close the device
		 */
		virtual void close() = 0;

		/**
		 * @brief Check if the current read/write position is at the end
		 * @return True if position is at the end
		 */
		virtual bool atEnd() const = 0;

		/**
		 * @brief Amount of available bytes for reading
		 * @return Available bytes
		 */
		virtual qint64 bytesAvailable() const = 0;

		/**
		 * @brief Set the read/write position to the given point
		 * @param position Position to set the 'cursor'
		 * @return True if success
		 */
		virtual bool seek(qint64 position) = 0;
		/**
		 * @brief Get the size of the file
		 * @return Size in bytes
		 */
		virtual qint64 size() const = 0;
		/**
		 * @brief Get the current read/write position
		 * @return Cursor position
		 */
		virtual qint64 pos() const = 0;

		/**
		 * @brief Read up to <em>maxSize</em> and write it to <em>data</em>
		 * @param data Pointer where the data should written to
		 * @param maxSize Amount of data to read
		 * @return Read bytes
		 */
		virtual qint64 read(char* data,qint64 maxSize) = 0;
		/**
		 * @brief Write up to <em>maxSize</em> of <em>data</em> to file
		 * @param data Pointer to the data to write
		 * @param maxSize Amount of data to write
		 * @return Written bytes
		 */
		virtual qint64 write(const char* data, qint64 maxSize) = 0;

	protected:
		/**
		 * @brief Informations about the file
		 */
		QMultiFileInfo fileInfo;

	private:
		/**
		 * @brief Supported file extensions
		 */
		QStringList fileExtensions;

};

#endif /* QFILETYPE_H_ */
