
BUILD_DIR = build
DEBUG_DIR = $(BUILD_DIR)/debug
RELEASE_DIR = $(BUILD_DIR)/release

all: debug release

debug: $(DEBUG_DIR) main_debug

$(DEBUG_DIR):
	mkdir -p $@
	
main_debug:
	cd $(DEBUG_DIR); qmake-qt4 CONFIG+=debug ../../ ; make
	
	
release: $(RELEASE_DIR) main_release

$(RELEASE_DIR):
	mkdir -p $@
	
main_release:
	cd $(RELEASE_DIR); qmake-qt4 CONFIG+=debug ../../ ; make
	

$(BUILD_DIR):
	mkdir -p $@
	

clean:
	rm -rf $(BUILD_DIR)