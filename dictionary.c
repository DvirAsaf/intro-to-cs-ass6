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

Dictionary* initDictionary()
{
    Dictionary* dict = (Dictionary*)malloc(sizeof(struct Dictionary));
    dict->head = NULL;
    dict->size = 0;
    return dict;
}

int sizeOfDictionary(Dictionary* d)
{
    return d->size;
}

Result putInDictionary(Dictionary* d, int key, int value)
{
    if(d->head == NULL)
    {
        Node* temp = (Node*)malloc(sizeof(Node));
        if(temp == NULL)
            return MEM_ERROR;
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

void destroyDictionary(Dictionary* d)
{
    Node* cure = d->head;
    while (cure != NULL)
    {
        Node* temp = cure;
        cure = cure->next;
        free(temp);
    }
}

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

//Result removeFromDictionary(Dictionary* d, int key)
//{
//
//}



