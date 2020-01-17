/************************************
 * Name: Dvir Asaf
 * ID: 313531113
 * Group: 01
 * Assignment: ass6
 ***********************************/

#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    int value;
    struct Node* next;
    struct Node* prev;
}Node;

struct Dictionary{
    Node* head;
    int size;
};

/************************************
 * Function Name: initDictionary.
 * Input: none.
 * Output: Dictionary pointer.
 * Function Operation: the function allocates initial memory for empty dictionary.
 ***********************************/

Dictionary* initDictionary()
{
    Dictionary* dict = (Dictionary*)malloc(sizeof(struct Dictionary));
    if(dict == NULL)
        return NULL;
    dict->head = NULL;
    dict->size = 0;
    return dict;
}

/************************************
 * Function Name: sizeOfDictionary.
 * Input: Dictionary* d.
 * Output: int(size of keys)
 * Function Operation: the function return the count of keys.
 ***********************************/

int sizeOfDictionary(Dictionary* d)
{
    return d->size;
}

/************************************
 * Function Name: putInDictionary.
 * Input: Dictionary* d, int key, int value.
 * Output: Result (SUCCESS, FAILURE, MEM_ERROR).
 * Function Operation: the function get key and value that need to be insert to the dictionary.
 * in order to make other operations on the dictionary easier, when we insert a new element
 * we keep the list sorted by key (increasing order).
 * if the key is already in the list, just replace its value.
 ***********************************/

Result putInDictionary(Dictionary* d, int key, int value)
{
    if(d->head == NULL)
    {
        Node* temp = (Node*)malloc(sizeof(Node));
        if(temp == NULL)
        {
            destroyDictionary(d);
            return MEM_ERROR;
        }
        temp->key = key;
        temp->value = value;
        temp->next = NULL;
        temp->prev = NULL;
        d->head = temp;
        d->size++;
        return  SUCCESS;
    }

    Node *cure = d->head;
    while (cure != NULL)
    {
        if(cure->key == key){
            cure->value = value;
            return SUCCESS;
        } else if (cure->key > key)
        {
            Node * temp = (Node*)malloc(sizeof(Node));
            if(temp == NULL)
                return MEM_ERROR;
            temp->key = key;
            temp->value = value;
            temp->next = cure;
            temp->prev = cure->prev;
            if(cure->prev != NULL)
            {
                cure->prev->next = temp;
            }else
            {
                d->head = temp;
            }

            cure->prev = temp;
            d->size++;
            return SUCCESS;
        }else if(cure->next == NULL)
        {
            Node* temp = (Node*)malloc(sizeof(Node));
            if(temp == NULL)
                return MEM_ERROR;
            temp->key = key;
            temp->value = value;
            temp->next = NULL;
            temp->prev = cure;
            cure->next = temp;
            d->size++;
            return SUCCESS;
        }
        else{
            cure = cure->next;
        }
    }
    //never reach here
    return FAILURE;
}

/************************************
 * Function Name: getFromDictionary.
 * Input: Dictionary* d, int key.
 * Output: int (value)
 * Function Operation: the function searches for element with the given key.
 * if the dictionary does not contain the key returns 0, else returns the value of key.
 ***********************************/

int getFromDictionary(Dictionary* d, int key)
{
    Node* cure = d->head;
    while (cure != NULL)
    {
        if(cure->key == key)
            return cure->value;
        cure = cure->next;
    }
    return 0;
}

/************************************
 * Function Name: printDictionary.
 * Input: Dictionary* d.
 * Output: none.
 * Function Operation: prints all elements of our dictionary.
 ***********************************/

void printDictionary(Dictionary* d)
{
    printf("{");
    Node* cure = d->head;
    for (int i = 0; i < d->size ; i++)
    {
        printf("[%d:%d]",cure->key,cure->value);
        cure = cure->next;

    }
    printf("}");
}

/************************************
 * Function Name: destroyDictionary.
 * Input: Dictionary* d.
 * Output: none.
 * Function Operation: the function frees all memory which had been allocated during the program.
 ***********************************/

void destroyDictionary(Dictionary* d)
{
    Node* cure = d->head;
    while (cure != NULL)
    {
        Node* temp = cure;
        cure = cure->next;
        free(temp);
    }
    free(d);
}

/************************************
 * Function Name: createDictionaryFromArrays.
 * Input: int keys[], int values[], int size.
 * Output: Dictionary pointer.
 * Function Operation: the function gets 2 arrays one for keys and the other for values, and get
 * size of each array.then creates dictionary from them.
 ***********************************/

Dictionary* createDictionaryFromArrays(int keys[], int values[], int size)
{
    Dictionary* newDict = initDictionary();
    for (int i = 0; i < size ; i++)
    {
        if( putInDictionary(newDict,keys[i],values[i]) == MEM_ERROR)
        {
            destroyDictionary(newDict);
            return NULL;
        }
    }
    return newDict;
}

/************************************
 * Function Name: removeFromDictionary.
 * Input: Dictionary* d, int key
 * Output:  Result(SUCCESS, FAILURE, MEM_ERROR).
 * Function Operation: get a key and delete it and its value from dictionary if exists.
 ***********************************/

Result removeFromDictionary(Dictionary* d, int key)
{
    if(!getFromDictionary(d,key)){
        return FAILURE;
    }
    if(d->size == 0){
        return FAILURE;
    }
    //if it is the head of the list
    if(d->head->key == key)
    {
        Node* temp = d->head;
        d->head = d->head->next;
        if(d->head != NULL)
        {
            d->head->prev = NULL;
        }
        free(temp);
        d->size--;
        return SUCCESS;
    }
    Node* cure = d->head;
    while(cure->key != key)
    {
        //go to next node
        cure = cure->next;
    }
    //now cure is the one we are looking fore
    //save cure in temp so we can delete it later
    Node* temp = cure;
    //make its prev to point on its next
    cure->prev->next = cure->next;
    //make its next to point on its prev
    if(cure->next != NULL)
    {
        cure->next->prev = cure->prev;
    }
    //free the temp - the node we planned to delete
    free(temp);
    d->size--;
    return SUCCESS;
}



