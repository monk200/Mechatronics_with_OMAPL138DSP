CXX= arm-none-linux-gnueabi-gcc

targets = LVDSPComm

all: $(targets)

netapi.o: netapi.c 
	$(CXX) -c netapi.c
	
omapl138_gpiofuncs.o: omapl138_gpiofuncs.c 
	$(CXX) -c omapl138_gpiofuncs.c

LVDSPComm.o: LVDSPComm.c
	$(CXX) -c LVDSPComm.c	 

LVDSPComm: netapi.o omapl138_gpiofuncs.o LVDSPComm.o
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ 
	#$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ -static
clean:
	rm -rf *.o $(targets)
  
