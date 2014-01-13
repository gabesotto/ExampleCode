#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

class Graph{
private:
  bool** adjacencyMatrix;
  int vertexCount;
public:
  //Constructor
  Graph(int vertexCount){
    //initialize private class members 
    this->vertexCount = vertexCount;
    adjacencyMatrix = new bool*[vertexCount];
    //loop through adjacencyMatrix setting all elements to false.
    for(int i = 0; i < vertexCount; i++){
      adjacencyMatrix[i] = new bool[vertexCount];
      for(int j = 0; j < vertexCount; j++){
	adjacencyMatrix[i][j] = false;
      }
    }
  }

  //Adds edge to graph data structure.
  void addEdge(int i, int j){
    if(i >= 0 && i < vertexCount && j < vertexCount && j >= 0){
	adjacencyMatrix[i][j] = true;
	adjacencyMatrix[j][i] = true;
      }
    
  }

  //removes edge from graph data structure.  
  void removeEdge(int i, int j){
    if(i >= 0 && i < vertexCount && j < vertexCount && j >= 0){
	adjacencyMatrix[i][j] = false;
	adjacencyMatrix[j][i] = false;
      }
  }

    //returns true if edge exists
  bool isEdge(int i, int j){
    if(i >= 0 && i < vertexCount && j < vertexCount && j >= 0){
	return adjacencyMatrix[i][j];
      }else{
	return false;
      }
  }

  //De-constructor
  ~Graph() {
    for(int i = 0; i < vertexCount; i++)
      delete[] adjacencyMatrix[i];
    delete[] adjacencyMatrix;
  }
};

int main(int argc, char**argv){

  char infile[50]; //string to hold filename from user
  ifstream indata; //input file stream to open file.

  //Obtain filename for input of graph data
  cout << "Please enter a file with graph data: " << endl;
  cin >> infile;
  indata.open(infile);

  //file could not be opened, also exits, preventing buffer overload.
   if(!indata){
    cerr << "Error: file could not be opened!" << endl;
    exit(1);
   }

   int temp = 0;    //temp variable for read
   int Array[1000]; // Array to hold data from file.
   int i = 0;       // Iterator
   
   while(indata >> temp){
     Array[i] = temp;
     i++;
   }
   indata.close;

   int vertexCount = Array[0]; //number of verticies in graph from file.

   
}

