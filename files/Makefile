TARGET  = smartnavsys
SUBDIR = modules/capture-frame modules/frame-processor modules/hc-sr04 modules/logger modules/fuzzy-control-system

OBJECTS_DIR = ./obj

HEADERS = $(wildcard *.hpp $(foreach fd, $(SUBDIR), $(fd)/*.hpp))
SOURCES = $(wildcard *.cpp $(foreach fd, $(SUBDIR), $(fd)/*.cpp))
OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(SOURCES:cpp=o))
INCLUDE_DIRS = $(addprefix -I, $(SUBDIR))

CFLAGS  = -std=c++17 -c -fPIC 
LDFLAGS = -shared
LDLIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -ltensorflow-lite -ldl -lpthread

all: lib$(TARGET).so

lib$(TARGET).so: $(OBJECTS)
	@echo Compiling lib$(TARGET).so
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJECTS_DIR)/%.o: %.cpp $(HEADERS)
	mkdir -p $(@D)
	@echo Compiling $@
	$(CXX) -o $@ -c $< $(CFLAGS) $(INCLUDE_DIRS)

install: lib$(TARGET).so
	cp lib$(TARGET).so $(DESTDIR)/usr/lib

clean:
	rm -rf $(OUTPUT_DIR)/* $(OBJECTS_DIR)/*