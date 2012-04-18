#ifndef SUFFIXARRAY_H
#define SUFFIXARRAY_H

#include <iostream>
#include <fstream>


using namespace std;

template <class Sequence,class ArrayStorage>
class SuffixArray {
public:
	// Structure Construction Flags

	int flag_SAConstructed;
	int flag_LCPConstructed;
	int flag_LenArrayConstructed;
	int flag_ReverseConstructed;
	int flag_SortedLenConstructed;
	int flag_SortedLCPConstructed;

	// Member variables to store suffix structure

	Sequence *s;
	unsigned long long int s_len;
        unsigned long long int max_value;
	int	inverted;
	unsigned long long int readTotalsLen;
	ArrayStorage	*lcp;
	ArrayStorage	*reverseArray;
	ArrayStorage	*sa;
	ArrayStorage	*contigBreakArray;
	ArrayStorage	*readTotals;
	
	SuffixArray() {
	}

	SuffixArray(Sequence *s_in,unsigned long long int s_len_in,unsigned long long int max_value_in=255) : max_value(max_value_in) {
		lcp=0;
		reverseArray=0;
		sa=0;

		flag_SAConstructed		= false;
		flag_LCPConstructed		= false;
		flag_LenArrayConstructed	= false;
		flag_ReverseConstructed		= false;
		flag_SortedLenConstructed	= false;
		flag_SortedLCPConstructed	= false;
		inverted = false;

                s = s_in;
                s_len = s_len_in;
 	}

	int freeAll() {
		if(lcp != 0)            delete lcp;
		if(reverseArray != 0)   delete reverseArray;
		if(sa != 0)             delete sa;

		return true;
	}

	int constructLCPOnly() {
		return true;
	}

	int constructContigBreakArray() {
		contigBreakArray = new ArrayStorage(s_len);
		ArrayStorage &contigBreakArrayRef = *contigBreakArray;
		Sequence &sRef = *s;
		
		long long int backCount = 0;
//		cout << "contigbreakarray, s_len: " << s_len << endl;
		for(long long int n=s_len-1;n>=0;n--) {

			if(sRef[n] == 'y') backCount = 0; else
			if(sRef[n] == 'z') backCount = 0; else
			if(sRef[n] == 'N') backCount = 0; else
			if(sRef[n] == 'n') backCount = 0;

			contigBreakArrayRef.insert(n,backCount);
			backCount++;
		}

		return true;
	}

	int constructReadTotalsArray(unsigned int readLength) {
		if(readLength > s_len) readLength=s_len+1;
		readTotals = new ArrayStorage(readLength+1);
		ArrayStorage &readTotalsRef = *readTotals;
		ArrayStorage &contigBreakArrayRef = *contigBreakArray;
		readTotalsLen = readLength+1;

		// zero array
		unsigned long long int n=0;

		for(n=0;n<readTotalsLen;n++) {
			readTotalsRef.insert(n,0);
		}

		// calculate

//		cout << "contigBreakArrayRef[n]: " << contigBreakArrayRef[n] << endl;
		for(n=0;n<s_len;n++) {
			if(contigBreakArrayRef[n] <= readLength)
			readTotalsRef.insert(contigBreakArrayRef[n],readTotalsRef[contigBreakArrayRef[n]]+1);
			else
			readTotalsRef.insert(readLength-1,readTotalsRef[readLength-1]+1);
		}

		// accumulate
		unsigned long long int runningSum = 0;
		int end=false;
		for(n=readTotalsLen-1;end==false;n--) {
			runningSum = runningSum + readTotalsRef[n];
			readTotalsRef.insert(n,runningSum);
			if(n==0) end=true;
		}

		return true;
	}

	int saveReadTotalsArray(string filename) {
//		cout << "Saving readTotals: " << filename << endl;

		ArrayStorage &readTotalsRef = *readTotals;

		ofstream out(filename.c_str());

		for(unsigned long long int n=0;n<readTotalsLen;n++) {
			out << readTotalsRef[n] << endl;			
		}
		
		out.close();
                                                 
		return true;
	}

