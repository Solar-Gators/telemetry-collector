
PYTHON_FLAGS = $(shell python-config --cflags) $(shell python-config --ldflags)

CPP_FILES = src/lib/*.cpp
CPP_FILES += CAN-Decoder/src/DataModules/src/*.cpp
CPP_FILES += src/main.cpp

CPP_INCLUDES = -I ./CAN-Decoder/src/DataModules/inc

all:
	g++ $(PYTHON_FLAGS) -o test $(CPP_INCLUDES) $(CPP_FILES)
