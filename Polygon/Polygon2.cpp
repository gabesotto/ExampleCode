/* Author: Gabe Russotto
 * Algorithms Assignment 4
 * File: russottg-asssgn2
 * Description :
 * Implementation :
 */ 
  
/*Includes******************************/
#include <iostream> //For input/output 
#include <fstream> //For file read.
#include <cstdlib> //For exit()
#include <cstring> //for strcmp and string.c_str()
using namespace std; 

/*Classes**************************/
class Point{
private:
  float x, y;
public:
  //Zero arg constructor only, must set points later.
  Point(){
    this->x = 0;
    this->y = 0;
  }
  //Two arg constructor to set x and y.
  Point(float x, float y){
    this->x = x;
    this->y = y;
  }

  //Prints point
  void print(){
    cout << "(" << this->x << ", " << this->y << ")" << endl;
  }
  //Get x
  float getX(){
    return x;
  }
  //Get y
  float getY(){
    return y;
  }
  //Set x
  void setX(float x){
    this-> x = x;
  }
  //Set y
  void setY(float y){
    this-> y = y;
  }
  //Check if 2 points are equal.
  bool isEqual(Point p2){
    Point p1 = *this;
    float x1 =  p1.getX();
    float y1 =  p1.getY();
    float x2 =  p2.getX();
    float y2 =  p2.getY();
    if(x1 == x2 && y1 == y2)
      return true;
    else
      return false; 
  }
};

class Line{
private:
  Point p1;
  Point p2;
  int connected[50];  //contains the int representation of each line connected to this line. For later traversal. -1 is null line.
  bool visited;
public:
  Line(){
    this->p1 = p1;
    this->p2 = p2;
    for(int i = 0; i < 50; i++)
      this->connected[i] = -1;
    this->visited = false;
  }
  Line(Point p1, Point p2){
    this->p1 = p1;
    this->p2 = p2;
    for(int i = 0; i < 50; i++)
      this -> connected[i] = -1;
    this->visited = false;
  }
  
  Point getP1(){
    return p1;
  }
  
  Point getP2(){
    return p2;
  }

  void setPoints(Point p1, Point p2){
    this-> p1 = p1;
    this-> p2 = p2;
  }
  
  void setConnections(int array[], int arraySize){
    for(int i = 0; i < arraySize; i++)
      this->connected[i] = array[i];
  }
  
  bool isConnected(int j){
    Line l = *this;
    int i = 0;
    while(true){
      if(l.connected[i] == -1)
	return false;
      if(l.connected[i] == j)
	return true;
      i++;
    }
  }
  
  void setVisited(bool b){
    this->visited = b;
  }
  
  bool getVisited(){
    return visited;
  }

  void print(){
    cout << "(" << p1.getX() << "," << p1.getY() << ")" << "-----" << "(" << p2.getX() << "," << p2.getY() << ")" << endl; 
  }
  
  Point intersection(Line l2){
    //Null point to return if needed
    Point NULLPoint(-1, -1);
    Line l1 = *this;
    //Store values for easy equation to code conversion
    // 4 points for line 1
    float x1 = l1.getP1().getX();
    float y1 = l1.getP1().getY();
    float x2 = l1.getP2().getX();
    float y2 = l1.getP2().getY();
    
    //4 points for line 2
    float x3 = l2.getP1().getX();
    float y3 = l2.getP1().getY();
    float x4 = l2.getP2().getX();
    float y4 = l2.getP2().getY();
    
    //if distance is zero, no intersection return.
    float dist = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (dist == 0) 
      return NULLPoint;
    
    //Get x and y
    float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
    float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / dist;
    float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / dist;
    
    // Check if x and y coords are within both lines
    if ( x < min(x1, x2) || x > max(x1, x2) || x < min(x3, x4) || x > max(x3, x4) ) 
      return NULLPoint;
    if ( y < min(y1, y2) || y > max(y1, y2) || y < min(y3, y4) || y > max(y3, y4) ) 
      return NULLPoint;
    
    //Return point of intersection as a point
    Point ret(x,y);
    return ret;
  }
};

