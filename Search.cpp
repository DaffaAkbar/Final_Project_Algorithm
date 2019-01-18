#include<iostream>
#include<cstdlib>
#include <vector>
#include <time.h>
#include"Algo.h"
#include <string>
#include <fstream>

Search::Search():cost( 0 ) {
    ifstream mapFile;
    char text[50];
    cin >> text;
    mapFile.open( text, ios::in ); // user input the maze file
    if ( mapFile.is_open() )
    {
		// Initialize both maps
		
		for ( int i = 0; i < Rowsize; i++ ) {
			int j=0;
			while ( j < Colsize ) {
				mapFile >> Map [i][j];
				Route [i][j] = Map [i][j];
			   
				// Mark the beginning and exit coordinates
				if ( Map[i][j] == Starting ) {
					startingRow = i;
					startingCol = j;
				} else if ( Map[i][j] == Exit ) {
					exitCoordRow = i;
					exitCoordCol = j;
				}
				j++;
			}
		} 
		mapFile.close();
    } else {
        cout << "File is not found";
    }        
}

//search template

void Search::SearchTemplate( int exit ) {
	// Define which exit are we and the starting position
	if ( exit == Exit ) {
		startRow = startingRow;
		startCol = startingCol;
		exitRow = exitCoordRow;
		exitCol = exitCoordCol;
	} 
	
	// Load the starting coordinates into the open queue
	if( BFS ) {
		openVec.push_back( new Coord( startRow, startCol, 0, 0 ) );
	} else if ( AS ) {
		int functionF = abs( startRow - exitRow ) + abs( startCol - exitCol ); 
		openVec.push_back( new Coord( startRow, startCol, 0, functionF, 0 ) );
	}	else if (DJ){
		int functionF = abs( startRow - exitRow ) + abs( startCol - exitCol ); 
		openVec.push_back( new Coord( startRow, startCol, 0, functionF, 0 ) );
	}
	maxOpenQSize = 1;
	
	Route[startRow][startCol] = Open;
	
	// Keep track of where we are in the maze
	int row = 0;
	int col = 0;
	bool solve = false; // to know wheter we solve the maze or not
	
	// Keep searching an exit is determined or no solution is found
	while( openVec.size() != 0 ) {
		
		// Get the row and column of the current position
		row = openVec.front() -> getRow();
		col = openVec.front() -> getCol();
		
		Route[row][col] = Closed; 								// Current position has now been opened and explored
		cost++; 													// Increase cost for each node explored
		
		if( Map[row][col] == exit ) { 							// Check if we reach the destination or not
			
			closeVec.push_back( openVec.front() );
			openVec.erase(openVec.begin());
			solve = true;
			break; 													

		} else { 													// Destination is not yet reached so we must check surrounding nodes
			
			closeVec.push_back( openVec.front() );
			openVec.erase(openVec.begin());								
			
			SearchImplementation( row, col );
		}
	}
	
	if ( !solve ) { cout << "This maze has no solution!" << endl; }
	
	PrintResult();
}



void Search::SearchImplementation( int row, int col ) {
	// Use this method to push_back nodes for BFS and call insertion sort for A*
	int depth = ( closeVec.back() -> getDepth() ) + 1; 	// Depth of the next node will be +1 of the current node recently 
	Coord * parent = closeVec.back();					// Parent address is the previous node
		
	// Try left of the current position
	if ( ( col - 1 > -1 ) && Route[row][col - 1] != Blocked && Route[row][col - 1] != Closed && Route[row][col - 1] != Open ) {

		Route[row][col - 1] = Open;

		if ( BFS ) {
			openVec.push_back( new Coord( row, col - 1, depth, parent ) );

		}else if ( DJ ) {
			Dijkstra( row , col - 1, depth, parent );
		}
		 else if ( AS ) {
			AStar( row, col - 1, depth, parent );
		}
	}
	// Try above the current position
	if ( ( row - 1 > -1 ) && Route[row - 1][col] != Blocked && Route[row - 1][col] != Closed && Route[row - 1][col] != Open ) {
		
		Route[row - 1][col] = Open;
		
		if ( BFS ) {
			openVec.push_back( new Coord( row - 1, col, depth, parent ) );

		}else if ( DJ ) {
			Dijkstra( row - 1, col, depth, parent );
		}
		 else if ( AS ) {
			AStar( row - 1, col, depth, parent );
		}
	}
	// Try right of the current position
	if ( ( col + 1 < Colsize ) && Route[row][col + 1] != Blocked && Route[row][col + 1] != Closed && Route[row][col + 1] != Open ) {

		Route[row][col + 1] = Open;

		if ( BFS ) {
			openVec.push_back( new Coord( row, col + 1, depth, parent ) );

		}else if ( DJ ) {
			Dijkstra( row, col +1, depth, parent );
		}
		 else if ( AS ) {
			AStar( row, col + 1, depth, parent );
		}
	}
	// Try below the current position
	if ( ( row + 1 < Rowsize ) && Route[row + 1][col] != Blocked && Route[row + 1][col] != Closed && Route[row + 1][col] != Open ) {
		
		Route[row + 1][col] = Open;
		
		if ( BFS ) {
			openVec.push_back( new Coord( row + 1, col, depth, parent ) );

		}else if ( DJ ) {
			Dijkstra( row + 1, col, depth, parent );
		}
		 else if ( AS ) {
			AStar( row + 1, col, depth, parent );
		}
	}
	maxOpenQSize = ( openVec.size() > maxOpenQSize ) ? openVec.size() : maxOpenQSize;
}

