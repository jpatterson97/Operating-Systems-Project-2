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
	int readCount, writeCount, *p;
	*p = page_table;
	while(fscanf(file, "%x %c", &addr, &rw) != EOF)
	{
		numLines++;
		
		for(int i=0; i < nframes; i++){
			if(page_table[i].address == addr){
				if(rw=='W"){
				   	dirtybit=1;
				   found =1;	
				   break;
				}
			}
		}
			if (found==0){
				for(int i=0; i < nframes; i++){
					if(page_table[i] == 0){
						page_table[i].address = addr;
						readcount++;
						if(rw =='W')
							dirtybit=1;
							break;
					else{
						go to where pointer is
						if (dirtybit == 1)
							writecount ++;
						readcount ++;
						if (pointer Is at last frame)
							p++;
						else
							p goes back to beginning (page_table[0]
										  
					}
				}
				
			}
		}
		
		/*for(int i=0; i < nframes; i++){
			if(page_table[i] == 0){
				page_table[i].address = addr;
				//break;
			}
			else{
				
			}
		}*/
		
		
	}
}

//void vms(){
  //second chance page replacement policy
//}

//each of these needs to also change the counters accordingly for the r and w

