#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

/*
Author: B103040001 孫世諭
Date: November. 10,2022
Purpose: 給予一串數字，找出所有出現次數為奇數之數字
*/

class Tree;
class Node // create a node
{
    private:
    int value; // value
    Node * left; // left
    Node * right; // right

    public:
    friend class Tree;
    Node() // constructir
    {
        left = nullptr;  // left Node
        right = nullptr; // right Node
    }
    Node(int num)// constructor (num)
    {
        value = num; // num
        left = nullptr;
        right = nullptr;
    }
    void setLeft(int num) // set left node
    {
        Node *new_node = new Node(num); // make a new node
        this->left = new_node;
    }
    void setRight(int num) // set right node
    {
        Node *new_node = new Node(num); // make a new node
        this->right = new_node;
    }
    void print_left() // print
    {
        if(this->left != nullptr)
        {
            this->left->print_left();
        }
        if(this->left == nullptr) cout << "0 ";
        else cout << this->left->value << " ";
        if(this->right != nullptr)
        {
            this->right->print_left();
        }
    }

    void print_right() // print
    {
        if(this->left != nullptr)
        {
            this->left->print_right();
        }
        if(this->right == nullptr) cout << "0 ";
        else cout << this->right->value << " ";
        if(this->right != nullptr)
        {
            this->right->print_right();
        }
    }
    void print_node() // print
    {
        if(this->left != nullptr)
        {
            this->left->print_node();
        }
        cout << this->value << " ";
        if(this->right != nullptr)
        {
            this->right->print_node();
        }
    }
};

class Tree // create a tree (head)
{
    private:
    Node * head; 

    public:
    Tree()
    {
        head = nullptr; // constructor 
    }
    void add(int num) // add a new number
    {
        if(head == nullptr) // if there is no node in this tree
        {
            Node *new_node = new Node(num);
            head = new_node;
        }
        else // else
        {
            Node * current = head;
            Node * prev = current;
            while(1)
            {
                if(current->value == num) // if there has a same num
                {
                    if(head == current && (head->left == nullptr || head->right == nullptr) ) // on head
                    {
                        if(current->left == nullptr && current->right == nullptr)
                        {
                            head = nullptr;
                        }
                        else if(current->left != nullptr && current->right == nullptr)
                        {
                            head = head->left;
                            delete current;
                        }
                        else if(current->left == nullptr && current->right != nullptr)
                        {
                            head = head->right;
                            delete current;
                        }
                    }
                    else if(current->left == nullptr && current->right == nullptr ) // not head (no no no)
                    {
                        if(prev->left == current)
                        {
                            delete prev->left;
                            prev->left = nullptr;
                        }
                        else if(prev->right == current)
                        {
                            delete prev->right;
                            prev->right = nullptr;
                        }
                    }
                    else if(current->left == nullptr && current->right != nullptr )// not head (only has right)
                    {
                        if(prev->left == current)
                        {
                            prev->left = current -> right;
                            delete current;
                        }
                        else if(prev->right == current)
                        {
                            prev->right = current -> right;
                            delete current;
                        }
                    }
                    else if(current->left != nullptr && current->right == nullptr ) // not head (only has left)
                    {
                        if(prev->left == current)
                        {
                            prev->left = current ->left;
                            delete current;
                        }
                        else if(prev->right == current)
                        {
                            prev->right = current ->left;
                            delete current;
                        }
                    }
                    else if(current->left != nullptr && current->right != nullptr ) // all has node
                    {
                        Node * stay_current = current;
                        prev = current;
                        current = current->right;
                        if(current->left == nullptr) // something wrong
                        {
                            stay_current->value = current->value;
                            prev->right = current->right;
                            delete current;
                            return;
                        }
                        while(current->left != nullptr) // tree walk
                        {
                            prev = current;
                            current = current->left;
                        }
                        stay_current->value = current->value;
                        prev->left = current->right;
                        delete current;
                    }
                    return;
                }
                else if(current->value > num && current->left == nullptr) // its time to set a node
                {
                    current->setLeft(num);
                    return;
                }
                else if(current->value < num && current->right == nullptr) // its time to set a node
                {
                    current->setRight(num);
                    return;
                }
                else if(current->value > num && current->left != nullptr) // tree walk
                {
                    prev = current;
                    current = current->left;
                }
                else if(current->value < num && current->right != nullptr) // tree walk
                {
                    prev = current;
                    current = current->right;
                }
            }
        }
    }

    void print_node()
    {
        if(head==nullptr) return; // i hate you
        head->print_node();
    }
    void print_right()
    {
        if(head==nullptr) return; // i hate you
        head->print_right();
    }
    void print_left()
    {
        if(head==nullptr) return; // i hate you
        head->print_left();
    }


};

int main()
{
    vector<int> a;
    int input;

    while( cin >> input )
    {
        if (input == -1)
        {
            Tree A;
            for(int i=0 ; i<a.size() ; i++)
            {
                A.add(a[i]);
            }
            cout << "node: ";
            A.print_node();
            cout << endl << "left: ";
            A.print_left();
            cout << endl << "right: ";
            A.print_right();
            cout << endl;
            a.clear();
        }
        else
        {
            a.push_back(input);
        }
    }



    return 0;
}