/*Prototypes*******************/
void greeting();
void readFile(int Edges[], float x[], float y[], int &xysize, int &edgeSize);
void inputToPoints(Point pArray[], float x[], float y[], int xySize);
void pointsToLines(Line lArray[], Point pArray[], int edges[], int edgeSize);
void checkIntersections(Line lArray[], Point intersectionArray[], int &arraySize, int &intersectionArraySize);
void removeElement(Line lArray[], int &sizeOfArray, int index);
void sliceOneLine(Line lArray[], int index, int &arraySize, Point POI);
void sliceBothLines(Line lArray[], int index1, int index2, int &arraySize, Point POI);
void setConnections(Line lArray[], int arraySize);

/* This is main dawg! ************/
int main(int argc, char **argv){

  int xySize = 10;
  int edgeSize = 42;
  float x[xySize]; //Array to hold all x polygon points.
  float y[xySize]; //Array to hold all y polygon points. 
  int edges[edgeSize]; //Array to hold edges of the form (i, j) where 
                       //Edges[n] = i, Edges[n+1] = j.
  Point pArray[xySize]; //Array of points to hold all points.
  Line lArray[edgeSize];//Array of lines to hold all lines (MAIN DATA STRUCTURE FOR REPRESENTING POLYS)
  Point intersectionArray[100]; //Array to hold all points of intersection
  int intersectionArraySize = 0;
  bool isPoly = false;  //Bool to hold weather the current loaded polygon is a polygon. 
  bool isConvex = false; //Bool to hold weather the current loaded polygon is convex.

  //Be polite and greet the user
  greeting();

  //Read a polygon from a file
  readFile(edges, x, y, xySize, edgeSize);

  //Put input from file into point class.
  inputToPoints(pArray, x, y, xySize);
  
  //Put attached points into line class.
  pointsToLines(lArray, pArray, edges, edgeSize);

  //check intersections then "spaghetti cuts" to add new lines to our line array "lArray"
  checkIntersections(lArray, intersectionArray, edgeSize, intersectionArraySize);
  
  //Now that extra points are added. Initalize connected array for each line in lArray.
  setConnections(lArray, edgeSize);
  
  
  //test code
  //cout << "new lArray size is " << edgeSize << endl;
  //for(int i = 0; i < edgeSize; i++)
  // lArray[i].print();
  //Split lines at intersections. Updatng lArray to hold new lines.
  
  //Next we check to see if the polygon is indeed a closed figure with no external lines.
  //isPoly = isPolygon();
  
  //If it is a polygon check if it is convex.
  //if(isPoly)
  //isConvex = isConvex();
  
  
  return 0;
}

/* Function Implementations ************/
void greeting() {
  cout << " (>^.^)> -Welcome to Gabe's Polygon Program- <(^.^<) " << endl;
}

void readFile(int Edges[], float x[], float y[], int &xysize, int &edgeSize){
  ifstream indata;
  string infile;
  string temp;
  xysize = 0;
  edgeSize = 0;

  //Retrieve file name from user.
  cout << "Please enter a file with polygon data: " << endl;
  cin >> infile;
  indata.open(infile.c_str());

  //check if file could be opened. 
  if(!indata){
    cerr << "Error: file could not be opened! TT.TT " << endl;
    exit(1);
  }
  
  string toInt; 
  int i = 0;
  //Get points in the form (x, y)
  while(indata >> temp){
    if(temp == "-")
      break;
    xysize++;
    toInt = temp[1];
    x[i] = atoi(toInt.c_str());
    toInt = temp[3];
    y[i] = atoi(toInt.c_str());
    i++;
  }

  //Done with points, get edges.
  i = 0;
  while(indata >> temp){
    edgeSize++;
    toInt = temp[1];
    Edges[i] = atoi(toInt.c_str());
    toInt = temp[3];
    Edges[i+1] = atoi(toInt.c_str());
    i += 2;
  }
}

void inputToPoints(Point pArray[], float x[], float y[], int xySize){
  for(int i = 0; i < xySize; i++){
    pArray[i].setX(x[i]);
    pArray[i].setY(y[i]);
  }
}

