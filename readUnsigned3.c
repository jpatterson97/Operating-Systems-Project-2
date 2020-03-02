#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MILL 1000000

void fifo(char* tracefile, int nframes, char bugtype);
void rdm();
void lru();
void vms();

struct Frame{
   unsigned address;
   char read_write;
   int dirty;
}pg;

int main(int argc, char *argv[])
{

// argument variables
   int nFrames;
   char runType;
   char bugType;
   char bug[2] = {'d', 'q'};
   char *traceFile;

   traceFile = argv[1];

   nFrames = atoi(argv[2]);
   runType = argv[3][0];
   bugType = argv[4][0];
   if(bugType == bug[0]){
      printf(" %c for %cebug.\n", bugType, bug[0]);
   } else {
      printf(" %c for %cuiet.\n", bugType, bug[1]);
   }
// end argument variables
      switch(runType){
	case 'f': fifo(traceFile, nFrames, bugType);
	   break;
	case 'r': rdm();
	   break;
	case 'l': lru();
	   break;
	case 'v': vms();
	   break;
	default: {
	   printf("The selections are: \n\t\"f\"\n\t\"r\"\n\t\"l\"\n\t\"v\"\n");
   	}
   }  // end switch(runType)	
   return 0;
}

void fifo(char* tracefile, int nframes, char bugtype){
   FILE *fp;		// file pointer
   fp = fopen(tracefile, "r"); 		// read file

   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }

   printf("FIFO");
// function variables
   int i = 0, j = 0, count = 0, countR = 0, countW = 0;
   char rw;
   char R = 'R';
   char W = 'W';
   struct Frame numFrames[nframes];
   unsigned fromfile;
   unsigned n;

   while(fscanf(fp, "%x %c", &fromfile, &rw) != EOF){		// read and put file data into character array
   //fscanf(fp, "%x %c", &fromFile, &rw);   
     n = fromfile >> 12;
     numFrames[i].address = n;

     printf("%d\t%x  %c\n",i, numFrames[i].address, rw );
     numFrames[i].read_write = rw;
     if((numFrames[i].read_write == R) == 1){
        countR++;
     }
     if((numFrames[i].read_write == W) == 1){
        countW++;
     }
	i++;
	count++;
  }	// end while(fscanf(fp, "%s %c", &fromFile, &rw))
   printf("address: %x \n", numFrames[0].address);
   printf("action: %c \n", numFrames[0].read_write);	
   printf("total memory frames: %d\n", nframes);
   printf("events in trace: %d\n", count);
   printf("total disk reads:  %d\n", countR);
   printf("total disk writes: %d\n", countW);
   fclose(fp);
}
void rdm(){
	printf("RDM");
}
void lru(){
   printf("LRU");
}
void vms(){
	printf("VMS");
}
