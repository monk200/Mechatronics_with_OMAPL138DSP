CXX = arm-none-linux-gnueabi-gcc

targets = SaveScratchToFile

all: $(targets)

netapi.o: netapi.c 
	$(CXX) -c netapi.c
	
omapl138_gpiofuncs.o: omapl138_gpiofuncs.c 
	$(CXX) -c omapl138_gpiofuncs.c

SaveScratchToFile.o: SaveScratchToFile.c
	$(CXX) -c SaveScratchToFile.c	 

SaveScratchToFile: netapi.o omapl138_gpiofuncs.o SaveScratchToFile.o
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ 
clean:
	rm -rf *.o $(targets)
  
