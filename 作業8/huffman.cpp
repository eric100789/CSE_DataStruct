#include <iostream>
#include <fstream>
using namespace std;

void huff_encode(char * file_path)
{
    cout << file_path << endl;
}

int main(int argc, char *argv[])
{
    if(argc == 4)
    {
        huff_encode(argv[3]);
    }
    else
    {

    }
    
    return 0;
}