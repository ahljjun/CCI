#include <iostream>

using namespace std;

void swap(char *p1, char *p2)
{
    char tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void reverse(char *str)
{
    if (!str)
        return ;

    char *pBegin, *pEnd;
    pBegin = str;
    pEnd = str+1;

    while(*pEnd)
        pEnd++;

    pEnd = pEnd-1;

    for(; pBegin < pEnd; pBegin++, pEnd--)
    {
        swap(pBegin, pEnd);
    }
}

void reverse_test()
{
    char str1[] = "abcdefg";
    char str2[] = "abcdef";
    cout<<"before reverse:"<<endl;
    cout<<"str1: "<<str1<<endl;
    cout<<"str2: "<<str2<<endl;

    reverse(str1);
    reverse(str2);

    cout<<"after reverse:"<<endl;
    cout<<"str1: "<<str1<<endl;
    cout<<"str2: "<<str2<<endl;
}


int main()
{
    reverse_test();
}



