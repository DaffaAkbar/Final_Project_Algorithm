#include <iostream>
#include<cstdlib>
#include <vector>
#include <fstream>

using namespace std;

static const int Rowsize = 305;
static const int Colsize = 305; 

// Used to define different blocks on the map
static const int Empty 		= 1; 	// Empty space
static const int Starting 	= 4;	// Starting position
static const int Blocked 	= 0;	// Represents a maze wall
static const int Open 		= 6;	// Node added to open queue but not expanded yet
static const int Closed 	= 7;	// After node is expanded and explores other nodes around it
static const int Exit 		= 5;	// Exit marked E1

// Flags for keeping track of which search technique we are using
static bool BFS = true; 	
static bool DJ = false;
static bool AS = false;  	

class Coord 								// Hold coordinates and attributes of places in the maze
{
	private:
            int row;
			int col;               	// Store the position of the agent
			int depth;						// Store the agent's current depth
			int functionF;					// f(n) = g(n) + h(n) , this is the estimated total path cost
			Coord * parent;					// Keep track of parent address
			
	public:
			// Constructor used for BFS
            Coord( int row, int col, int depth, Coord * parent ) {	
				this->row = row;
				this->col = col;
				this->depth = depth;
				this->parent = parent;
			}
			
			// Constructor used for A* search and Dijsktra
			Coord( int row, int col, int depth, int functionF, Coord * parent ) {	
				this->row = row;
				this->col = col;
				this->depth = depth;
				this->functionF = functionF;
				this->parent = parent;
			}
			
			// Delete the pointer to the parent node
			~Coord() { delete parent; }
			
			// Accessor methods
			int getRow() { return row; };
			int getCol() { return col; };
			int getDepth() { return depth; };
			int getFunctionF() { return functionF; };
			Coord * getParent() { return parent; };
};

//search func

class Search 
{
	private:
			
			int Map [Rowsize][Colsize];					// Two dimensional array for mapping the original maze
			int Route [Rowsize][Colsize]; 				// Two dimensional array for keeping track of open and closed nodes
            
            int startRow; 
			int startCol;     	// Store the starting position of the agent
			int startingRow; 
			int startingCol;	// Store the starting position for searching the destination point
			int exitRow; 
			int exitCol;			// Store exit coordinates
			int exitCoordRow; 
			int exitCoordCol;		
			int cost;						// Total number of moves made
			int maxOpenQSize; 				// Keep track of maximum open queue size to report on memory performance
			
	
			vector<Coord *> openVec;
			vector<Coord *> closeVec;	
			
	public:
            Search();
			
			void SearchTemplate( int );
			void SearchImplementation( int, int );
			void Dijkstra ( int, int, int, Coord * );
			void AStar( int, int, int, Coord * );
			void PrintResult();
			void PrintMaze();
			void CleanUp();
			void SwitchSearch(int);
			void SelectSearch();
};
