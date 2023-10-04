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


int main(int argc, char *argv[]){
    char *myself = argv[0];
    char *scheduleType = argv[1];
    char *jobFile = argv[2];
    char *timeSlice = argv[3];
    listHead = NULL;
    
    
    if(argc != 4){
        printf("FOUR! FOUR! We need FOUR arguments, please.");
        return -1;
    }

    // Read input file
    FILE * fd = fopen(jobFile, "r");
    char buffer[100];

    int lineNum = 0;
    
    while (!feof(fd)){ // While not at the end of the file
        //int rc = getline(buffer, 99, fd); //need to uncomment eventually, we just tryin to get it to compile
        int runLength = atoi(buffer);
    
        printf("%d", runLength);

        // Insert into linked list, runLength and lineNumber as job ID
        if(listHead == NULL){
            // Create node to be pointed at it, set listHead to point at it
        } else{
            // add to end of list
        }
        lineNum++;
    }
    fclose(fd);

    if(strcmp(scheduleType, "FIFO") == 0){ // If given "FIFO"
        printf("fifo");
        // DO FIFO STUFF HEREEEE
    }

    if(strcmp(scheduleType, "SJF") == 0){ // If given "SJF"
        printf("sjf");
        // DO SJF STUFF HERE
    } 

    if(strcmp(scheduleType, "RR") == 0){ // If given "RR"
        printf("rr");
        // DO RR STUFF HERE
    }
    return 0;
}