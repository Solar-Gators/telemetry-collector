CPP_FILES = src/lib/*.cpp
CPP_FILES += CAN-Decoder/src/DataModules/src/*.cpp
CPP_FILES += src/main.cpp

CPP_INCLUDES = -I ./CAN-Decoder/src/DataModules/inc -I ./src/lib/inc

EXECUTABLE = collector

BASE_COMPILE = g++ -D IS_TELEMETRY $(shell python3-config --cflags --embed) -o $(EXECUTABLE)  $(CPP_INCLUDES) $(CPP_FILES) $(shell python3-config --embed --ldflags) -fPIE

all:
	$(BASE_COMPILE)

coverage:
	$(BASE_COMPILE) --coverage

COVERAGE_FILE = coverage.info

coverage-html:
	lcov --no-external --directory . --capture -o $(COVERAGE_FILE) && \
	lcov --remove $(COVERAGE_FILE) "*CAN-Decoder/*" -o $(COVERAGE_FILE) && \
	genhtml --demangle-cpp -o coverage $(COVERAGE_FILE)

clean:
	rm -rf \
		*.gcda \
		*.gcov \
		*.gcno \
		$(COVERAGE_FILE) \
		coverage \
		$(EXECUTABLE)
