#include "memory_sim.h"
#include <stdio.h>

/*struct frame{
  dirtybit = 0;
  nframes[]; //? 
};*/

int main(){
    
  #variables
//  int nframes;
  unsigned addr;
  char rw;
  int numLines=0;
  char chr;
  
  FILE *file;
    
 
    file = fopen("swim.trace", "r");
 chr = getc(file);
    if(file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
 
    printf("Testing fscanf() function: \n\n");
 
    while( fscanf(file, "Event: %x %c", &addr, &rw) != EOF )
    {
        if (chr == 'n'){
            numLines += 1;
        }
        //printf("%x %c", addr, rw);
    }
 
    fclose(file);
    return 0;
  
  
  
  
  
  
  
  
 // struct frame arr_framenum[/*"Input from user in make file"*/];
  //file is one of the four trace files
  //fscanf(file,"%x %c", &addr, &rw);
  
  
  //  printf("Total Memory Frames: ", nframes/* Same variable as user inputs*/ );
    printf("Events In Trace: ", numLines/* Number of line reads*/ );
 //   printf("Total Disk Reads: ", );
 //   printf("Total Disk Writes: ", );
    return 0;
}
