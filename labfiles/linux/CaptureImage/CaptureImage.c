#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "omapl138_gpiofuncs.h"
#include "../../sharedmem_com/sharedmem.h"


#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

//typedef struct sharedmemstruct {
//	volatile float obj_x;
//	volatile float obj_y;
//	volatile float numpix;
//	volatile float datahasbeenreadbylinux;
//	volatile float Linux_needs_new_image;
//	volatile float orange_ref;
//	volatile float blue_ref;
//	volatile float red_ref;
//	volatile float New_ref_ready;
//} sharedmemstruct;
//sharedmemstruct* myshared;

volatile GPIOregs* mygpio;

typedef struct bgr {
	volatile unsigned char blue;
	volatile unsigned char green;
	volatile unsigned char red;
} bgr;
volatile bgr* myimage;

void writebmp(volatile bgr* myimage);

int fd;
void *map_base, *virt_addr;
off_t target = 0x80000000;

char filename[300];
 

/*
 * main()
 *   process command line input
 */
int main (int argc, char **argv)
{
	
  int j = 0;
  int i = 0;
  int index = 0;

 // printf("Websocket sample program\n");
	
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) {
      printf("/dev/mem could not be opened.\n");
        exit(1);
   } else {
       printf("/dev/mem opened.\n");
   }
    fflush(stdout);

   target = 0xC3F80000;// + 0x9BDC;
    /* Map one page for shared memory structure*/
    map_base = mmap(0, MAP_SIZE*19, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target);//(target & ~MAP_MASK));
    if(map_base == (void *) -1) {
        printf("Memory map failed.\n");
    } else {
        //printf("image Struct mapped at address %p.\n", map_base);
    }
    fflush(stdout);
    virt_addr = (void*)((unsigned long int)map_base + (target & MAP_MASK));
    myimage = (bgr *) map_base;
    
    target = 0x01E26000;
    /* Map one page for shared memory structure*/
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target);
    if(map_base == (void *) -1) {
        printf("Memory map failed.\n");
    } else {
        //printf("gpio Struct mapped at address %p.\n", map_base);
    }
    fflush(stdout);
    //virt_addr = (void*)((unsigned long int)map_base + (target & MAP_MASK));	
    mygpio = (GPIOregs *) map_base;


  if (argc ==2) {
    printf("BMP file name: %s.bmp\n",argv[1]);
    sprintf(filename,"%s.bmp",argv[1]);
  }
  // clear previous picture out of memory by waiting for flag and clearing flag right away
  while (GPIO_getOutput(mygpio,IMAGE_TO_LINUX_BANK,IMAGE_TO_LINUX_FLAG) == 1) {
	  usleep(5);
  }
GPIO_setOutput(mygpio,IMAGE_TO_LINUX_BANK,IMAGE_TO_LINUX_FLAG,OUTPUT_HIGH);
  
  while (GPIO_getOutput(mygpio,IMAGE_TO_LINUX_BANK,IMAGE_TO_LINUX_FLAG) == 1) {
	  usleep(5);
  }
  
 /*   memcpy(&localimage,(void *)(&myimage[0]),76032);
		  
  for (i = 0; i < 25344; i++){
	//if (myimage[i].blue > 255) 
		localimage[i].blue =(unsigned char)((localimage[i].blue * 128)/255);
	//if (localimage[i].green> 255) 
		localimage[i].green =(unsigned char)((localimage[i].green * 128)/255);
	//if (localimage[i].red > 255) 
		localimage[i].red =(unsigned char)((localimage[i].red* 128)/255);
  }*/
    
    writebmp(myimage);
		  
		 
GPIO_setOutput(mygpio,IMAGE_TO_LINUX_BANK,IMAGE_TO_LINUX_FLAG,OUTPUT_HIGH);
		//}
		  //GPIO_toggleBit(mygpio,GPIO_BANK6,GPIO_PIN10);
    //sched_yield();


}

void writebmp(volatile bgr* myimage){
	FILE *f;
	unsigned char *img = NULL;

	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	int r = 0;
	int g = 0;
	int b = 0;
	int w = 176;
	int h = 144;
	int filesize = 54 + 3*w*h;
	printf("file size %d\n",filesize);

	if( img )
	    free( img );
	img = (unsigned char *)malloc(3*w*h);
	memset(img,0,sizeof(img));

	

	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
	//unsigned char bmppad[3] = {0,0,0};

	//printf("%d\n",(int)(bmpfileheader[0]));
	//printf("%d\n",(int)(bmpinfoheader[0]));

	for(i=(h-1); i>-1; i--)
	{
	    for(j=(w-1); j>-1; j--)
	    {
		y=i; x=j;
		r = myimage[y*w+x].red;
		g = myimage[y*w+x].green;
		b = myimage[y*w+x].blue;
		if (r > 255) r=255;
		if (g > 255) g=255;
		if (b > 255) b=255;
		img[(((w-x-1)+y*w)*3)+2] = (unsigned char)(r);
		img[(((w-x-1)+y*w)*3)+1] = (unsigned char)(g);
		img[(((w-x-1)+y*w)*3)+0] = (unsigned char)(b);
	    }
	}

	//printf("past for loops\n");
	//printf("RGB IMG %d %d %d\n")

	bmpfileheader[ 2] = (unsigned char)(filesize    );
	bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);

	bmpinfoheader[ 4] = (unsigned char)(       w    );
	bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
	bmpinfoheader[ 6] = (unsigned char)(       w>>16);
	bmpinfoheader[ 7] = (unsigned char)(       w>>24);
	bmpinfoheader[ 8] = (unsigned char)(       h    );
	bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
	bmpinfoheader[10] = (unsigned char)(       h>>16);
	bmpinfoheader[11] = (unsigned char)(       h>>24);

	bmpinfoheader[20] = (unsigned char)((filesize-54)    );
	bmpinfoheader[21] = (unsigned char)((filesize-54)>> 8);
	bmpinfoheader[22] = (unsigned char)((filesize-54)>>16);
	bmpinfoheader[23] = (unsigned char)((filesize-54)>>24);

	bmpinfoheader[24] = (unsigned char)(2835    );
	bmpinfoheader[25] = (unsigned char)(2835>> 8);
	bmpinfoheader[26] = (unsigned char)(2835>>16);
	bmpinfoheader[27] = (unsigned char)(2835>>24);
	
	f = fopen(filename,"wb");
	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);
	for(i=0; i<h; i++)
	{
	    fwrite(img+((w*i)*3),3,w,f);
	    //fwrite(bmppad,1,(4-(w*3)%4)%4,f);
	}
	fclose(f);
}

