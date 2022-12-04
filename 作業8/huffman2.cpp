#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 
#include <vector>
#include <algorithm>
using namespace std;
#define testF do{char test;\
    while(inputFile>>test)\
    {\
        cout << test;\
    }}while(0)

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
    bool isadd;
    Node * right;
    Node * left;

    public:
    friend class Tree;
    Node()
    {
        this->num = 0;
        this->right = nullptr;
        this->left = nullptr;
        isadd = false;
    }
    Node(int val, int num, bool isAdded)
    {
        this->val = val;
        this->num = num;
        this->right = nullptr;
        this->left = nullptr;
        this->isadd = isAdded;
    }
    Node(int val, int num, Node * right, Node * left, bool isAdded)
    {
        this->val = val;
        this->num = num;
        this->right = right;
        this->left = left;
        this->isadd = isAdded;
    }
    Node(Node * right, Node * left)
    {
        this->val = right->val + left->val;
        this->num = right->num + left->num;
        this->right = right;
        this->left = left;
        this->isadd = true;
    }
    int getNum()
    {
        return num;
    }
    int getVal()
    {
        return val;
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
            
            this->left->makeEncoder(target, now+"0");
            this->right->makeEncoder(target, now+"1");
            
        }
    }

};

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

int binary_search(const vector<Encoder> &data, int key) {
    int low = 0;
    int high = data.size()-1;
    while (low <= high) {
        int mid = int((low + high) / 2);
        if (key == data[mid].prenum)
            return mid;
        else if (key > data[mid].prenum)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
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
            vec_node.push_back(new Node(i-128,i_arr[i],false));
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
    vector<Encoder> huffmaned;
    vec_node[0]->makeEncoder(huffmaned);



    for(int i=0 ; i<huffmaned.size() ; i++)
    {
        cout << huffmaned[i].prenum << endl << huffmaned[i].lastnum << endl;
    }

    ofstream outputFile("output.txt", ios::out | ios::binary);

    outputFile << huffmaned.size() << '\n';
    for(int i=0 ; i<huffmaned.size() ; i++)
    {
        outputFile << huffmaned[i].prenum << ' ' << huffmaned[i].lastnum.size() << ' ' << huffmaned[i].lastnum << endl;
    }

    for(int i=0 ; i<text.size() ; i++)
    {
        //int index = binary_search(huffmaned, text[i]);
        /*if(index == -1)
        {
            cout << "ohno" << endl;
            continue;
        }*/
        int index;
        for(int j=0 ; j<huffmaned.size() ; j++)
        {
            if(huffmaned[j].prenum == text[i])
            {
                outputFile << huffmaned[j].lastnum;
                break;
            }
        }
        
    }


    outputFile.close();
    inputFile.close();
}

void huff_decode(char * file_path)
{
    cout << "-----------------------------------" << endl;
    ifstream inputFile(file_path, ios::in | ios::binary);

    int huff_num;
    inputFile >> huff_num;
    vector<Encoder> huff_vec;    

    for(int i=0 ; i<huff_num ; i++)
    {
        Encoder temp;
        string last = "";
        int len;
        inputFile >> temp.prenum >> len >> temp.lastnum ;
        cout << temp.prenum << " " << len << " " << temp.lastnum  << endl;
        huff_vec.push_back(temp);
    }

    string get_huff;
    ofstream outputFile("output_unzipped.txt", ios::out | ios::binary);
    while (inputFile >> get_huff)
    {
        for(int j=0 ; j<huff_vec.size() ; j++)
        {
            if(huff_vec[j].lastnum == get_huff)
            {
                outputFile << huff_vec[j].prenum;
                break;
            }
        }
    }

    inputFile.close();
    outputFile.close();
}

int main(int argc, char *argv[])
{
    if(argc == 4)
    {
        huff_encode(argv[3]);
    }
    else
    {
        char a[] = "output.txt";
        huff_encode(argv[0]);
        huff_decode(a);
    }
    
    return 0;
}