	int constructLCP() {
		
//		cout << "allocating lcp..." << endl;
		lcp = new ArrayStorage(s_len);
		ArrayStorage &lcpRef = *lcp;
		ArrayStorage &saRef = *sa;

		Sequence &t = *s;
		unsigned long long int n = s_len;

//		cout << "allocating rank..." << endl;
        	ArrayStorage *rankPtr = new ArrayStorage(n);
		ArrayStorage &rank    = *rankPtr;
	
        	unsigned long long int i=0,j=0,h=0,k=0;

//		cout << "initialising rank..." << endl;
        	for(i=0;i<n;i++) {
			rank.insert(saRef[i],i); 
		}


        	h=0;

        	for(i=0;i<n;i++) {
                	k = rank[i];
                	if(k==0) lcpRef.insert(k,0);
                	else {
				j = saRef[k-1];
                        	while(i+h<=n && j+h<=n && t[i+h]==t[j+h]) h++;
                        	lcpRef.insert(k,h);
                	}
        	        if(h>0) h--;
       		 }

        	delete rankPtr;

		return 0;
	}

	int constructReverseArray() {
		reverseArray = new ArrayStorage(s_len);
		ArrayStorage &saRef = *sa;

		for(unsigned long long int n=0;n<s_len;n++) {
			reverseArray->insert(saRef[n],n);
		}

		return 0;
	}

	int dumpS() {
		cout << "S  : ";
		
		Sequence &sRef = *s;
		for(unsigned long long int n=0;n<s_len;n++) {
			cout << (char) sRef[n] << " ";
		}

		cout << "*END*" << endl;
		
		return 0;
	}

	int dumpSA() {
		cout << "SA : ";
		ArrayStorage &saRef = *sa;

		for(unsigned long long int n=0;n<s_len;n++) {
			cout << saRef[n] << " ";
		}

		cout << "*END*" << endl;

		return 0;
	}

	int dumpContigBreakArray() {
		cout << "ContigBreakArray : ";
		ArrayStorage &contigBreakRef = *contigBreakArray;

		for(unsigned long long int n=0;n<s_len;n++) {
			cout << contigBreakRef[n] << " ";
		}

		cout << "*END*" << endl;

		return 0;
	}

	int dumpLCP() {
		cout << "LCP: ";
		
		ArrayStorage &lcpRef = *lcp;
		for(unsigned long long int n=0;n<s_len;n++) {
			cout << lcpRef[n] << " ";
		}

		cout << "*END*" << endl;

		return 0;
	}

	int dumpReverse() {
		ArrayStorage &reverseArrayRef = *reverseArray;

		cout << "Rev: ";

		for(unsigned long long int n=0;n<s_len;n++) {
			cout << reverseArrayRef[n] << " ";
		}

		cout << "*END*" << endl;

		return 0;
	}

	template<class Array> int saveArray(string filename,Array *write_in,unsigned long long int arrayLen) {


		cout << "Saving: " << filename << endl;

		Array &write = *write_in;

		fstream out(filename.c_str(),ios::out | ios::binary);

		for(unsigned long long int n=0;n<arrayLen;n++) {
			unsigned long long int temp = write[n];
			out.write((char *) &temp,sizeof(write[n]));
		}
		
		out.close();
                                                 
		return true;
	}

	/// Load file into given array, returns size
	template<class Array> unsigned long long int loadArray(string filename,Array **read) {

		Array *tA = new Array(1);
		Array &tref = *tA;
		int readSize = sizeof(tref[0]);
		delete tA;	

		cout << "Loading: " << filename << endl;
		fstream in(filename.c_str(),ios::in | ios::binary);

		// calculate size
		unsigned long long int n;
		unsigned long long int arraylen=0;

		// read to get memory requirements
		unsigned long long int t;
		for(n=0;!in.eof();n++) {
			in.read((char *) &t,readSize);
			arraylen++;
		}
		in.close();

		// allocate memory
		Array *r = new Array(arraylen);

		// move to start of file
		fstream in2(filename.c_str(),ios::in | ios::binary);

		// read file
		for(n=0;!in2.eof();n++) {
			in2.read((char *) &t,readSize);
			r->insert(n,t);
		}
		in2.close();

		*read = r;

		return arraylen;
	}

	int saveS(string filename) {
		return saveArray(filename,s,s_len);
	}

	int loadS(string filename) {

		s_len = loadArray(filename,&s);
		return true;
	}

	int saveSA(string filename) {
		return saveArray(filename,sa,s_len);
	}

	int loadSA(string filename) {
		loadArray(filename,&sa);
		return true;
	}

	int saveLCP(string filename) {
		return saveArray(filename,lcp,s_len);
	}

	int loadLCP(string filename) {
		loadArray(filename,&lcp);
		return true;
	}

	int saveReverse(string filename) {
		return saveArray(filename,reverseArray,s_len);
	}

	int loadReverse(string filename) {
		loadArray(filename,&reverseArray);
		return true;
	}

};

#endif
