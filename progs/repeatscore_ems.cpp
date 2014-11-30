#include "KarkSuffixArray.h"
#include <iostream>
#include <fstream>
#include "BitPlusArray.h"
#include "SimpleArray.h"
#include "combined.h"
#include "stdio.h"
#include "stringify.h"
#include <vector>
#include "malloc.h"
#include "string.h"

using namespace std;

extern "C" {
   int *repeat_score(char *inputstring);
}

int *repeat_score(char *inputstring) {
  int *repeat_score = (int *) malloc(101*101*sizeof(int));

  int breaks=0;

  int size = strlen(inputstring);
  SimpleArray<unsigned char> *s = new SimpleArray<unsigned char>(size+4);
  for(int n=0;inputstring[n]!=0;n++) {
    s->insert(n,inputstring[n]);
  }

  // Generate Suffix array and analysis
  KarkSuffixArray<SimpleArray<unsigned char>,BitPlusArray> sarray(s,size-1);
  sarray.construct();
  sarray.constructLCP();

  vector<int> lcp_vector;
  for(int n=0;n<sarray.s_len;n++) {
    lcp_vector.push_back((*(sarray.lcp))[n]);
  }
  

  vector<vector<int> > *C_ptr;
  int score[100][100];
  int result = repeatscore(lcp_vector,&C_ptr);
  vector<vector<int> > &C = *C_ptr;

  for(int j=0;j<C[0].size() && (j<100);j++) {
    for(int i=1;i<C.size() && (i<100);i++) {
      if(j==0) C[i][j] -= (i*breaks)-1;

      repeat_score[i+(j*100)] = C[i][j];
    }
  }

  return repeat_score;
}


int main() {
  char *c="testtesttestbananatesttesters";
  printf("calling\n");
  int *d = repeat_score(c);
  for(int n=0;n<10000;n++) { cout << d[n] << " "; }
  
}

