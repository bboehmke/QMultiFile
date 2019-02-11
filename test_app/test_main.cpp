/**
 * @file test_main.cpp
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

#include <QDebug>
#include <QtTest>

#include <qmultifile/QMultiFileInfo.h>
#include <qmultifile/QMultiFile.h>

#include <QStringList>


class TestQMultiFile: public QObject {
    Q_OBJECT
    private slots:
        void initTestCase();

        void testFiles_data();
        void testFiles();
};

void TestQMultiFile::initTestCase() {
    QMultiFile::addArchiveAlias("zip", "zippy");
}

void TestQMultiFile::testFiles_data() {
    QTest::addColumn<QString>("src");
    QTest::addColumn<QString>("filePath");
    QTest::addColumn<QString>("archivePath");
    QTest::addColumn<QString>("inArchivePath");
    QTest::addColumn<QString>("path");
    QTest::addColumn<QString>("wildcardFilePath");
    QTest::addColumn<QString>("wildcardPath");
    QTest::addColumn<QString>("wildcardArchivePath");
    QTest::addColumn<QString>("archiveExtension");

    QTest::newRow("normal path")
            << "testFiles/dir2/df.txt"
            << "testFiles/dir2/df.txt"
            << ""
            << "testFiles/dir2/df.txt"
            << "testFiles/dir2"
            << "testFiles/dir2/df.txt"
            << "testFiles/dir2"
            << ""
            << "";

    QTest::newRow("simple zip")
            << "testFiles/test.zip/dir2/df.txt"
            << "testFiles/test.zip/dir2/df.txt"
            << "testFiles/test.zip"
            << "dir2/df.txt"
            << "testFiles/test.zip/dir2"
            << "testFiles/test.zip/dir2/df.txt"
            << "testFiles/test.zip/dir2"
            << "testFiles/test.zip"
            << "zip";

    QTest::newRow("zip with . in name")
            << "testFiles/test.bla.zip/dir2/df.txt"
            << "testFiles/test.bla.zip/dir2/df.txt"
            << "testFiles/test.bla.zip"
            << "dir2/df.txt"
            << "testFiles/test.bla.zip/dir2"
            << "testFiles/test.bla.zip/dir2/df.txt"
            << "testFiles/test.bla.zip/dir2"
            << "testFiles/test.bla.zip"
            << "zip";

    QTest::newRow("zip with different name")
            << "testFiles/test.zippy/dir2/df.txt"
            << "testFiles/test.zippy/dir2/df.txt"
            << "testFiles/test.zippy"
            << "dir2/df.txt"
            << "testFiles/test.zippy/dir2"
            << "testFiles/test.zippy/dir2/df.txt"
            << "testFiles/test.zippy/dir2"
            << "testFiles/test.zippy"
            << "zippy";

    QTest::newRow("simple tar")
            << "testFiles/test.tar/dir2/df.txt"
            << "testFiles/test.tar/dir2/df.txt"
            << "testFiles/test.tar"
            << "dir2/df.txt"
            << "testFiles/test.tar/dir2"
            << "testFiles/test.tar/dir2/df.txt"
            << "testFiles/test.tar/dir2"
            << "testFiles/test.tar"
            << "tar";

    QTest::newRow("simple tar.gz")
            << "testFiles/test.tar.gz/dir2/df.txt"
            << "testFiles/test.tar.gz/dir2/df.txt"
            << "testFiles/test.tar.gz"
            << "dir2/df.txt"
            << "testFiles/test.tar.gz/dir2"
            << "testFiles/test.tar.gz/dir2/df.txt"
            << "testFiles/test.tar.gz/dir2"
            << "testFiles/test.tar.gz"
            << "tar.gz";

    QTest::newRow("wildcard with exact match")
            << "testFiles/tst_[1-2].zip/dir2/df.txt"
            << "testFiles/tst_2.zip/dir2/df.txt"
            << "testFiles/tst_2.zip"
            << "dir2/df.txt"
            << "testFiles/tst_2.zip/dir2"
            << "testFiles/tst_[1-2].zip/dir2/df.txt"
            << "testFiles/tst_[1-2].zip/dir2"
            << "testFiles/tst_[1-2].zip"
            << "zip";

    QTest::newRow("wildcard to large")
            << "testFiles/tst_[1-20].zip/dir2/df.txt"
            << "testFiles/tst_2.zip/dir2/df.txt"
            << "testFiles/tst_2.zip"
            << "dir2/df.txt"
            << "testFiles/tst_2.zip/dir2"
            << "testFiles/tst_[1-20].zip/dir2/df.txt"
            << "testFiles/tst_[1-20].zip/dir2"
            << "testFiles/tst_[1-20].zip"
            << "zip";

    QTest::newRow("zip inside directory with .")
            << "testFiles/test.ext/test.zip/dir2/df.txt"
            << "testFiles/test.ext/test.zip/dir2/df.txt"
            << "testFiles/test.ext/test.zip"
            << "dir2/df.txt"
            << "testFiles/test.ext/test.zip/dir2"
            << "testFiles/test.ext/test.zip/dir2/df.txt"
            << "testFiles/test.ext/test.zip/dir2"
            << "testFiles/test.ext/test.zip"
            << "zip";

    QTest::newRow("zip with capital letter extension")
            << "testFiles/test2.ZIP/dir2/df.txt"
            << "testFiles/test2.ZIP/dir2/df.txt"
            << "testFiles/test2.ZIP"
            << "dir2/df.txt"
            << "testFiles/test2.ZIP/dir2"
            << "testFiles/test2.ZIP/dir2/df.txt"
            << "testFiles/test2.ZIP/dir2"
            << "testFiles/test2.ZIP"
            << "zip";

    QTest::newRow("zip with .. inside")
            << "testFiles/test.zip/dir2/../dir2/df.txt"
            << "testFiles/test.zip/dir2/df.txt"
            << "testFiles/test.zip"
            << "dir2/df.txt"
            << "testFiles/test.zip/dir2"
            << "testFiles/test.zip/dir2/df.txt"
            << "testFiles/test.zip/dir2"
            << "testFiles/test.zip"
            << "zip";

}

void TestQMultiFile::testFiles() {
    QFETCH(QString, src);
    QFETCH(QString, filePath);
    QFETCH(QString, archivePath);
    QFETCH(QString, inArchivePath);
    QFETCH(QString, path);
    QFETCH(QString, wildcardFilePath);
    QFETCH(QString, wildcardPath);
    QFETCH(QString, wildcardArchivePath);
    QFETCH(QString, archiveExtension);
    //qDebug() << src;

    QMultiFileInfo info(src);
    QCOMPARE(info.baseName(), QString("df"));
    QCOMPARE(info.fileName(), QString("df.txt"));
    QCOMPARE(info.filePath(), filePath);
    QCOMPARE(info.archivePath(), archivePath);
    QCOMPARE(info.inArchivePath(), inArchivePath);
    QCOMPARE(info.path(), path);
    QCOMPARE(info.absoluteFilePath(),
             QDir::currentPath() + "/" + wildcardFilePath);
    QCOMPARE(info.absolutePath(),
             QDir::currentPath() + "/" + wildcardPath);
    QCOMPARE(info.wildcardFilePath(), wildcardFilePath);
    QCOMPARE(info.wildcardPath(), wildcardPath);
    QCOMPARE(info.wildcardArchivePath(), wildcardArchivePath);
    QCOMPARE(info.getArchiveExtension(), archiveExtension);
    QCOMPARE(info.isInArchive(), !archiveExtension.isEmpty());
    QVERIFY(info.exist());
    QVERIFY(info.exists());

    qint64 archiveSizeDiff = 0;
    if (info.isInArchive()) {
        archiveSizeDiff = 10;
    }

    QMultiFile file(src);
    QVERIFY(file.open(QIODevice::ReadOnly));
    QCOMPARE(file.size(), 552LL-archiveSizeDiff);
    QCOMPARE(file.pos(), 0LL);
    QVERIFY(!file.atEnd());
    QCOMPARE(file.bytesAvailable(), 552LL-archiveSizeDiff);

    QVERIFY(file.seek(32));
    QCOMPARE(file.read(10), QByteArray("t Verf. Ve"));
    QVERIFY(file.seek(32));
    QCOMPARE(file.read(10), QByteArray("t Verf. Ve"));

    QCOMPARE(file.pos(), 42LL);
    QVERIFY(!file.atEnd());
    QCOMPARE(file.bytesAvailable(), 510LL-archiveSizeDiff);

    file.close();
}


QTEST_MAIN(TestQMultiFile)
#include "test_main.moc"