void Search::Dijkstra( int row, int col, int depth, Coord * parent ) {
	

	int gN = depth;

	int functionF = gN;
	
	bool insertSuccess = false;
	
	// Use insertion sort to insert the element into vector according to highest priority ( ie. lowest functionF value )
	if ( openVec.size() == 0 ) {
	
		openVec.push_back( new Coord( row, col, depth, functionF, parent ) );
		
	} else {
		
		vector<Coord *>::iterator it;
		int i = 0;
		
		for ( it = openVec.begin(); it != openVec.end(); it++ ) {
			if ( functionF < openVec[i] -> getFunctionF() ) {
				openVec.insert( it, new Coord( row, col, depth, functionF, parent ) );
				insertSuccess = true;
				break;
			}
			i++;
		}
		if ( !insertSuccess ) {
			openVec.push_back	( new Coord( row, col, depth, functionF, parent ) );
		}	
	}
}
//A*search

void Search::AStar( int row, int col, int depth, Coord * parent ) {
	// A * Search uses a priority queue

	int gN = depth;
	int hN = abs( exitRow - row ) + abs( exitCol - col );//use manhattan bridge heuristic
	int functionF = gN + hN;
	
	bool insertSuccess = false;
	
	// Use insertion sort to insert the element into vector according to highest priority ( ie. lowest functionF value )
	if ( openVec.size() == 0 ) {
	
		openVec.push_back( new Coord( row, col, depth, functionF, parent ) );
		
	} else {
		
		vector<Coord *>::iterator it;
		int i = 0;
		
		for ( it = openVec.begin(); it != openVec.end(); it++ ) {
			if ( functionF < openVec[i] -> getFunctionF() ) {
				openVec.insert( it, new Coord( row, col, depth, functionF, parent ) );
				insertSuccess = true;
				break;
			}
			i++;
		}
		if ( !insertSuccess ) {
			openVec.push_back	( new Coord( row, col, depth, functionF, parent ) );
		}	
	}
}

void Search::PrintResult() {
	Coord * treeIterator;
	vector<Coord *> path;
	for ( treeIterator = closeVec.back(); treeIterator -> getParent() != 0; treeIterator = treeIterator -> getParent() ) {
		path.insert(path.begin(), treeIterator);
	}
	path.insert(path.begin(), treeIterator);
	
	cout << "Path Cost: " << path.size() << endl;
	cout << "Maximum Size of Open Queue: " << maxOpenQSize << endl;
	cout << "Total Cost: " << cost - 1 << endl;
	cout << "Total number of explored nodes: " << openVec.size() + closeVec.size() << endl;
}
void Search::PrintMaze() {
	// Building the path taken by the agent by climbing the tree from the exit state
	Coord * treeIterator;
	vector<Coord *> path;
	for ( treeIterator = closeVec.back(); treeIterator -> getParent() != 0; treeIterator = treeIterator -> getParent() ) {
		path.insert(path.begin(), treeIterator);
	}
	
	path.insert(path.begin(), treeIterator);
	std::ofstream outfile;
	char text[50];
    cin >> text;
	outfile.open(text, std::ios_base::app);
	for ( int i = 0; i < Rowsize; i++ ) {
        int j=0;
		while ( j < Colsize ) {
            
			if( Map [i][j] == Blocked ) outfile << "0";
            else if(Map [i][j] == Starting) outfile << "S";
            else if( Map [i][j] == Exit ) outfile << "E";
            else {
                 bool on_the_path = false;
                 int k = 0;
                 while (k < path.size()){
                      if( path[k] -> getRow() == i && path[k] -> getCol() == j ) on_the_path = true;
                      k++;
                 }
                 if( on_the_path ) outfile << "+";
                 else outfile << " ";
            }
        j++;
        }
        outfile << "\n";
      
    }
    
    cout << endl << endl;
}

