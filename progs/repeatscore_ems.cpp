#include "KarkSuffixArray.h"
#include <iostream>
#include <fstream>
#include "BitPlusArray.h"
#include "SimpleArray.h"
#include "stdio.h"
#include "stringify.h"
#include <vector>
#include "malloc.h"
#include "string.h"
#include "combined.h"

using namespace std;

/*
typedef vector<vector<int> > vec2d;
  vector<int> lcp;

class DisjSets {
public:
  vector<int> s, s_sizes;
  DisjSets(int l) : s(l,-1) , s_sizes(l,1) {}

  int find(int x) {
    if(s[x] < 0) return x;
    return s[x] = find(s[x]);
  }

  int unionsets(int r1,int r2) {
    if(s[r2] < s[r1]) {int sw=r1; r1=r2; r2=sw;}

    if(s[r1]==s[r2]) s[r2]--;
    s_sizes[r1]=s_sizes[r1]+s_sizes[r2];
    return s[r2]=r1;
  }

  int set_size(int x) { return s_sizes[x]; }
};

int repeatscore_printonly(int breaks,int max_repeats,int max_length) {

  int n=lcp.size();
  DisjSets p(n);

  int v_max=0;
  for(int i=0;i<n;i++) // find v_max
    if(lcp[i] > v_max) v_max=lcp[i];

  vec2d height(v_max+1,vector<int>(0));

  for(int i=1;i<n;i++) {
    // create height
    int lcpi = lcp[i];
    height[lcpi].push_back(i);
  }

  vector<int> C(n,0);
  C[0]=n;
  for(int k=v_max;k>0;k--) {
    int n=0;

    if(k<=max_length) {
      for(vector<int>::iterator j = C.begin();j != C.end();j++) {
        if(n < max_repeats) {
          if(n == 0) cout << (*j)-((k+1)*breaks)-k-1 << " ";
          else       cout << (*j) << " ";
        }
        n++;
      }
      cout << endl;
    }

    vector<int>::iterator i = height[k].begin();
    for(;i != height[k].end();i++) {
      int s = p.find((*i));
      int t = p.find((*i)-1);

      C[p.set_size(s)-1]--; // remove old
      C[p.set_size(t)-1]--;

      int l = p.unionsets(s,t);

      C[p.set_size(l)-1]++; // add new set
    }
  }

  int m=0,k=0;
  for(vector<int>::iterator j = C.begin();j != C.end();j++,k++) {
    if(m < max_repeats) {
      if(m == 0) cout << (*j)-(breaks*(k+1))-1 << " ";
      else       cout << (*j) << " ";
    }
    m++;

  }
  cout << endl;

  return 0;
}
*/

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

 // repeatscore_printonly(1,100,100);

  return repeat_score;
}

/*
int main() {
  char *c="testtesttestbananatesttesters";
  printf("calling\n");
  int *d = repeat_score(c);
  for(int n=0;n<10000;n++) { cout << d[n] << " "; }
  
}
*/
