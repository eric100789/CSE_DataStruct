#include <iostream>
#include <cstdio>
using namespace std;

class Tree
{
    private:
    Tree * left;
    Tree * right;
    int val;

    public:
    Tree()
    {
        left = nullptr;
        right = nullptr;
        val = -1;
    }
    Tree(int val)
    {
        left = nullptr;
        right = nullptr;
        this->val = val;
    }

    void add(int val)
    {
        if(this->val == -1)
        {
            this->val = val;
        }
        else if(this->val == val && this->left == nullptr && this->right == nullptr)
        {
            this->val = -1;
        }
        else if(this->val == val && this->left != nullptr && this->right == nullptr)
        {
            this->val = this->left->val;
            this->right = this->left->right;
            this->left= this->left->left;
        }
        else if(this->val == val && this->left == nullptr && this->right != nullptr)
        {
            this->val = this->right->val;
            this->left= this->right->left;
            this->right = this->right->right;
        }
        else if(this->val == val && this->left != nullptr && this->right != nullptr)
        {
            Tree * current = this->right;
            if(current->left == nullptr)
            {
                this->val = current->val;
                Tree * added = this->right;
                delete this->right;
                this->right = nullptr;
                return;
            }
            while(current->left->left != nullptr)
            {
                current = current->left;
            }
            this->val = current->left->val;
            Tree * added = current->left->right;
            delete current->left;
            current->left = added;
        }
        else if(this->right != nullptr && this->right->val == val)
        {
            if(this->right->left == nullptr && this->right->right == nullptr) 
            {
                delete this->right;
                this->right = nullptr;
            }
            else if(this->right->left == nullptr && this->right->right != nullptr)
            {
                Tree * added = this->right->right;
                delete this->right;
                this->right = added;
            }
            else if(this->right->left != nullptr && this->right->right == nullptr)
            {
                Tree * added = this->right->left;
                delete this->right;
                this->right = added;
            }
            else if(this->right->left != nullptr && this->right->right != nullptr)
            {
                Tree * current = this->right->right;
                if(current->left == nullptr)
                {
                    Tree * added = this->right->right;
                    delete this->right;
                    this->right = added;
                    return;
                }
                while(current->left->left != nullptr)
                {
                    current = current->left;
                }
                this->right->val = current->left->val;
                Tree * added = current->left->right;
                delete current->left;
                current->left = added;
            }
        }
        else if(this->left != nullptr && this->left->val == val)
        {
            if(this->left->left == nullptr && this->left->right == nullptr) this->left = nullptr;
            else if(this->left->left == nullptr && this->left->right != nullptr)
            {
                Tree * added = this->left->right;
                delete this->left;
                this->left = added;
            }
            else if(this->left->left != nullptr && this->left->right == nullptr)
            {
                Tree * added = this->left->left;
                delete this->left;
                this->left = added;
            }
            else if(this->left->left != nullptr && this->left->right != nullptr)
            {
                Tree * current = this->left->right;
                if(current->left == nullptr)
                {
                    this->left->val = current->val;
                    Tree * added = this->left->right;
                    delete this->left->right;
                    this->left->right = added;
                    return;
                }
                while(current->left->left != nullptr)
                {
                    current = current->left;
                }
                this->left->val = current->left->val;
                Tree * added = current->left->right;
                delete current->left;
                current->left = added;
            }
        }
        else if( this->val > val && this->left == nullptr)
        {
            this->left = new Tree(val);
        }
        else if( this->val < val && this->right == nullptr)
        {
            this->right = new Tree(val);
        }
        else if( this->val > val)
        {
            this->left->add(val);
        }
        else if( this->val < val)
        {
            this->right->add(val);
        }
    }

    void print_node()
    {
        if(this->left != nullptr)
        {
            this->left->print_node();
        }
        cout << this->val << " ";
        if(this->right != nullptr)
        {
            this->right->print_node();
        }
    }

    void print_left()
    {
        if(this->left != nullptr)
        {
            this->left->print_left();
        }
        if(this->left == nullptr) cout << "0 ";
        else cout << this->left->val << " ";
        if(this->right != nullptr)
        {
            this->right->print_left();
        }
    }

    void print_right()
    {
        if(this->left != nullptr)
        {
            this->left->print_right();
        }
        if(this->right == nullptr) cout << "0 ";
        else cout << this->right->val << " ";
        if(this->right != nullptr)
        {
            this->right->print_right();
        }
    }
};


int main()
{
    int a[] = {3,3,5,9,5,3,4,8,5,3,10,10,8};
    Tree A(-1);

    for(int i=0 ; i<13 ; i++)
    {
        A.add(a[i]);
        cout << "---------" << i << "---------" << endl;
        A.print_node();
        cout << endl;
        A.print_left();
        cout << endl;
        A.print_right();
        cout << endl;
    }

    return 0;
}