#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MILL 1000000

void fifo(char* tracefile, int nframes);
void rdm();
void lru(char* tracefile, int nframes);
void vms();

struct Frame{
   unsigned address;
   //char read_write;
   int dirty;
};

struct node{
	unsigned hexAdd;
	bool dirty;
	int id;
	struct node *next;
	struct node *prev;
};

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
	case 'l': lru(tracefile, nframes);
	   break;
	case 'v': vms();
	   break;
	default: {
	   printf("The selections are: \n\t\"f\"\n\t\"r\"\n\t\"l\"\n\t\"v\"\n");
   	}
   }  // end switch(runType)	
   return 0;
}

void fifo(char* tracefile, int nframes){
	//variables	
	int readcount, writecount, found, numLines;
	unsigned addr;
	char rw;
	//pointer to the first element of frame array
	struct Frame *p = NULL;
	struct Frame page_table[nframes];
	p=page_table;
	FILE *file;
	file = fopen(tracefile, "r");
	if(file == NULL)
	{
        	printf("Error opening file\n");
       		
	}
	//while loop goes through each line in the trace file
	while(fscanf(file, "%x %c", &addr, &rw) != EOF)
	{
		//adds each line up
		numLines++;
		//convert to 5 bits to use
		unsigned n= addr>>12;
		//for loop goes through first to see if it finds the value already in the frames
		for(int i=0; i < nframes; i++){
			//if it finds that address already in the frames
			if(page_table[i].address == n){
				//it will check if it had a W (on original line in trace file)
				if(rw=='W'){
				   //make the bit dirty
				   page_table[i].dirty=1;
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
				if(page_table[i].address == 0){
					//if it is then put the address in first empty frame found
					page_table[i].address = n;
					//increase readcount
					readcount++;
					//check if the address is a W
					if(rw =='W'){
						//change bit to dirty
						page_table[i].dirty=1;
						//break out of this for loop
						break;
					}
				}//if all of them are full
				else{
					//go to where pointer is (in beginning it should be first frame)
					
					//if dirty bit of that frame is dirty add to write counter
					if (page_table[i].dirty == 1){
						writecount ++;
					}
					//add to read counter
					readcount ++;
					//if pointer is not at the last frame move pointer to next frame and if it is then go back to the beginning
					if(p < nframes){
						p++;
					}
					else{
						p=page_table;
					}			  
				}
			}
		}
		//reset found back to 0 for the next address
		found =0;
	}
	fclose(file);	
   printf("Total Memory Frames: %d\n", nframes);
   printf("Events in Trace: %d\n", numLines);
   printf("Total Disk Reads:  %d\n", readcount);
   printf("Total Disk Writes: %d\n", writecount);
}

void rdm(){
	printf("RDM");
}

void lru(char* tracefile, int nframes){
   //least recently used
	//variables	
	int readcount, writecount, found, numLines;
	unsigned addr;
	char rw;
	FILE *file;
	file = fopen(tracefile, "r");
	if(file == NULL)
	{
        	printf("Error opening file\n");
       		
	}
	struct node *tempnode;
	//making this the size of the frames inserting new empty nodes
	for(int i=0; i<nframes;i++){
		struct node *p=malloc(size(struct node));
		p->id= i;
		tempnode->next= next;
		tempnode=next;
	}
	while(fscanf(file, "%x %c", &addr, &rw) != EOF)
		{
			//adds each line up
			numLines++;
			for(int i=0; i< nframes; i++){
				unsigned n= addr>>12;
				p->address= n;
			}
			//for loop goes through first to see if it finds the value already in the frames
			//for(int i=0; i < nframes; i++){
			for(p->id = 0; p->id <nframes; p = p->next){
				//if it finds that address already in the frames
				if(p->hexAdd == addr){
					//it will check if it had a W (on original line in trace file)
					if(rw=='W'){
					   //make the bit dirty
					   p->dirty=1;
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
				//for(int i=0; i < nframes; i++){
				for(p->id =0; p->id < nframes; p = p->next){
					//checks if the frame is empty
					if(p->hexAdd == NULL){
						//if it is then put the address in first empty frame found
						p->hexAdd = addr;
						//increase readcount
						readcount++;
						//check if the address is a W
						if(rw =='W'){
							//change bit to dirty
							p->dirty=1;
							//break out of this for loop
							break;
						}
					//if all of them are full
					else{
						//if dirty bit of that frame is dirty add to write counter
						if (p->dirty == 1){
							writecount ++;
						}
						//add to read counter
						readcount ++;
						//if pointer is not at the last frame move pointer to next frame 
						if (p->id < nframes){
							p=p->next;
						}
						//if pointer is at last frame move it back to beginning
						else{
							p
						}			  
					}
				}
			}
			//reset found back to 0 for the next address
			found =0;
		}
	  printf("Total Memory Frames: %d\n", nframes);
   printf("Events in Trace: %d\n", numLines);
   printf("Total Disk Reads:  %d\n", readcount);
   printf("Total Disk Writes: %d\n", writecount);
	
}
void vms(){
	printf("VMS");
}
