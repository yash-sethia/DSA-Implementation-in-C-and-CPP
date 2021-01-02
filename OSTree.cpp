#include <bits/stdc++.h>
using namespace std;

enum Color {RED, BLACK};

struct Node
{
    int data;
    int color;
    int size;
    Node *left, *right, *parent;


    Node(int data)
    {
        this->data = data;
        this->left = this->right = this->parent = NULL;
        this->color = RED;
        this->size = 1;
    }

};


class RBTree
{
    Node *root;

    Node * osSelectHelper(Node * root, int i)
    {
        
        int r = size(root->left) + 1;
        
        if(i == r)
            return root;
        else if(i < r)
            return osSelectHelper(root->left, i);
        else
            return osSelectHelper(root->right, i - r);
    }


    int osRankHelper(Node * node)
    {
        int r = size(node->left) + 1;
        Node * y = node;
        while(y != root)
        {
            if(y == y->parent->right)
            {
                r = r + size(y->parent->left) + 1;
            }

            y = y->parent;
        }

        return r;
    }

    int size(Node * node)
    {
        if(node == NULL)
            return 0;
        return node->size;
    }

    int setSize(Node * node)
    {
        if(node == NULL)
            return 0;
        int r = setSize(node->right);
        int l = setSize(node->left);

        node->size = r + l + 1;
        return node->size;
    }

    void inorderHelper(Node *root)
    {
        if (root == NULL)
            return;

        inorderHelper(root->left);
        cout << root->data << " ";
        inorderHelper(root->right);
    }

    void preorderHelper(Node *root)
    {
        if (root == NULL)
            return;
        cout << root->data << " ";
        inorderHelper(root->left);
        inorderHelper(root->right);
        
    }

    void postorderHelper(Node *root)
    {
        if (root == NULL)
            return;

        postorderHelper(root->left);
        postorderHelper(root->right);
        cout << root->data << " ";
    }

    Node * minimum(Node * node)
    {
        while (node->left != NULL) 
            node = node->left;
        
        return node;
    }

    void rotateLeft(Node *&root, Node *&pt)
    {
        Node *pt_right = pt->right;

        pt->right = pt_right->left;

        if (pt->right != NULL)
            pt->right->parent = pt;

        pt_right->parent = pt->parent;

        if (pt->parent == NULL)
            root = pt_right;

        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;

        else
            pt->parent->right = pt_right;

        pt_right->left = pt;
        pt->parent = pt_right;
        
    }

    void rotateRight(Node *&root, Node *&pt)
    {
        Node *pt_left = pt->left;

        pt->left = pt_left->right;

        if (pt->left != NULL)
            pt->left->parent = pt;

        pt_left->parent = pt->parent;

        if (pt->parent == NULL)
            root = pt_left;

        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;

        else
            pt->parent->right = pt_left;

        pt_left->right = pt;
        pt->parent = pt_left;

    }

    bool hasRedChild(Node * t)
    {
        return (t->left != NULL and t->left->color == RED) or (t->right != NULL and t->right->color == RED);
    }


    bool isOnLeft(Node *t)
    {
        return t == t->parent->left;
    }

    Node *sibling(Node * t)
    {
        if (t->parent == NULL)
          return NULL;

        if (isOnLeft(t))
          return t->parent->right;

        return t->parent->left;
    }


public:

    RBTree()
    {
         root = NULL;
    }

    Node* BSTInsert(Node* root, Node *pt)
    {

        if (root == NULL)
            return pt;


        if (pt->data < root->data)
        {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        }
        else if (pt->data > root->data)
        {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }


        return root;
    }


