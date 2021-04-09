In ComWithLinux

        if (GET_DATAFORFILE_TO_LINUX) {

            // This is an example write to scratch
            // The Linux program SaveScratchToFile can be used to write the
            // ptrshrdmem->scratch[0-499] memory to a .txt file.
//          for (i=100;i<300;i++) {
//              ptrshrdmem->scratch[i] = (float)i;
//          }

            if (playflag == 1) {
                ptrshrdmem->scratch[0] = whattoplay;
                // Flush or write back source
                Cache_wb((void *)ptrshrdmem,sizeof(sharedmemstruct), Cache_Type_ALL, EDMA3_CACHE_WAIT);
                //BCACHE_wb((void *)ptrshrdmem,sizeof(sharedmemstruct),EDMA3_CACHE_WAIT);

                CLR_DATAFORFILE_TO_LINUX;
                playflag = 0;
            }

        }

		
		
In RobotControl

        if (timecount%3000 == 0) {
            if (playflag == 0) {
                whattoplay = 2.0;
                playflag = 1;
            }
        }