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
    node->next = NULL;
    node->prev = NULL;
    return node;
}

int main() {
    struct Node* head = NULL;
    int choice = 1, value = 0;

    while (1) {
        printf("\n1. Insert at end\n");
        printf("2. Insert at front\n");
        printf("3. Insert at position\n");
        printf("4. Delete from front\n");
        printf("5. Delete from end\n");
        printf("6. Delete from position\n");
        printf("7. Display\n");
        printf("8. Search\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1: {
                struct Node* newNode1 = newNode();
                if (newNode1 == NULL) break;
                if (head == NULL) {
                    head = newNode1;
                } else {
                    struct Node* ptr = head;
                    while (ptr->next != NULL)
                        ptr = ptr->next;
                    ptr->next = newNode1;
                    newNode1->prev = ptr;
                }
                break;
            }

            case 2: {
                struct Node* newNode1 = newNode();
                if (newNode1 == NULL) break;
                newNode1->next = head;
                if (head != NULL)
                    head->prev = newNode1;
                head = newNode1;
                break;
            }

            case 3: {
                int pos;
                printf("Enter position to insert at: ");
                scanf("%d", &pos);

                struct Node* newNode1 = newNode();
                if (newNode1 == NULL) break;

                if (pos == 0) {
                    newNode1->next = head;
                    if (head != NULL)
                        head->prev = newNode1;
                    head = newNode1;
                } else {
                    struct Node* ptr = head;
                    for (int i = 0; i < pos - 1 && ptr->next != NULL; i++)
                        ptr = ptr->next;

                    newNode1->next = ptr->next;
                    if (ptr->next != NULL)
                        ptr->next->prev = newNode1;
                    ptr->next = newNode1;
                    newNode1->prev = ptr;
                }
                break;
            }

            case 4: {
                if (head == NULL) {
                    printf("List is empty.\n");
                } else {
                    struct Node* temp = head;
                    head = head->next;
                    if (head != NULL)
                        head->prev = NULL;
                    free(temp);
                }
                break;
            }

            case 5: {
                if (head == NULL) {
                    printf("List is empty.\n");
                } else if (head->next == NULL) {
                    free(head);
                    head = NULL;
                } else {
                    struct Node* ptr = head;
                    while (ptr->next != NULL)
                        ptr = ptr->next;
                    ptr->prev->next = NULL;
                    free(ptr);
                }
                break;
            }

            case 6: {
                int pos;
                printf("Enter position to delete from: ");
                scanf("%d", &pos);

                if (head == NULL) {
                    printf("List is empty.\n");
                } else if (pos == 0) {
                    struct Node* temp = head;
                    head = head->next;
                    if (head != NULL)
                        head->prev = NULL;
                    free(temp);
                } else {
                    struct Node* ptr = head;
                    for (int i = 0; i < pos && ptr != NULL; i++)
                        ptr = ptr->next;

                    if (ptr == NULL) {
                        printf("Position out of bounds.\n");
                    } else {
                        ptr->prev->next = ptr->next;
                        if (ptr->next != NULL)
                            ptr->next->prev = ptr->prev;
                        free(ptr);
                    }
                }
                break;
            }

            case 7: {
                if (head == NULL) {
                    printf("List is empty.\n");
                } else {
                    struct Node* ptr = head;
                    printf("List elements: ");
                    while (ptr != NULL) {
                        printf("%d ", ptr->data);
                        ptr = ptr->next;
                    }
                    printf("\n");
                }
                break;
            }

            case 8: {
                if (head == NULL) {
                    printf("List is empty.\n");
                } else {
                    printf("Enter value to search: ");
                    scanf("%d", &value);
                    struct Node* ptr = head;
                    int found = 0;
                    while (ptr != NULL) {
                        if (ptr->data == value) {
                            printf("Value %d found in the list.\n", value);
                            found = 1;
                            break;
                        }
                        ptr = ptr->next;
                    }
                    if (!found)
                        printf("Value %d not found.\n", value);
                }
                break;
            }

            case 9:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}
