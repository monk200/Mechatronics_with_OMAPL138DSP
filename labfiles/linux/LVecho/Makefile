CXX= arm-none-linux-gnueabi-gcc

targets = LVecho

all: $(targets)

netapi.o: netapi.c 
	$(CXX) -c netapi.c
	
omapl138_gpiofuncs.o: omapl138_gpiofuncs.c 
	$(CXX) -c omapl138_gpiofuncs.c

LVecho.o: LVecho.c
	$(CXX) -c LVecho.c	 

LVecho: netapi.o omapl138_gpiofuncs.o LVecho.o
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ 
	#$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ -static
clean:
	rm -rf *.o $(targets)
  
