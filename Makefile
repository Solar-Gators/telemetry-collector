
PYTHON_FLAGS = $(shell python-config --cflags) $(shell python-config --ldflags)

CPP_FILES = src/lib/DataLinkRecieve.cpp src/lib/PythonScripts.cpp src/lib/NetworkReceive.cpp src/main.cpp

all:
	g++ $(PYTHON_FLAGS) -o test $(CPP_FILES)
