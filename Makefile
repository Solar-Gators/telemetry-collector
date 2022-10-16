CPP_FILES = src/lib/*.cpp
CPP_FILES += CAN-Decoder/src/DataModules/src/*.cpp
CPP_FILES += src/main.cpp

CPP_INCLUDES = -I ./CAN-Decoder/src/DataModules/inc -I ./src/lib/inc

EXECUTABLE = collector

all:
	g++ -D IS_TELEMETRY $(shell python3-config --cflags --embed) -o $(EXECUTABLE)  $(CPP_INCLUDES) $(CPP_FILES) $(shell python3-config --embed --ldflags) -fPIE
