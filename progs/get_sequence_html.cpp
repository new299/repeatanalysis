#include "KarkSuffixArray.h"
#include <iostream>
#include <fstream>
#include "BitPlusArray.h"
#include "SimpleArray.h"
#include "get_sequence.h"
#include "stdio.h"
#include "offset2contigposhtml.h"

using namespace std;

int main(int argc,char **argv) {
  if(argc < 5) {
    cout << "getsequence <input file> <repeats> <length> <contig starts> <htmltarget> [break symbol]" << endl;
    cout << "break symbol is optional and should be specified by ascii code" << endl;
    return 0;
  }

  int repeats = atoi(argv[2]);
  int length  = atoi(argv[3]);

  int break_detect = false;
  int break_symbol;

  Offset2ContigPosHtml convPos(argv[4]);
  convPos.set_htmltarget(string(argv[5]));

  if(argc > 6) {break_detect = true; break_symbol = atoi(argv[5]);}

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

  vector<int> sa_vector;
  for(int n=0;n<sarray.s_len;n++) {
    sa_vector.push_back((*(sarray.sa))[n]);
  }

  vector<char> s_vector;
  for(int n=0;n<sarray.s_len;n++) {
    s_vector.push_back((*(sarray.s))[n]);
  }

  get_sequence(s_vector,sa_vector,lcp_vector,length,repeats,break_detect,break_symbol,convPos);
  return 0;
}
