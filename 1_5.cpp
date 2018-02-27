#include <iostream>
#include <string>

using std::string;

string compressString(string sourceString)
{
    int len = sourceString.length();
    string retStr;
    int i =0, j=0;
    while( i < len )
    {
        int j = i+1;
        while( j < len )
        {
            if ( sourceString[j] == sourceString[i] )
                j++;
            else
                break;
        }

        retStr.push_back(sourceString[i]);
        retStr.push_back( j-i + '0');
        i = j;
    }

    std::cout<<"retStr: "<< retStr<< std::endl;
    return retStr.length() >= len ? sourceString : retStr;
}


void test_1()
{
    string test1 = "aabcccccaaa";
    string test2 = compressString(test1);

    std::cout<<"test1: "<< test1 << std::endl;
    std::cout<< "test2: "<<test2<<std::endl;

    string test3 = "abcdcccce";
    string test4 = compressString(test3);

    std::cout<<"test3: "<< test3 << std::endl;
    std::cout<< "test4: "<<test4<<std::endl;
}

int main()
{
    test_1();

    return 0;
}
