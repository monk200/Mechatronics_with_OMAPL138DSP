CXX = arm-none-linux-gnueabi-gcc

targets = TurnOnLEDS

all: $(targets)
	
omapl138_gpiofuncs.o: omapl138_gpiofuncs.c 
	$(CXX) -c omapl138_gpiofuncs.c

TurnOnLEDS.o: TurnOnLEDS.c
	$(CXX) -c TurnOnLEDS.c	 

TurnOnLEDS: omapl138_gpiofuncs.o TurnOnLEDS.o
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ 
clean:
	rm -rf *.o $(targets)
  
