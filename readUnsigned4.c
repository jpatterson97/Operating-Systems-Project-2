#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
 
void fifo(char* tracefile, int nframes, char bugtype);
void rdm(char* tracefile, int nframes, char bugtype);
void lru(char* tracefile, int nframes, char bugtype);
void vms(char* tracefile, int nframes, char bugtype);

struct Frame{
   unsigned address;
   char read_write;
   int dirty;
};

int main(int argc, char *argv[])
{
	// argument variables
	int nFrames;
   	char runType;
 	char bugType;
   	char *traceFile;

   	traceFile = argv[1];

   	nFrames = atoi(argv[2]);
   	runType = argv[3][0];
   	bugType = argv[4][0];
	// end argument variables
     	switch(runType){
		case 'f': fifo(traceFile, nFrames, bugType);
	   		break;
		case 'r': rdm(traceFile, nFrames, bugType);
	   		break;
		case 'l': lru(traceFile, nFrames, bugType);
	   		break;
		case 'v': vms(traceFile, nFrames, bugType);
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

   	printf("FIFO\n");
	// function variables
   	int i = 0, j = 0, count = 0, countR = 0, countW = 0;
   	char rw;
   	char R = 'R';
   	char W = 'W';
   	struct Frame numFrames[nframes];
   	struct Frame morFrames[nframes];
   	struct Frame oneFrame;
   	unsigned fromfile;
   	unsigned n;
   	char bug[2] = {'d', 'q'};

   	while(fscanf(fp, "%x %c", &fromfile, &rw) != EOF){		// read and put file data into character array
   		//fscanf(fp, "%x %c", &fromFile, &rw);   
     		n = fromfile >> 12;		// shift positions right
     		oneFrame.address = n;		// put it in oneFrame
     		oneFrame.read_write = rw;
     		if(rw == W){
        		oneFrame.dirty = 1;
     		} 
		else { 
			oneFrame.dirty = 0; 
		}
     		if(bugtype == bug[0]){
			printf("%d.\taddr %x  r/w %c\t dirty %d \n",i, oneFrame.address,  oneFrame.read_write, oneFrame.dirty);
     		}
		i=0;
     		if(i >= nframes){			// if i < nframes, assign oneFrame to numFrames
			// if i >= nframes, then put new value in the frame.
			for(j = 0 ; j < i; j++ ){				// go through numFrames until j = i
				if(numFrames[j].address != oneFrame.address){	// if oneFrame.address == numFames[i].address
	   				morFrames[j] = numFrames[j];			// assign value at j to morFrames[j].address
				} 
				else if((numFrames[j].address == oneFrame.address) && (numFrames[j].read_write == oneFrame.read_write) == 1){
					// if address equal and read_write, swap value: o -> n -> m
           				numFrames[j] = oneFrame;
	   				morFrames[j] = numFrames[j];
    	   				if((numFrames[j].read_write == R) == 1){	// read access count
              					countR++;
           				} 
					else if((numFrames[j].read_write == W) == 1){	// write access, it's dirty
              					numFrames[j].dirty = 1;
           				}
	   				else {
	      					printf("ERROR: Unexpected value: %c \n", numFrames[j].read_write);
	   				}
        			} else if(((numFrames[j].read_write == W) == 1) && ((oneFrame.read_write == R) == 1)){	
					// if numF equal oneF and r_w !equal, then put oneF into numF at j
	  				numFrames[j].address = oneFrame.address;
	   				numFrames[j].dirty = 0;	
	   				numFrames[j].read_write = R;
	   				morFrames[j] = numFrames[j];		// then keep assign numF into morF
	   				countR++;
      				}
				else {
					numFrames[i] = oneFrame;
					if(numFrames[i].read_write == W){
	   					numFrames[i].dirty = 1;
	   					countW++;
					}	// if it's W, then it's dirty
					else { 
	   					numFrames[i].dirty = 0;
						   countR++;
     					}
				}
     			} 
		}
		i++;
		count++;
     	}	// end while(fscanf(fp, "%s %c", &fromFile, &rw))
   	printf("total memory frames: %d\n", nframes);
   	printf("events in trace: %d\n", count);
   	printf("total disk reads:  %d\n", countR);
   	printf("total disk writes: %d\n", countW);
   	fclose(fp);
}

void rdm(char* tracefile, int nframes, char bugtype){
   	printf("RDM\n");
   	FILE *fp;		// file pointer
   	fp = fopen(tracefile, "r"); 		// read file

   	if (fp == NULL)
   	{
      		perror("Error while opening the file.\n");
      		exit(EXIT_FAILURE);
   	}
	// function variables
   	int i = 0, count = 0, countR = 0, countW = 0, upper = 0, lower = 0;
	
   	char rw;
   	char R = 'R';
   	char W = 'W';
   	struct Frame numFrames[nframes];
   	struct Frame morFrames[nframes];
   	struct Frame oneFrame;
   	unsigned fromfile;
   	unsigned n;
   	char bug[2] = {'d', 'q'};
   	int random, found;
   	srand(time(0));
   	upper = 13;
   	lower = 3;

   	while(fscanf(fp, "%x %c", &fromfile, &rw) != EOF){		// read and put file data into character array
		// generating seed
		srand(time(0));
   		//fscanf(fp, "%x %c", &fromFile, &rw);   
     		n = fromfile >> 12;		// shift positions right
     		oneFrame.address = n;		// put it in oneFrame
     		oneFrame.read_write = rw;
     		for(int i=0; i<nframes;i++){
			if(oneFrame.address == n)
				if(oneFrame.read_write == W){
        				oneFrame.dirty = 1;
					found=1;
     				} 
				else { 
					oneFrame.dirty = 0; 
				}
			}
     			if(bugtype == bug[0]){
				printf("%d.\taddr %x  r/w %c\t dirty %d \n",i, oneFrame.address,  oneFrame.read_write, oneFrame.dirty);
     			}
		}
		//if not found 
		if(found==0){
			//loop thru frames again
			for(i;i<nframes;i++){
				int j = (rand() % (upper - lower + 1)) + lower;
				if( j == 0){			// if i < nframes, assign oneFrame to numFrames
					 
     					if(bugtype == bug[0]){
						printf("Random number: %d \n", j);	
     					}
				}
			}
		}
		// if i >= nframes, then put new value in the frame.
		//	for(j = 0 ; j < random; j++ ){				// go through numFrames until j = i
		while(numFrames[j].address != oneFrame.address){	// if oneFrame.address == numFames[i].address
	  	   	j++;
		
		i=0;
		if((numFrames[j].address == oneFrame.address) && (numFrames[j].read_write == oneFrame.read_write) == 1){
			// if address equal and read_write, swap value: o -> n -> m
           		numFrames[j] = oneFrame;
	   		morFrames[j] = numFrames[j];
    	   		if((numFrames[j].read_write == R) == 1){	// read access count
              			countR++;
           		} else if((numFrames[j].read_write == W) == 1){	// write access, it's dirty
              			numFrames[j].dirty = 1;
           		}
	   		else {
	      			printf("ERROR: Unexpected value: %c \n", numFrames[j].read_write);
	   		}
        	} else if(((numFrames[j].read_write == W) == 1) && ((oneFrame.read_write == R) == 1)){	
			// if numF equal oneF and r_w !equal, then put oneF into numF at j
	   		numFrames[j].address = oneFrame.address;
	   		numFrames[j].dirty = 0;	
	   		numFrames[j].read_write = R;
	   		morFrames[j] = numFrames[j];		// then keep assign numF into morF
	   		countR++;
      		}//}
//	i = 0;
      		else {
			numFrames[i] = oneFrame;
			if(numFrames[i].read_write == W){
	   			numFrames[i].dirty = 1;
	   			countW++;
				printf("WRITE COUNT: %d", countW);
			}	// if it's W, then it's dirty
			else { 
	   			numFrames[i].dirty = 0;
	   			countR++;
			}
     		}
	i++;
	count++;
	}
     	
   	}	// end while(fscanf(fp, "%s %c", &fromFile, &rw))
   	printf("total memory frames: %d\n", nframes);
   	printf("events in trace: %d\n", count);
   	printf("total disk reads:  %d\n", countR);
   	printf("total disk writes: %d\n", countW);
   	fclose(fp);
}

void lru(char* tracefile, int nframes, char bugtype){
   printf("LRU\n");
}
void vms(char* tracefile, int nframes, char bugtype){
   printf("VMS\n");
}
/*
 *    	if((numFrames[j].read_write == R) == 1){	// read access count
           countR++;
        }
	if((numFrames[j].read_write == W) == 1){	// read access count
           countW++;
        }

 */
