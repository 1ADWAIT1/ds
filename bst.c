#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node *left,*right;
};

struct Node* newNode(int item)
{
    struct Node* temp=(struct Node*)malloc(sizeof(struct Node));
    temp->data=item;
    temp->left=temp->right=NULL;
    return temp;
}

struct Node* insert(struct Node* node,int data)
{
    if(node==NULL)
        return newNode(data);
    if(data<node->data)
        node->left=insert(node->left,data);
    else if(data>node->data)
        node->right=insert(node->right,data);
    return node;
}

int minValueNode(struct Node* node)
{
    while(node && node->left!=NULL)
        node=node->left;
    return node->data;
}

struct Node* delete(struct Node* root,int data)
{
    if(root==NULL)
    {
        printf("Deletion not possible\n");
        return root;
    }
    if(data<root->data)
        root->left=delete(root->left,data);
    else if(data>root->data)
        root->right=delete(root->right,data);
    else
    {
        if(root->left==NULL)
        {
            struct Node *temp=root->right;
            free(root);
            printf("Deleted successfully\n");
            return temp;
        }
        else if(root->right==NULL)
        {
            struct Node *temp=root->left;
            free(root);
            printf("Deleted successfully\n");
            return temp;
        }
        root->data=minValueNode(root->right);
        root->right=delete(root->right,root->data);
    }
    return root;
}

struct Node* search(struct Node* root,int data)
{
    if(root==NULL || root->data==data)
        return root;
    if(data<root->data)
        return search(root->left,data);
    return search(root->right,data);
}

void inorder(struct Node* root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    }
}

void preorder(struct Node* root)
{
    if(root!=NULL)
    {
        printf("%d ",root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node* root)
{
    if(root!=NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->data);
    }
}

void display(struct Node* root)
{
    if(root==NULL){
        printf("BST is empty.");
        return;
    }
    int choice;
    printf("\n1.Inorder\n2.Preorder\n3.Postorder\n");
    printf("Enter choice:");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1: inorder(root); break;
        case 2: preorder(root); break;
        case 3: postorder(root); break;
        default: printf("Invalid choice");
    }
}

int main()
{
    int choice,value;
    struct Node *root=NULL;
    while(1)
    {
        printf("1.Insert\n2.Delete\n3.Search\n4.Display\n5.Exit\n");
        printf("Enter your choice:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("Enter value to be inserted:");
                scanf("%d",&value);
                root=insert(root,value);
                break;
            case 2:
                printf("Enter value to be deleted:");
                scanf("%d",&value);
                root=delete(root,value);
                break;
            case 3:
            {
                struct Node* result;
                printf("Enter value to be searched:");
                scanf("%d",&value);
                result=search(root,value);
                if(result==NULL)
                    printf("Not found");
                else
                    printf("Found");
                break;
            }
            case 4:
                display(root);
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice");
        }
    }
    return 0;
}
