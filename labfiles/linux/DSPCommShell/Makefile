CXX = arm-none-linux-gnueabi-gcc

targets = DSPcommshell

all: $(targets)

netapi.o: netapi.c 
	$(CXX) -c netapi.c
	
omapl138_gpiofuncs.o: omapl138_gpiofuncs.c 
	$(CXX) -c omapl138_gpiofuncs.c

DSPcommshell.o: DSPcommshell.c
	$(CXX) -c DSPcommshell.c	 

DSPcommshell: netapi.o omapl138_gpiofuncs.o DSPcommshell.o
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ 
clean:
	rm -rf *.o $(targets)
  
