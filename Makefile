CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++17 -g
COVERAGE_FLAGS = --coverage -fprofile-arcs -ftest-coverage
TEST_FILES = tests/*.cc src/model/*.cc
TEST_FLAGS = -lgtest -pthread

PATH_BUILD_TEST = tests/build
PATH_BUILD = build
PATH_BUILD_DVI = documentation/build

.PHONY : all install uninstall test gcov_report dvi dist leaks valgrind clean

UNAME := $(shell uname -s)
ifeq ($(UNAME), Darwin)
	RUN = ./build/smart_calc.app/Contents/MacOS/smart_calc
	APP = build/smart_calc.app
endif
ifeq ($(UNAME), Linux)
	RUN = ./build/smart_calc
	APP = build/smart_calc
endif

all : install

install : uninstall
	mkdir $(PATH_BUILD)
	cd $(PATH_BUILD) && qmake -o Makefile ../src/view/smart_calc.pro
	cd $(PATH_BUILD) && make all

run :
	$(RUN)

test : 
	rm -rf $(PATH_BUILD_TEST)
	mkdir $(PATH_BUILD_TEST)
	$(CXX) $(CXXFLAGS) $(TEST_FILES) -o $(PATH_BUILD_TEST)/test $(TEST_FLAGS)
	./$(PATH_BUILD_TEST)/test

test_coverage :
	rm -rf $(PATH_BUILD_TEST)
	mkdir $(PATH_BUILD_TEST)
	$(CXX) $(CXXFLAGS) $(COVERAGE_FLAGS) $(TEST_FILES) -o $(PATH_BUILD_TEST)/test $(TEST_FLAGS)
	./$(PATH_BUILD_TEST)/test

uninstall :
	rm -rf $(PATH_BUILD)

dvi :
	doxygen documentation/doc
	open $(PATH_BUILD_DVI)/html/index.html

dist :
	mkdir SmartCalc
	cp -r src tests Makefile documentation SmartCalc
	tar -cvzf smartcalc.tar.gz SmartCalc
	rm -r SmartCalc

valgrind :
	valgrind ./$(PATH_BUILD_TEST)/test

gcov_report : test_coverage
	gcovr --html-details -o $(PATH_BUILD_TEST)/test_list.html
	open $(PATH_BUILD_TEST)/test_list.html

clean : 
	rm -rf $(PATH_BUILD_TEST) $(PATH_BUILD_DVI)