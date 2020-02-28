#include "memory_sim.h"
#include <stdio.h>

/*struct frame{
  dirtybit = 0;
  nframes[]; //? 
};*/

int main(){
    
  //variables
  int nframes;
  unsigned addr;
  char rw;
  int numLines=0;
  char chr;
  
printf("Enter number of frames");
scanf("%d",&nframes);
printf("%d", nframes);
  FILE *file;
    
 
    file = fopen("swim.trace", "r");

if(file == NULL)
    {
        printf("Error opening file\n");
       	return 0;
    }
 
    printf("Testing fscanf() function: \n\n");
 
    while( fscanf(file, "%x %c", &addr, &rw) != EOF )
    {
        numLines++;
       // printf("%x %c \n", addr, rw);
    }
    fclose(file);
   // return 0;
  
  
  
  
  
  
  
  
 // struct frame arr_framenum[/*"Input from user in make file"*/];
  //file is one of the four trace files
  //fscanf(file,"%x %c", &addr, &rw);
  
  
  //  printf("Total Memory Frames: ", nframes/* Same variable as user inputs*/ );
    printf("Events In Trace: %d", numLines);
	printf("\n");
 //   printf("Total Disk Reads: ", );
 //   printf("Total Disk Writes: ", );
    return 0;
}
