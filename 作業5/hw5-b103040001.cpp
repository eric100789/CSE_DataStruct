#include <iostream>
using namespace std;

/*
Author: B103040001 孫世諭
Date: Sept. 19,2022
Purpose: 設計一個程式，可以處理兩個多項式之加法與乘法
*/

// class linklist
class LinkList
{
    private:
    int val;
    int exp;
    LinkList * next;

    public:
    LinkList() // constructer
    {
        val = 0;
        exp = 0;
        next = NULL;
    }
    ~LinkList(){} // destructor
    LinkList(int val , int exp) // constructer with value
    {
        this->exp = exp;
        this->val = val;
        this->next = NULL;
    }

    void debug() // print the linklist and kill 0-value class
    {
        this->remove_zero();
        LinkList * current = this;
        while(current->next != NULL)
        {
            cout << current->val << " " << current->exp << endl;
            current = current->next;
        }
        cout << current->val << " " << current->exp << endl;
    }

    void remove_zero() // kill 0-value class
    {
        LinkList * current = this;
        LinkList * temp;

        if(current->val == 0 && current->next == NULL)
        {
            this->exp = 0;
            return;
        }
        else if(current->val == 0)
        {
            this->val = this->next->val;
            this->exp = this->next->exp;
            this->next = this->next->next;
        }

        if(current->next == NULL) return;
        while (current->next->next != NULL)
        {
            if(current->next->val == 0)
            {
                temp = current->next->next;
                delete current->next;
                current->next = temp;
            }
            current = current->next;
            if(current->next == NULL) return;
        }
        
        if(current->next->val == 0)
        {
            delete current->next;
            current->next = NULL;
        }
        
    }

    void reset() // reset the linklist 
    {
        LinkList * current_this = this->next;
        LinkList * temp = NULL;
        int val,exp;
        
        while(current_this!=NULL && current_this->next != NULL)
        {
            temp = current_this->next;
            delete current_this;
            current_this = temp;
        }
        delete current_this;

        this->val = 0;
        this->exp = 0;
        this->next = NULL;
    }

    // add val and exp to target linklist
    void add(int val , int exp)
    {
        if(val == 0) return; // wrong input
        LinkList * current = this; 

        if(current->exp < exp)
        {
            LinkList * added = new LinkList(this->val,this->exp);
            current->val=val;
            current->exp=exp;
            added->next = current->next;
            current->next = added;
            return;
        }
        else if(current->exp == exp)
        {
            current->val += val;
            return;
        }
        else
        {
            while(current->next != NULL)
            {
                if(current->next->exp == exp)
                {
                    current->next->val += val;
                    return;
                }
                else if(current->next->exp < exp)
                {
                    LinkList * added = new LinkList(val,exp);

                    added->next = current->next;
                    current->next = added;
                    return;
                }
                else
                {
                    current = current->next;
                }
            }
            if(current->exp == exp)
            {
                current->val += val;
                return;
            }
            LinkList * added = new LinkList(val,exp);
            current->next = added;
        }
    }

    // operator + in order to add two linklist
    LinkList operator+ (LinkList & target)
    {
        // add to current for two linklist
        LinkList new_list;
        LinkList * current_this = this;
        LinkList * current_tar = &target;

        // keep going until next ptr is NULL
        while(current_this->next != NULL)
        {
            new_list.add(current_this->val,current_this->exp);
            current_this = current_this->next;
        }
        new_list.add(current_this->val,current_this->exp); // add now current
       
       // do it again
        while(current_tar->next != NULL)
        {
            new_list.add(current_tar->val,current_tar->exp);
            current_tar = current_tar->next;
        }
        new_list.add(current_tar->val,current_tar->exp); // add now tar_current
 		
        // if there is any 0-value, we GG
        new_list.remove_zero();
        
        return new_list;
    }

    // operator * in order to multipy
    LinkList operator* (LinkList target)
    {
        LinkList new_list;
        LinkList * current_this = this;
        LinkList * current_tar = &target;

        while(current_this->next != NULL)
        {
            current_tar = &target;
            while(current_tar->next != NULL)
            {
                new_list.add(current_this->val*current_tar->val , current_this->exp+current_tar->exp);
                current_tar = current_tar->next;
            }
            new_list.add(current_this->val*current_tar->val , current_this->exp+current_tar->exp);
            current_this = current_this->next;
        }
        current_tar = &target;
        while(current_tar->next != NULL)
        {
            new_list.add(current_this->val*current_tar->val , current_this->exp+current_tar->exp);
            current_tar = current_tar->next;
        }
        new_list.add(current_this->val*current_tar->val , current_this->exp+current_tar->exp);
        // if there is any 0-value, we GG
        new_list.remove_zero();
        return new_list;
    }

    LinkList operator= (LinkList target)
    {   
        LinkList new_list; // new list to make target assign
        LinkList * current_this = this->next;
        LinkList * current_tar = &target;
        LinkList * temp = NULL;
        int val,exp;
        
        while(current_this!=NULL && current_this->next != NULL)
        {
            temp = current_this->next;
            delete current_this;
            current_this = temp;
        }
        delete current_this;

        while(current_tar->next != NULL)
        {
            new_list.add(current_tar->val,current_tar->exp);
            //cout << "adding" <<  current_tar->val << "," << current_tar->exp << endl;
            current_tar = current_tar->next;
        }
        new_list.add(current_tar->val,current_tar->exp);
        //cout << "adding" <<  current_tar->val << "," << current_tar->exp << endl;
        
        this->val = 0;
        this->exp = 0;
        this->next = &new_list;
        
        this->remove_zero();   
        return *this;
    }
};

int main()
{
    int input_p,input_q,input_n,input_m;
    LinkList A,B,C;
    int cases = 0;

    // some input
    while(true)
    {
        A.reset();
        B.reset();
        cases++;
        cin >> input_p;
        for(int i=0 ; i<input_p ; i++)
        {
            cin >> input_n >> input_m;
            A.add(input_n,input_m);
        }
        cin >> input_q;
        for(int i=0 ; i<input_q ; i++)
        {
            cin >> input_n >> input_m;
            B.add(input_n,input_m);
        }

        if(input_p == 0 && input_q == 0) return 0;

        cout << "Case" << cases << ":" << endl;

        cout << "ADD" << endl;
        C = A+B;
        C.debug();

        cout << "MULTIPLY" << endl;
        C = A*B;
        C.debug();
    }
    




   return 0;
}
