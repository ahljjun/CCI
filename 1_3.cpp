#include <iostream>
#include <string>
using namespace std;

bool isSameChars(string s1, string s2)  
{
	int s1Len = s1.length();
	int s2Len = s2.length();

	if ( s1Len != s2Len )
		return false;

    unsigned ret = 0;
	for(int i=0; i<s1Len; i++)
	{
		ret ^= s1[i] ^ s2[i] ;
	}

	return ret ? false : true;
}


void isSameChars_test()
{
	string s1 = "abcdefg";
    string s2 = "gfedcba";
    string s3 = "abewefwifgwg";

    cout<< isSameChars(s1, s2)<<endl;
    cout<< isSameChars(s1, s3)<<endl;
}


int main()
{
	isSameChars_test();
}
