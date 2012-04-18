#include <vector>
#include <iostream>
#include "stringify.h"

using namespace std;

template<class _convertPosition>
void get_sequence(vector<char> &s,
                  vector<int> &sa,
                  vector<int> &lcp,
                  int length,
                  int repeats,
                  bool break_detect,
                  bool print_maximal,
                  int break_symbol,
                  ostream &getseqout,
                  ostream &getmaxout,
                  _convertPosition &convPos) {

  // for all subsequence lengths, itterate over length array
  if(repeats > 0)
  for(int n=0;n<sa.size();n++) {
    if(sa[n] <= (sa.size() - length - 1)) {

      int unique_length;
      if(n >= sa.size()) unique_length = -1; else
      if(lcp[n] > lcp[n+1]) {unique_length = lcp[n]+1; } else
      if(lcp[n] < lcp[n+1]) {unique_length = lcp[n+1]+1; } else
                            {unique_length = lcp[n]+1;}

      if(unique_length >= length) {

        // walk right from this point until becomes more less than k..
        int repeat_count=1;
        int start = n-1;
        int maximal_length=-1;
        for(;(n < lcp.size()) && (lcp[n] >= length);n++) {
          if((lcp[n] < maximal_length) || (maximal_length == -1)) maximal_length = lcp[n];
          repeat_count++;
        }

        if((repeats+1) == repeat_count) {
          // check sequence contains no breaks
          bool breaks=false;
          if(break_detect)
          for(int ns=0;ns<length;ns++) {
            if(s[sa[start]+ns] == break_symbol) breaks=true;
          }

          if(breaks==false) {
            // dump this sequence and its location
            getseqout << "> ";
            getmaxout << "> ";
            for(int pos=start;pos<n;pos++) {
              if((sa[pos] + (length-1)) < s.size()) {
                getseqout << convPos.convert(sa[pos]) << " ";
                getmaxout << convPos.convert(sa[pos]) << " ";
              }
            }
            getseqout << endl;
            getmaxout << endl;

            // print SA[start] to k characters...
            for(int ns=0;ns<length;ns++)         getseqout << s[sa[start]+ns];
            for(int ns=0;ns<maximal_length;ns++) getmaxout << s[sa[start]+ns];
            getseqout << endl;
            getmaxout << endl;

          }
        }
      }
    }
  }

  if(repeats == 0)
  for(int n=0;n<sa.size();n++) {
    if(sa[n] <= (sa.size() - length - 1)) {
      int unique_length;
      if(n >= sa.size()) unique_length = -1; else
      if(lcp[n] > lcp[n+1]) {unique_length = lcp[n]+1; } else
      if(lcp[n] < lcp[n+1]) {unique_length = lcp[n+1]+1; } else
                            {unique_length = lcp[n]+1;}

      if(unique_length <= length) {

        // check sequence contains no breaks
        bool breaks=false;
        if(break_detect)
        for(int ns=0;ns<length;ns++) {
          if(s[sa[n]+ns] == break_symbol) breaks=true;
        }

        if(breaks == false) {
          getseqout << "> " << convPos.convert(sa[n]) << endl;
          getmaxout << "> " << convPos.convert(sa[n]) << endl;
          // print SA[start] to k characters...
          for(int ns=0;ns<length;ns++) {
            getseqout << s[sa[n]+ns];
            getmaxout << s[sa[n]+ns];
          }
          getseqout << endl;
          getmaxout << endl;
        }
      }
    }
  }

}
