 #include <bits/stdc++.h> 

using namespace std; 

#define V 5 

int minKey(int key[], bool mstSet[]) 
{  
	int min = INT_MAX, min_index; 

	for (int v = 0; v < V; v++) 
		if (mstSet[v] == false && key[v] < min) 
			min = key[v], min_index = v; 

	return min_index; 
} 
 
void printMST(int parent[], int graph[V][V]) 
{ 
    int edge_count = 0;
	for (int i = 1; i < V; i++) 
        cout<<"Edge "<<edge_count++<<":("<<parent[i]<<", "<<i<<") cost : "<<graph[i][parent[i]]<<"\n";
} 


void primMST(int graph[V][V]) 
{ 
	int parent[V]; 
	
	int key[V]; 
	
	bool mstSet[V]; 

	for (int i = 0; i < V; i++) 
		key[i] = INT_MAX, mstSet[i] = false; 

	key[0] = 0; 
	parent[0] = -1; 

	for (int count = 0; count < V - 1; count++) 
	{ 
		int u = minKey(key, mstSet); 

		mstSet[u] = true; 

		for (int v = 0; v < V; v++) 
			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) 
				parent[v] = u, key[v] = graph[u][v]; 
	} 

	printMST(parent, graph); 
} 



int parent[V];

int find(int i) 
{ 
    while (parent[i] != i) 
        i = parent[i]; 
    return i; 
} 
  
void union1(int i, int j) 
{ 
    int a = find(i); 
    int b = find(j); 
    parent[a] = b; 
} 
   
void kruskalMST(int cost[][V]) 
{ 
    int mincost = 0; 
  
    for (int i = 0; i < V; i++) 
        parent[i] = i; 
  
    int edge_count = 0; 
    while (edge_count < V - 1) { 
        int min = INT_MAX, a = -1, b = -1; 
        for (int i = 0; i < V; i++) { 
            for (int j = 0; j < V; j++) { 
                if (find(i) != find(j) && cost[i][j] < min) { 
                    min = cost[i][j]; 
                    a = i; 
                    b = j; 
                } 
            } 
        } 
  
        union1(a, b); 
        cout<<"Edge "<<edge_count++<<":("<<a<<", "<<b<<") cost : "<<min<<"\n"; 
        mincost += min; 
    } 
    cout<<"\n Minimum cost= "<<mincost<<"\n"; 
}


int main() 
{ 

	int graph[][V] = { 
        { INT_MAX, 2, INT_MAX, 6, INT_MAX }, 
        { 2, INT_MAX, 3, 8, 5 }, 
        { INT_MAX, 3, INT_MAX, INT_MAX, 7 }, 
        { 6, 8, INT_MAX, INT_MAX, 9 }, 
        { INT_MAX, 5, 7, 9, INT_MAX }, 
    };  

    cout<<"Prim's Algorithm : - "<<endl;

	primMST(graph); 

	cout<<"Krushkal's Algorithm : - "<<endl;

	kruskalMST(graph);

	return 0; 
} 
