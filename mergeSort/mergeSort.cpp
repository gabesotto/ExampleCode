/*
 * Author: Gabe Russotto (SID: 810-86-6788)
 */
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;
void merge(int array[], int left, int right);
void mergeSort(int array[], int left, int right);
int main( int argc, const char* argv[] )
{
  char infile[50]; //string to hold filename from user
  ifstream indata; //input file stream to open file
  //Obtain filename for input of unsorted array
  cout << "Please enter a file for sorting" << endl;
  cin >> infile;
  indata.open(infile);
  //file could not be opened, also exits, preventing a buffer overload. 
  if(!indata){
    cerr << "Error: file could not be opened" << endl;
    exit(1);
  }
  int temp = 0; //Temporary variable for file read.
  int Array [10000]; // Array to hold ints from file.
  int noe = 0; //Number of Elements (noe)
  //Store elements from file into array.
  while(indata >> temp){
    Array[noe] = temp;
    noe++;
  }
  indata.close();
  // call to mergeSort to sort array.
  mergeSort(Array, 0, noe);
  //output array and algo. stats to file output.txt
  ofstream outfile("output.txt");
  outfile << "Length: " << noe << endl;
 
  for(int i = 0; i < noe; i++){
    outfile << Array[i] << endl;
  }
  outfile.close();
  exit(0);
}
void merge(int A[], int left, int right){
  int mid = floor((left+right)/2);
  int i1 = 0;  //Begining
  int i2 = left;  //Left
  int i3 = mid + 1; //Mid
  
  int temp[right - left + 1];
  
  //merge  the two arrays in sorted form
  while(i2 <= mid && i3 <= right){
    if(A[i2] < A[i3])
      temp[i1++] = A[i2++];
    else
      temp[i1++] = A[i3++];
  }
  
  //Merge the remaining elements in left array
  while(i2 <= mid)
    temp[i1++] = A[i2++];
  
  //Move from temp array to final array
  for( int i = left; i <= right; i++)
    A[i] = temp[i-left];
}
void mergeSort(int A[], int left, int right){
  if( left < right){
    int mid = floor((left + right)/2);
    mergeSort(A, left, mid);
    mergeSort(A, mid + 1, right);
    merge(A, left, right);
  }
}
