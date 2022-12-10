#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;

/*
Author: B103040001 孫世諭
Date: December. 11,2022
Purpose: 以Huffman演算法製作一個檔案壓縮與解壓縮之軟體，而且我有GUI
*/

struct Encoder // 建立一個 Encoder Struct 紀錄編碼前編碼後
{
    int prenum; // 讀到的字元的ASCII
    string lastnum; // 讀完後變成binary 以 string 的形式儲存
};

class Node // Tree 的部分
{
    private:
    int num;
    int val;
    Node * right;
    Node * left;
    string str;

    public:
    friend class Tree; // 我好像沒有class Tree???
    Node()
    {
        this->num = 0;
        this->right = nullptr;
        this->left = nullptr;
        str = "";
    }
    Node(int val, int num)
    {
        this->val = val;
        this->num = num;
        this->right = nullptr;
        this->left = nullptr;
        this->str = "";
        str += (char)val;
    }
    Node(int val, int num, Node * right, Node * left)
    {
        this->val = val;
        this->num = num;
        this->right = right;
        this->left = left;
        this->str = "";
        this->str += (char)val;
    }
    Node(Node * right, Node * left)
    {
        this->val = right->val + left->val;
        this->num = right->num + left->num;
        this->right = right;
        this->left = left;
        this->str += (char)right->val;
        this->str += (char)left->val;
    }
    int getNum()
    {
        return num;
    }
    int getVal()
    {
        return val;
    }
    string getStr()
    {
        return str;
    }
    void makeEncoder(vector<Encoder> & target, string now="")
    {
        if(this->right == nullptr && this->left == nullptr)
        {
            Encoder temp;
            temp.prenum = this->val;
            temp.lastnum = now;
            target.push_back(temp);
        }
        else
        {
            if(this->left)
            this->left->makeEncoder(target, now+"0");
            if(this->right)
            this->right->makeEncoder(target, now+"1");
        }
    }
    void debug()
    {
        if(this->left == nullptr && this->right == nullptr)
        {
            return;
        }
        if(this->left) this->left->debug();
        if(this->right) this->right->debug();
    }
};

string convert_string(string tar, int len) // 輸入一個被編碼過後的binary char string，接下來len是判斷要看幾個binary
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

bool compare(const void* a, const void* b) // 用來sort的東西
{
    const int x = ((Node*)a)->getNum();
    const int y = ((Node*)b)->getNum();
    const int p = ((Node*)a)->getVal();
    const int q = ((Node*)b)->getVal();

    if (x < y)
        return false;
    else if (x > y)
        return true;
    else if(x == y)
    {
        if (p < q)
            return false;
        else if (p > q)
            return true;
    }

    return false;
}

