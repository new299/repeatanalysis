#ifndef KARKSUFFIXARRAY_H
#define KARKSUFFIXARRAY_H

#include "SuffixArray.h"
#include "Array.h"
#include "SimpleArray.h"
#include "BitPlusArray.h"

template <class _Sequence,class ArrayStorage>
class KarkSuffixArray : public SuffixArray<_Sequence,ArrayStorage> {
public:
	KarkSuffixArray() {
	}

        KarkSuffixArray(_Sequence *s_in,unsigned long long int s_len_in,unsigned long long int max_value_in=255):SuffixArray<_Sequence,ArrayStorage>(s_in,s_len_in,max_value_in) 
        {
	}

	/**
	* Constructs the suffix array of the current string s.
	*@return returns true if an array was constructed, false if it wasn't
	*/
	int construct() {

		if(this->flag_SAConstructed == false) {
			// call construction code

			_Sequence &sRef = *(this->s);
			suffixArray<_Sequence,ArrayStorage>(sRef,&(this->sa),this->s_len,this->max_value);

			return true;
		} else {
			// SA is already constructed and can only be constructed once for each object
			return false;
		}
	}

	
	/**
       * Create the suffix array (SA) of the string s, where the key size of s is k. Uses Karkkainen's linear time suffix array construction algorithm
       * @param s     The original string from which the suffix array is constructed, note: s should have 3 additional empty positions after it's final length (as identified by len) this is used internally by the algorithm.
       * @param SA_in A Pointer which will store the suffix array on exit, memory is allocated and a pointer is returned, should be deallocated with delete
       * @param len   The length of s, which will also be the length of SA
       * @param k     The key size of s, no symbol in s should be larger than this (it is used by RadixSort)
       * @return true on success, false on fail (no path currently returns false...).
       */
	template <class _SSequence, class ArrayType> int  suffixArray(_SSequence &s,ArrayType **SA_in,unsigned long long int len,unsigned long long int k) {

//		cout << "Karkainens algorithm entered, len: " << len << endl;

	
		unsigned long long int  n; // random loop counter

		ArrayType *listA_ptr = new ArrayType(((len/3)*2)+3);
		ArrayType &listA = *listA_ptr;

		unsigned long long int  listAlen = 0;
		
		// 0.0. stick some extra 0s on the end of the string...

                s.push_back(0);
                s.push_back(0);
                s.push_back(0);

		// adjust length so total length is multiple of 3?
	
		unsigned long long int nlen=0;	
		if((len-1) % 3 == 0) {nlen = 1;} else
		if((len-1) % 3 == 1) {nlen = 0;} 
	
		// 0. Build listA containing indexes to mod 1/2 suffix triples
	
		// create listA: i mod 3 != 0
	
		for(n=0;n<(len+nlen);n++) {
			// take every i mod 3 != 0 point...
	
			if((n % 3) != 0) {
				listA.insert(listAlen,n);
				listAlen++;
			} 
		}
	

	
		// listA currently contains unsorted mod 1 and 2 indexes into suffix array
	
		// 1. Sort listA - mod 1 and 2 suffixes
		// inputs  listA,s
		// outputs listA now containing lexicographic names, s unchanged.
	
		// 1.1 Radix sort listA
		SortTriples(listA,listAlen,s,len,k);

		// 1.2 Assign lexicographic names
		
		// each triple is named based upon it's position in the list, name is incremented
		// once for each position, however is ONLY incremented if the the triple contents
		// has changed
	
		// cout << "beginning lexicographic naming" << endl;
	
		unsigned long long int name=1;
		unsigned long long int lastTriple=0;

		ArrayType *lexicoNames_ptr = new ArrayType(listAlen);
		ArrayType &lexicoNames = *lexicoNames_ptr;

		for(n=1;n<listAlen;n++) {
			lastTriple = listA[n-1];
			
			lexicoNames.insert(n-1,name);
			unsigned long long int listAn = listA[n];			

			if(	s[lastTriple]   == s[listAn]   &&
				s[lastTriple+1] == s[listAn+1] &&
				s[lastTriple+2] == s[listAn+2]) {
				// lexicographic names matched, haha you need to do another recursion!!!
			} else {
				name++;
			}
		}
		lexicoNames.insert(listAlen-1,name);
	
		// for some reason the lexicographic names must be stored first ordered by weither they
		// are mod 1 or mod 2 suffix triples, so we now seperate the string out into this order...
			
		unsigned long long int lexico2pos=0;

		if(listAlen % 2 == 0) lexico2pos = listAlen/2;
		else lexico2pos = (listAlen+1)/2;
		

		ArrayType *lexicoReordered_ptr = new ArrayType(listAlen+10); // recursion requires extra junk space
		ArrayType &lexicoReordered = *lexicoReordered_ptr;


		for(n=0;n<listAlen;n++) {
			// dividing by 3 ensures that values are compressed into the correct range while
			// order is preserved (that is the original order in sorted list?).
	
			if((listA[n] % 3) == 1) lexicoReordered.insert(listA[n]/3,lexicoNames[n]); else
			if((listA[n] % 3) == 2) lexicoReordered.insert(listA[n]/3+lexico2pos,lexicoNames[n]);//-1
		}
		delete listA_ptr;
		delete lexicoNames_ptr;
		
		// 1.3 Create suffix array of triples...
		// 1.3 If lexicographic names are not unique recurse

		ArrayType *lexicoSA_ptr=0;// = new ArrayType(listAlen);

		if(name < listAlen) { 
			// recursion required...
	
			// what does running the recursion do?
			// well if all the names where unique then creating a suffix tree of this would
			// simply order the lexicographic names
	
			// if they are not unique then lexicographic names that are the same will be
			// reordered based upon the names that come after them.
	
			// the names that come after them are suffixes stored in the order they appear
			// in the original string (?). So.. the new lexicographic names will repersent
			// sorting of triples from the original string, taking into account the following
			// triple (following in the string not sorted order), if triples are the same.
	

			lexicoSA_ptr = NULL;

                        suffixArray<ArrayType,ArrayType>(lexicoReordered,&lexicoSA_ptr,listAlen,name+1);
                        
                        // the commented code allowed recursive calls to use less memory through the use of small sized ints, it has been removed as I
                        // am no longer using the Array base class on which it relied, when refactoring this should be reconsidered.

//			if((name+10 < USHRT_MAX) && (listAlen+10 < USHRT_MAX)) suffixArray<ArrayType, SimpleArray<unsigned short> >(lexicoReordered,(SimpleArray<unsigned short> **) &lexicoSA_ptr,listAlen,name+1); else
//			if((name+10 < UINT_MAX)  && (listAlen+10 < UINT_MAX))  suffixArray<ArrayType, SimpleArray<unsigned int>   >(lexicoReordered,(SimpleArray<unsigned int> **) &lexicoSA_ptr,listAlen,name+1);
//			else                   				   suffixArray<ArrayType, BitPlusArray>               (lexicoReordered,(BitPlusArray **) &lexicoSA_ptr,listAlen,name+1);


			// fix lexicographic names based on lexicoSA

			for(n=0;n<listAlen;n++) {
				// position of name in lexicoSA determines it's name?
	
				// lexicoReordered is the inverse of lexicoSA...
				lexicoReordered.insert(lexicoSA_ptr->at(n),n + 1);
			}


		} else {
			// print lexicoReordered:
			lexicoSA_ptr = new ArrayType(listAlen+100);

			// make lexicoSA based on lexicographic names
			for(n=0;n<listAlen;n++) {
				lexicoSA_ptr->insert(lexicoReordered[n]-1,n);
			}
	

		}
		ArrayType &lexicoSA     = *lexicoSA_ptr;

		// lexicoReordered contains the lexicographic names of mod 1 then mod 2 suffixes
		// lexicoSA	   contains the suffix array of lexicoReordered. This is fundimentially
		//		   the inverse of lexicoReordered, when all names are unique. Which
		//		   they are.
	
		// so lexicoSA contains the indexes, in name order. And if the value at this position
		// is less than the mod1 mod2 break point. It's a mod 1 suffix, else it's a mod 2 suffix.
	
	
		// by this point everything should have a unique lexicographic name
		// 2 Arrays are the product of the code so far they are:
	
		// lexicoReorderd: 	lexicographic names of i mod 3 != 0 triples,
		//			in a rather odd order in that i mod 3 = 1 triples are in the order
		//			they appear in the string, but come first in the array
		//			i mod 3 = 2 triples are in the order they appear in the string
		//			but come second.
	
		// lexicoSA:		A suffix array of lexicoReordered used later...
	
		// 2. Sort i mod 3 = 0 triples, this is done using the suffix array of i mod 3 != 0 triples
	
		// 2.1 sort listB, by putting triples in the order that the triples starting at the second
		// position occur in lexicoSA.
	
		// listB currently contains indexes into s, that are i mod 3 = 0 triples
	
	
	
		// When we made lexico names, we put everything in order, such that all the mod 1 triples
		// came first and the mod 2 triples came second.
	
		// Take all the i mod 3 = 1 suffixes. Find the lexicographic names.
		// Put the original names in the order of the lexicographic names.
		// compress the range so it fits in listB correctly...
	
		// THERE ARE BETTER WAYS OF CODING THIS TO RUN FASTER - SEE REFERENCE CODE BY KARKKAINEN

		ArrayType *listB_ptr = new ArrayType((len/3)+3);
		ArrayType &listB     = *listB_ptr;

		unsigned long long int listBlen = 0;
		for(n=0;n<listAlen;n++) {
			unsigned long long int curIndex=0;
			if(lexicoSA[n] < lexico2pos) {
				curIndex = lexicoSA[n] * 3;
	
				listB.insert(listBlen,curIndex);
				listBlen++;
			}
		}		
	
		// 2.2 sort listB (i mod 3 = 0) based on first character only
		radixSortPass(listB,listBlen,s,len,0,k);
	
		// Step 3 - Merge
	
		// cout << "Merging arrays" << endl;
	
		// itterate over listB which contains the lexicographic names for i mod 3 = 0 suffixes
		unsigned long long int SA0Position=0;
		unsigned long long int SA12Position=nlen;
		unsigned long long int currentPosition=0;


		ArrayType *SA_ptr = new ArrayType(len+100);// len
		ArrayType &SA     = *SA_ptr;// len
		*SA_in    = SA_ptr;	

		for(;(SA12Position < listAlen) && (SA0Position < listBlen);) {
			//lexicoSA contains indexes to lexicoReordered in the name order...
			
			int SA12isMore=false;
			if(lexicoSA[SA12Position] < lexico2pos) {
	
				unsigned long long int SA12Index = lexicoSA[SA12Position] * 3 + 1;
				unsigned long long int SA0Index  = listB[SA0Position];
	
				// Get lexicographic name for the suffix that follows this position
	


				if(((SA12Index+1)-2)/3+(lexico2pos) >= listAlen) {

					SA12isMore = true;
				} else {

					unsigned long long int SA12plus1 = lexicoReordered[((SA12Index+1)-2)/3+(lexico2pos)];
					unsigned long long int SA0plus1  = lexicoReordered[((SA0Index+1)/3)];

					if(SA12plus1 > SA0plus1) SA12isMore = true; else SA12isMore = false;
				}
	
				// Compare first character
	
				if(s[SA12Index] > s[SA0Index]) SA12isMore = true;
				if(s[SA12Index] < s[SA0Index]) SA12isMore = false;
	
				
				// Comparison done, use the correct one
	
				if(SA12isMore) {
					// use SA0
					SA.insert(currentPosition,SA0Index);
					SA0Position++;
					currentPosition++;
				} else {
					// use SA12
					SA.insert(currentPosition,SA12Index);
					SA12Position++;
					currentPosition++;
				}
			} else {
				unsigned long long int SA12Index = (lexicoSA[SA12Position]-lexico2pos) * 3 + 2;// ERROR?
				unsigned long long int SA0Index  = listB[SA0Position];
	
				// Get lexicographic name for the suffix that follows this position
	
				unsigned long long int SA12plus2 = lexicoReordered[((SA12Index+2)-1)/3];

				// TERMINAL SYMBOL IS SMALL
				if((SA0Index+2) >= len) SA12isMore = true; else {
					unsigned long long int SA0plus2 = lexicoReordered[(SA0Index+2)/3+(lexico2pos)]; // BAD
					if(SA12plus2 > SA0plus2) SA12isMore = true; else SA12isMore = false;
				}
	
				// Compare second character
				if(((SA0Index+1) >= len) && ((SA12Index+1) >= len)) sleep(0); else
				if((SA0Index+1) >= len) SA12isMore = true;            else
				if((SA12Index+1) >= len) SA12isMore = false;          else
				if(s[SA12Index+1] > s[SA0Index+1]) SA12isMore = true; else
				if(s[SA12Index+1] < s[SA0Index+1]) SA12isMore = false;
	
				// Compare first character
				if(s[SA12Index] > s[SA0Index]) SA12isMore = true;
				if(s[SA12Index] < s[SA0Index]) SA12isMore = false;
	
				// Comparison done, use the correct one
	
				if(SA12isMore) {
					// use SA0
					SA.insert(currentPosition,SA0Index);
					SA0Position++;
					currentPosition++;
				} else {
					// use SA12
					SA.insert(currentPosition,SA12Index);
					SA12Position++;
					currentPosition++;
				}
	
	
	
			}
		}
	
		// if anything is left of either array, stick it on the end...
		if(SA0Position < listBlen) {
			for(;SA0Position<listBlen;SA0Position++) {
				SA.insert(currentPosition,listB[SA0Position]);
				currentPosition++;
			}
		}
	
		if(SA12Position < listAlen) {
			for(;SA12Position<listAlen;SA12Position++) {
	
				if(lexicoSA[SA12Position] < lexico2pos) {
					SA.insert(currentPosition, (lexicoSA[SA12Position])*3+1);
				}
				else {
					SA.insert(currentPosition, (lexicoSA[SA12Position]-(lexico2pos))*3+2);
				}
	
				currentPosition++;
			}
		}

//		cout << "Memory report, before exiting Karkkainens algorithm:" << endl;
//		cout << endl;

		// Deallocate
		delete lexicoReordered_ptr;
		delete lexicoSA_ptr;
		delete listB_ptr;


		return true;
	}

private:

