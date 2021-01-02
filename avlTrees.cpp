#include<iostream>

using namespace std;

struct Node
{
    int data;
    struct Node * left;
    struct Node * right;
    int height;
};


class AVLTree
{
    Node * root;

    int height(Node * node)
    {
        if (node == NULL)
            return -1;
        return node->height;
    }

    Node * rightRotate(Node * q)
    {
        struct Node * p;
        struct Node * hold;

        //cout<<"Right Rotation is Required\n";

        p = q->left;
        hold = p->right;
        p->right = q;
        q->left = hold;

        q->height = max(height(q->left), height(q->right))+1;
        p->height = max(height(p->left), height(p->right))+1;

        return p;
    }

    Node * leftRotate(Node * p)
    {
        struct Node * q;
        struct Node * hold;

        //cout<<"Left Rotation is Required\n";

        q = p->right;
        hold = q->left;
        q->left = p;
        p->right = hold;

        p->height = max(height(p->left), height(p->right))+1;
        q->height = max(height(q->left), height(q->right))+1;

        
        return q;
    }

    void preorderHelper(Node *root)
    {
        if(root != NULL)
        {
            cout<<root->data<<" ";
            preorderHelper(root->left);
            preorderHelper(root->right);
        }
    }

    void postorderHelper(Node *root)
    {
        if(root != NULL)
        {
            postorderHelper(root->left);
            postorderHelper(root->right);
            cout<<root->data<<" ";
        }
    }


    void inorderHelper(Node *root)
    {
        if(root != NULL)
        {
            inorderHelper(root->left);
            inorderHelper(root->right);
            cout<<root->data<<" ";
        }
    }


    int getBalance(Node * N)
    {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }


    Node * insertHelper(Node * node, int data)
    {
        int balance;
        if (node == NULL)
        {
            node = new Node;
            node->data = data;
            node->left = node->right = NULL;
            node->height = 1;
            return node;
        }

        if (data < node->data)
            node->left  = insertHelper(node->left, data);
        else if (data > node->data)
            node->right = insertHelper(node->right, data);
        else 
            return node;

     
        node->height = 1 + max(height(node->left),height(node->right));

      
        balance = getBalance(node);

      
        if (balance > 1 && data < node->left->data)
            return rightRotate(node);


        if (balance < -1 && data > node->right->data)
            return leftRotate(node);

        if (balance > 1 && data > node->left->data)
        {
            node->left =  leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && data < node->right->data)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }


    Node * minvalNode(Node * node)
    {
        Node * current = node;

        while(current->left != NULL)
            current = current->left;

        return current;
    }


    Node * deleteNodeHelper(Node* root, int key)
    {
        Node * temp;
        int balance;

        

        if(root == NULL)
            return root;

        
        if(key < root->data)
            root->left = deleteNodeHelper(root->left, key);

        
        else if(key > root->data)
            root->right = deleteNodeHelper(root->right, key);

        
        else
        {
            
            if( (root->left == NULL) || (root->right == NULL) )
            {
                if(root->left)
                    temp = root->left;
                else
                    temp = root->right;

                
                if(temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else 
                 *root = *temp; 
                free(temp);
            }
            else
            {
                
                temp = minvalNode(root->right);

                
                root->data = temp->data;

                
                root->right = deleteNodeHelper(root->right, temp->data);
            }
        }

        
        if (root == NULL)
          return root;

        
        root->height = 1 + max(height(root->left), height(root->right));

        
        balance = getBalance(root);

       
        if (balance > 1 && getBalance(root->left) >= 0)
        {
            return rightRotate(root);;
        }
        
        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left =  leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
        {
            return leftRotate(root);
        }

        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }


public:

    AVLTree(int data)
    {
        root = new Node;
        root->data   = data;
        root->left   = NULL;
        root->right  = NULL;
        root->height = 0;
    }

    void preorder()
    {
        if(root != NULL)
        {
            preorderHelper(root);
        }
    }

    void postorder()
    {
        if(root != NULL)
        {
            postorderHelper(root);
        }
    }


    void inorder()
    {
        if(root != NULL)
        {
            inorderHelper(root);
        }
    }


    void insert(int data)
    {
        root = insertHelper(root, data);
    }

    void deleteNode(int data)
    {
        root = deleteNodeHelper(root, data);
    }
};


int main()
{
    AVLTree root(60);
    cout<<"Inserting 60"<<" \n";
    cout<<"Preorder traversal of the constructed AVL tree is \n";
    root.preorder();
    cout<<endl;

    int x= 50;
    cout<<"Inserting "<<x<<" \n";
    root.insert(x);
    cout<<"Preorder traversal of the constructed AVL tree is \n";
    root.preorder();
    cout<<endl;

    x= 30;
    cout<<"Inserting "<<x<<" \n";
    root.insert(x);
    cout<<"Preorder traversal of the constructed AVL tree is \n";
    root.preorder();
    cout<<endl;

    x= 70;
    cout<<"Inserting "<<x<<" \n";
    root.insert(x);
    cout<<"Preorder traversal of the constructed AVL tree is \n";
    root.preorder();
    cout<<endl;

    x= 80;
    cout<<"Inserting "<<x<<" \n";
    root.insert(x);
    cout<<"Preorder traversal of the constructed AVL tree is \n";
    root.preorder();
    cout<<endl;

    x=20;
    cout<<"Inserting "<<x<<" \n";
    root.insert(x);
    cout<<"Preorder traversal of the constructed AVL tree is \n";
    root.preorder();
    cout<<endl;

    x=25;
    cout<<"Inserting "<<x<<" \n";
    root.insert(x);
    cout<<"Preorder traversal of the constructed AVL tree is \n";
    root.preorder();
    cout<<endl;

    x=100;
    cout<<"Inserting "<<x<<" \n";
    root.insert(x);
    cout<<"Preorder traversal of the constructed AVL tree is \n";
    root.preorder();
    cout<<endl;

    x=90;
    cout<<"Inserting "<<x<<" \n";
    root.insert(x);
    cout<<"Preorder traversal of the constructed AVL tree is \n";
    root.preorder();
    cout<<endl;

    x=90;
    cout<<"Deleting "<<x<<"\n";
    root.deleteNode(x);
    cout<<"Preorder traversal of the constructed AVL tree is \n";
    root.preorder();
    cout<<"\n";

    return 0;
}