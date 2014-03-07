
// Daniel Newman
// danielnewman@umich.edu


#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <queue>

using namespace std;


struct listnode {struct listnode * next; 
				 int vertexnumber;};

//returns an integer showing edge length from vertex i to vertex j
int getMatrixEdgeLength(int *matrix,int n, int i, int j)
{
	return *(matrix+i*n+j);
}

//returns the length of a path from the first to last vertices listed in a linked list
int getLinkedListLength(listnode* start, int n, int *dist)
{
	int length = 0;
	listnode* tempNode = new listnode;
	tempNode = start;
	while (tempNode->next != NULL)
	{
		length += getMatrixEdgeLength(dist,n,tempNode->vertexnumber,tempNode->next->vertexnumber);
		tempNode = tempNode->next;
	}
	return length;
}

//Copies a linked list and adds a node with value vertexNumToAdd
struct listnode *copyListAndAddNode(listnode *inputList, int vertexNumToAdd)
{
	listnode *tmp = new listnode;
	tmp = inputList;
	listnode *copy = new listnode;
	listnode *copyStart = copy;

	
	while (tmp != NULL)
	{
		copy->vertexnumber = tmp->vertexnumber;
		tmp = tmp->next;
		copy = copy->next = new listnode;
	}
	copy->vertexnumber = vertexNumToAdd;
	copy->next = NULL;
	return copyStart;
}


//Returns a linked list of vertices with the shortest path from s to t
struct listnode *shortest_path(int n, int s, int t, int *dist)
{
	// n: the number of vertices of the graph,
	// s: the start vertex,
	// t: the target vertex
	// dist: the matrix of edgelengths.

	int* distancesS_T = new int[n]; //array to hold distances to all points from starting point
	
	//Declare array of pointers to listnodes that will hold the current path to each node
	listnode** shortestPaths = new listnode*[n];

	//Initialize the initial distances
	for(int i = 0; i < n; i++)
	{
		listnode* tempNode = new listnode;
		listnode* tempNode2 = new listnode;
		tempNode->vertexnumber = i;
		tempNode->next = NULL;
		tempNode2->next = tempNode;
		tempNode2->vertexnumber = s;
		shortestPaths[i]=tempNode2;
		distancesS_T[i] = getMatrixEdgeLength(dist,n,s,i);
	}

	int tempInt;
	//increment through each vertex and update distances each time
	for(int i = 0; i < n; i++)
	{
		for(int j = 1; j < n; j++)
		{
			tempInt = getMatrixEdgeLength(dist,n,(i+s)%n,j)+distancesS_T[(i+s)%n];
			if (distancesS_T[j] > tempInt)
			{
				distancesS_T[j] = tempInt;
				shortestPaths[j] = copyListAndAddNode(shortestPaths[(i+s)%n],j);
			}
		}
	}

	return shortestPaths[t];
}

//Test function
int main(void)
{  int dist[1000][1000];
   int i,j;
   struct listnode *tmp;
   for(i=0; i< 1000; i++)
     for( j =0; j< 1000; j++ )
     {  if( i<500 && j<500 )
           dist[i][j] = 110 + ((i*i +j*j + 13*(i+j) )%20);
        else
           dist[i][j] = 200 + ((i*i +j*j + 13*(i+j) )%20);
     }


   for(i=0; i< 1000; i++)
     dist[i][i]=0;
   for(i=0; i< 100; i++)
   {  dist[i][2*i+1] = 15; dist[2*i+1][i] = 15;
      dist[i][2*i+2] = 15; dist[2*i+2][i] = 15;
   }
   dist[0][128] = 100; dist[128][0]=100;
   dist[128][500] = 1; dist[500][128]= 1;
   for( i = 0; i< 100; i++)
   {  dist[300+ (7*i)%100][300+(7*i+7)%100] = 1; 
      dist[300+ (7*i+7)%100][300+(7*i)%100] = 1; 
      dist[300+i][450] = 2; dist[450][300+1] = 2;
   }
   for(i=502; i<900; i++)
   { dist[450][i] = 3; dist[i][450]=3;
     dist[500][i] = 2;   dist[i][500]=2;
     dist[501][i] = 10; dist [i][501] = 10;
   }
   dist [500][900] = 50; dist[900][500]=50;
   dist [899][900] = 49; dist[899][900]=49;
   dist [900][999] = 1; dist [999][900] = 1;
   printf("constructed distance matrix for graph with 1000 vertices\n");
   tmp =  shortest_path(1000, 0, 999, &(dist[0][0]));
   printf("The shortest path from 0 to 999 uses the vertices\n");
   while( tmp != NULL )
   {  printf("%d, ", tmp->vertexnumber);
      tmp = tmp->next;
   }
   printf("End test\n");
   exit(0);
} 

