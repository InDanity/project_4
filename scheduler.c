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
    int newLength;
    int newID;
    int newChecked;

      while(tempCurrent != NULL && tempCurrent->next !=NULL){
        if(tempCurrent->length > tempCurrent->next->length){  // If the current node has a smaller run length than the last, SWAPPING TIME!!!
            // Store the next node's values in temp values...
            newLength = tempCurrent->next->length;
            newID = tempCurrent->next->id;
            newChecked = tempCurrent->next->checked;

            // Replace next node's data with current node's data...
            tempCurrent->next->length = tempCurrent->length;
            tempCurrent->next->id = tempCurrent->id;
            tempCurrent->next->checked = tempCurrent->checked;

            // Replace current node's data with temp data...
            tempCurrent->length = newLength;
            tempCurrent->id = newID;
            tempCurrent->checked = newChecked;

            tempCurrent = currJob;
        }

        else{
            tempCurrent = tempCurrent->next;
        }
      }
}

int seeIfAllChecked(struct job* currJob){ // Returns a 1 if all nodes have a check value of 1, returns a 0 if otherwise.
    struct job* tempCurrent = currJob; // used to hold the address of the current node.

    while(tempCurrent != NULL && tempCurrent->next !=NULL){
        if(tempCurrent->checked != 1 || tempCurrent->next->checked != 1){  // If a single node hasn't been checked, WE ARE DONE.
            return 0;
        }

        else{
            tempCurrent = tempCurrent->next;
        }
    }
    printf("All programs have run to completion!\n");
    return 1;
}

void roundRobin(struct job* currJob, int timeSlice){
    struct job* tempCurrent = currJob; // used to hold the address of the current node.
    int slicedRuntime;
    
    if(timeSlice == 0){ // In case some bozo (me) gives a time slice of 0.
        printf("Why is the time slice 0???\n");
        return;
    }
    printf("--------------------------------------------------------\n");

    while(tempCurrent != NULL){ // While we still got nodes...
        if(tempCurrent->length >= timeSlice){ // If the remaining length is still greater than the time slice, run for the time slice.
            printf("Job %d ran for: %d.\n", tempCurrent->id, timeSlice);
            tempCurrent->length -= timeSlice;
        }

        else if(tempCurrent->length > 0 && tempCurrent->length < timeSlice){ // Or, if the remaining length is less than the time slice but greater than 0, run for the remaining time.
            printf("Job %d ran for: %d.\n", tempCurrent->id, tempCurrent->length);
            tempCurrent->length = 0;
        }

        else { // Or, if the remaining length is 0 but the node hasn't been checked yet, check it.
            tempCurrent->checked = 1;
        }

        tempCurrent = tempCurrent->next;
    }

    if(seeIfAllChecked(currJob)){ // If all jobs have been checked off, we are done.
        printf("Finished executing RR.\n");
        return;
    }
    else{
        roundRobin(currJob, timeSlice);
    }
}


void main(int argc, char *argv[]){
    char *myself = argv[0];
    char *scheduleType = argv[1];
    char *jobFile = argv[2];
    char *timeSliceString = argv[3];
    listHead = NULL;

    int timeSlice = atoi(timeSliceString);
    printf("Given a time slice of: %d\n", timeSlice);
    
    
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

        // Insert into linked list, runLength and lineNumber as job ID
        if(listHead == NULL){
        // Create node to be pointed at, set listHead to point at it

        //idk if any of this is right lol pls dan help:
            listHead = malloc(sizeof(struct job));
            listHead->id = -1;

            // struct job *node;
            // node = malloc(sizeof(struct job));
            // node->id = lineNum; 
            // node->length = runLength;
            // listHead->next = node;

            printf("Adding node of Job %d with length %d to job list.\n", lineNum, runLength);
            addNode(listHead, lineNum, runLength);

        } else{
            printf("Adding node of Job %d with length %d to job list.\n", lineNum, runLength);
            addNode(listHead, lineNum, runLength);
        }
        lineNum++; 
    }
    fclose(fd);

    printf("There are %d jobs.\n", lineNum);

    if(strcmp(scheduleType, "FIFO") == 0){ // If given "FIFO"
        printf("Executing FIFO...\n");
        jobListPrint(*listHead->next);
        printf("End of execution with FIFO.\n");
    }
    else if(strcmp(scheduleType, "SJF") == 0){ // If given "SJF"
        printf("Executing SJF...\n");
        makeListSJF(listHead);
        jobListPrint(*listHead->next);
        printf("End of execution with SJF.\n");

    } 
    else if(strcmp(scheduleType, "RR") == 0){ // If given "RR"
        printf("Executing RR...\n");
        roundRobin(listHead->next, timeSlice);
    }
    else{
        printf("Make the scheduleType one of the following: 'FIFO,' 'SJF,' OR 'RR.'\n");
        exit(-1);
    }
    exit(0);
}