	/**
       * Radix sort based on triples (groups of three symbols)
       * @param listA The indexes to the triples (from the string s) which are to be sorted, is modified to resort these indexes into the lexicographic order of the triples.
       * @param s     The string to which the indexes in listA point.
       * @param len   Length of listA
       * @param k     The key size of s, that is the largest symbol that occurs (or could occur) in s.
       * @return true on success, false on fail (no path currently returns false...).
       */

template <class ASequence, class ArrayType> int SortTriples(ArrayType &listA,unsigned long long int len,ASequence &s,unsigned long long int slen,unsigned long long int k) {
	// shift indexes around in listA, depending on triples found in s...

	radixSortPass(listA,len,s,slen,2,k);
	radixSortPass(listA,len,s,slen,1,k);
	radixSortPass(listA,len,s,slen,0,k);
	return true;
}

	/**
       * A Single Radix pass, used by SortTriples to perform a full sort, also used to store SA0 suffixes by first character only
       * @param listA A list of indexes to s, which will be reordered based upon sorting only the character that occurs at this position in s. listA will be modified on return.
       * @param s     The string to which the indexes in listA point.
       * @param len   Length of listA
       * @param k     The key size of s, that is the largest symbol that occurs (or could occur) in s.
       * @return true on success, false on fail (no path currently returns false...).
       */
template <class ASequence, class ArrayType> int radixSortPass(ArrayType &listA,unsigned long long int len,ASequence &s,unsigned long long int slen,int offset,unsigned long long int k) {

	// shift indexes around in listA, depending on values found in s...

	unsigned long long int n; // random loop counter
	ArrayType *symbolCount_ptr = new ArrayType(k+2);	// create symbol counters
	ArrayType &symbolCount     = *symbolCount_ptr;
	for(n=0;n<(k+2);n++) symbolCount.insert(n,0); // zero symbol count

	// count symbols in string
//	cout << "RadixPass" << endl;
	for(n=0;n<len;n++) {
		
		if(listA[n] > 0) sleep(0);

		unsigned long long int symbol;
		if(listA[n]+offset >= slen) symbol = 0; else
		symbol = s[listA[n]+offset]+1; 	// push everything up by one to make way for special 0 symbol, which is terminal symbol above

		if(symbol > (k+1)) cout << "ERROR IN RADIX PASS SYMBOL TOO LARGE: symbol=" << symbol << endl;
		symbolCount.insert(symbol,symbolCount[symbol]+1);
	}

	// convert symbol counts to symbol output positions
	unsigned long long int runningSum=0;
	for(n=0;n<(k+2);n++) {
		unsigned long long int temp = symbolCount[n];
		symbolCount.insert(n,runningSum);

		runningSum+=temp;
	}

	// create a new output
	ArrayType *listAout_ptr = new ArrayType(len);
	ArrayType &listAout     = *listAout_ptr;

	for(n=0;n<len;n++) {
		unsigned long long int symbol;

		if(listA[n]+offset >= slen) symbol=0; else
		symbol = s[listA[n]+offset]+1;	  // find out which symbol we're sorting
		listAout.insert(symbolCount[symbol],listA[n]);	  // put it in the right position
		symbolCount.insert(symbol,symbolCount[symbol]+1); // increment symbolCount to point to next position
	}
	
	// when doing multiple radix passes this is using additional time, not really required...
	// move listAout over listA

	for(n=0;n<len;n++) {
		listA.insert(n,listAout[n]);
	}
	delete listAout_ptr;
	delete symbolCount_ptr;

	return true;
}

};

#endif
