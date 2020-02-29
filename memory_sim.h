#include <stdio.h>

struct Frame{
	bool dirtybit;
	unsigned addr;
};

//rdm(/* Frame number, addr, rw*/){
  //randomly selects page to replace
//}

//lru(){
  //least recently used
//}

fifo(){
	//first in first out
	while(fscanf(file, "%x %c", &addr, &rw) != EOF)
	{
		numLines++;
		if(rw == 'W'){
			dirtybit=1;	
		}
		
	}
}

//vms(){
  //second chance page replacement policy
//}

//each of these needs to also change the counters accordingly for the r and w

