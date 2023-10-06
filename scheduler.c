#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct job{
    int id;
    int length;
    // Other data
    struct job *next;
    int checked;
 
};

struct job* listHead;

void jobListPrint(struct job currentJob){ // Will print out the job id and it's runtime, then make the next job do the same thing provided it exist. 
    printf("Job %d ran for: %d\n", currentJob.id, currentJob.length);
    if(currentJob.next != NULL){
        jobListPrint(*currentJob.next);
    }
    else{
        printf("That's all, folks!\n");
    }
    return;
}

void addNode(struct job* jobList, int jobID, int runLength){ // REMEMBER TO UPDATE AS YOU ADD MORE FIELDS! Copies data of given node to the final node of a list.
    if(jobList->next == NULL){
        struct job *node;
        node = malloc(sizeof(struct job));
        node->id = jobID; 
        node->length = runLength;
        node->checked = 0;
        
        jobList->next = node;
        return;
    }
    else{
        addNode(jobList->next, jobID, runLength);
    }
}

void makeListSJF(struct job* jobList){


}


void main(int argc, char *argv[]){
    char *myself = argv[0];
    char *scheduleType = argv[1];
    char *jobFile = argv[2];
    char *timeSlice = argv[3];
    listHead = NULL;
    
    
    if(argc != 4){
        printf("FOUR! FOUR! We need FOUR arguments, please.\n");
        exit(-1);
    }

    // Read input file
    FILE * fd = fopen(jobFile, "r");
    //char buffer[100];
    char* buffer = NULL;
    int readSize = 99;
    int lineNum = 0; // Number of jobs (lines that contain)

    if(fd == NULL){
        printf("ERROR\n");
        exit(-1);
    }
    
    while (getline(&buffer, &readSize, fd) != -1){ // While not at the end of the file 
        int runLength = atoi(buffer);
    
        //printf("%s\n", buffer);
        printf("%d\n", runLength);

        // Insert into linked list, runLength and lineNumber as job ID
        if(listHead == NULL){
        // Create node to be pointed at, set listHead to point at it

        //idk if any of this is right lol pls dan help:
            listHead = malloc(sizeof(struct job));

            // struct job *node;
            // node = malloc(sizeof(struct job));
            // node->id = lineNum; 
            // node->length = runLength;
            // listHead->next = node;

            printf("Adding node of Job %d to job list.\n", lineNum);
            addNode(listHead, lineNum, runLength);

        } else{
            printf("Adding node of Job %d to job list.\n", lineNum);
            addNode(listHead, lineNum, runLength);
        }
        lineNum++; 
    }
    fclose(fd);

    printf("There are %d jobs.\n", lineNum);

    if(strcmp(scheduleType, "FIFO") == 0){ // If given "FIFO"
        printf("fifo\n");
        
        jobListPrint(*listHead->next);
    }
    else if(strcmp(scheduleType, "SJF") == 0){ // If given "SJF"
        printf("sjf\n");
        // DO SJF STUFF HERE
    } 
    else if(strcmp(scheduleType, "RR") == 0){ // If given "RR"
        printf("rr\n");
        // DO RR STUFF HERE
    }
    else{
        printf("Make the scheduleType one of the following: 'FIFO,' 'SJF,' OR 'RR.'\n");
        exit(-1);
    }
    exit(0);
}