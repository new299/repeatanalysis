#include "KarkSuffixArray.h"
#include <iostream>
#include <fstream>
#include "BitPlusArray.h"
#include "BasePlusArray.h"
#include "SimpleArray.h"
#include "combined.h"
#include "stdio.h"
#include "stringify.h"

using namespace std;

int main(int argc,char **argv) {
  if(argc < 3) {
    cout << "repeatscore <input file> <max repeats> <max length> [breaks symbol]" << endl;
    cout << "breaks symbol should be specificed as ASCII value e.g. # = 35" << endl;
    return 0;
  }

  int max_repeats = convertTo<int>(argv[2]);
  int max_length  = convertTo<int>(argv[3]);
  bool breaks = false;
  char break_symbol;
  if(argc > 4) {break_symbol = convertTo<int>(argv[4]); breaks=true;}

  // load string in to s
  BasePlusArray<unsigned char,255,int,int,int> *s = new BasePlusArray<unsigned char,255,int,int,int>;
  ifstream input_file(argv[1]);
  
  int num_breaks = 0;
  if(breaks) num_breaks = s->load(input_file,break_symbol);
        else { s->load(input_file); }

  input_file.close();

  s->push_back(s->get_max_value()+1);

  // cout << "s: " << *s << endl;
  // Generate Suffix array and analysis
  KarkSuffixArray<BasePlusArray<unsigned char,255,int,int,int>,SimpleArray<int> > sarray(s,s->size(),s->get_max_value()+1);
  sarray.construct();
  sarray.constructLCP();

  // sarray.dumpSA();
  // sarray.dumpLCP();

  vector<int> lcp_vector;
  for(int n=0;n<sarray.s_len;n++) {
    lcp_vector.push_back((*(sarray.lcp))[n]);
  }

  int result = repeatscore_printonly(lcp_vector,num_breaks,max_repeats,max_length);
  return result;
}
