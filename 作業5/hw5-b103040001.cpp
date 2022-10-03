#include <iostream>
using namespace std;

class LinkList // class of linklist
{
    private:
    // record value
    int val;
    // record exponent
    int exp;
    // next node
    LinkList * next;

    public:
    // constructor
    LinkList()
    {
        val = 0;
        exp = 0;
        next = NULL;
    }
    // destructor
    ~LinkList(){}
    LinkList(int val , int exp)
    {
        this->exp = exp;
        this->val = val;
        this->next = NULL;
    }

    // print all things and remove all 0 value
    void debug()
    {
        // remove zero (0*x^3)
        this->remove_zero();
        // current
        LinkList * current = this;
        // walk 
        while(current->next != NULL)
        {
            cout << current->val << " " << current->exp << endl;
            current = current->next;
        }
        cout << current->val << " " << current->exp << endl;
    }

    // remove zero (such as 0*x^3)
    void remove_zero()
    {
        LinkList * current = this;
        LinkList * temp;

        // first value is 0 and every thing is goodbye
        if(current->val == 0 && current->next == NULL)
        {
            this->exp = 0;
            return;
        }
        // val not good
        else if(current->val == 0)
        {
            this->val = this->next->val;
            this->exp = this->next->exp;
            this->next = this->next->next;
        }

        // we should stop walking
        if(current->next == NULL) return;
        // delete node must do: current->next->next
        while (current->next->next != NULL)
        {
            // if current's next is 0
            if(current->next->val == 0)
            {
                temp = current->next->next;
                // delete the target
                delete current->next;
                current->next = temp;
            }
            current = current->next;
            if(current->next == NULL) return;
        }
        
        // because of while, we should do another test
        if(current->next->val == 0)
        {
            delete current->next;
            current->next = NULL;
        }
        
    }

    // kill the data
    void reset()
    {
        LinkList * current_this = this->next;
        LinkList * temp = NULL;
        int val,exp;
        
        while(current_this!=NULL && current_this->next != NULL)
        {
            // i got to keep my data alive to delete them
            temp = current_this->next;
            delete current_this;
            current_this = temp;
        }
        delete current_this;

        // reset the val and exp to 0
        this->val = 0;
        this->exp = 0;
        this->next = NULL;
    }

    void add(int val , int exp)
    {
        // bad value:0
        if(val == 0) return;
        LinkList * current = this;

        // find the place we should insert
        // insert at first
        if(current->exp < exp)
        {
            LinkList * added = new LinkList(this->val,this->exp);
            current->val=val;
            current->exp=exp;
            added->next = current->next;
            current->next = added;
            return;
        }
        // add val at first
        else if(current->exp == exp)
        {
            current->val += val;
            return;
        }
        // not first
        else
        {
            while(current->next != NULL)
            {
                // adding value
                if(current->next->exp == exp)
                {
                    current->next->val += val;
                    return;
                }
                // insert here
                else if(current->next->exp < exp)
                {
                    LinkList * added = new LinkList(val,exp);

                    added->next = current->next;
                    current->next = added;
                    return;
                }
                // next node
                else
                {
                    current = current->next;
                }
            }
            // last test(adding)
            if(current->exp == exp)
            {
                current->val += val;
                return;
            }
            // last test(insert)
            LinkList * added = new LinkList(val,exp);
            current->next = added;
        }
    }

    // operator + make two target be added
    LinkList operator+ (LinkList & target)
    {
        LinkList new_list; // a none linklist
        LinkList * current_this = this;
        LinkList * current_tar = &target;

        // add all a into new_list
        while(current_this->next != NULL)
        {
            new_list.add(current_this->val,current_this->exp);
            current_this = current_this->next;
        }
        new_list.add(current_this->val,current_this->exp);
       
       // add all b into new_list
        while(current_tar->next != NULL)
        {
            new_list.add(current_tar->val,current_tar->exp);
            current_tar = current_tar->next;
        }
        new_list.add(current_tar->val,current_tar->exp);
 		
        // avoid bug
        new_list.remove_zero();
        
        // return my new linklist
        return new_list;
    }

    // operator + make two target be multify
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
        new_list.remove_zero();
        return new_list;
    }

    // = place A to B
    LinkList operator= (LinkList target)
    {   
        LinkList new_list;
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

        cout << "ADD" << endl;
        C = A+B;
        C.debug();

        cout << "MULTIPLY" << endl;
        C = A*B;
        C.debug();
    }
    




   return 0;
}
