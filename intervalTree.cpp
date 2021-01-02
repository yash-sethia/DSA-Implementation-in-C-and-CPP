#include <bits/stdc++.h>
using namespace std;

enum Color {RED, BLACK};

struct Node
{
    int low, high;
    int color;
    int m;
    Node *left, *right, *parent;


    Node(int low, int high)
    {
      this->low = low;
      this->high = high;
      this->left = this->right = this->parent = NULL;
      this->color = RED;
      this->m = high;
    }

};


class RBTree
{
    Node *root;

    int returnM(Node * p)
    {
        if(p == NULL)
            return 0;
        return p->m;
    }
    void setM(Node * node)
    {
        if(node == NULL)
            return;
        else
        {
          setM(node->right);
          setM(node->left);
          node->m = max(node->high , max(returnM(node->right) , returnM(node->left) ));
        }
    }

    void inorderHelper(Node *root)
    {
        if (root == nullptr)
            return;

        inorderHelper(root->left);
        cout<<" ( "<<root->low<<" , "<<root->high<<" ) "<<" , ";
        inorderHelper(root->right);
    }

    void preorderHelper(Node *root)
    {
        if (root == nullptr)
            return;

        cout<<" ( "<<root->low<<" , "<<root->high<<" ) "<<" , ";
        inorderHelper(root->left);
        inorderHelper(root->right);
        
    }

    void postorderHelper(Node *root)
    {
        if (root == nullptr)
            return;

        postorderHelper(root->left);
        postorderHelper(root->right);
        cout<<" ( "<<root->low<<" , "<<root->high<<" ) "<<" , ";
    }

    void rotateLeft(Node *&root, Node *&pt)
    {
        Node *pt_right = pt->right;

        pt->right = pt_right->left;

        if (pt->right != nullptr)
            pt->right->parent = pt;

        pt_right->parent = pt->parent;

        if (pt->parent == nullptr)
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

        if (pt->left != nullptr)
            pt->left->parent = pt;

        pt_left->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_left;

        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;

        else
            pt->parent->right = pt_left;

        pt_left->right = pt;
        pt->parent = pt_left;
    }

public:

    RBTree()
    {
        root = nullptr;
    }

    Node * minimum(Node * node)
    {
        while (node->left != nullptr) 
            node = node->left;
        
        return node;
    }


    Node* BSTInsert(Node* root, Node *pt)
    {

        if (root == nullptr)
        return pt;


        if (pt->low < root->low)
        {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        }
        else if (pt->low > root->low)
        {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }


        return root;
    }


    void fixViolation(Node *&root, Node *&pt)
    {
        Node *parent_pt = nullptr;
        Node *grand_parent_pt = nullptr;

        while ((pt != root) && (pt->color != BLACK) &&
            (pt->parent->color == RED))
        {

            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;


            if (parent_pt == grand_parent_pt->left)
            {

                Node *uncle_pt = grand_parent_pt->right;

                if (uncle_pt != nullptr && uncle_pt->color == RED)
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


                if ((uncle_pt != nullptr) && (uncle_pt->color == RED))
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

    void insert(int low, int high)
    {
        Node *pt = new Node(low, high);

        root = BSTInsert(root, pt);

        fixViolation(root, pt);

        setM(root);
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




  void swapColors(Node *x1, Node *x2) {
    int temp;
    temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
  }

  void swaplowvalues(Node *u, Node *v) 
  {
    int temp;
    temp = u->low;
    u->low = v->low;
    v->low = temp;
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
        if (uvBlack) 
        {
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
      setM(root);
      return;
    }

    if (v->left == NULL or v->right == NULL) 
    {
      
      if (v == root) 
      {
        v->low = u->low;
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

        setM(root);
        return;
      }

    swaplowvalues(u, v);
    deleteNode(u);
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
        if (n < temp->low) 
        {
          if (temp->left == NULL)
              break;
          else
            temp = temp->left;
        } 

        else if (n == temp->low) 
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

    void deleteBylow(int n) {
    if (root == NULL)
      return;

    Node *v = search(n), *u;

    if (v->low != n) {
      cout << "No node found to delete with lowue:" << n << endl;
      return;
    }

    deleteNode(v);
  }
  

  bool Overlap(int low1, int high1, int low2, int high2)
  {
    return (low1 <= high2 and low2 <= high1);
  }

  Node * intervalSearch(int low, int high)
  {
      Node * x = root;

      while(x != NULL and !Overlap(low, high, x->low, x->high))
      {
        if(x->left != NULL and x->left->m > low)
          x = x->left;
        else
          x = x->right;
      }

      return x;
  }

};

int main()
{
    RBTree tree;

    tree.insert(7, 11);
    tree.insert(6, 8);
    tree.insert(5, 6);
    tree.insert(4, 10);
    tree.insert(3, 5);
    tree.insert(2, 3);
    tree.insert(1, 7);

    Node * t = tree.intervalSearch(6, 11);

    cout<<"After interval search, result = ( "<<t->low<<" , "<<t->high<<" ) ";

    return 0;
}