void huff_encode(char * file_path, char * output_path) // encode 主軸
{
    ifstream inputFile(file_path, ios::in | ios::binary); // 打開我要編的東西

    if(!inputFile) { // 如果被騙了
        cout << "error" <<endl;
        return;
    }

    char c; // 開始一個一個看
    int i_arr[256] = {0}; // 用256陣列當作SET
    vector<char> text; // 每一個text
    vector<Node *> vec_node; // 存Node的東西 做賀夫曼術用
    
    while(inputFile.get(c)) // 一直看阿
    {
        i_arr[((int)c)+128] += 1; // 紀錄數量
        text.push_back(c); // 紀錄咚咚
    }
    for(int i=0; i<256; i++)
    {
        if(i_arr[i] > 0)
        {
            vec_node.push_back(new Node(i-128,i_arr[i])); // 建立TREE
        }
    }
    sort(vec_node.begin(),vec_node.end(), compare ); 

    while(vec_node.size() != 1) // 瘋狂合併
    {
        Node * temp1 = vec_node.back(); vec_node.pop_back();
        Node * temp2 = vec_node.back(); vec_node.pop_back();
        vec_node.push_back( new Node(temp1,temp2) );
        sort(vec_node.begin(),vec_node.end(), compare ); // 每合併一次就要整理一次
    }
    vec_node[0]->debug(); // debug
    vector<Encoder> huffmaned; // good
    vec_node[0]->makeEncoder(huffmaned); // easy?



    for(int i=0 ; i<huffmaned.size() ; i++)
    {
        cout << huffmaned[i].prenum << endl << huffmaned[i].lastnum << endl; // debug
    }

    ofstream outputFile(output_path, ios::out | ios::binary); // 打開檔案開存

    outputFile << huffmaned.size() << ' ' << text.size() << '\n'; // HEADERS
    for(int i=0 ; i<huffmaned.size() ; i++)
    {
        outputFile << huffmaned[i].prenum << ' ' << huffmaned[i].lastnum.size() << ' '; // HEADERS

        char tmp = 0, cnt = 0; // 處理該死的二進位 把string 變成 char 存成 header
        for(int j=0 ; j<huffmaned[i].lastnum.size() ; j++)
        {
            tmp <<= 1;
            tmp |= ( huffmaned[i].lastnum[j] - '0');
            cnt++;
            if(cnt==8)
            {
                outputFile << tmp;
                tmp = cnt = 0;
            }
        }
        if (cnt)
        {
            tmp <<= (8 - cnt);
            outputFile << tmp;
        }
        outputFile << '\n'; // 一個HEADER換一行
    }// 終於結束HEADER

    char tmp = 0, cnt = 0; // 這邊是無情的壓縮檔案 
    /* 
        作法是把所有char都擠在一起
        Header的存法 EX: 193 6 11000000 但看的時候只看前6個 110000
        壓縮檔案存法 EX: 11000011 00001111 那就是兩個193加一個1111對應的東東
    */
    for(int i=0 ; i<text.size() ; i++)
    {
        int index;
        for(int j=0 ; j<huffmaned.size() ; j++)
        {
            if(huffmaned[j].prenum == text[i])
            {
                index = j;
                //cout << huffmaned[j].lastnum;
                break;
            }
        }

        for(int j=0 ; j<huffmaned[index].lastnum.size() ; j++)
        {
            tmp <<= 1;
            tmp |= ( huffmaned[index].lastnum[j] - '0');
            cnt++;
            if(cnt==8)
            {
                outputFile << tmp;
                tmp = cnt = 0;
            }
        }
    }
    if (tmp)
    {
        tmp <<= (8 - cnt);
        outputFile << tmp;
    }

    outputFile.close();
    inputFile.close();
}

void huff_decode(char * file_path, char * output_file) // 瘋狂DECODE
{
    ifstream inputFile(file_path, ios::in | ios::binary);
    ofstream outputFile(output_file, ios::out | ios::binary);
    int decode_num,text_num; inputFile >> decode_num >> text_num;
    map<string, int> huffmanMap; // 這邊用map存編碼表

    for(int i=0 ; i<decode_num ; i++) // 存起來
    {
        int prenum, len; string get_str="",lastnum;
        char ch;
        inputFile >> prenum >> len;
        inputFile.get();
        for(int j=0 ; j<=(len-1)/8 ; j++)
        {
            char ch;
            ch = inputFile.get();
            get_str += ch;
        }
        lastnum = convert_string(get_str, len);
        huffmanMap[ lastnum ] = prenum;
    }

    inputFile.get();
    char ch;
    int cnt=0;
    int nowch = 0;
    string ans = "";  
    while(!inputFile.eof())
    {
        ch=inputFile.get();
        for(int i=0; i<8 ; i++) 
        {
            if( ((ch>>(7-i))&1) == 1) ans+= '1';
            else ans += '0'; 
            // 每讀一次我就測試一遍，用for會慢到哭，所以這邊我用map增加搜尋速度
            if(huffmanMap.find(ans) != huffmanMap.end()) // 如果STRING在這個MAP有對應的東西的話我就直接寫入檔案
            {
                if(nowch >= text_num) goto STOP; // 其實程式應該結束了 所以我就跳到STOP
                nowch++;
                outputFile << (char)huffmanMap[ans]; 
                ans = "";
            }
        }
    }
    STOP:
    outputFile.close();
    inputFile.close();
}

int main(int argc, char *argv[])
{
    if(argc == 5)
    {
        huff_encode(argv[2],argv[3]); // 串接Python GUI用的
    }
    else if(argc == 6)
    {
        huff_decode(argv[2],argv[3]); // 串接Python GUI用的
    }
    else if(argc == 4)
    {
        huff_encode(argv[1],argv[2]); // 單純的用終端機輸入
        huff_decode(argv[2],argv[3]);
    }
    else
    {
        cout << "SOMETHING WRONG!" << endl;
    }
    
    return 0;
}