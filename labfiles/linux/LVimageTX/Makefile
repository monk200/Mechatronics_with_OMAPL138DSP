CXX= arm-none-linux-gnueabi-gcc

targets = LVimageTX

all: $(targets)

netapi.o: netapi.c 
	$(CXX) -c netapi.c
	
omapl138_gpiofuncs.o: omapl138_gpiofuncs.c 
	$(CXX) -c omapl138_gpiofuncs.c

LVimageTX.o: LVimageTX.c
	$(CXX) -c LVimageTX.c	 

LVimageTX: netapi.o omapl138_gpiofuncs.o LVimageTX.o
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ 
	#$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ -static
clean:
	rm -rf *.o $(targets)
  
