#include "memory_sim.h"
#include <stdio.h>

struct frame{
  dirtybit = 0;
  nframes[]; //? 
};

int main(){
    
  #variables
  int nframes;
  unsigned addr;
  char rw;
  struct frame arr_framenum[/*"Input from user in make file"*/];
  //file is one of the four trace files
  fscanf(file,"%x %c", &addr, &rw);
  
  
    printf("Total Memory Frames: ", nframes/* Same variable as user inputs*/ );
    printf("Events In Trace: ",/* Number of line reads*/ );
    printf("Total Disk Reads: ", );
    printf("Total Disk Writes: ", );
    return 0;
}
