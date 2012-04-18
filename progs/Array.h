#ifndef ARRAY_H
#define ARRAY_H

class Array {
public:
	virtual unsigned long long int at(unsigned long long int position)=0;
	virtual unsigned long long int operator[](unsigned long long int position)=0;
	virtual void insert(unsigned long long int position,unsigned long long int value)=0;
	virtual ~Array(){}
};

#endif

