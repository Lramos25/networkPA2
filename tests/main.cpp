// imports
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <string>
#include <sstream>

using namespace std;


// driver function
int main(void) {



  
	int n = 3; //line one of file
	
	int** table = new int*[n];

	for (int i = 0; i < n; i++) {
		table[i] = new int[3];
	}


	//fill arrays
	int a = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			table[i][j] = a;
			a++;
		}
	}
  

	//print table

	for (int i = 0; i < n; i++) {
		cout << "\n";
		for (int j = 0; j < 3; j++) {
			cout << "\t" << table[i][j]; 
		}
	}


	//delete to unallocate memory **start at bottom then work up**
	for (int i = 0; i < n; i++) {
		delete[] table[i];
	}
	delete[] table;
	table = NULL;

	system("pause>0");
	return 0;
}

