#include <stdio.h>

struct Frame{
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

void fifo(){
	//first in first out
	while(fscanf(file, "%x %c", &addr, &rw) != EOF)
	{
		numLines++;
		if(rw == 'W'){
			dirtybit=1;	
		}
		for(int i=0; i < nframes; i++){
			if(page_table[i].address == addr)
				break;
			else if (page_table==0){
				page_table[i] = addr;
        			break;
			}
			else
				
		
	}
}

//void vms(){
  //second chance page replacement policy
//}

//each of these needs to also change the counters accordingly for the r and w

