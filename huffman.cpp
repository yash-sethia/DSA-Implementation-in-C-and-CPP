#include <bits/stdc++.h> 

using namespace std; 

#define maxHeight 100 

struct Node 
{ 
	char data; 
	int freq; 
	Node *left, *right; 
}; 

struct MinHeap 
{ 
	int size; 
	int capacity; 
	Node** array; 
}; 

Node* newNode(char data, int freq) 
{ 
	Node* temp = new Node; 
	temp->left = temp->right = NULL; 
	temp->data = data; 
	temp->freq = freq; 
	return temp; 
} 

MinHeap* createMinHeap(int capacity) 
{
	MinHeap* minHeap = new MinHeap; 
	minHeap->size = 0; 
	minHeap->capacity = capacity; 
	minHeap->array = new Node*[minHeap->capacity];
	return minHeap; 
} 

void swapNode(Node** a, Node** b) 
{ 
	Node* t = *a; 
	*a = *b; 
	*b = t; 
} 

void minHeapify(MinHeap* minHeap, int idx) 
{
	int smallest = idx; 
	int left = 2 * idx + 1; 
	int right = 2 * idx + 2; 

	if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq) 
		smallest = left; 

	if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq) 
		smallest = right; 

	if (smallest != idx) { 
		swapNode(&minHeap->array[smallest], &minHeap->array[idx]); 

		minHeapify(minHeap, smallest); 
	} 
} 

int isSizeOne(MinHeap* minHeap) 
{
	return (minHeap->size == 1); 
}


Node* extractMin(MinHeap* minHeap) 
{
	Node* temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1]; 
	--minHeap->size; 

	minHeapify(minHeap, 0); 

	return temp; 
} 

void insertMinHeap(MinHeap* minHeap, Node* minHeapNode) 
{ 
	++minHeap->size; 
	int i = minHeap->size - 1; 

	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) 
	{ 
		minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
		i = (i - 1) / 2; 
	} 

	minHeap->array[i] = minHeapNode; 
} 
 
void buildMinHeap(MinHeap* minHeap) 
{ 
	int n = minHeap->size - 1; 
	int i; 
	for (i = (n - 1) / 2; i >= 0; --i) 
		minHeapify(minHeap, i); 
} 

void printArr(int arr[], int n) 
{ 
	int i; 
	for (i = 0; i < n; ++i) 
		cout<< arr[i]; 

	cout<<"\n"; 
} 

int isLeaf(Node* root) 
{ 
	return !(root->left) && !(root->right); 
} 

MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) 
{ 
	MinHeap* minHeap = createMinHeap(size); 

	for (int i = 0; i < size; ++i) 
		minHeap->array[i] = newNode(data[i], freq[i]); 

	minHeap->size = size; 
	buildMinHeap(minHeap); 

	return minHeap; 
} 


Node* buildHuffmanTree(char data[], int freq[], int size) 
{ 
	struct Node *left, *right, *top; 
 
	struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size); 

	while (!isSizeOne(minHeap)) 
	{ 
		left = extractMin(minHeap); 
		right = extractMin(minHeap); 

		top = newNode('@', left->freq + right->freq); 

		top->left = left; 
		top->right = right; 

		insertMinHeap(minHeap, top); 
	} 

	return extractMin(minHeap); 
} 

void printCodes(struct Node* root, int arr[], int top) 
{ 

	if (root->left) 
	{ 
		arr[top] = 0; 
		printCodes(root->left, arr, top + 1); 
	} 

	if (root->right) 
	{ 
		arr[top] = 1; 
		printCodes(root->right, arr, top + 1); 
	} 

	if (isLeaf(root)) { 

		cout<< root->data <<": "; 
		printArr(arr, top); 
	} 
} 

void HuffmanCodes(char data[], int freq[], int size) 
{ 
	struct Node* root = buildHuffmanTree(data, freq, size); 

	int arr[maxHeight], top = 0; 

	printCodes(root, arr, top); 
} 

int main() 
{ 

	char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' }; 
	int freq[] = { 5, 9, 12, 13, 16, 45 }; 

	int size = sizeof(arr) / sizeof(arr[0]); 

	HuffmanCodes(arr, freq, size); 

	return 0; 
} 
