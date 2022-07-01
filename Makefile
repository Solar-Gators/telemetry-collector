CPP_FILES = src/lib/*.cpp
CPP_FILES += CAN-Decoder/src/DataModules/src/*.cpp
CPP_FILES += src/main.cpp

CPP_INCLUDES = -I ./CAN-Decoder/src/DataModules/inc -I ./src/lib/inc

all:
	g++ $(shell python3-config --cflags --embed) -o test  $(CPP_INCLUDES) $(CPP_FILES) $(shell python3-config --embed --ldflags)
