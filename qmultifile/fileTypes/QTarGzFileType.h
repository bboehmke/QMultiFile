/**
 * @file QTarGzFileType.h
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
 
#ifndef QTARGZFILETYPE_H_
#define QTARGZFILETYPE_H_

#include "../QFileType.h"

#include <QIODevice>

/**
 * @class QTarGzFileType
 * @brief Class to handle files in gzip compressed TAR archives
 *
 * This class use quazip for reading gzip compressed TAR files.
 *
 */
class QTarGzFileType : public QFileType {
	public:
		/**
		 * @brief Construct the TAR file handler
		 * @param fileInfo Information about the file
		 */
		QTarGzFileType(QMultiFileInfo& fileInfo);
		~QTarGzFileType();

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
		bool open(QIODevice::OpenMode mode);

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
		 * @brief Get the current read/write position
		 * @return Cursor position
		 */
		qint64 pos() const;

		/**
		 * @brief Read up to <em>maxSize</em> and write it to <em>data</em>
		 * @param data Pointer where the data should written to
		 * @param maxSize Amount of data to read
		 * @return Read bytes
		 */
		qint64 read(char* data,qint64 maxSize);
		/**
		 * @brief Write up to <em>maxSize</em> of <em>data</em> to file
		 * @param data Pointer to the data to write
		 * @param maxSize Amount of data to write
		 * @return Written bytes
		 */
		qint64 write(const char* data, qint64 maxSize);

	private:
		/**
		 * @brief File handle
		 */
		QIODevice* file;

		/**
		 * @brief Last open mode
		 */
		QIODevice::OpenMode openMode;
};

#endif /* QTARFILETYPE_H_ */
