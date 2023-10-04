#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct job{
    int id;
    int length;
    // Other data
    struct job* next;
 
};

struct job *listHead;
{
    /* data */
};


int main(int argc, char *argv[]){
    char *myself = argv[0];
    char *scheduleType = argv[1];
    char *jobFile = argv[2];
    char timeSlice = argv[3];

    
    
    if(argc != 4){
        printf("FOUR! FOUR! We need FOUR arguments, please.");
        return -1;
    }

    // Read input file
    int fd = fopen(jobFile, "r");
    char buffer[100];

    int lineNumber = 0;
    while (!eof(fd)){ // While not at the end of the file
        int rc = getline(buffer, 99, fd);
        int runLength = atoi(buffer);

        // Insert into linked list, runLength and lineNumber as job ID
        if(listHead == NULL){
            // Create node to be pointed at it
        } else{
            // add to end of list
        }
        lineNumber++;
    }
    fclose(fd);

    if(strcmp(scheduleType, "FIFO") == 0){ // If given "FIFO"
        // DO FIFO STUFF HEREEEE
    }

    if(strcmp(scheduleType, "SJF") == 0){ // If given "SJF"
        // DO SJF STUFF HERE
    } 

    if(strcmp(scheduleType, "RR") == 0){ // If given "RR"
        // DO RR STUFF HERE
    }
    return 0;
}