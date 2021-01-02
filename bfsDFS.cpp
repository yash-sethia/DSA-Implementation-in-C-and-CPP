#include <bits/stdc++.h> 

using namespace std; 
   
class Graph 
{ 
    int V;   
  
    list <int> *adj;
    list <int> *adjrev; 


    void DFSUtil(int v, bool *visited)
    {
        visited[v] = true;
     
        list<int>::iterator i;

        for (i = adj[v].begin(); i != adj[v].end(); ++i)
            if (!visited[*i])
                DFSUtil(*i, visited);
    }

    void DFSUtilrev(int v, bool *visited)
    {
        visited[v] = true;
     
        list<int>::iterator i;

        for (i = adjrev[v].begin(); i != adjrev[v].end(); ++i)
            if (!visited[*i])
                DFSUtil(*i, visited);
    }


public: 
    Graph(int V)
    { 
        this->V = V; 
        adj = new list <int> [V]; 
        adjrev = new list <int> [V];
    } 
  
    
    void addEdge(int v, int w)
    { 
        adj[v].push_back(w);
        adjrev[w].push_back(v);  
    } 

    void printGraph()
    {
        for(int i = 0; i < V; i++)
        {
            cout<<"For vertex "<<i<<" the adjacency list is : ";

            list <int> :: iterator j;

            for(j = adj[i].begin(); j != adj[i].end(); ++j)
            {
                cout<<(*j)<<" ";
            }
            
            cout<<endl;
        }
    }
  
    void BFS(int s)
    { 
        bool *visited = new bool[V]; 
        for(int i = 0; i < V; i++) 
            visited[i] = false; 
      
        list <int> queue; 
      
        visited[s] = true; 

        queue.push_back(s); 
      
        list <int> :: iterator i; 
      
        while(!queue.empty()) 
        { 
            s = queue.front(); 
            cout << s << " "; 
            queue.pop_front(); 
      
            for (i = adj[s].begin(); i != adj[s].end(); ++i) 
            { 
                if (!visited[*i]) 
                { 
                    visited[*i] = true; 
                    queue.push_back(*i); 
                } 
            } 
        }
        cout<<endl; 
    }

    bool * DFS(int v) 
    {
        bool* visited = new bool[V];

        for (int i = 0; i < V; i++)
            visited[i] = false;
 
        DFSUtil(v, visited);

        return visited;
    }

    bool * DFSrev(int v) 
    {
        bool* visited = new bool[V];

        for (int i = 0; i < V; i++)
            visited[i] = false;
 
        DFSUtilrev(v, visited);

        return visited;
    }

    bool isConnected()
    {
        bool * visited = DFS(0);
        bool * visitedRev = DFSrev(0);

        for(int i = 0; i < V; i++)
        {
            if(!visited[i] and !visitedRev[i])
                return false;
        }

        return true;
    }
      
}; 
  

int main() 
{ 
    Graph g(4); 
    g.addEdge(0, 1); 
    g.addEdge(0, 2); 
    g.addEdge(1, 2); 
    g.addEdge(2, 0); 
    g.addEdge(2, 3); 
    g.addEdge(3, 3); 

    g.printGraph();
  
    cout<<"Following is Breadth First Traversal to find vertex reachable from 2 "<<"\n"; 
    g.BFS(2); 

    if(g.isConnected())
    {
        cout<<"Graph is connected"<<endl;
    }
    else
    {
        cout<<"Graph is not connected"<<endl;
    }
  
    return 0; 
} 