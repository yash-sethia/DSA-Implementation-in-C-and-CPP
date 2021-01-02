#include<iostream>
#include<cstring>

using namespace std;


#define MAX 100

class Node
{ 
    string identifier, scope, type; 
    int lineNo; 
    Node* next; 
  
public: 
    Node() 
    { 
        next = NULL; 
    } 
  
    Node(string key, string value, string type, int lineNo) 
    { 
        this->identifier = key; 
        this->scope = value; 
        this->type = type; 
        this->lineNo = lineNo; 
        next = NULL; 
    } 
  
    void print() 
    { 
        cout<<"Identifier's Name:"<<identifier<<endl;
        cout<<"Type: "<<type<<endl;
        cout<<"Scope: "<<scope<<endl;
        cout<<"Line Number: "<<lineNo<<endl; 
        cout<<endl;
    } 
    friend class HashTable; 
};




class HashTable 
{

    Node* head[MAX]; 
  
public: 
    HashTable() 
    { 
        for (int i = 0; i < MAX; i++) 
            head[i] = NULL; 
    } 
  

    int hashf(string id)
    {
    	int aSum = 0; 
	    for (int i = 0; i < id.length(); i++) 
	    { 
	        aSum = aSum + id[i]; 
	    } 
	  
	    return (aSum % 100); 
    }


    bool insert(string id, string scope, string Type, int lineno)
    {
    	int index = hashf(id); 
	    Node* p = new Node(id, scope, Type, lineno); 
	  
	    if (head[index] == NULL) 
	    { 
	        head[index] = p; 
	        cout<<"Inserting "<<id<<endl; 
	  
	        return true; 
	    } 
	  
	    else 
	    { 
	        Node* start = head[index];


	        while (start->next != NULL) 
	            start = start->next; 
	  
	        start->next = p; 
	        cout<<endl<<" Inserting "<<id<<endl<<endl; 
	        return true; 
	    } 
        cout<<endl;
	    return false;
    } 

  
    string find(string id)
    {
    	int index = hashf(id); 
	    Node* start = head[index]; 
	  
	    if (start == NULL) 
	        return "-1"; 
	  
	    while (start != NULL) 
	    { 
	  
	        if (start->identifier == id) 
	        { 
	            cout<<"Found at index = "<<index<<endl<<endl;
	            start->print(); 
	            return start->scope; 
	        } 
	  
	        start = start->next; 
	        index++;
	    } 
	  
	    return "-1"; 
    }
  

    bool deleteRecord(string id)
    {
	    int index = hashf(id); 
	    Node* tmp = head[index]; 
	    Node* par = head[index]; 
	  
	    if (tmp == NULL)  
	        return false; 


	    if (tmp->identifier == id && tmp->next == NULL) 
	    { 
	        delete tmp; 
	        return true; 
	    } 

	  
	    while (tmp->identifier != id && tmp->next != NULL) 
	    { 
	        par = tmp; 
	        tmp = tmp->next; 
	    } 


	    if (tmp->identifier == id) 
	    { 
	        par->next = tmp->next; 
	        tmp->next = NULL; 
	        delete tmp; 
	        return true; 
	    } 
	  	else
	    	return false; 

    }
  
    bool modify(string id, string scope, string Type, int lineno)
    {
    	int index = hashf(id); 
	    Node* start = head[index]; 
	  
	    if (start == NULL) 
	        return false; 
	  
	    while (start != NULL) 
	    { 
	        if (start->identifier == id) 
	        { 
	            start->scope = scope; 
	            start->type = Type; 
	            start->lineNo = lineno; 
	            return true; 
	        } 


	        start = start->next; 
	    } 
	  
	    return false; 
    } 


    void printHashTable()
    {
        for(int i = 0; i < MAX; i++)
        {
            Node * p = head[i];
            while(p != NULL)
            {
                p->print();
                //cout<<i<<endl<<endl;
                p = p->next;
            }
        }
    }


};



int main() 
{ 
    HashTable st; 
    string check; 

    cout<<st.hashf("delete")<<endl<<endl<<endl;
    cout<<st.hashf("temp")<<endl<<endl<<endl;

    cout<<"------ SYMBOL TABLE ------"<<endl; 
  


    if (st.insert("delete", "local", "keyword", 4)) 
        cout<<" 'delete' inserted successfully"<<endl; 
    

    else
        cout<<"ERROR : Failed to insert."<<endl; 


 	cout<<endl<<endl;


    if (st.insert("temp", "global", "variable", 2)) 
        cout<<" 'temp' inserted successfully"<<endl; 
    

    else
        cout<<"ERROR : Failed to insert"<<endl; 



 	cout<<endl<<endl;


    st.printHashTable();


  
    check = st.find("delete"); 



 	cout<<endl<<endl;


    if (check != "-1") 
        cout<<endl<<" 'delete' Is present"<<endl; 
    
    else
        cout<<"'delete' is Not Present"<<endl;



 	cout<<endl<<endl;



    if (st.deleteRecord("delete")) 
        cout<<"'delete' Identifier is deleted "<<endl; 
    
	else
        cout<<"Failed to delete "<<endl; 



 	cout<<endl<<endl;
  
    

    if (st.modify("temp", "global", "variable", 3)) 
        cout << "'temp' Identifier updated "<<endl; 




 	cout<<endl<<endl;

 	
  
    check = st.find("number"); 
    
	
	if (check != "-1") 
        cout<<"'temp' Identifier Is present"<<endl; 
    
	else
        cout<<"Identifier Not Present"<<endl; 
  
    return 0; 
} 
  
 