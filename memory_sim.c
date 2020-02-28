#include "memory_sim.h"
#include <stdio.h>
#include <stdlib.h>
/*struct frame{
  dirtybit = 0;
  nframes[]; //? 
};*/

int main(int argc, char *argv[]){
    
  //variables
  char *trace, *algo, *quiOrDeb;
  int nframes;
  unsigned addr;
  char rw;
  int numLines=0;
  char chr;
trace= argv[1];
//nframes=atoi(argv[2]);
//algo=argv[3];
//quiOrDeb=argv[4];
  
printf("Enter number of frames");
scanf("%d",&nframes);
printf("%d", nframes);
  FILE *file;
    
	if(argc< 3){
		printf("Not enough arguments");
	}	
    file = fopen(argv[1], "r");

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
