/**
 * @file QTar.h
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
#ifndef QTAR_H_
#define QTAR_H_

#include <QString>
#include <QStringList>
#include <QIODevice>
#include <QSharedPointer>


/**
 * @class QTar
 * @brief Class to get informations about a TAR archives
 *
 */
class QTar {
	public:
		/**
		 * @brief Construct a empty instance
		 */
		QTar();

		/**
		 * @brief Construct the class with the given file
		 * @param tarName Name of the file
		 */
		QTar(const QString& tarName);
		/**
		 * @brief Construct the class with the given IODevice
		 * @param ioDevice IODevice of the tar archive
		 */
		QTar(QSharedPointer<QIODevice> ioDevice);

		/**
		 * @brief Possible open modes
		 */
		typedef enum {
			mdNotOpen,    //!< Archive not open
			mdUntar       //!< Archive open for extraction
		} Mode;

		/**
		 * @brief Open the Archive
		 * @param mode Mode to open the archive
		 * @return True if the action was successful
		 */
		bool open(Mode mode);

		/**
		 * @brief Close the archive
		 */
		void close();

		/**
		 * @brief Get a list with all files in the archive
		 * @return List with the file names
		 */
		QStringList getFileNameList() const;

		/**
		 * @brief Struct for informations about a file
		 */
		typedef struct {
			quint64 offset;    //!< Offset of the file data in the tar archive
			QString fileName;  //!< Name of the file
			quint64 fileSize;  //!< Size of the file
		} FileInfo;

		/**
		 * @brief Get a list with informations about all files in the archive
		 * @return List with file informations
		 */
		QList<FileInfo> getFileInfoList() const;

	private:
		/**
		 * @brief Actual open mode
		 */
		Mode openMode;

		/**
		 * @brief handle of the archive
		 */
		QSharedPointer<QIODevice> file;
};

#endif /* QTAR_H_ */
