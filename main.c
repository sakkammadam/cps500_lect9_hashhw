#include <stdio.h>
#include <stdlib.h>


typedef struct ChainedHashNode{
    int value;
    struct ChainedHashNode* next;
} ChainedHashNode;

int hash_function(int dataValue, int size){
    return dataValue%size;
}

typedef struct ChainedHashTable{
    // Array of pointers to HashNode*
    ChainedHashNode** array; // array for lookup!
    int N; // size of array
} ChainedHashTable;

ChainedHashTable* initializeTable(int size){
    ChainedHashTable * table = (ChainedHashTable*)malloc(sizeof(ChainedHashTable));
    table->N = size;
    table->array = (ChainedHashNode**)malloc(sizeof(ChainedHashNode)*size);
    // initialize array
    for(int i=0; i<table->N; i++){
        table->array[i] = NULL;
    }
    return table;
}

ChainedHashNode* initializeNode(int dataValue){
    ChainedHashNode * tempNode = malloc(sizeof(ChainedHashNode));
    tempNode->value=dataValue;
    tempNode->next=NULL;
    return tempNode;
}

void ChainedHashTableInsert(ChainedHashTable* table, int dataValue){
    // initialize a node
    ChainedHashNode* newNode = initializeNode(dataValue);
    // calculate hash key using hash_function
    int hashKey = hash_function(dataValue, table->N);
    // lets evaluate if there is an item already in the array
    ChainedHashNode* evalCurrentNode = table->array[hashKey];
    // we are going to check this node -
    // if null - that means it is the first insert
    // if not null - collision! - we need to use linked list property of the struct to extend!
    // there is another edge case! updating value - for that we need key/value but since we are only doing value - skip
    if(evalCurrentNode == NULL){
        // [Area of improvement] - check if the hash table is full or not ? - needs to be there for probing for alpha
        table->array[hashKey] = newNode;
    } else {
        // collision scenario - extend list
        while(evalCurrentNode->next){
            // keep going down the linked list chain
            evalCurrentNode=evalCurrentNode->next;
        }
        evalCurrentNode->next = newNode;
    }
}

void printHashTable(ChainedHashTable* table){
    printf("\nPrinting the hash table....");
    for(int i=0; i < table->N; i++){
        printf("\n===========================================================");
        printf("\nAt index - %d, the values are - ", i);
        ChainedHashNode* temp = table->array[i];
        while(temp!=NULL){
            if(temp->next==NULL){
                printf("%d", temp->value);
            } else {
                //lets chain
                printf("%d->", temp->value);
            }
            temp = temp->next;
        }
    }
}

typedef struct ProbedHashNode{
    int value;
    int key;
} ProbedHashNode;

typedef struct ProbedHashTable{
    ProbedHashNode** array;
    int N;
} ProbedHashTable;

ProbedHashTable* initializeProbTable(int size){
    ProbedHashTable * table = (ProbedHashTable*)malloc(sizeof(ProbedHashTable));
    table->N = size;
    table->array = (ProbedHashNode **)malloc(sizeof(ProbedHashNode)*size);
    // initialize array
    for(int i=0; i<table->N; i++){
        table->array[i] = NULL;
    }
    return table;
}

ProbedHashNode * initializeProbNode(int dataValue){
    ProbedHashNode* tempNode = malloc(sizeof(ProbedHashNode));
    tempNode->value=dataValue;
    return tempNode;
}

int insertProbeHashTable(ProbedHashTable* table, int dataValue){
    // initialize a node
    ProbedHashNode* newNode = initializeProbNode(dataValue);
    // hash key
    int hashKey = hash_function(dataValue, table->N);
    for(int i=0; i < table->N; i++){
        if(table->array[hashKey]==NULL){
            table->array[hashKey] = newNode;
            return 1;
        } else {
            hashKey=(hashKey+i)%table->N;
        }
    }
    // there was hash-collision if not null!
    return 0;
}

void displayProbHashArray(ProbedHashTable * table){
    printf("\nPrinting the Linear Prob hash table...");
    printf("\n=======================================");
    for(int i=0; i< table->N; i++){
        ChainedHashNode* tempProbeNode = table->array[i];
        printf("\nAt Index %d, the Value is %d", i, tempProbeNode->value);
    }
};

int main() {
    printf("\nStarting with HashTables using Chaining.....");
    // Prof. Roueche this was to match what you did in the HW answers - pls change to 11 if needed
    ChainedHashTable* chainTable = initializeTable(8);
    int userInput[13] = {17,
                         23,
                         100,
                         50,
                         61,
                         9,
                         12,
                         15,
                         6,
                         4,
                         33,
                         27,
                         51
    };
    int sizeOfArray = sizeof(userInput)/sizeof(userInput[0]);
    for(int k=0; k < sizeOfArray; k++){
        ChainedHashTableInsert(chainTable, userInput[k]);
    }
    printHashTable(chainTable);

    // linear probing...
    printf("\nMoving to Linear Probing.....");
    // Prof. Roueche this was to match what you did in the HW answers - pls change to 11 if needed
    ProbedHashTable* probeTable = initializeProbTable(8);
    for(int k=0; k < sizeOfArray; k++){
        insertProbeHashTable(probeTable, userInput[k]);
    }
    displayProbHashArray(probeTable);

    return 0;
}
