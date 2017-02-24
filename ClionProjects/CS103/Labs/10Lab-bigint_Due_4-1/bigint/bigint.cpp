#include "bigint.h"

using namespace std;

BigInt::BigInt(string s)
{
	for(int i=0;i<s.size();i++)
	{
		char temp1=s[i];
		int temp2=temp1-'0'; // convert the char into a integer
		bigint.push_back(temp2); // add the int into the vector
	}
	base=10;		 // base is 10 by default
}

BigInt::BigInt(string s,int b)
{
	for(int i=0;i<s.size();i++)
	{
		char temp1=s[i];
		if(temp1>='0'&&temp1<='9')
		{
			int temp2=temp1-'0'; // convert the char into a integer
			bigint.push_back(temp2); // add the int into the vector
		}
		else if(temp1>='A' && temp1 <='Z')
		{
			int temp2=temp1-55; // convert the char into a integer
			bigint.push_back(temp2); // add the int into the vector
		}
	}
	base=b;
}
string BigInt::to_string()
{
	string s;
	for(int i=0;i<bigint.size();i++)
	{
		if(bigint[i]<10)
		{	
			char temp=bigint[i]+'0'; // convert the int back into a char
			s+=temp; 	// add the character to the string 
		}
		else 
		{
			char temp=bigint[i]+55; // convert the int back into a char
			s+=temp; 	// add the character to the string 
		}
	}
	return s;
}

void BigInt::add(BigInt b)
{
	if(base==b.base)
	{
		int dif=bigint.size()-b.bigint.size();
		if(dif>0)
		{
			for(int i=0;i<dif;i++)
			{
				b.bigint.insert(b.bigint.begin()+0,0);
			}
		}
		else if(dif<0)
		{
			dif=-dif;
			for(int i=0;i<dif;i++)
			{
				bigint.insert(bigint.begin()+0,0);
			}
		}	
		for(int i=bigint.size()-1;i>=1;i--)  // count to the last second number
		{
			bigint[i]+=b.bigint[i];
			if(bigint[i]>=base)    //carry 1 if bigger than the base
			{
			bigint[i]-=base;
			bigint[i-1]++;
			}
		}
		bigint[0]+=b.bigint[0];
		if(bigint[0]>=10)
		{
		bigint[0]-=base;
		bigint.insert(bigint.begin()+0,1);
	}
		
		
	}
	else
	{
		throw runtime_error("Error-different bases");
	}
}