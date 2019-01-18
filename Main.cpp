#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include <time.h>
#include "Search.cpp"

using namespace std;

//main

int main() {
	int quit = 0;
	cout<<" --------------------------------------------\n";
	cout<<"|    Welcome to Maze Solver Program          |\n";
	cout<<" --------------------------------------------\n";
	cout<<" ----------------------------------------------\n";
	cout<<"| Please enter the file that you want to solve |\n";
	cout<<" ----------------------------------------------\n";
	Search * search = new Search();
	while(true){
		search -> SelectSearch();
		cout <<"--------------------------------\n" << endl;
		cout <<"do you want to quit the program?\n";
		cout <<"--------------------------------\n" << endl;
		cout<<"\n\n";
		cout <<"-----------------------------------------------------------------\n" << endl;
		cout <<"Input 1 exit the program and input any number to continue Solving\n";
		cout <<"-----------------------------------------------------------------\n" << endl;
		cin >>quit;
		if (quit==1){
			exit(1);
		}
		else{
			system("CLS");
		}
		search -> CleanUp();

	}	
}
