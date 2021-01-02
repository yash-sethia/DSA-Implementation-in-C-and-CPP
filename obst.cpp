#include <bits/stdc++.h> 

using namespace std; 

class node
{
public:
    int data;
    node *left;
    node *right;

    node(int d)
    {
        data = d;
        left = NULL;
        right = NULL;
    }
};
 
int sum(int freq[], int i, int j) 
{ 
	int s = 0; 
	for (int k = i; k <= j; k++) 
	s += freq[k]; 
	return s; 
}

node * creatOBST(int keys[], int freq[], int n, pair <int, int> cost[][5], int x, int y)
{
	if(cost[x][y].second == -1 or x > y)
		return NULL;


	node * root = new node(keys[cost[x][y].second]);

	root->left = creatOBST(keys, freq, n, cost, x, cost[x][y].second - 1);
	root->right = creatOBST(keys, freq, n, cost, cost[x][y].second + 1, y);

	return root;
}

node * optimalSearchTree(int keys[], int freq[], int n) 
{ 

	pair <int, int> cost[5][5]; 

	for (int i = 0; i < n; i++) 
		cost[i][i] = make_pair(freq[i], i); 


	for (int L = 2; L <= n; L++) 
	{ 
		for (int i = 0; i <= n-L+1; i++) 
		{ 
			int j = i+L-1; 
			cost[i][j] = make_pair(INT_MAX, -1); 

			for (int r = i; r <= j; r++) 
			{ 			 
			int c = ((r > i)? cost[i][r-1].first : 0) + ((r < j)? cost[r+1][j].first : 0) + sum(freq, i, j); 
			if (c < cost[i][j].first) 
				cost[i][j] = make_pair(c, r); 
			} 
		} 
	}

	return creatOBST(keys, freq, n, cost, 0, n - 1);

} 

bool searchBST(node * root, int key)
{
	if(root == NULL)
		return false;
	if(root->data > key)
		return searchBST(root->left, key);
	else if(root->data < key)
		return searchBST(root->right, key);
	
	return true;
}
node * insert(node  * root, int data)
{
	if(root == NULL)
	{
		root = new node(data); 
		return(root);
	}
	if(data < root->data)
		root->left = insert(root->left, data);
	else if(data > root->data)
		root->right = insert(root->right, data);

	return(root);
}

node * removeNode(node * root, int key)
{
	if(root == NULL)
		return NULL;

	if(root->data > key)
	{
		root->left = removeNode(root->left,key);
		return root;
	}
	else if(root->data < key)
	{
		root->right = removeNode(root->right, key);
		return root;
	}

	if(root->left == NULL and root->right == NULL)
	{
		delete root;
		return NULL;
	}
	else if(root->left != NULL and root->right == NULL)
	{
		node * left = root->left;
		delete(root);
		return left;
	}
	else if(root->left == NULL  and root->right != NULL)
	{
		node * right = root->right;
		delete(root);
		return right;
	}
	else 
	{
		node * replace = root->right;
		while(replace->left != NULL)
		{
			replace = replace->left;
		}

		root->data = replace->data;
		root->right = removeNode(root->right, replace->data);
		return root;
	}
}

void printPreorder(node * root)
{
	if(root == NULL)
		return;
	cout<<root->data<<" ";
	printPreorder(root->left);
	printPreorder(root->right);
}



int main() 
{ 
	int keys[] = {10, 12, 16, 21}; 
	int freq[] = {4, 2, 6, 3}; 
	cout<<"Keys \t\t Frequency"<<endl;
	int n = sizeof(keys)/sizeof(keys[0]);
	for(int i =0; i < n; i++)
	{
		cout<<" "<<keys[i]<<"\t\t    "<<freq[i]<<endl;
	}

	node * root = optimalSearchTree(keys, freq, n);

	cout<<"The preorder pf Optimal BST created is :";
	printPreorder(root);
	cout<<endl;

	if(searchBST(root, 12))
	{
		cout<<"12 is present in BST"<<endl;
	}
	else
	{
		cout<<"12 is not present in BST"<<endl;
	}
	if(searchBST(root, 30))
	{
		cout<<"30 is present in BST"<<endl;
	}
	else
	{
		cout<<"30 is not present in BST"<<endl;
	}

	insert(root, 30);
	cout<<"Added 30 in BST"<<endl;

	if(searchBST(root, 30))
	{
		cout<<"30 is present in BST"<<endl;
	}
	else
	{
		cout<<"30 is not present in BST"<<endl;
	}

	removeNode(root, 30);
	cout<<"Removed 30 from BST"<<endl;

	if(searchBST(root, 30))
	{
		cout<<"30 is present in BST"<<endl;
	}
	else
	{
		cout<<"30 is not present in BST"<<endl;
	}

	return 0; 
} 

