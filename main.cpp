#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "RedBlack.h"
using namespace std;
using std::ofstream;


// READ-ar
int main() {
  RedBlack tree;
  
  ifstream inFile("books_data.csv");

  if (inFile.is_open()) {
    string genre, title, review, timePeriod = "";
    int length = 0;
    double rating = 0.0;

    string lineFromFile;
    while (getline(inFile, lineFromFile)) {
      istringstream stream(lineFromFile);
      
      
    }
    
  }
  
  
}

