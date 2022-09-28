#include <iostream>
#include <string>

using namespace std;

/*
Author: B103040001 孫世諭
Date: Sept. 9,2022
Purpose: 以C++製作一個「集合」類別 (set class)，使其能進行「聯集」、「交集」、「差集」、「包含」、「屬於」等五種運算。
*/

// adding a class set
class set
{
    private:
    // array to save the ascii code the string involved
    bool ascii_set[256];

    public:
    // constructer
    // make all of array bool false
    // then, make the ascii of char's index to true
    // for example, if A(65) exist, array[65] = true
    set()
    {
        for(int i=0 ; i<256 ; i++) ascii_set[i] = false;
    }

    set(char c)
    {
        for(int i=0 ; i<256 ; i++) ascii_set[i] = false;
        ascii_set[c] = true;
    }

    set(string target)
    {
        for(int i=0 ; i<256 ; i++) ascii_set[i] = false;
        for(int i=0 ; i<target.size() ; i++) ascii_set[target[i]] = true;
    }

    // set method
    void setSet(int num)
    {
        this->ascii_set[num] = true;
    }

    // get the array(private)
    bool * getArr()
    {
        return this->ascii_set;
    }

    // set Set by input string
    void strSet(string target)
    {
        for(int i=0 ; i<256 ; i++) ascii_set[i] = false;
        for(int i=0 ; i<target.size() ; i++) ascii_set[target[i]] = true;
    }

    // print out the set
    void print()
    {
        for(int i=0 ; i<256 ; i++)
        {
            if(this->ascii_set[i])
            {
                cout << char(i);
            }
        }
    }

    //operator overloading + (Union)
    set operator+ (set &tar)
    {
        set new_set;
        for(int i=0 ; i<256 ; i++)
        {
            if(tar.getArr()[i] || this->ascii_set[i])
            {
                new_set.setSet(i);
            }
        }
        return new_set;
    }

    //operator overloading - (difference set)
    set operator- (set &tar)
    {
        set new_set;
        for(int i=0 ; i<256 ; i++)
        {
            if(this->ascii_set[i] && !(tar.getArr()[i]) )
            {
                new_set.setSet(i);
            }
        }
        return new_set;
    }

    //operator overloading * (intersection)
    set operator* (set &tar)
    {
        set new_set;
        for(int i=0 ; i<256 ; i++)
        {
            if(this->ascii_set[i] && tar.getArr()[i] )
            {
                new_set.setSet(i);
            }
        }
        return new_set;
    }

    //operator overloading >= (contains)
    bool operator>= (set &tar)
    {
        for(int i=0 ; i<256 ; i++)
        {
            if( !(this->ascii_set[i]) && tar.getArr()[i] )
            {
                return false;
            }
        }

        return true;
    }

    //operator overloading = (assign)
    set operator= (set &tar)
    {
        for(int i=0 ; i<256 ; i++)
        {
            if(tar.getArr()[i])
            {
                this->ascii_set[i] = true;
            }
            else
            {
                this->ascii_set[i] = false;
            }
        }
        return *this;
    }

};

// function of test the string set
void test(string A , string B , char C)
{
    // make three varible into set
    set A_set(A);
    set B_set(B);
    set C_set(C);

    // print A_set
    cout << "A: {";
    A_set.print();
    cout << "}" << endl;

    // print B_set
    cout << "B: {";
    B_set.print();
    cout << "}" << endl;

    // print A+B set
    cout << "A+B: {";
    (A_set+B_set).print();
    cout << "}" << endl;

    // print A*B set
    cout << "A*B: {";
    (A_set*B_set).print();
    cout << "}" << endl;

    // print A-B set
    cout << "A-B: {";
    (A_set-B_set).print();
    cout << "}" << endl;

    // print B-A set
    cout << "B-A: {";
    (B_set-A_set).print();
    cout << "}" << endl;

    // a lot of if, which is designed for testing the contains or not
    if(A_set >= B_set) cout << "A contains B" << endl;
    else cout << "A does not contain B" << endl;

    if(B_set >= A_set) cout << "B contains A" << endl;
    else cout << "B does not contain A" << endl;

    if(A_set >= C_set) cout << "'" << C << "'" << " is in A" << endl;
    else cout << "'" << C << "'" << " is not in A" << endl;

    if(B_set >= C_set) cout << "'" << C << "'" << " is in B" << endl;
    else cout << "'" << C << "'" << " is not in B" << endl;
}

// struct for record user's input
struct inputAns
{
    string A;
    string B;
    char C;
};

int main()
{
    string A,B;
    char C;
    int input;
    string input_str;

    // cin how many N
    cin >> input;
    inputAns input_List[20];

    // cin A,B and 1 char
    for(int i=0 ; i<input ; i++)
    {
        fflush(stdin);
        getline(cin, input_List[i].A);
        fflush(stdin);
        getline(cin, input_List[i].B);
        fflush(stdin);
        getline(cin, input_str);
        fflush(stdin);
        input_List[i].C = input_str[0];
    }

    cout << endl;
    // print out the answer the question need
    for(int i=0 ; i<input ; i++)
    {
        cout << "Test Case " << i+1 << ":" << endl;
        test(input_List[i].A,input_List[i].B,input_List[i].C);
        cout << endl;
    }


    return 0;
}