#include <iostream>
using namespace std;

string convert_string(string tar, int len)
{
    string ans = "";
    for (int i=0 ; i<=(len-1)/8 ; i++)
    {        
        char a=tar[i];
        int nowlen;
        if(i==(len-1)/8) nowlen = (len-1)%8+1;
        else nowlen=8;
        for(int j=0 ; j<nowlen ; j++)
        {
            if( ((a>>(7-j))&1) == 1) ans+= '1';
            else ans += '0';
        }
    }
    return ans;
}

string convert_string2(string tar, int len)
{
    string ans = "";
    if(len <=8)
    {        
        char a=tar[0];
        for(int j=0 ; j<len ; j++)
        {
            if( ((a>>(7-j))&1) == 1) ans+= '1';
            else ans += '0';
        }
    }
    else if(len >8)
    {        
        char a=tar[0];
        for(int j=0 ; j<8 ; j++)
        {
            if( ((a>>(7-j))&1) == 1) ans+= '1';
            else ans += '0';
        }
        a=tar[1];
        len -=8 ;
        for(int j=0 ; j<len ; j++)
        {
            if( ((a>>(7-j))&1) == 1) ans+= '1';
            else ans += '0';
        }
    }
    return ans;
}

int main()
{
    cout << "�" << (char)'a' << (int)'a' << endl;
    cout << "�" << convert_string("ab",8) << endl;
    cout << "�" << convert_string2("ab",16) << endl;
}