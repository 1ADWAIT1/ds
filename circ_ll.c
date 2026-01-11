#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Node* newNode() {
    int value;
    printf("Enter value to insert: ");
    scanf("%d", &value);
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    node->data = value;
    node->next = node;
    node->prev = node;
    return node;
}

struct Node* inend(struct Node* head) {
    struct Node* node = newNode();
    if (node == NULL) return head;

    if (head == NULL) {
        return node;
    }

    struct Node* last = head->prev;
    last->next = node;
    node->prev = last;
    node->next = head;
    head->prev = node;
    return head;
}

struct Node* infront(struct Node* head) {
    struct Node* node = newNode();
    if (node == NULL) return head;

    if (head == NULL) {
        return node;
    }

    struct Node* last = head->prev;
    node->next = head;
    node->prev = last;
    last->next = node;
    head->prev = node;
    return node;
}

struct Node* insertAtPos(struct Node* head, int pos) {
    if (pos == 0)
        return infront(head);

    if (head == NULL)
        return head;

    struct Node* ptr = head;
    for (int i = 0; i < pos - 1; i++) {
        ptr = ptr->next;
        if (ptr == head)
            return inend(head);
    }

    struct Node* node = newNode();
    if (node == NULL) return head;

    node->next = ptr->next;
    node->prev = ptr;
    ptr->next->prev = node;
    ptr->next = node;
    return head;
}

struct Node* delfront(struct Node* head) {
    if (head == NULL) return NULL;

    if (head->next == head) {
        free(head);
        return NULL;
    }

    struct Node* last = head->prev;
    struct Node* temp = head;
    head = head->next;
    last->next = head;
    head->prev = last;
    free(temp);
    return head;
}

struct Node* delend(struct Node* head) {
    if (head == NULL) return NULL;

    if (head->next == head) {
        free(head);
        return NULL;
    }

    struct Node* last = head->prev;
    last->prev->next = head;
    head->prev = last->prev;
    free(last);
    return head;
}

struct Node* delAtPos(struct Node* head, int pos) {
    if (head == NULL) return NULL;
    if (pos == 0) return delfront(head);

    struct Node* ptr = head;
    for (int i = 0; i < pos; i++) {
        ptr = ptr->next;
        if (ptr == head) {
            printf("Position out of bounds\n");
            return head;
        }
    }

    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;
    free(ptr);
    return head;
}

void display(struct Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node* ptr = head;
    do {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    } while (ptr != head);
    printf("\n");
}

void search(struct Node* head, int value) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node* ptr = head;
    do {
        if (ptr->data == value) {
            printf("Value %d found\n", value);
            return;
        }
        ptr = ptr->next;
    } while (ptr != head);

    printf("Value %d not found\n", value);
}

int main() {
    struct Node* head = NULL;
    int choice, pos, value;

    while (1) {
        printf("\n1.Insert end\n2.Insert front\n3.Insert position\n4.Delete front\n5.Delete end\n6.Delete position\n7.Display\n8.Search\n9.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: head = inend(head); break;
            case 2: head = infront(head); break;
            case 3: printf("Position: "); scanf("%d",&pos); head = insertAtPos(head,pos); break;
            case 4: head = delfront(head); break;
            case 5: head = delend(head); break;
            case 6: printf("Position: "); scanf("%d",&pos); head = delAtPos(head,pos); break;
            case 7: display(head); break;
            case 8: printf("Value: "); scanf("%d",&value); search(head,value); break;
            case 9: return 0;
            default: printf("Invalid\n");
        }
    }
}
