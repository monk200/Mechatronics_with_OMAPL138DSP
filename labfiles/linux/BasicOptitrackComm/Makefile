CXX = arm-none-linux-gnueabi-gcc
#CXX = gcc

targets = BasicOptitrackComm

all: $(targets)

netapi.o: netapi.c 
	$(CXX) -c netapi.c
	
omapl138_gpiofuncs.o: omapl138_gpiofuncs.c 
	$(CXX) -c omapl138_gpiofuncs.c

BasicOptitrackComm.o: BasicOptitrackComm.c
	$(CXX) -c BasicOptitrackComm.c	 

BasicOptitrackComm: netapi.o omapl138_gpiofuncs.o BasicOptitrackComm.o
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ 
	#$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ -static
clean:
	rm -rf *.o $(targets)
  
