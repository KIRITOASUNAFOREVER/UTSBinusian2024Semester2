#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct node{
    char name[31];
    int todo;
    struct node *next, *prev;
}*head = NULL, *tail = NULL;

struct node *createNode(char name[], int todo){
    struct node *newNode = (struct node*) malloc(sizeof(struct node));
    strcpy(newNode->name, name);
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->todo = todo;
    return newNode;
}

void pushData(char name[], int todo){
    if(head == NULL){
        tail = head = createNode(name, todo);
    } else if(head == tail){ 
        if(head->todo <= todo){
            tail = createNode(name, todo);
            tail->prev = head;
            head->next = tail;
        } else {
            head = createNode(name, todo);
            tail->prev = head;
            head->next = tail;
        }
    } else {
        struct node *curr = head;
        bool EOD = false;
        while(curr->todo <= todo){
            if(curr->next){
                curr = curr->next;
            } else {
                EOD = true;
                break;
            }
        }
        if(curr == head){
            head = createNode(name, todo);
            head->next = curr;
            curr->prev = head;
        } else if(EOD){
            tail->next = createNode(name, todo);
            tail->next->prev = tail;
            tail = tail->next;
        } else {
            struct node *dangleNode = createNode(name, todo);
            curr->prev->next = dangleNode;
            dangleNode->prev = curr->prev;
            dangleNode->next = curr;
            curr->prev = dangleNode;
        }
    }
}

void popHead(){
	if(!head) return;
    if(!head->next){
        switch(head->todo){
            case 1:
                printf("%s is in the Emergency Room\n", head->name);
                break;
            case 2:
                printf("%s is in the Examination Room\n", head->name);
                break;
            case 3:
                printf("%s is in the Consultation Room\n", head->name);
                break;
            case 4:
                printf("%s is in the Consultation Room\n", head->name);
                break;
        }
        free(head);
        head = tail = NULL;
    } else {
        switch(head->todo){
            case 1:
                printf("%s is in the Emergency Room\n", head->name);
                break;
            case 2:
                printf("%s is in the Examination Room\n", head->name);
                break;
            case 3:
                printf("%s is in the Consultation Room\n", head->name);
                break;
            case 4:
                printf("%s is in the Consultation Room\n", head->name);
                break;
        }
        struct node *deleteThis = head;
        head->next->prev = NULL;
        head = head->next;
        free(deleteThis);
    }
}

void createTask(){
    char name[101], condition[15];
    scanf(" %s %s", name, condition); getchar();
    int todo;
    if(strcmp(condition,"Good") == 0){
        todo = 4;
    }
    else if(strcmp(condition,"Fair")== 0){
        todo = 3;
    }
    else if(strcmp(condition,"Serious") == 0){
        todo = 2;
    }
    else if(strcmp(condition, "Critical") == 0){
        todo = 1;
    }
    pushData(name, todo);
}

void printWaiting(){
    printf("Waiting Room:");
    if(!head){
        printf(" None\n");
    } else {
        printf(" %s", head->name);
        struct node *curr = head;
        while(curr->next){
            curr = curr->next;
            printf(", %s", curr->name);
        }
        printf("\n");
    }
}

int main(){
    int n; scanf(" %d", &n); 
    getchar();
    for(int i = 0; i < n; i++){
        char str[10], n;
        scanf(" %s", str); getchar();
        if(strcmp(str, "ADD") == 0){
            n = '1';
        } else {
            n = '2';
        }
        switch(n){
            case '1' :
                createTask();
                break;
            case '2' :
                popHead();
                break;
        }
    }
    printWaiting();
    return 0;
}
