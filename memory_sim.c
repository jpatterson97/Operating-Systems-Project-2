#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Frame{
  bool dirtybit;
  unsigned addr;
  char rw;
};
struct node{
	unsigned hexAdd;
	bool dirty;
	int id;
	struct node *next;
	struct node *prev;
	char rw;
};

void rdm();
void vms();
void fifo();
void lru();

int main(int argc, char *argv[]){    
  //variables
	int numLines=0;
	int no_writes=0, no_reads=0;
  char *trace, *algo, *debug; 
  
  //char chr;
  trace= argv[1];
  int nframes = atoi(argv[2]);
  algo = argv[3][0];
  //debug = argv[4];
  
if(argc< 3){
		printf("Not enough arguments");
	}	
  struct Frame page_table[nframes];
  
  printf("Enter number of frames");
  scanf("%d",&nframes);
  printf("%d", nframes);

    printf("Testing fscanf() function: \n\n");
    //while( fscanf(file, "%x %c", &addr, &rw) != EOF )
    //{
        //numLines++;
	switch(algo){
		case 'r': rdm();
			break;
		case 'l': lru();
			break;
		case 'f': fifo();
			break;
		case 'v': vms();
			break;
		default: printf("Not valid input");
			break;
	}
       // printf("%x %c \n", addr, rw);
    //}
	fclose(file);

  //  printf("Total Memory Frames: ", nframes/* Same variable as user inputs*/ );
	printf("Total Memory Frames: %d", nframes);
	printf("\n");
	printf("Events In Trace: %d", numLines);
	printf("\n");
	printf("Total Disk Reads: %d", readcount);
	printf("\n");
	printf("Total Disk Writes: %d ", writecount);
	printf("\n");
	
	return 0;

}


//void rdm(/* Frame number, addr, rw*/){
  //randomly selects page to replace
//}


//void vms(){
  //second chance page replacement policy
//}


//first in first out
void fifo(){
	//variables	
	int readcount, writecount, *p, found;
	//pointer to the first element of frame array
	p = page_table;
	FILE *file;
	file = fopen(argv[1], "r");
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
			page_table[i].address= n;
		}
		//for loop goes through first to see if it finds the value already in the frames
		for(int i=0; i < nframes; i++){
			//if it finds that address already in the frames
			if(page_table[i].address == addr){
				//it will check if it had a W (on original line in trace file)
				if(rw=='W"){
				   //make the bit dirty
				   dirtybit=1;
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
				if(page_table[i] == 0){
					//if it is then put the address in first empty frame found
					page_table[i].address = addr;
					//increase readcount
					readcount++;
					//check if the address is a W
					if(rw =='W'){
						//change bit to dirty
						dirtybit=1;
						//break out of this for loop
						break;
					}
				//if all of them are full
				else{
					//go to where pointer is (in beginning it should be first frame)
					go to where pointer is
					//if dirty bit of that frame is dirty add to write counter
					if (dirtybit == 1){
						writecount ++;
					}
					//add to read counter
					readcount ++;
					//if pointer is not at the last frame move pointer to next frame 
					if (pointer is not at the last frame){
						p++;
					}
					//if pointer is at last frame move it back to beginning
					else{
						p goes back to beginning (page_table[0])
					}			  
				}
			}
		}
		//reset found back to 0 for the next address
		found =0;
	}
	fclose(file);
}


//lru algorithm
void lru(){
 	//least recently used
	struct node *frameset;
	struct node *p;
	FILE *file;
	file = fopen(argv[1], "r");
	if(file == NULL)
	{
        	printf("Error opening file\n");
       		return 0;
	}
	//making this the size of the frames inserting new empty nodes
	for(int i=0; i<nframes;i++){
		p=malloc(size(struct node);
		p->id= i;
		p->next= frameset;
		return p;
	}
	while(fscanf(file, "%x %c", &addr, &rw) != EOF)
		{
			//adds each line up
			numLines++;
			for(int i=0; i< nframes; i++){
				unsigned n= addr>>12;
				page_table[i].address= n;
			}
			//for loop goes through first to see if it finds the value already in the frames
			//for(int i=0; i < nframes; i++){
			for(p->id = 0; p->id <nframes; p = p->next){
				//if it finds that address already in the frames
				if(node->hexAdd == addr){
					//it will check if it had a W (on original line in trace file)
					if(rw=='W"){
					   //make the bit dirty
					   node->dirty=1;
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
					if(node->hexAdd == NULL){
						//if it is then put the address in first empty frame found
						node->hexAdd = addr;
						//increase readcount
						readcount++;
						//check if the address is a W
						if(rw =='W'){
							//change bit to dirty
							node->dirty=1;
							//break out of this for loop
							break;
						}
					//if all of them are full
					else{
						//go to where pointer is (in beginning it should be first frame)
						go to where pointer is
						//if dirty bit of that frame is dirty add to write counter
						if (node->dirty == 1){
							writecount ++;
						}
						//add to read counter
						readcount ++;
						//if pointer is not at the last frame move pointer to next frame 
						if (pointer is not at the last frame){
							q=q->next;
						}
						//if pointer is at last frame move it back to beginning
						else{
							p goes back to beginning (page_table[0])
						}			  
					}
				}
			}
			//reset found back to 0 for the next address
			found =0;
		}
		fclose(file);
}





