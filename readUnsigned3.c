#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MILL 1000000

void fifo();
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
	case 'f': fifo(traceFile, nFrames);
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

void fifo(char* tracefile, int nframes,){
	//variables	
	int readcount, writecount, *p, found, numLines;
	//pointer to the first element of frame array
	p = pg;
	FILE *file;
	file = fopen(tracefile, "r");
	if(file == NULL)
	{
        	printf("Error opening file\n");
       		return 0;
	}
	//while loop goes through each line in the trace file
	while(fscanf(file, "%x %c", &addr, &rw) != EOF)
	{
		//adds each line up
		numLines++;
		//convert to 5 bits to use
		for(int i=0; i< nframes; i++){
			unsigned n= addr>>12;
			pg[i].address= n;
		}
		//for loop goes through first to see if it finds the value already in the frames
		for(int i=0; i < nframes; i++){
			//if it finds that address already in the frames
			if(pg[i].address == n){
				//it will check if it had a W (on original line in trace file)
				if(rw=='W"){
				   //make the bit dirty
				   pg.dirty=1;
				   //and change it to found
				   found =1;
				   //break out of this for loop
				   break;
				}
			}
		}
		//says if its not found in the frames (which this should be skipped if it went through that first loop and did find it
		if (found==0){
			//loop will go through frames again
			for(int i=0; i < nframes; i++){
				//checks if the frame is empty
				if(pg[i] == 0){
					//if it is then put the address in first empty frame found
					pg[i].address = n;
					//increase readcount
					readcount++;
					//check if the address is a W
					if(rw =='W'){
						//change bit to dirty
						pg.dirty=1;
						//break out of this for loop
						break;
					}
				//if all of them are full
				else{
					//go to where pointer is (in beginning it should be first frame)
					//go to where pointer is
					//if dirty bit of that frame is dirty add to write counter
					if (pg.dirty == 1){
						writecount ++;
					}
					//add to read counter
					readcount ++;
					//if pointer is not at the last frame move pointer to next frame 
					//if (pointer is not at the last frame){
					//	p++;
					//}
					//if pointer is at last frame move it back to beginning
					//else{
					//	p goes back to beginning (page_table[0])
					//}			  
				}
			}
		}
		//reset found back to 0 for the next address
		found =0;
	}
	fclose(file);
//printf("address: %x \n", numFrames[0].address);
  // printf("action: %c \n", numFrames[0].read_write);	
   printf("total memory frames: %d\n", nframes);
   printf("events in trace: %d\n", numLines);
   printf("total disk reads:  %d\n", readcount);
   printf("total disk writes: %d\n", writecount);
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