void Search::CleanUp() {
	// Reinitialize the maze
	for ( int i = 0; i < Rowsize; i++ ) {
        for ( int j = 0; j < Colsize; j++ ) {
            Route [i][j] = Map[i][j];
        }
    }	
	openVec.clear();
	closeVec.clear();
	cost = 0;
	maxOpenQSize = 0;

}

void Search::SwitchSearch(int switchA) {
	// Specify the next search to be completed
	if ( switchA == 1 ) { 
		BFS = true;
		AS = false;
		DJ = false;
	} else if ( switchA == 2 ) {
		BFS = false;
		AS = true;
		DJ = false;	
	}else if ( switchA ==3 ) {
		BFS = false;
		AS = false;
		DJ = true;
	}
}

void Search::SelectSearch() {
	// Specify the what algorithm that want to be choose
	int switchA;
	int print;
	cout <<"------------------------------------------\n";
	cout <<"What kind of Algorithm do you want to use?"<<endl;
	cout <<"------------------------------------------\n";
	cout <<"\n\n";
	cout <<"-----------------------------------------------------------------\n";
	cout <<"Input 1 to use BFS, input 2 to use A* and input 3 to use Dijkstra\n";
	cout <<"-----------------------------------------------------------------\n";
	cout <<"\n\n";
	cin >>switchA;
	
	SwitchSearch(switchA);
	if ( BFS ) {
		cout<<  "--------------------\n";
		cout << "Using BFS Algorithm" << endl;
		cout << "--------------------\n" << endl;
		cout << "Searching...." << endl << endl;
		int start = clock();
    	SearchTemplate( Exit );
    	int end = clock();
    	cout << "it took " << end - start << "ticks, or " << ((float)end - start)/CLOCKS_PER_SEC << "seconds." << endl;
		cout <<"\n\n";
		cout <<"------------------------------\n" << endl;
		cout <<"do you want to print the maze?\n";
		cout <<"------------------------------\n" << endl;
		cout<<"\n\n";
		cout <<"-------------------------------------------------\n" << endl;
		cout <<"Input 1 to print and input any number to continue\n";
		cout <<"-------------------------------------------------\n" << endl;
		cin >> print;
    	if (print == 1){
    		cout <<"------------------------------------------------\n" << endl;
    		cout << "What file name do you want to put the result in ?"<<endl;
    		cout <<"------------------------------------------------\n" << endl;
    		PrintMaze();
		}else{
			//do nothing
			}	
		}
	

	else if ( AS) {
		cout << "-------------------\n" << endl;
		cout << "Using A* Algorithm" << endl;
		cout << "-------------------\n" << endl;
		cout << "Searching...." << endl;
		int w = clock();
		SearchTemplate( Exit );
		int e = clock();
    	cout << "it took " << e - w << "ticks, or " << ((float)e - w)/CLOCKS_PER_SEC << "seconds." << endl;
		cout <<"\n\n";
		cout <<"------------------------------\n" << endl;
		cout <<"do you want to print the maze?\n";
		cout <<"------------------------------\n" << endl;
		cout<<"\n\n";
		cout <<"-------------------------------------------------\n" << endl;
		cout <<"Input 1 to print and input any number to continue\n";
		cout <<"-------------------------------------------------\n" << endl;
		cin >> print;
    	if (print == 1){
    		cout <<"------------------------------------------------\n" << endl;
    		cout << "What file name do you want to put the result in ?"<<endl;
    		cout <<"------------------------------------------------\n" << endl;
    		PrintMaze();
		}
		else{
			//do nothing
		}
	}
	else if ( DJ) {
		cout << "-------------------\n" << endl;
		cout << "Using DJ Algorithm" << endl;
		cout << "-------------------\n" << endl;
		cout << "Searching...." << endl;
		int wd = clock();
		SearchTemplate( Exit );
		int ed = clock();
		cout << "it took " << ed - wd << "ticks, or " << ((float)ed - wd)/CLOCKS_PER_SEC << "seconds." << endl;
		cout <<"\n\n";
		cout <<"------------------------------\n" << endl;
		cout <<"do you want to print the maze?\n";
		cout <<"------------------------------\n" << endl;
		cout<<"\n\n";
		cout <<"-------------------------------------------------\n" << endl;
		cout <<"Input 1 to print and input any number to continue\n";
		cout <<"-------------------------------------------------\n" << endl;
		cin >> print;
    	if (print == 1){
    		cout <<"------------------------------------------------\n" << endl;
    		cout << "What file name do you want to put the result in ?"<<endl;
    		cout <<"------------------------------------------------\n" << endl;
    		PrintMaze();
		}
		else{
			//do nothing
		}
	}
}

