
all:
	g++ $(python-config --cflags) -o test $(python-config --ldflags) main.cpp