    void fixViolation(Node *&root, Node *&pt)
    {
        Node *parent_pt = NULL;
        Node *grand_parent_pt = NULL;

        while ((pt != root) && (pt->color != BLACK) &&
            (pt->parent->color == RED))
        {

            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;


            if (parent_pt == grand_parent_pt->left)
            {

                Node *uncle_pt = grand_parent_pt->right;

                if (uncle_pt != NULL && uncle_pt->color == RED)
                {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }

                else
                {

                    if (pt == parent_pt->right)
                    {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    rotateRight(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }

            else
            {
                Node *uncle_pt = grand_parent_pt->left;


                if ((uncle_pt != NULL) && (uncle_pt->color == RED))
                {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }
                else
                {

                    if (pt == parent_pt->left)
                    {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    rotateLeft(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }

        root->color = BLACK;
    }

    void insert(const int &data)
    {
        Node *pt = new Node(data);

        root = BSTInsert(root, pt);

        fixViolation(root, pt);

        setSize(root);
    }



    void swapColors(Node *x1, Node *x2) 
    {
      int temp;
      temp = x1->color;
      x1->color = x2->color;
      x2->color = temp;
    }

  void swapdatavalues(Node *u, Node *v) 
  {
    int temp;
    temp = u->data;
    u->data = v->data;
    v->data = temp;
  }

  Node *successor(Node *x) 
  {
    Node *temp = x;

    while (temp->left != NULL)
      temp = temp->left;

    return temp;
  }


  Node *BSTreplace(Node *x) 
  {
    if (x->left != NULL and x->right != NULL)
      return successor(x->right);

    if (x->left == NULL and x->right == NULL)
      return NULL;

    if (x->left != NULL)
      return x->left;
    else
      return x->right;
  }

  
  void deleteNode(Node *v) 
  {
    Node *u = BSTreplace(v);

   
    bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
    Node *parent = v->parent;

    if (u == NULL) 
    {
      
      if (v == root) 
      {
        root = NULL;
      } 
      else 
      {
        if (uvBlack) {
          fixDoubleBlack(v);
        } 
        else 
        {
          if (sibling(v) != NULL)
            sibling(v)->color = RED;
        }

        
        if (isOnLeft(v)) 
        {
          parent->left = NULL;
          
        } 
        else 
        {
          parent->right = NULL;
          
        }
      }
      delete v;
      return;
    }

    if (v->left == NULL or v->right == NULL) 
    {
      
      if (v == root) 
      {
      
        v->data = u->data;
        v->left = v->right = NULL;
        delete u;
        
      } 
    else 
    {
        if (isOnLeft(v)) 
        {
          parent->left = u;
        } 
        else 
        {
          parent->right = u;
        }

        delete v;

        u->parent = parent;
        if (uvBlack) 
        {
          fixDoubleBlack(u);
        } 
        else 
        {
          u->color = BLACK;
        }
      }
      return;
    }
    swapdatavalues(u, v);
    deleteNode(u);

    setSize(root);
  }

  void fixDoubleBlack(Node *x) 
  {
    if (x == root)
      return;

    Node *sib = sibling(x), *parent = x->parent;

    if (sib == NULL) 
    {
      fixDoubleBlack(x->parent);
    } 
    else 
    {
        if (sib->color == RED) 
        {
          parent->color = RED;
          sib->color = BLACK;

          if (isOnLeft(sib)) 
          {
            rotateRight(root, parent);
          } 

          else 
          {
            rotateLeft(root, parent);
          }

          fixDoubleBlack(x);

      } 

      else 
      {
        if (hasRedChild(sib)) 
        {
          if (sib->left != NULL and sib->left->color == RED) 
          {
              if (isOnLeft(sib)) 
              {
                sib->left->color = sib->color;
                sib->color = parent->color;
                rotateRight(root, parent);
              } 
              else 
              {
                sib->left->color = parent->color;
                rotateRight(root, sib);
                rotateLeft(root, parent);
              }
          } 

          else 
          {
            if (isOnLeft(sib)) 
            {
              sib->right->color = parent->color;
              rotateLeft(root, sib);
              rotateRight(root, parent);
            } 

            else 
            {
              sib->right->color = sib->color;
              sib->color = parent->color;
              rotateLeft(root, parent);
            }

          }
          
          parent->color = BLACK;
        } 
        else 
        {
          sib->color = RED;
          if (parent->color == BLACK)
            fixDoubleBlack(parent);
          else
            parent->color = BLACK;
        }
      }
    }
  }



    void inorder()
    {
         inorderHelper(root);
    }
    void preorder()
    {
         preorderHelper(root);
    }
    void postorder()
    {
         postorderHelper(root);
    }


    Node *search(int n) 
    {
        Node *temp = root;
        while (temp != NULL) 
        {
              if (n < temp->data) 
              {
                    if (temp->left == NULL)
                        break;

                    else
                        temp = temp->left;
              } 
              else if (n == temp->data) 
              {
                    break;
              } 

              else 
              {
                    if (temp->right == NULL)
                        break;
                    else
                        temp = temp->right;
              }
        }

        return temp;
  }

    void deleteBydata(int n) 
    {
        if (root == NULL)
          return;

        Node *v = search(n), *u;

        if (v->data != n) 
        {
          cout << "No node found to delete with dataue:" << n << endl;
          return;
        }

        deleteNode(v);
  }


    void osSelect(int i)
    {
        Node * x = osSelectHelper(root, i);
        cout<<i<<"th smallest element is "<<x->data<<endl;
    }

    int osRank(int val)
    {
        Node * node = search(val);
        int rank = osRankHelper(node);
        return rank;
    }

};

int main()
{
    RBTree tree;

      tree.insert(7); 
      tree.insert(3); 
      tree.insert(18); 
      tree.insert(10); 
      tree.insert(22); 
      tree.insert(8); 
      tree.insert(11); 
      tree.insert(26); 
      tree.insert(2); 
      tree.insert(6); 
      tree.insert(13); 
  

    cout << "Inoder Traversal of Created Tree\n";
    tree.inorder();
    cout<<endl;


    cout << "\n Preder Traversal of Created Tree\n";
    tree.preorder();

    cout<<endl;

    cout << "\n Postoder Traversal of Created Tree\n";
    tree.postorder();

    cout<<endl;

    tree.osSelect(1);

    tree.osSelect(2);

    tree.osSelect(4);

    cout<<"Rank of node with value 1 = "<<tree.osRank(1);

    return 0;
}

