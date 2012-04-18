#include <vector>
#include <iostream>

using namespace std;
typedef vector<vector<int> > vec2d;

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

int repeatscore(vector<int> &lcp,vec2d **C_ptr) {
  int n=lcp.size();
  DisjSets p(n);

  int v_max=0;
  for(int i=0;i<n;i++) // find v_max
   if(lcp[i] > v_max) v_max=lcp[i];

  vec2d height(v_max+1,vector<int>(0));
  for(int i=1;i<n;i++) // create height
    height[lcp[i]].push_back(i);

  *C_ptr = new vec2d(v_max+2,vector<int>(n,0));
  vec2d &C = **C_ptr;

  C[v_max+1][0]=n;

  for(int k=v_max;k>0;k--) {
    for(int cp=0;cp<n;cp++) C[k][cp]=C[k+1][cp];

    vector<int>::iterator i = height[k].begin();
    for(;i != height[k].end();i++) {
      int s = p.find((*i));
      int t = p.find((*i)-1);

      C[k][p.set_size(s)-1]--; // remove old
      C[k][p.set_size(t)-1]--;

      int l = p.unionsets(s,t);

      C[k][p.set_size(l)-1]++; // add new set
    }
  }
}

int repeatscore_printonly(vector<int> &lcp,int breaks,int max_repeats,int max_length) {
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
}
