CXX= arm-none-linux-gnueabi-gcc

targets = CaptureImage

all: $(targets)

omapl138_gpiofuncs.o: omapl138_gpiofuncs.c
	$(CXX) -c omapl138_gpiofuncs.c

CaptureImage.o: CaptureImage.c
	$(CXX) -c CaptureImage.c	 

CaptureImage: omapl138_gpiofuncs.o CaptureImage.o 
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ 
	#$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ -static
clean:
	rm -rf *.o $(targets)
  
