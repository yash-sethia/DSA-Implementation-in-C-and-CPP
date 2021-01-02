#include<iostream> 

using namespace std; 

class Node
{
public:

	int *key;  
    int t;      
    Node **Child;  
    int n;     
    bool leaf; 

    Node(int tg, bool leafg)
    {
    	t = tg;
		leaf = leafg;
		key = new int  [2*t - 1];
		Child = new Node * [2*t]; 
		n = 0;
    }

 
	void insertNonFull(int k)
	{
		int i = n - 1;

		if(leaf == true)
		{
			while(i>=0 and key[i] > k)
			{
				key[i + 1] = key[i];
				i--;
			}

			key[i + 1] = k;

			n = n + 1;
		}
		else
		{
			while (i >= 0 && key[i] > k) 
            	i--;

            if(Child[i + 1]->n == 2*t - 1)
            {
            	splitChildhild(i + 1, Child[i + 1]);

            	if(key[i + 1] < k)
            		i++;
            } 

            Child[i + 1]->insertNonFull(k);
		}
	}

	void splitChildhild(int i, Node * y)
	{
		Node * z = new Node(y->t, y->leaf);

		z->n = t - 1;


		for(int j = 0; j < t - 1; j++)
		{
			z->key[j] = y->key[j + t]; 
		} 

		if (y->leaf == false) 
    	{ 
        	for (int j = 0; j < t; j++) 
            	z->Child[j] = y->Child[j + t]; 
    	}

    	y->n = t - 1;

    	for (int j = n; j >= i+1; j--) 
        	Child[j+1] = Child[j]; 

        Child[i+1] = z; 

        for (int j = n-1; j >= i; j--) 
        	key[j+1] = key[j]; 

    	key[i] = y->key[t-1]; 
  
    	n = n + 1; 

	}

	int findKey(int k)
	{
		int idx=0; 
	    while (idx<n && key[idx] < k) 
	        idx++; 
	    return idx;
	}


	void removeFromLeaf (int idx) 
	{ 
	  
	    for (int i=idx+1; i<n; ++i) 
	        key[i-1] = key[i]; 
	  
	    n--; 
	  
	    return; 
	} 
   
	void removeFromNonLeaf(int idx) 
	{ 
	  
	    int k = key[idx]; 
	
	    if (Child[idx]->n >= t) 
	    { 
	        int pred = getPred(idx); 
	        key[idx] = pred; 
	        Child[idx]->remove(pred); 
	    } 
	  
	    
	    else if  (Child[idx+1]->n >= t) 
	    { 
	        int succ = getSucc(idx); 
	        key[idx] = succ; 
	        Child[idx+1]->remove(succ); 
	    } 
	  
	    else
	    { 
	        merge(idx); 
	        Child[idx]->remove(k); 
	    } 
	    return; 
	} 

	int getPred(int idx) 
	{ 
	     
	    Node *cur=Child[idx]; 
	    while (!cur->leaf) 
	        cur = cur->Child[cur->n]; 
	  
	    return cur->key[cur->n-1]; 
	} 
	  
	int getSucc(int idx) 
	{ 
	  Node *cur=Child[idx]; 
	    
	    while (!cur->leaf) 
	        cur = cur->Child[0]; 
	  
	    return cur->key[0]; 
	} 
	   
	void fill(int idx) 
	{ 
	  
	    if (idx!=0 && Child[idx-1]->n>=t) 
	        borrowFromPrev(idx); 
	  
	    else if (idx!=n && Child[idx+1]->n>=t) 
	        borrowFromNext(idx); 

	    else
	    { 
	        if (idx != n) 
	            merge(idx); 
	        else
	            merge(idx-1); 
	    } 
	    return; 
	} 
	  

	void borrowFromPrev(int idx) 
	{ 
	  
	    Node *child=Child[idx]; 
	    Node *sibling=Child[idx-1]; 
	  
	    for (int i=child->n-1; i>=0; --i) 
	        child->key[i+1] = child->key[i]; 
	   
	    if (!child->leaf) 
	    { 
	        for(int i=child->n; i>=0; --i) 
	            child->Child[i+1] = child->Child[i]; 
	    } 
	  
	    
	    child->key[0] = key[idx-1]; 
	   
	    if(!child->leaf) 
	        child->Child[0] = sibling->Child[sibling->n]; 
	  
	    key[idx-1] = sibling->key[sibling->n-1]; 
	  
	    child->n += 1; 
	    sibling->n -= 1; 
	  
	    return; 
	} 
	  
	void borrowFromNext(int idx) 
	{ 
	  
	    Node *child=Child[idx]; 
	    Node *sibling=Child[idx+1]; 
	  
	   
	    child->key[(child->n)] = key[idx]; 
	  
	    
	    if (!(child->leaf)) 
	        child->Child[(child->n)+1] = sibling->Child[0]; 
	  
	     
	    key[idx] = sibling->key[0]; 
	  
	    
	    for (int i=1; i<sibling->n; ++i) 
	        sibling->key[i-1] = sibling->key[i]; 
	  
	    
	    if (!sibling->leaf) 
	    { 
	        for(int i=1; i<=sibling->n; ++i) 
	            sibling->Child[i-1] = sibling->Child[i]; 
	    } 
	  
	    child->n += 1; 
	    sibling->n -= 1; 
	  
	    return; 
	} 
	  
