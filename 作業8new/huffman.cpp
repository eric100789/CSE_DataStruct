#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;

struct Encoder
{
    int prenum;
    string lastnum;
};

class Node
{
    private:
    int num;
    int val;
    Node * right;
    Node * left;
    string str;

    public:
    friend class Tree;
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
            //cout << "My:" << this->val << "/" << (char)this->val << "/num" << this->num << endl;
            return;
        }
        if(this->left) this->left->debug();
        if(this->right) this->right->debug();
    }
};

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

bool compare(const void* a, const void* b)
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

int string_to_dec(string tstr)
{
    int now=0;
    int tstrsize = tstr.size();
    for(int i=tstrsize ; i>=0 ; i--)
    {
        if(tstr[i] == '1') now+= pow(2,tstrsize-i);
    }
    return now;
}

void huff_encode(char * file_path, char * output_path)
{
    ifstream inputFile(file_path, ios::in | ios::binary);

    if(!inputFile) {
        cout << "error" <<endl;
        return;
    }

    char c;
    int i_arr[256] = {0};
    vector<char> text;
    vector<Node *> vec_node;
    
    while(inputFile.get(c))
    {
        i_arr[((int)c)+128] += 1;
        text.push_back(c);
    }
    for(int i=0; i<256; i++)
    {
        if(i_arr[i] > 0)
        {
            //cout << "Hey:" << (char)(i-128) << " has " << i_arr[i] << endl;
            vec_node.push_back(new Node(i-128,i_arr[i]));
        }
    }
    sort(vec_node.begin(),vec_node.end(), compare );

    while(vec_node.size() != 1)
    {
        Node * temp1 = vec_node.back(); vec_node.pop_back();
        Node * temp2 = vec_node.back(); vec_node.pop_back();
        vec_node.push_back( new Node(temp1,temp2) );
        sort(vec_node.begin(),vec_node.end(), compare );
        //delete temp1,temp2;
    }
    vec_node[0]->debug();
    vector<Encoder> huffmaned;
    vec_node[0]->makeEncoder(huffmaned);



    for(int i=0 ; i<huffmaned.size() ; i++)
    {
        cout << huffmaned[i].prenum << endl << huffmaned[i].lastnum << endl;
    }

    ofstream outputFile(output_path, ios::out | ios::binary);

    outputFile << huffmaned.size() << ' ' << text.size() << '\n';
    for(int i=0 ; i<huffmaned.size() ; i++)
    {
        outputFile << huffmaned[i].prenum << ' ' << huffmaned[i].lastnum.size() << ' ';

        char tmp = 0, cnt = 0;
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
        outputFile << '\n';
    }

    char tmp = 0, cnt = 0;
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

void huff_decode(char * file_path, char * output_file)
{
    ifstream inputFile(file_path, ios::in | ios::binary);
    ofstream outputFile(output_file, ios::out | ios::binary);
    int decode_num,text_num; inputFile >> decode_num >> text_num;
    map<string, int> huffmanMap;

    for(int i=0 ; i<decode_num ; i++)
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

            if(huffmanMap.find(ans) != huffmanMap.end())
            {
                if(nowch >= text_num) goto STOP;
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
        huff_encode(argv[2],argv[3]);
    }
    else if(argc == 6)
    {
        huff_decode(argv[2],argv[3]);
    }
    else if(argc == 4)
    {
        huff_encode(argv[1],argv[2]);
        huff_decode(argv[2],argv[3]);
    }
    else
    {
        cout << "SOMETHING WRONG!" << endl;
    }
    
    return 0;
}