#include <stdio.h>

struct Frame{
	//I think we might also need rw for each as well?
	bool dirtybit;
	unsigned address;
};

struct Frame page_table[nframes];
//void rdm(/* Frame number, addr, rw*/){
  //randomly selects page to replace
//}

//void lru(){
  //least recently used
//}


//first in first out
void fifo(){
	//variables	
	int readcount, writecount, *p, found;
	//pointer to the first element of frame array
	*p = page_table;
	//while loop goes through each line in the trace file
	while(fscanf(file, "%x %c", &addr, &rw) != EOF)
	{
		//adds each line up
		numLines++;
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
}

//void vms(){
  //second chance page replacement policy
//}

