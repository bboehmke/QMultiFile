/**
 * @file QTarFile.h
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
#ifndef QTARFILE_H_
#define QTARFILE_H_

#include <QIODevice>
#include <QString>
#include <QSharedPointer>

/**
 * @class QTarFile
 * @brief Class to access a file in a TAR archive
 *
 */
class QTarFile : public QIODevice {
	Q_OBJECT
	public:
		/**
		 * @brief construct an empty file
		 */
		QTarFile();
		/**
		 * @brief Construct a file in the given archive
		 * @param tarName Name of the archive
		 * @param fileName Name of the file
		 */
		QTarFile(const QString tarName, const QString &fileName);
		/**
		 * @brief Construct a file in the given archive
		 * @param ioDevice IODevice of the archive
		 * @param fileName Name of the file
		 */
		QTarFile(QIODevice* ioDevice, const QString &fileName);

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
		 * @brief File handle of the archive
		 */
		QSharedPointer<QIODevice> file;

		/**
		 * @brief Name of the file in the archive
		 */
		QString fileName;

		/**
		 * @brief Offset of the file in the archive
		 */
		qint64 offset;
		/**
		 * @brief Size of the file
		 */
		qint64 fileSize;
};

#endif /* QTARFILE_H_ */
