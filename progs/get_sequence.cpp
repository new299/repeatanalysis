#include "KarkSuffixArray.h"
#include <iostream>
#include <fstream>
#include "BasePlusArray.h"
#include "BitPlusArray.h"
#include "SimpleArray.h"
#include "get_sequence.h"
#include "stdio.h"
#include "offset2contigpos.h"
#include "stringify.h"
#include "string.h"

using namespace std;

int main(int argc,char **argv) {
  if(argc < 5) {
    cout << "getsequence <input file> <getsequence out> <getmaximal out> <repeats> <length> <contig starts> <maximal?> [break symbol]" << endl;
    cout << "maximal: true/false" << endl;
    cout << "break symbol is optional and should be specified by ascii code" << endl;
    return 0;
  }

  ofstream getseqfile(argv[2]);
  ofstream getmaxfile(argv[3]);

  int repeats = convertTo<int>(argv[4]);
  int length  = convertTo<int>(argv[5]);

  bool get_maximal=false;
  if(string(argv[7]) == string("true")) get_maximal=true; else get_maximal=false; 

  int break_detect = false;
  int break_symbol;

  Offset2ContigPos convPos(argv[6]);

  bool breaks = false;
  if(argc > 7) {breaks=false; break_detect = true; break_symbol = convertTo<int>(argv[8]);}

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

  vector<int> lcp_vector;
  for(int n=0;n<sarray.s_len;n++) {
    lcp_vector.push_back((*(sarray.lcp))[n]);
  }

  vector<int> sa_vector;
  for(int n=0;n<sarray.s_len;n++) {
    sa_vector.push_back((*(sarray.sa))[n]);
  }

  vector<char> s_vector;
  for(int n=0;n<sarray.s_len;n++) {
    s_vector.push_back((*(sarray.s))[n]);
  }

  get_sequence(s_vector,sa_vector,lcp_vector,length,repeats,get_maximal,break_detect,break_symbol,getseqfile,getmaxfile,convPos);
  getseqfile.close();
  getmaxfile.close();
  return 0;
}
