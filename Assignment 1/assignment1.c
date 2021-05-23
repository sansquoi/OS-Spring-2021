/**
 * Write your solutions here and turn in just this file.
 * Please keep in mind that your solution must compile and work with the basic
 * tester and tests. Feel free to extend them, but we will have our
 * own edits to them and your assignment1.c needs to work correctly with the
 * original tests/tester.
 */
#define _POSIX_C_SOURCE 200809L // for strdup; it won't be part of C until 2023.
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "assignment1.h"


struct node  {
	const char *key;
   const char *value;
	struct node* next;
	struct node* prev;
};

//static int cacheLength;

static struct node *head = NULL;
static struct node *current = NULL;
static const int cacheLimit = 16;

static struct node* createNode(const char *passedKey, const char *passedValue) {
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
   newNode->key = strdup(passedKey);
   newNode->value = strdup(passedValue);
   newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

//---------------------
// Util Functions
//---------------------
static int getCacheLength(struct node *nodeHead){
   int count = 1;
   while(nodeHead->next != NULL){
         count++;
         nodeHead=nodeHead->next;
   }
   return count;
}

static void insertHead(const char *x, const char *y) {
	struct node* newNode = createNode(x,y);   
	if(head == NULL) {
		head = newNode;
		return;
	}
	head->prev = newNode;
	newNode->next = head; 
	head = newNode;
}

static void moveToHead(struct node *nodeHead) {                         //TEST
   if(nodeHead!=NULL){
      if(nodeHead->prev == NULL){
         if(nodeHead == head){
               //do nothing
            }
      }
      else if (nodeHead->next == NULL && nodeHead->prev != NULL){
            nodeHead->prev->next = NULL;
            nodeHead->next = head;
            nodeHead->prev= NULL;
            head = nodeHead;
      }
      else if (nodeHead->next != NULL && nodeHead->prev != NULL){
            nodeHead->prev->next = nodeHead->next;
            nodeHead->next->prev = nodeHead->prev;
            head->prev = nodeHead;
	         nodeHead->next = head;
	         head = nodeHead;
      }
   }
}

static void deleteTail(struct node *nodeHead){
   while(nodeHead->next != NULL){
         nodeHead=nodeHead->next;
   }
   cache_del(nodeHead->key);
}


//-----------------
//Cache functions
//-----------------
char* cache_get(const char* key) {
   current=head;
   while (current != NULL)
         {              
            if (current->key && strcmp(current->key, key) == 0)  {                                  
                  moveToHead(current);         
                  char * my_copy;
                  my_copy = malloc(sizeof(char) * (strlen(current->value) + 1));
                  strcpy(my_copy,current->value);         
                  return (char*) my_copy;             //caller's responsibility to free
            }
            current=current->next;
         }
   return NULL;
}

void cache_set(const char* key, const char* value) {    
    current = head; // Initialize current  
    if(current == NULL)
    {
       insertHead(key, value);
    }
    else{
         int foundFlag = 0;       
         while (current != NULL)  
         {              
            if (current-> key && key && strcmp(current->key, key) == 0)  {
                  foundFlag = 1;   
                  moveToHead(current);
                  break;         
               }
               current = current->next; 
         }
         if(foundFlag == 0){                             //no match found & new key-value pair needs to be inserted
               int cacheLength = getCacheLength(head);
               if(cacheLength >= cacheLimit){               
                  deleteTail(head);
                  insertHead(key, value);
               }
               else{                  
                  insertHead(key, value);
               }
            }            
    }
}

bool cache_del(const char* key) {
   struct node *traverseNode = head;
   while (traverseNode != NULL)  
    {  
        if (traverseNode->key && strcmp(traverseNode->key, key) == 0)  {
            if(traverseNode->prev == NULL){                       //node is head
                  if (traverseNode->next != NULL){                //if head is not the only element            
                     traverseNode->next->prev = NULL;
                     head = traverseNode->next;
                     free((char *)traverseNode->key);
                     free((char *)traverseNode->value);
                     free(traverseNode);
                  }
                  else if (traverseNode->next == NULL) {            //head is the only element //TEST
                     free((char *)traverseNode->key);
                     free((char *)traverseNode->value);
                     free(traverseNode);
                     head= NULL;
                  }                  
                  return true;
            }
            else if (traverseNode->next == NULL && traverseNode->prev != NULL){                 //node is tail
                  traverseNode->prev->next = NULL;  
                  free((char *)traverseNode->key);
                  free((char *)traverseNode->value);
                  free(traverseNode);  
                  return true;
            }
            else{                                                 //node is somewhere in between                   
                  traverseNode->next->prev = current->prev;
                  traverseNode->prev->next = traverseNode->next;
                  free((char *)traverseNode->key);
                  free((char *)traverseNode->value);
                  free(traverseNode);
                  return true;                 
            }
         }
         else {

         }
         traverseNode = traverseNode->next;  
   }
   return false;
}

void cache_clear(void) {
   current = head;   
   if(current != NULL){
      struct node * nodeDelete;
      while(current!=NULL){
         nodeDelete = current;
         current = current->next;
         free((char *)nodeDelete->key);
         free((char *)nodeDelete->value); 
         free(nodeDelete);
      }
   }
   head=NULL;
}



