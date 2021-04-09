CXX= arm-none-linux-gnueabi-gcc

targets = playit

all: $(targets)

netapi.o: netapi.c 
	$(CXX) -c netapi.c
	
omapl138_gpiofuncs.o: omapl138_gpiofuncs.c 
	$(CXX) -c omapl138_gpiofuncs.c

playit.o: playit.c
	$(CXX) -c playit.c	 

playit: netapi.o omapl138_gpiofuncs.o playit.o
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ 
	#$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ -static
clean:
	rm -rf *.o $(targets)
  
