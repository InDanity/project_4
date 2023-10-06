#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct job{
    int id;
    int length;
    // Other data
    struct job* prev;
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
    
    if(fd != NULL && lineNum < 100){
        while (!feof(fd)){ // While not at the end of the file //TAKE OUT THE LINENUM THING THIS IS JUST TO KEEP FROM INFINITE LOOP BEFORE WE IMPLEMENT FUNTIONALITY
            //int rc = getline(*buffer, 99, fd); //this line is causing a segmentation fault :/
            int runLength = atoi(buffer);
        
            printf("%d", runLength);

            // Insert into linked list, runLength and lineNumber as job ID
            if(listHead == NULL){
            // Create node to be pointed at, set listHead to point at it

            //idk if any of this is right lol pls dan help:
                listHead = malloc(sizeof(struct job));

                struct job *node;
                node = malloc(sizeof(struct job));
                node->id = lineNum; 
                node->length = runLength;
                listHead->next = node;

            } else{
                // add to end of list

                //uh so theoretically you wanna access prev element, point that to this node.... gotta figure out how to do that
            }
            lineNum++; 
        }
        fclose(fd);

        if(strcmp(scheduleType, "FIFO") == 0){ // If given "FIFO"
            printf("fifo\n");
            // DO FIFO STUFF HEREEEE
        }

        if(strcmp(scheduleType, "SJF") == 0){ // If given "SJF"
            printf("sjf\n");
            // DO SJF STUFF HERE
        } 

        if(strcmp(scheduleType, "RR") == 0){ // If given "RR"
            printf("rr\n");
            // DO RR STUFF HERE
        }
        return 0;
    } else { //if fd is NULL
        printf("Couldn't find file:(\n");
        return -1;
    }
}