#include <iostream>
#include <cassert>

using namespace std;

bool IsUniqueChars(const char *str)
{
    char ch[128] = {0};
    for(const char *p = str; *p ; p++)
    {
        ch[*p]++;
    }

    for(int i=0; i < 128; i++)
    {
        if ( ch[i] > 1 )
            return false;
    }

    return true;
}


void IsUniqueChars_test()
{
    const char* str1 = "abc123ABC*#& ";
    const char* str2 = " abc123ABC*#& ";
    assert(IsUniqueChars(str1));
    assert(!IsUniqueChars(str2));
    return ;
}

int main ()
{
    IsUniqueChars_test();
}
