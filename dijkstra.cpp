#include <bits/stdc++.h> 

using namespace std;
 

class Graph 
{ 
    int V;   
  
    list < pair<int, int> > *adj;


    
public: 
    Graph(int V)
    { 
        this->V = V; 
        adj = new list < pair<int, int> > [V]; 
    } 
  
    
    void addEdge(int v, int w, int wt)
    { 
        adj[v].push_back(make_pair(w, wt)); 
    } 

    void printGraph()
    {
        for(int i = 0; i < V; i++)
        {
            cout<<"For vertex "<<i<<" the adjacency list is : ";

            list <pair <int, int>> :: iterator j;

            for(j = adj[i].begin(); j != adj[i].end(); ++j)
            {
                cout<<"("<<(*j).first<<" - "<<(*j).second<<" ";
            }
            
            cout<<endl;
        }
    }

    int minDistance(int dist[], bool sptSet[]) 
    { 
        int min = INT_MAX, min_index; 
      
        for (int v = 0; v < V; v++) 
            if (sptSet[v] == false && dist[v] <= min) 
                min = dist[v], min_index = v; 
      
        return min_index; 
    } 

    void printSolution(int dist[]) 
    { 
        cout<<"Vertex \t\t Distance from Source \n"; 
        for (int i = 0; i < V; i++) 
            cout<<i<<" \t\t"<<dist[i]<<"\n"; 
    } 

    void dijkstra(int src)
    {
        int dist[V];

        bool sptSet[V];

        for (int i = 0; i < V; i++) 
        {
            dist[i] = INT_MAX;
            sptSet[i] = false; 
        }

        dist[src] = 0; 

        for (int count = 0; count < V - 1; count++) 
        { 
            int u = minDistance(dist, sptSet); 
      
            sptSet[u] = true; 
      
            
            for (int v = 0; v < V; v++) 
            {
                int vwt;
                for(auto it = adj[u].begin(); it != adj[u].end(); ++it)
                {
                    if((*it).first == v)
                    {
                        vwt = (*it).second;
                        if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + vwt < dist[v]) 
                            dist[v] = dist[u] + vwt; 
                    }
                }

            }
            
    } 
   
        printSolution(dist); 
    } 
};


int main() 
{ 
    Graph graph(5);
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 4, 2);
    graph.addEdge(1, 3, 3);
    graph.addEdge(1, 2, 3);
    graph.addEdge(3, 2, 5);
    graph.addEdge(3, 1, 1);
    graph.addEdge(4, 3, 1); 
  
    graph.dijkstra(0); 
  
    return 0; 
} 
      