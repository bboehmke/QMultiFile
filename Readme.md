# QMultiFile

## Features

* Open files in archives as normal files
* Actual supported Archives:
    * ZIP
    * TAR
    * TAR.GZ
* Support for archive extension alias names
* Easy to extend for more archive types
* Support for wildcard in archive path

## Requirements

* Qt 4.x
* [QuaZIP](http://quazip.sourceforge.net/) 0.6.2+  

## How to Use

The 'QMultiFile' class can be used as replacement for 'QFile'.

Possible file path:

* test/ex.zip/aa/bb.txt (open the file "aa/bb.txt" in the archive "test/ex.zip")
* test/aa/bb.txt (open the file "test/aa/bb.txt" like QFile)
* test/ex[1-2].zip/aa/bb.txt (open the file "aa/bb.txt" in the archive "test/ex1.zip" or "test/ex2.zip")

## ToDo
* Support writing of files