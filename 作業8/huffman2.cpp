#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 
#include <vector>
#include <algorithm>
using namespace std;

struct Encoder
{
    int prenum;
    string lastnum;
};

struct Decoder
{
    int prenum;
    int len;
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

void huff_encode(char * file_path)
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

    ofstream outputFile("output.txt", ios::out | ios::binary);

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

void huff_decode(char * file_path)
{
    //cout << "---------"<<endl;
    ifstream inputFile(file_path, ios::in | ios::binary);
    ofstream outputFile("unzipped.txt", ios::out | ios::binary);
    int decode_num,text_num; inputFile >> decode_num >> text_num;
    vector<Decoder> huffmaned;
    for(int i=0 ; i<decode_num ; i++)
    {
        Decoder temp; string get_str="";
        char ch;
        inputFile >> temp.prenum >> temp.len;
        inputFile.get();
        for(int j=0 ; j<=(temp.len-1)/8 ; j++)
        {
            char ch;
            ch = inputFile.get();
            get_str += ch;
        }
        temp.lastnum = convert_string(get_str,temp.len);
        huffmaned.push_back(temp);
        //cout<< "here:" << temp.prenum << "/" << temp.len << "/" << temp.lastnum << endl;
    }
    inputFile.get();
    char ch;
    int cnt=0;
    int nowch = 0;
    string ans = "";  
    while(~(ch=inputFile.get()))
    {
        for(int i=0; i<8 ; i++)
        {
            if( ((ch>>(7-i))&1) == 1) ans+= '1';
            else ans += '0';
            for(int j=0; j<huffmaned.size() ; j++)
            {
                if(huffmaned[j].lastnum == ans )
                {
                    if(nowch > text_num) goto STOP;
                    nowch++;
                    //cout << huffmaned[j].lastnum << "/" << ans << "/" << huffmaned[j].prenum << "/" << (char)huffmaned[j].prenum << endl;
                    outputFile << (char)huffmaned[j].prenum;
                    ans = "";
                    break;
                }
            }
        }
    }
    STOP:
    outputFile.close();
    inputFile.close();
}

int main(int argc, char *argv[])
{
    if(argc == 4)
    {
        huff_encode(argv[3]);
    }
    else
    {
        char a[]= "output.txt";
        huff_encode(argv[1]);
        huff_decode(a);
    }
    
    return 0;
}