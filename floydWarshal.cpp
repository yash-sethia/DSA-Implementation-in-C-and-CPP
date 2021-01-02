// C++ Program for Floyd Warshall Algorithm 
#include <bits/stdc++.h> 
using namespace std; 

#define V 4 
#define X 999999

void printShortestDistance(int arr[][V]) 
{ 
	cout<<"The following matrix shows the shortest distance between every pair of vertices \n"; 
	for (int i = 0; i < V; i++) 
	{ 
		for (int j = 0; j < V; j++) 
		{ 
			if (arr[i][j] == X) 
				cout<<"X"<<"	 "; 
			else
				cout<<arr[i][j]<<"	 "; 
		} 
		cout<<endl; 
	} 
}  

void floydWarshall (int graph[][V]) 
{ 
	int arr[V][V], i, j, k; 

	for (i = 0; i < V; i++) 
		for (j = 0; j < V; j++) 
			arr[i][j] = graph[i][j]; 

	for (k = 0; k < V; k++) 
	{  
		for (i = 0; i < V; i++) 
		{ 
			for (j = 0; j < V; j++) 
			{ 
				if (arr[i][k] + arr[k][j] < arr[i][j]) 
					arr[i][j] = arr[i][k] + arr[k][j]; 
			} 
		} 
	} 

	printShortestDistance(arr); 
} 


int main() 
{
	int graph[V][V] = { {0, 5, X, 10},
						{X, 0, 3, X},
						{X, X, 0, 1},
						{X, X, X, 0}
					}; 

	floydWarshall(graph); 
	return 0; 
} 