	void merge(int idx) 
	{ 
	    Node *child = Child[idx]; 
	    Node *sibling = Child[idx+1]; 
	  
	    child->key[t-1] = key[idx]; 
	   
	    for (int i=0; i<sibling->n; ++i) 
	        child->key[i+t] = sibling->key[i]; 
	  
	    
	    if (!child->leaf) 
	    { 
	        for(int i=0; i<=sibling->n; ++i) 
	            child->Child[i+t] = sibling->Child[i]; 
	    } 
	 
	    for (int i=idx+1; i<n; ++i) 
	        key[i-1] = key[i]; 
	  
	    for (int i=idx+2; i<=n; ++i) 
	        Child[i-1] = Child[i]; 
	  
	    child->n += sibling->n+1; 
	    n--; 
	   
	    delete(sibling); 
	    return; 
	} 

	void remove(int k)
    {
    	int idx = findKey(k); 
	 
	    if (idx < n && key[idx] == k) 
	    { 
	        if (leaf) 
	            removeFromLeaf(idx); 
	        else
	            removeFromNonLeaf(idx); 
	    } 
	    else
	    { 
	        if (leaf) 
	        { 
	            cout << "The key "<< k <<" does not exist in the tree\n"; 
	            return; 
	        } 
	  
	        bool flag = ( (idx==n)? true : false ); 
	        if (Child[idx]->n < t) 
	            fill(idx); 

	        if (flag && idx > n) 
	            Child[idx-1]->remove(k); 
	        
	        else
	            Child[idx]->remove(k); 
	    } 
	    return; 

    }


    void traverse()
    {

	    int i; 
	    for (i = 0; i < n; i++) 
	    { 
	        if (leaf == false) 
	            Child[i]->traverse(); 
	        cout << " " << key[i]; 
	    } 
	  
	    if (leaf == false) 
	        Child[i]->traverse(); 
    }


    Node * search(int k)
    {
        int i = 0; 
        while (i < n && k > key[i]) 
            i++; 
    
        if (key[i] == k) 
            return this; 
    
        if (leaf == true) 
            return NULL; 
    
        return Child[i]->search(k); 
    }

    friend class BTree;
};


class BTree 
{ 
    Node * root;
    int t;

public:
	BTree(int tgiven) 
    { 
        root = NULL; 
        t = tgiven; 
    } 
  	void traverse() 
    { 
        if (root != NULL) 
        	root->traverse(); 
    } 
  
    
    Node* search(int k) 
    { 
        if(root == NULL)
        	return root;
        else
        	return root->search(k);
    } 
  
    
    void insert(int k)
    {
    	if(root == NULL)
		{
			root = new Node(t, true);
			root->key[0] = k;
			root->n = 1;
		}

		else
		{
			if(root->n == (2 * t - 1))
			{
				Node * s = new Node(t, false);
				s->Child[0] = root;

				s->splitChildhild(0, root);

				int i = 0;

				if(s->key[0] < k)
					i = 1;

				s->Child[i]->insertNonFull(k);

				root = s;
			}

			else
				root->insertNonFull(k);
		}
    }

    void remove(int k)
    {
        if (!root) 
        { 
            cout << "The tree is empty\n"; 
            return; 
        } 
    
        root->remove(k); 
    
        if (root->n==0) 
        { 
            Node *tmp = root; 
            if (root->leaf) 
                root = NULL; 
            else
                root = root->Child[0]; 
    
            delete tmp; 
        } 
        return; 
    }
	
};


int main()
{
	BTree t(3); 
  
    t.insert(1); 
    t.insert(3); 
    t.insert(7); 
    t.insert(10); 
    t.insert(11); 
    t.insert(13); 
    t.insert(14); 
    t.insert(15); 
    t.insert(18); 
    t.insert(16); 
    t.insert(19); 
    t.insert(24); 
    t.insert(25); 
    t.insert(26); 
    t.insert(21); 
    t.insert(4); 
    t.insert(5); 
    t.insert(20); 
    t.insert(22); 
    t.insert(2); 
    t.insert(17); 
    t.insert(12); 
    t.insert(6); 
  
    cout<<"Traversal of tree constructed is\n"; 
    t.traverse(); 
    cout<<endl; 
  
    
    t.remove(2); 
    cout<<"Traversal of tree after removing 2\n"; 
    t.traverse(); 
    cout<<endl; 
  
    t.remove(16); 
    cout<<"Traversal of tree after removing 16\n"; 
    t.traverse(); 
    cout<<endl; 
  
	return 0;
}