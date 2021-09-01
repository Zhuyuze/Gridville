#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

int* task1(int** matrix, int m, int n, int h) {
	int* results = new int[4];	
	bool** mem = new bool*[m];
	for (int i = 0; i < m; i++) {
		mem[i] = new bool[n];
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] >= h) mem[i][j] = true;
			else mem[i][j] = false;
		}
	}
	int count = 0, side = 1, currentSide = 0;
	for (int k = 0; k < m; k++) {
		for (int i = 0; i < m - side; i++) {
			for (int j = 0; j < n - side; j++) {
				mem[i][j] = mem[i][j] && mem[i][j+1] && mem[i+1][j] && mem[i+1][j+1];
				if (mem[i][j]) {
					count++;
					if (side > currentSide) {
						results[0] = i;
						results[1] = j;
						results[2] = i + side;
						results[3] = j + side;
						currentSide = side;
					}
				}
			}	
		}
		if (count < 4) break;
		side++;
		count = 0;
	}	
	for (int i = 0; i < m; i++) delete[] mem[i];
	delete[] mem;
	return results;
}


int* task2alt(int** matrix, int m, int n, int h) {
	int* results = new int[4];
	int side = -1;
	int* mem = new int[n];
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] >= h) mem[j] += 1;
			else mem[j] = 0;
		}
		int counter = 0;
		for (int tside = 0; tside < n; tside++) {
			for (int j = 0; j < n - tside; j++) {
				bool fit = true;
				for (int k = 0; k < tside + 1; k++) {
					fit = fit && (mem[j+k] > tside);
				}
				if (fit) {
					counter++;
					if (tside > side) {
						side = tside;
						results[0] = i - tside;
						results[1] = j;
						results[2] = i;
						results[3] = j + tside;
					}
				}
			}
			if (counter < 2) break; 
			counter = 0;
		}		
	}		
	delete[] mem;
	return results;
}

int* task3(int** matrix, int m, int n, int h) {
	int* results = new int[4];
	bool mark;
	int size = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			for (int x = i; x < m; x++) {
				for (int y = j; y < n; y++) {
					mark = true;
					for (int a = i; a <= x; a++) {
						for (int b = j; b <= y; b++) {
							mark = mark && (matrix[a][b] >= h);
						}
					}
					if (mark) {
						int tsize = (x-i+1) * (y-j+1);
						if (tsize > size) {
							results[0] = i;
							results[1] = j;
							results[2] = x;
							results[3] = y;
							size = tsize;
						}
					}
				}
			}
		}
	}
	return results;
}

int* task4(int** matrix, int m, int n, int h) {
	int* results = new int[4];
	int size = 0;
	int** mem = new int*[m];
	for (int i = 0; i < m; i++) {
		mem[i] = new int[n];
		int flag = 0;
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] >= h) {
				mem[i][j] = j - flag + 1;
				if (mem[i][j] > size) {
					size = mem[i][j];
					results[0] = i;
					results[1] = j - size + 1;
					results[2] = i;
					results[3] = j;
				}
			} else {
				flag = j + 1;
				mem[i][j] = 0;
			}
		}
	}
	int count = 0;
	for (int height = 1; height < m; height++) {
		for (int i = 0; i < m - height; i++) {
			for (int j = 0; j < n; j++) {
				mem[i][j] = (mem[i][j] < mem[i+1][j])?mem[i][j]:mem[i+1][j];
				int tsize = mem[i][j] * (height + 1);
				if (tsize > 0) count++;
				if (tsize > size) {
					size = tsize;
					results[0] = i ;
					results[1] = j- mem[i][j] + 1;
					results[2] = i + height;
					results[3] = j;
				}
			}
		}
		if (count < 2) break; 
		count = 0;
	}
	return results;
}

int* task4alt(int** matrix, int m, int n, int h) {
	int* results = new int[4];
	int size = 0;
	int* mem = new int[n];
	for (int i = 0; i < n; i++) mem[i] = 0;
	int* temp = new int[n];
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] >= h) mem[j] += 1;
			else mem[j] = 0;
			temp[j] = mem[j];
			if (mem[j] > size) {
				size = mem[j];
				results[0] = i - mem[j] + 1;
				results[1] = j;
				results[2] = i;
				results[3] = j;
			}
		}
		int counter = 0;
		for (int width = 1; width < n; width++) {
			for (int j = 0; j < n - width; j++) {
				temp[j] = (temp[j] < temp[j+1])?temp[j]:temp[j+1];
				if (temp[j] > 0) counter++;
				int tsize = (width + 1) * temp[j];
				if (tsize > size) {
					size = tsize;
					results[0] = i - temp[j] + 1;
					results[1] = j;
					results[2] = i;
					results[3] = j + width;
				}
			}
			if (counter < 2) break; 
			counter = 0;
		}		
	}
	delete[] mem;
	delete[] temp;
	return results;
}




int main(int argc, char* argv[]) {
	string taskMode;
	string fileName;
	if (argc > 1) {
		taskMode = argv[1];
		fileName = argv[2];
	} else {
		cin >> taskMode;
		cin >> fileName;
	} 
	int** matrix; // to save data;
	int m, n, h;
	ifstream input;
	input.open(fileName.c_str(), ios::in);
	if (!input.is_open()) {
		cout << "failed to open file!";
		return 1;
	}
	input >> m >> n >> h;
	matrix = new int*[m];
	for (int i = 0; i < m; i++) {
		matrix[i] = new int[n];
		for (int j = 0; j < n; j++) input >> matrix[i][j];
	}
	input.close();
	
	/*
	cin >> m >> n >> h;
	matrix = new int*[m];
	for (int i = 0; i < m; i++) {
		matrix[i] = new int[n];
		for (int j = 0; j < n; j++) cin >> matrix[i][j];
	}
	*/
	
	int* results = NULL;
	clock_t start = clock();
	if (taskMode == "1") {
		results = task1(matrix, m, n, h);
	} else if (taskMode == "2") {
		results = task2alt(matrix, m, n, h);
	} else if (taskMode == "3") {
		results = task3(matrix, m, n, h);
	} else if (taskMode == "4") {
		results = task4(matrix, m, n, h);
	} else if (taskMode == "5") {
		results = task4alt(matrix, m, n, h);
	}
	cout << clock() - start << endl;
	for (int i = 0; i < 4; i++) cout << results[i] + 1 << " ";
	
	delete[] results;
	for (int i = 0; i < m; i++) delete[] matrix[i];
	delete[] matrix;
	return 0;
}
