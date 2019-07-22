ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
    GTEST_DIR = c:/MinGW/include/gtest
	GMOCK_DIR = c:/MinGW/include/gmock
	OS=WIN
else
    GTEST_DIR = /usr/local/gtest
	GMOCK_DIR = /usr/local/gmock
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OS = LIN
		MYTEST_DIR = /home/stratis/dev/c++/myTestSuit/include
	endif
	ifeq ($(UNAME_S),Darwin)
		OS = OS
		
	endif
endif


#curl support
#LDFLAGS=-L/usr/local/opt/curl/lib
#CPPFLAGS=-I/usr/local/opt/curl/include
CC=g++
DEBUG = -ggdb 
CFLAGS_STANDARD = -std=gnu++11
CFLAGS_WARNING1 = -Wall
CFLAGS_WARNING2 = -Werror
CFLAGS_EXTRA = -m64

CFLAGS_NO_ERROR = $(CFLAGS_STANDARD) $(DEBUG) $(CFLAGS_EXTRA) 
CFLAGS = $(CFLAGS_NO_ERROR) $(CFLAGS_WARNING1) $(CFLAGS_WARNING2)
CFLAGS_NO_WERROR = $(CFLAGS_NO_ERROR) $(CFLAGS_WARNING1)
CFPRODUCTION=$(CFLAGS_STANDARD) $(CFLAGS_EXTRA) -O2

BOOST_LIBS = -lboost_filesystem -lboost_system #any other lib
INC = -Iinclude
TEST_INC = -I$(GTEST_DIR)  -I$(GTEST_DIR)/include  -I$(GMOCK_DIR) -I$(GMOCK_DIR)/include 

OBJS_DIR = objs/${OS}
BUILD_DIR = build/${OS}
TESTS_DIR=$(BUILD_DIR)/${OS}/tests
DIR_GUARD=@mkdir -p $(@D)
PROJECT = main

all: programs tests libs

#  PROGRAMS
programs: $(BUILD_DIR)/$(PROJECT)

$(BUILD_DIR)/$(PROJECT): $(OBJS_DIR)/bignums.o $(OBJS_DIR)/stdfuncs.o src/main.cpp  #any other object files like objs/route.o 
	$(DIR_GUARD)
	@echo -n compiling $@
	@$(CC) $(CFLAGS)  $^ $(INC) -o $@ 
	@echo " ...finished\n"

# OBJECTS

# $(OBJS_DIR)/gtest.o: 
# 	$(DIR_GUARD)
# 	@echo -n compiling Google Test Library $@
# 	@$(CC) $(CFLAGS) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR)  -isystem $(GMOCK_DIR) \
# 	-pthread -c $(GTEST_DIR)/src/gtest-all.cc -o $@  
# 	@echo " ...finished\n"

# $(OBJS_DIR)/gmock.o: 
# 	$(DIR_GUARD)
# 	@echo -n compiling Google Mocking Library $@
# 	@$(CC) $(CFLAGS) -isystem ${GTEST_DIR}/include -I${GTEST_DIR} \
#     -isystem ${GMOCK_DIR}/include -I${GMOCK_DIR} \
#     -pthread -c ${GMOCK_DIR}/src/gmock-all.cc -o $@ 
# 	@echo " ...finished\n"

$(OBJS_DIR)/route.o: src/route.cpp include/route.hpp  $(OBJS_DIR)/coordinates.o
	$(DIR_GUARD)
	@echo -n compiling $@ 
	@$(CC) $(CFLAGS) -c src/route.cpp -o $@ $(INC)
	@echo " ...finished\n"

$(OBJS_DIR)/coordinates.o: src/coordinates.cpp include/coordinates.hpp 
	$(DIR_GUARD)
	@echo -n compiling $@ 
	@$(CC) $(CFLAGS) -c src/coordinates.cpp -o $@ $(INC)
	@echo " ...finished\n"

$(OBJS_DIR)/bignums.o: src/bignums.cpp include/bignums.hpp 
	$(DIR_GUARD)
	@echo -n compiling $@ 
	@$(CC) $(CFLAGS) -c src/bignums.cpp -o $@ $(INC)
	@echo " ...finished\n"

$(OBJS_DIR)/stdfuncs.o: src/stdfuncs.cpp include/stdfuncs.hpp 
	$(DIR_GUARD)
	@echo -n compiling $@ 
	@$(CC) $(CFLAGS) -c src/stdfuncs.cpp -o $@ $(INC)
	@echo " ...finished\n"


	
#LIBS


# $(OBJS_DIR)/libgmock.a: ${OBJS_DIR}/gtest.o ${OBJS_DIR}/gmock.o
# 	@echo -n creating static Library $@
# 	@ar -rc $@ $^
# 	@echo " ...finished\n"


	
libs:${OBJS_DIR}/bignums.o ${OBJS_DIR}/stdfuncs.o  #$(OBJS_DIR)/libgmock.a  ${OBJS_DIR}/gtest.o ${OBJS_DIR}/gmock.o 

# TESTS	

# $(TESTS_DIR)/gen: $(OBJS_DIR)/gtest.o $(OBJS_DIR)/gmock.o $(OBJS_DIR)/route.o tests/gen.cpp
# 	$(DIR_GUARD)
# 	@echo -n compiling test $@ 
# 	@$(CC) $(CFLAGS) $(INC) $(TEST_INC) $^ -o $@  -pthread
# 	@echo " ...finished\n"

# $(TESTS_DIR)/gpn: ${OBJS_DIR}/gtest.o ${OBJS_DIR}/gmock.o  ${OBJS_DIR}/bignums.o ${OBJS_DIR}/stdfuncs.o tests/gpn.cpp
# 	$(DIR_GUARD)
# 	@echo -n compiling test $@ 
# 	@$(CC) $(CFLAGS) $(INC) $(TEST_INC) $^ -o $@  -pthread
# 	@echo " ...finished\n"

$(TESTS_DIR)/alfa: ${OBJS_DIR}/bignums.o ${OBJS_DIR}/stdfuncs.o tests/alfa.cpp
	$(DIR_GUARD)
	@echo -n compiling test $@ 
	@$(CC) $(CFLAGS) $(INC) -I${MYTEST_DIR} $^ -o $@ 
	@echo " ...finished\n"

tests: ${TESTS_DIR}/alfa # $(TESTS_DIR)/gen  $(TESTS_DIR)/gpn 

clean:
	@rm -rf objs build
