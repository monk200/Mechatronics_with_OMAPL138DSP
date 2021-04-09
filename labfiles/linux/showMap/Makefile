CXX = arm-none-linux-gnueabi-gcc

targets = showMap

all: $(targets)
	
omapl138_gpiofuncs.o: omapl138_gpiofuncs.c 
	$(CXX) -c omapl138_gpiofuncs.c

showMap.o: showMap.c
	$(CXX) -c showMap.c	 

showMap: omapl138_gpiofuncs.o showMap.o
	$(CXX) -lm -o $@ $(CXXFLAGS) $(INCLUDES) $^ 
clean:
	rm -rf *.o $(targets)
  
