#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int E;

struct ListNode{
    E element;
    struct ListNode * next;
};

typedef struct ListNode * Node;

void initList(Node node) {
    node->next = NULL;
}

bool insertList(Node head, E element, int index) {
    if(index < 0) return 0;
    while(--index) {
        head = head->next;
        if(head == NULL) return 0;
    }

    Node node = malloc(sizeof(struct ListNode));
    if(node == NULL) return 0;
    node->element = element;
    node->next = head->next;

    head->next = node;
    return 1;
}

bool deleteList(Node head, int index) {
    if(index < 0) return 0;
    while(--index) {
        head = head->next;
        if(head == NULL) return 0;
    }
    if(head->next == NULL) return 0;

    Node tmp = head->next;
    E e = tmp->element;
    head->next = tmp->next;
    free(tmp);
    return e;
}

bool isEmptyList(Node head) {
    if(head == NULL) return 1;
}

void printList(Node head) {
    if(head == NULL) return;
    head = head->next;
    while(head != NULL) {
        printf("%d ", head->element);
        head = head->next;
    }

    printf("\n");
}

int main() {
    struct ListNode head;
    initList(&head);
    for(int i = 1; i <= 10; i++)
        insertList(&head, i*100, i);
    printList(&head);
    while(!isEmptyList(&head)) {
        printf("%d ", deleteList(&head, 10));
    }

    return 0;
}