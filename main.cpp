#include <iostream>
#define __MATLAB__ 
#include <eblearn/libidx.h> 

int main(int argc, char **argv) {    
  char *matFileName = "testMATLAB.mat";
  char* varName = "var_a";
  cout<< "Reading variable: \"" << varName 
      << "\" from file: " << matFileName <<endl;
  // create ebl::matlab object
  ebl::matlab matWrapper(matFileName);
  // read the variable into an idx
  ebl::idx<double> varToGet=matWrapper.load_matrix<double>(varName);
  // Display tensor information
  varToGet.pretty();
  cout << endl;
  // display the idx values
  varToGet.printElems();
  cout << endl;
  return 0;
}
