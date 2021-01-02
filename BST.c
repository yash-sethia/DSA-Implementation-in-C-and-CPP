#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct bstNode
{
    int data;
    struct bstNode * left;
    struct bstNode * right;
};

struct bstNode *newNode(int val)
{
    struct bstNode *root =(struct bstNode *)malloc(sizeof(struct bstNode));
    if(root==NULL)
    {
        printf(" Memory could not be allocated ");
        exit(1);
    }

    root->data = val;
    root->right=NULL;
    root->left=NULL;
    return(root);

}


struct bstNode * insert(struct bstNode * root, int val)
{
    if(root==NULL)
        return(newNode(val));
    if(val<(root->data))
        root->left=insert(root->left, val);
    if(val>=(root->data))
        root->right=insert(root->right, val);

    return(root);
}


bool member(struct bstNode * T, int key)
{
    if(T==NULL)
        return(false);
    if(T->data == key)
        return(true);
    if(key<T->data)
        return(member(T->left,key));
    if(key>=T->data)
        return(member(T->right, key));

}


int removeSmallest(struct bstNode ** T)
{
    int result;
    struct bstNode *temp;
    if((*T)->left == NULL)
    {
        result = (*T)->data;
        temp = *T;
        *T = (*T)->right;
        free(temp);
        return result;
    }
    else
    {
        return removeSmallest( &((*T)->left) );
    }
}


void inorder(struct bstNode *root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        printf(" %d ", root->data);
        inorder(root->right);
    }
}


void preorder(struct bstNode *root)
{
    if(root!=NULL)
    {
        printf(" %d ", root->data);
        inorder(root->left);
        inorder(root->right);
    }
}


void postorder(struct bstNode *root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        inorder(root->right);
        printf(" %d ", root->data);
    }
}



void removeNode(struct bstNode ** T, int key)
{
    struct bstNode *temp;
    if((*T)!=NULL)
    {
        if(key < (*T)->data)
            removeNode(&((*T)->left),key);
        else if(key > (*T)->data)
            removeNode(&((*T)->right),key);
        else if((*T)->left == NULL)
        {
            temp=*T;
            *T=(*T)->right;
            free(temp);
        }
        else if((*T)->right == NULL)
        {
            temp=*T;
            *T=(*T)->left;
            free(temp);
        }
        else
        {
            (*T)->data = removeSmallest(&((*T)->right));
        }

    }
}

int  main()
{
    struct bstNode *TreeRoot =  NULL, *temp =NULL;
    TreeRoot = insert(TreeRoot,5);
    TreeRoot = insert(TreeRoot,3);
    TreeRoot = insert(TreeRoot,2);
    TreeRoot = insert(TreeRoot,4);
    TreeRoot = insert(TreeRoot,7);
    TreeRoot = insert(TreeRoot,6);
    TreeRoot = insert(TreeRoot,8);

    printf("INORDER \n");
    inorder(TreeRoot);
    printf("\n");
    


    printf("PREORDER \n");
    preorder(TreeRoot);
    printf("\n");

    printf("POSTORDER \n");
    postorder(TreeRoot);
    printf("\n");
    

    if(!member(TreeRoot,10))
        printf("The value 10 is not present in the tree\n");
    if(member(TreeRoot,3))
        printf("The value 3 is present in the tree\n");

    removeNode(&TreeRoot,5);
    printf("Removed 5\n");
    inorder(TreeRoot);
    printf("\n");

    removeNode(&TreeRoot,7);
    printf("Removed 7\n");
    inorder(TreeRoot);
    printf("\n");

    
    return 0;
}
