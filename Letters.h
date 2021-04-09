#ifndef LETTERS_H_INCLUDED
#define LETTERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char ID[50];
	char receiver[50] ;
	char copyTo[50] ;
	char sender[50];
	char title[50];
	char content[150];
	char date[20];
} letter;

typedef struct Node
{
    letter data;
	struct Node* next;
} node;

void loadFile(node** head);
void saveFile(node* head);
char* getFileName();
void addNode(node**head, letter data, int mode);
letter initLetter(node*head);
int getID(node* head, char*ID, int mode);
int isUnique(node* head, char *ID);
void printData(letter data);
void printList(node*head);
void printSpecificLetters(node*head);
void printLetterByID(node *head);
void getDate(char* date);
void freeList(node* head);
void deleteSpam(node**head);
void deleteNodeAtPoss(node** head, int poss);
void deleteNode(node** head);

#endif // LETTERS_H_INCLUDED
