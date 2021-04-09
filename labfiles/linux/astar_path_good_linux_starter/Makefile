CXX = arm-none-linux-gnueabi-gcc

targets = astar_path

all: $(targets)
	
omapl138_gpiofuncs.o: omapl138_gpiofuncs.c 
	$(CXX) -c omapl138_gpiofuncs.c

pQueue.o: pQueue.c
	$(CXX) -c pQueue.c	 
	
astar_path.o: astar_path.c
	$(CXX) -c astar_path.c	 

astar_path: omapl138_gpiofuncs.o pQueue.o astar_path.o
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ 
clean:
	rm -rf *.o $(targets)
  
