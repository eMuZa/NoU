#---------------Variabler---------------------
SOURCES=main.cpp MsgQueue.cpp Message.cpp
OBJECTS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.o))
DEPS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.d))
EXE=$(BUILD_BIN)/prog
CXXFLAGS=-I.
LDFLAGS=-lpthread

#----------Valg imellem host og target--------
# Making for host
# > make ARCH=host
ifeq (${ARCH},host)
BUILD_DIR=build/host
BUILD_BIN=bin/host
endif

# Making for target
# > make ARCH=target
ifeq (${ARCH},target)
CXX=arm-rpizw-g++
BUILD_DIR=build/target
BUILD_BIN=bin/target
endif

#--------------------Build--------------------
.PHONY: all clean help

${EXE}: $(DEPS) $(OBJECTS) # << Check the $(DEPS) new dependency
	@mkdir -p $(BUILD_BIN)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

# Rule that describes how a .d (dependency) file is created from a .cpp file
# Similar to the assigment that you just completed %.cpp -> %.o

#---------------Dependencys------------------
${BUILD_DIR}/%.d: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $^ > $@

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif

#---------------pattern search---------------
${BUILD_DIR}/%.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

#---------------Utilitys-------------------
clean:
	@rm -rf build
	@rm -rf bin
	@echo "Done cleaning"

help:
	@echo "Targets: ARCH=host, ARCH=target, clean, help"
