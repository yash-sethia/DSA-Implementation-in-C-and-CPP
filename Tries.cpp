#include<iostream>
#include<cstring>
using namespace std;

#define MAX 26

struct TrieNode 
{ 
    struct TrieNode *child[MAX]; 
    bool endOfWord; 

    TrieNode()
    {
  
	    endOfWord = false; 
	  
	    for (int i = 0; i < MAX; i++) 
	        child[i] = NULL; 
    }
}; 

class Trie
{
	TrieNode * root;

public:
	Trie()
	{
		root = new TrieNode;
	}

	TrieNode * sendRoot()
	{
		return root;
	}

	void insert(string s)
	{
		TrieNode *pCrawl = root; 
	    for (int i = 0; i < s.length(); i++) 
	    { 
	        int index = s[i] - 'a'; 
	        if (!pCrawl->child[index]) 
	            pCrawl->child[index] = new TrieNode; 
	  
	        pCrawl = pCrawl->child[index]; 
	    } 
	    pCrawl->endOfWord = true; 
	}

	bool search(string s) 
	{ 
	    TrieNode *pCrawl = root; 
	  
	    for (int i = 0; i < s.length(); i++) 
	    { 
	        int index = s[i] - 'a'; 
	        if (!pCrawl->child[index]) 
	            return false; 
	  
	        pCrawl = pCrawl->child[index]; 
	    } 
	  
	    return (pCrawl != NULL && pCrawl->endOfWord); 
	} 

	bool isEmpty(TrieNode * root) 
	{ 
	    for (int i = 0; i < MAX; i++) 
	        if (root->child[i]) 
	            return false; 
	    return true; 
	} 

	TrieNode * remove(TrieNode * root, string s, int deapth = 0)
	{
		if(root == NULL)
			return root;

		if(deapth == s.length())
		{
			if(root->endOfWord)
				root->endOfWord = false;

			if(isEmpty(root))
			{
				delete root;
				root = NULL;
			}

			return root;
		}
		else
		{
			int idx = s[deapth] - 'a';
			root->child[idx] = remove(root->child[idx], s, deapth + 1);

			if(isEmpty(root) and !root->endOfWord)
			{
				delete(root);
				root = NULL;
			}

			return root;
		}
	}
};	

int main()
{
	string keys[] = { "why", "do", "people", 
                      "micro", "any", "by", 
                      "bye", "their", "plan", 
                      "planet", "the", "these", 
                      "hero" }; 

    int n = 13;
  
    Trie root; 
   


    for (int i = 0; i < n; i++) 
        root.insert(keys[i]); 


  
    if(root.search("the")) 
    	cout << "Yes 'the' is present \n";
    else
    	cout << "No 'the' is not present \n";
 

    if(root.search("these"))
    	 cout << "Yes 'these' is present \n";
    else
    	 cout << "No 'these is not present \n"; 
  

    root.remove(root.sendRoot(), "heroplane"); 


    if(root.search("hero")) 
    	 cout << "Yes 'hero' is present \n";
    else
		 cout << "No 'hero' is absent\n"; 
	return 0;
}