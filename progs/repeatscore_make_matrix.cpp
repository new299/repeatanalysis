#include "KarkSuffixArray.h"
#include <iostream>
#include <fstream>
#include "BitPlusArray.h"
#include "SimpleArray.h"
#include "combined.h"
#include "stdio.h"
#include "stringify.h"

using namespace std;

int main(int argc,char **argv) {
  if(argc < 2) {
    cout << "repeatscore <input file> <num breaks>" << endl;
    return 0;
  }

  int breaks = convertTo<int>(argv[2]);

  // load string into s

  FILE *input_file = fopen(argv[1],"rw");
  int size=0;
  for(;!feof(input_file);) {
    getc(input_file);
    size++;
  }
  fclose(input_file);

  SimpleArray<unsigned char> *s = new SimpleArray<unsigned char>(size+4);
  input_file = fopen(argv[1],"rw");
  for(int n=0;!feof(input_file);n++) {
    s->insert(n,getc(input_file));
  }
  fclose(input_file);

  // Generate Suffix array and analysis
  KarkSuffixArray<SimpleArray<unsigned char>,BitPlusArray> sarray(s,size-1);
  sarray.construct();
  sarray.constructLCP();

  vector<int> lcp_vector;
  for(int n=0;n<sarray.s_len;n++) {
    lcp_vector.push_back((*(sarray.lcp))[n]);
  }
  
  vector<vector<int> > *C_ptr;
  int result = repeatscore(lcp_vector,&C_ptr);
  vector<vector<int> > &C = *C_ptr;

  for(int j=0;j<C[0].size();j++) {
    for(int i=1;i<C.size();i++) {
      if(j==0) C[i][j] -= (i*breaks)-1;

      cout << C[i][j] << " ";
    }
    cout << endl;
  }
}
