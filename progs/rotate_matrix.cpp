#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main(int argc,char **argv) {
  if(argc < 2) {
    cout << "rotate_matrix <input file>" << endl;
    return 0;
  }

  // load string into s

  vector<vector<int> > matrix;

  ifstream infile(argv[1]);
  int size=0;

  vector<int> c_line;
  for(;!infile.eof();) {
    
    stringstream ss(stringstream::in | stringstream::out);
    string str;
    getline(infile,str);
    ss << str;

    if(!ss.eof()) {
      int n=0;
      for(;!ss.eof();n++) {
        int i;
        ss >> i;
        c_line.push_back(i);
      }
      if(n>1) matrix.push_back(c_line);
    }
    c_line.clear();
  }
  infile.close();

  int x_size = matrix.size();
  int y_size = (*(matrix.begin())).size();

  for(int y=0;y<y_size;y++) {
    for(int x=x_size-1;x>=0;x--) {
      cout << matrix[x][y] << " ";
    }
    cout << endl;
  }

}