void pointsToLines(Line lArray[], Point pArray[], int edges[], int edgeSize){
  int blah = 0;
  for(int i = 0; i < edgeSize; i++){
    lArray[i].setPoints(pArray[edges[blah]], pArray[edges[blah+1]]);
    blah += 2;
  }  
}

void checkIntersections(Line lArray[], Point intersectionArray[], int &arraySize, int &intersectionArraySize){
  int k = 0;
  for(int i = 0; i < arraySize; i++){
    for(int j = i; j < arraySize; j++){
      Point NULLPoint(-1, -1);
      Point p1 = lArray[i].getP1();
      Point p2 = lArray[i].getP2();
      Point p3 = lArray[j].getP1();
      Point p4 = lArray[j].getP2();
      Point POI = lArray[i].intersection(lArray[j]); //Point of Intersection
      
      //If they Intersect.
      if(!NULLPoint.isEqual(POI)){
	  
	//If they are not endpoints of the first line.
	if(!p1.isEqual(POI) && !p2.isEqual(POI)){
	  //if array is empty, add it. (It seems all of our test cases have only 1 intersection. this case always happens.)
	  if(intersectionArraySize == 0){
	    intersectionArray[k] = POI;
	    intersectionArraySize++;
	    k++;
 
	    //intersection has been added slice lines appropriatly. 
	    if(p3.isEqual(POI) || p4.isEqual(POI)){
	      //Line is intersected by another lines endpoint, cut only the line being intersected.
	      //In this case that would be line i. ie lArray[i].
	      sliceOneLine(lArray, i, arraySize, POI);
	    }
	    else{
	      //2 Lines intersect somewhere besides the endpoint, cut both lines into two.
	      sliceBothLines(lArray, i, j, arraySize, POI);
	    }
	  }
	}
      }
    }
  }
}
//teeest meeeee
void removeElement(Line lArray[], int &sizeOfArray, int index){
  for(int i = index; i < sizeOfArray; ++i){
    lArray[i] = lArray[i+1];
  }
  sizeOfArray--;
}

void sliceOneLine(Line lArray[], int index, int &arraySize, Point POI){
  Line Line2Cut = lArray[index];
  Point p1 = Line2Cut.getP1();
  Point p2 = Line2Cut.getP2();
  Line newLine1(p1, POI);
  Line newLine2(POI, p2);
 
  //Remove old line.
  removeElement(lArray, arraySize, index);

  //Add 2 new lines
  lArray[arraySize++] = newLine1;
  lArray[arraySize++] = newLine2;
}
void sliceBothLines(Line lArray[], int index1, int index2, int &arraySize, Point POI){
  Line Line2Cut1 = lArray[index1];
  Line Line2Cut2 = lArray[index2];
  Point p1 = Line2Cut1.getP1();
  Point p2 = Line2Cut1.getP2();
  Point p3 = Line2Cut2.getP1();
  Point p4 = Line2Cut2.getP2();
  Line newLine1(p1, POI);
  Line newLine2(p2, POI);
  Line newLine3(p3, POI);
  Line newLine4(p4, POI);

  removeElement(lArray, arraySize, index1);
  removeElement(lArray, arraySize, index2);

  //add 4 new lines
  lArray[arraySize++] = newLine1;
  lArray[arraySize++] = newLine2;
  lArray[arraySize++] = newLine3;
  lArray[arraySize++] = newLine4;
  
}
void setConnections(Line lArray[], int arraySize){
  Point NULLPoint(-1,-1);
  int temp[50];
  int counter;

  
  for(int i = 0; i < arraySize; i++){
  
    //Every time line is changed, reset temp array to all -1.
    counter = 0;
    for(int k = 0; k < 50; k++){
      temp[i] = -1;
    }
    
    for(int j = 0; j < arraySize; j++){
      Point POI = lArray[i].intersection(lArray[j]);
      
      //If the lines intersect then they are connected. Update connected array.
      if(!NULLPoint.isEqual(POI)){
	temp[counter] = j;
	counter++;
      }
    }
    lArray[i].setConnections(temp, counter);
  }
}
/*EOF ******************************************/
