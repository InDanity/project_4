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

void jobListPrint(struct job currJob){ // Will print out the job id and it's runtime, then make the next job do the same thing provided it exist. 
    printf("Job %d ran for: %d\n", currJob.id, currJob.length);
    if(currJob.next != NULL){
        jobListPrint(*currJob.next);
    }
    else{
        printf("That's all, folks!\n");
    }
    return;
}

void addNode(struct job* currJob, int jobID, int runLength){ // REMEMBER TO UPDATE AS YOU ADD MORE FIELDS! Copies data of given node to the final node of a list.
    if(currJob->next == NULL){
        struct job *node;
        node = malloc(sizeof(struct job));
        node->id = jobID; 
        node->length = runLength;
        node->checked = 0;
        
        currJob->next = node;
        return;
    }
    else{
        addNode(currJob->next, jobID, runLength);
    }
}

void makeListSJF(struct job* currJob){
    struct job* tempCurrent = currJob; // used to hold the address of the current node.
    struct job* tempNewNext;           // used to hold the address of the node 2 nodes away from the current one, provided it EXISTS.
    struct job* tempNewFirst;          // used to hold the value of the second node (what will be the new first node), in case the first node needs to be switched.
    while(tempCurrent != NULL){
        printf("Looking at 3 nodes with lengths %d, %d, and %d.\n", tempCurrent->length, tempCurrent->next->length, tempCurrent->next->next->length);

        if(tempCurrent->length > tempCurrent->next->length){  // If the current node has a smaller run length than the last, SWAPPING TIME!!!
            printf("Well, %d is greater than %d. Swapping!\n", tempCurrent->length, tempCurrent->next->length);

            if(tempCurrent->next->next != NULL){ // If the node after the next node exists...
                tempNewNext = tempCurrent->next->next; 
            }
            else{ // If the node after the next node does NOT exist...
               tempNewNext = NULL;
            }

            if(tempCurrent = currJob->next){ // If this is the first node, AND we were planning on swapping anyhow...
                tempNewFirst = tempCurrent->next;
                currJob->next = tempNewFirst; // Make the first node the second node
            }
            
            tempCurrent->next->next = tempCurrent; // Make the next node point to the current node, or "put it behind the current node."
            printf("Made node w/ length %d point to node w/ length %d.\n", tempCurrent->next->next->length, tempCurrent->length);
            tempCurrent->next = tempNewNext; // Make the current node point to the previously next node's next node, or "put it behind the next next node."

            printf("Swapped job of length %d with job of length %d.\n", tempCurrent->length, tempCurrent->next->length);

            tempCurrent = currJob; // Start from beginning 
        }
        else{ // Otherwise, check the next node
            tempCurrent = tempCurrent->next;
        }
    }
    return;
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
        makeListSJF(listHead);

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