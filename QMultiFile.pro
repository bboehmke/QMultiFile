TEMPLATE = subdirs
CONFIG += ordered

## Lib
SUBDIRS += qmultifile

## Test App
!isEmpty(BUILD_TEST_APP) {
	SUBDIRS += test_app
	test_app.depends = quazip
} else {
	warning("Test app will not be build, to FORCE it set: BUILD_TEST_APP=1 at qmake command line.")
}

