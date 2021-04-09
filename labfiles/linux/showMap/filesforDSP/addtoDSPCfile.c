void CallAstar(void)
{
    int i;
    while(1) {
        SEM_pend(&SEM_whatever, SYS_FOREVER);

//        LCDPrintfLine(1,"Here");
//        LCDPrintfLine(2,"Here");

        if(!GET_ASTAR_COMMAND) {
             //For now, Update the shared variables that need to be sent for astar
             for (i=0;i<176;i++) {
                 ptrshrdmem->sharedAstarMap[i] = map[i];
             }

             BCACHE_wb((void *)ptrshrdmem,sizeof(sharedmemstruct),EDMA3_CACHE_WAIT);
             SET_ASTAR_COMMAND;
        }


        astar(row_start, col_start, row_end, col_end);

//        LCDPrintfLine(1,"%d %d %d %d %d", row_start, col_start, row_end, col_end, pathLen);

        //LCDPrintfLine(2,"%d %d %d %d %d %d",pathRow[3], pathCol[3], pathRow[4], pathCol[4], pathRow[5], pathCol[5]);

        Astar_path_state = 0;
        Astar_path_length = pathLen-1;

        for(i=0; i<Astar_path_length; i++)
        {
            convert_maze_to_act_coords(pathRow[Astar_path_length-i-1], pathCol[Astar_path_length-i-1], &(Astar_path_x[i]), &(Astar_path_y[i]));
        }
//        LCDPrintfLine(2,"%.1f %.1f %.1f %.1f %.1f %.1f %d",Astar_path_x[0], Astar_path_y[0], Astar_path_x[1], Astar_path_y[1], Astar_path_x[2], Astar_path_y[2], pathLen);
        Astar_path_ready = 1;
//        i = 0;
//        i= 1/i;
    }
}
