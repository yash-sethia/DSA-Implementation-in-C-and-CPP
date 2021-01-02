#include <bits/stdc++.h>
#include<list>

using namespace std;
#define V 4
 

int travllingSalesmanProblem(int graph[][V], int s)
{
    vector <int> vertex;
    for (int i = 0; i < V; i++)
        if (i != s)
            vertex.push_back(i);
 
    int min_path = INT_MAX;

    do {
        int current_pathweight = 0;
 
        int k = s;
        for (int i = 0; i < vertex.size(); i++) 
        {
            current_pathweight += graph[k][vertex[i]];
            k = vertex[i];
        }

        current_pathweight += graph[k][s];
 
        min_path = min(min_path, current_pathweight);
 
    }while (next_permutation(vertex.begin(), vertex.end()));
 
    return min_path;
}

int minKey(int key[], bool mstSet[])  
{  
    int min = INT_MAX, min_index;  
  
    for (int v = 0; v < V; v++)  
        if (mstSet[v] == false && key[v] < min)  
            min = key[v], min_index = v;  
  
    return min_index;  
}  
  

list <int> printMST(int parent[], int graph[V][V])  
{
    list <int> pre;
    list <int> temp;

    pre.push_back(0);
    temp.push_back(0);  

    while(!temp.empty()) 
    {
        for (int i = 1; i < V; i++) 
        {
            if(parent[i] == temp.front())
            {
                temp.push_back(i);
                pre.push_back(i);
            }
        }
        temp.pop_front();
    } 

    pre.push_back(0);

    return pre;
        
}  

int approxTSP(list <int> pre, int graph[V][V])
{
    int sum = 0;
    while(!pre.empty())
    {
        int s = pre.front();
        pre.pop_front();
        if(pre.empty())
            break;
        int e = pre.front();
        sum += graph[s][e];
    }

    return sum;
}

int travllingSalesmanProblemApprox(int graph[V][V])  
{   
    int parent[V];  
       
    int key[V];  
       
    bool mstSet[V];  
  
    for (int i = 0; i < V; i++)  
    {
        key[i] = INT_MAX;
        mstSet[i] = false;  
    }
  
    key[0] = 0;  
    parent[0] = -1;  
    
    for (int count = 0; count < V - 1; count++) 
    {  
        int u = minKey(key, mstSet);  
  
        mstSet[u] = true;  
  
        for (int v = 0; v < V; v++)  
            if (graph[u][v] != 0 && mstSet[v] == false && graph[u][v] < key[v]) 
            {  
                parent[v] = u;
                key[v] = graph[u][v];
            }  

    }  

    list <int> pre = printMST(parent, graph);

    return approxTSP(pre, graph);
}  


 
int main()
{
    int graph[][V] = { { 0, 10, 15, 20 },
                       { 10, 0, 35, 25 },
                       { 15, 35, 0, 30 },
                       { 20, 25, 30, 0 } };
    int s = 0;
    int app = travllingSalesmanProblemApprox(graph);
    int opt = travllingSalesmanProblem(graph, s);
    cout<<"Minimum cost of the path for the traveller is : "<<opt<<endl;
    cout<<"Approx solution is : "<<app<<endl;

    int err = (app - opt) * 100 / opt ;

    cout<<"With an error of "<<err<<"%";


    return 0;
}