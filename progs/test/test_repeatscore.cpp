#include "test_repeatscore.h"
#include <iostream>
#include <vector>
#include "../KarkSuffixArray.h"
#include <iostream>
#include <fstream>
#include "../BitPlusArray.h"
#include "../SimpleArray.h"
#include "../combined.h"


using namespace std;

void test_repeatscore(UnitTest &ut) {

  ut.begin_test_set("repeatscore");

  SimpleArray<unsigned char> *s = new SimpleArray<unsigned char>(14);

  s->insert(0,'A');
  s->insert(1,'T');
  s->insert(2,'G');
  s->insert(3,'C');
  s->insert(4,'A');
  s->insert(5,'T');
  s->insert(6,'G');
  s->insert(7,'C');
  s->insert(8,'A');
  s->insert(9,'A');

  // Generate Suffix array and analysis
  KarkSuffixArray<SimpleArray<unsigned char>,BitPlusArray> sarray(s,10);
  sarray.construct();
  sarray.constructLCP();

  vector<int> lcp_vector;
  for(int n=0;n<sarray.s_len;n++) {
    lcp_vector.push_back((*(sarray.lcp))[n]);
  }

  vector<vector<int> > *C_ptr;
  int result = repeatscore(lcp_vector,&C_ptr);
  vector<vector<int> > &C = *C_ptr;

  size_t breaks=1;
  for(int j=0;j<C[0].size();j++) {
    for(int i=1;i<C.size();i++) {
      if(j==0) C[i][j] -= (i*breaks)-1;
    }
  }

  ut.test(C[0][0],0);
  ut.test(C[1][0],0);
  ut.test(C[2][0],1);
  ut.test(C[3][0],2);
  ut.test(C[4][0],3);
  ut.test(C[5][0],4);

  ut.test(C[0][1],0);
  ut.test(C[1][1],3);
  ut.test(C[2][1],4);
  ut.test(C[3][1],3);
  ut.test(C[4][1],2);
  ut.test(C[5][1],1);

  ut.test(C[0][2],0);
  ut.test(C[1][2],0);
  ut.test(C[2][2],0);
  ut.test(C[3][2],0);
  ut.test(C[4][2],0);
  ut.test(C[5][2],0);

  ut.test(C[0][3],0);
  ut.test(C[1][3],1);
  ut.test(C[2][3],0);
  ut.test(C[3][3],0);
  ut.test(C[4][3],0);
  ut.test(C[5][3],0);
  
  ut.test(C[0][4],0);
  ut.test(C[1][4],0);
  ut.test(C[2][4],0);
  ut.test(C[3][4],0);
  ut.test(C[4][4],0);
  ut.test(C[5][4],0);
  
  ut.test(C[0][5],0);
  ut.test(C[1][5],0);
  ut.test(C[2][5],0);
  ut.test(C[3][5],0);
  ut.test(C[4][5],0);
  ut.test(C[5][5],0);
  
  ut.test(C[0][6],0);
  ut.test(C[1][6],0);
  ut.test(C[2][6],0);
  ut.test(C[3][6],0);
  ut.test(C[4][6],0);
  ut.test(C[5][6],0);

  ut.end_test_set();
}
