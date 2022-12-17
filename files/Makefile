TARGET  = smartnavsys-lib
SOURCES = $(wildcard modules/*/*.cpp)
HEADERS = $(wildcard modules/*/*.hpp)
OBJECTS = $(SOURCES:.cpp=.o)

OBJECTS_DIR = obj

CFLAGS  = -std=c++17 -c -fPIC 
LDFLAGS = -shared

LDLIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -ltensorflow-lite -ldl -lpthread

OBJS_WITH_DIR = $(patsubst %,$(OBJECTS_DIR)/%,$(OBJECTS))

all: $(TARGET)

$(TARGET): $(OBJS_WITH_DIR)
	@echo Compiling $(TARGET)
	$(CXX) -o $(TARGET) $(OBJS_WITH_DIR) $(LDFLAGS) $(LDLIBS)
 
$(OBJS_WITH_DIR): $(SOURCES)
	@echo Compiling $< to $@
	mkdir -p $(OBJECTS_DIR)
	$(CXX) $(CFLAGS) -o $@ $<

install: $(TARGET)
	cp $(TARGET) $(DESTDIR)/usr/lib

clean:
	rm -r $(OBJECTS_DIR) 
	rm -f $(TARGET)
