/**
 * @file QMultiFileInfo.h
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
 
#ifndef QMULTIFILEINFO_H_
#define QMULTIFILEINFO_H_

#include <QString>

/**
 * @class QMultiFileInfo
 * @brief This class provides file informations
 *
 */
class QMultiFileInfo {
	public:
		/**
		 * @brief Constructs with empty data
		 */
		QMultiFileInfo();
		/**
		 * @brief Constructs the information with the given file
		 * @param file Path to the file
		 */
		QMultiFileInfo(QString file);

		/**
		 * @brief Returns the name of the file without extension
		 * @return File name
		 */
		QString baseName() const;
		/**
		 * @brief Returns the name of the file with extension
		 * @return File name
		 */
		QString fileName() const;

		/**
		 * @brief Returns the path to the file (which may be absolute or relative)
		 * @return Path to file
		 */
		QString filePath() const;

		/**
		 * @brief Returns the path to archive
		 * @return Path to the archive
		 */
		QString archivePath() const;

		/**
		 * @brief Returns the path of the file in the archive
		 * @return Path of the file
		 */
		QString inArchivePath() const;

		/**
		 * @brief Path to the folder of the file (which may be absolute or relative)
		 * @return Path to the folder
		 */
		QString path() const;

		/**
		 * @brief Returns the path to the file which may be contains wildcard
		 * @return Path to file
		 */
		QString wildcardFilePath() const;
		/**
		 * @brief Path to the folder of the file which may be contains wildcard
		 * @return Path to the folder
		 */
		QString wildcardPath() const;
		/**
		 * @brief Returns the path to archive
		 * @return Path to the archive
		 */
		QString wildcardArchivePath() const;

		/**
		 * @brief Returns the extension of the archive if the file is in one
		 * @return Archive file extension
		 */
		QString getArchiveExtension() const;

		/**
		 * @brief Check if it is file in a ZIP archive
		 * @return true if file is in archive
		 */
		bool isInArchive() const;

		/**
		 * @brief Check if the file exist
		 * @return True if the file exist
		 */
		bool exist() const;

	private:
		/**
		 * @brief Path to the archive, if file in archive, with wildcard
		 */
		QString path_wildcardArchive;

		/**
		 * @brief Path to the archive, if file in archive
		 */
		QString path_archive;
		/**
		 * @brief Path to the file (inside the archive, if file in archive)
		 */
		QString path_file;

		/**
		 * @brief File extension of the archive
		 */
		QString archiveExtension;

		bool fileExist;


		bool checkIfArchive(QString path);

		QStringList getArchivePath(QString path);
};

#endif /* QMULTIFILEINFO_H_ */
