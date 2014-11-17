# QMultiFile

## Requirements

* Qt 4.x
* [QuaZIP](http://quazip.sourceforge.net/) 0.6.2+  


## Features

* Open files in archives as normal files
* Easy to extend for more archive types
* Support for wildcard in archive path


## ToDo
* Support writing of files
* Support tar and tar.gz archives

## How to Use

The 'QMultiFile' class can be used as replacement for 'QFile'.

Possible file path:

* test/ex.zip/aa/bb.txt (open the file "aa/bb.txt" in the archive "test/ex.zip")
* test/aa/bb.txt (open the file "test/aa/bb.txt" like QFile)
