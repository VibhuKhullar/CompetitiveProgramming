#include <bits/stdc++.h>
using namespace std;


class BigInt
{
    typedef vector<int> vi;
    public:

    int base = 1e9; // Fixed base
    bool sign = false;  // 0 - positive, 1 - negative
    vi arr = {0};



    // Trim leading zeroes
    void trim_leading_zero()    {while(arr.size() > 1 and !arr.back())  arr.pop_back();}


    BigInt(string s)
    {
        if(s.empty())   return;

        if(s[0] == '-' or s[0] == '+')
        {
            if(s.size() == 1)   return;
            sign = s[0] == '-';
            s = s.substr(1);
        }

        arr.resize((s.size() + 8) / 9);
        for(int i = s.size(), ind = 0; i > 0; i -= 9, ind++)
            arr[ind] = stoi(i > 8 ? s.substr(i - 9, 9) : s.substr(0, i));


        trim_leading_zero();
        if(arr.size() == 1 and !arr.back()) sign = false;
    }
};


int main()
{
    // ✅ Can pass digits and atmost one sign(+, -) or empty string
    BigInt bi("12");

    auto print = [&]()
    {
        if(bi.sign) cout << '-';
        cout << bi.arr.back();
        for(auto i = bi.arr.rbegin() + 1; i != bi.arr.rend(); i++)  cout << '_' << *i;
        cout << endl;
    };

    print();


    bi = BigInt("");
    print();
    bi = BigInt("-");
    print();
    bi = BigInt("+1");
    print();
    bi = BigInt("0");
    print();
    bi = BigInt("-0");
    print();

    bi = BigInt("123456789");   // 9 digits
    print();
    bi = BigInt("-123456789");  // 9 digits
    print();
    bi = BigInt("1234567890");  // 10 digits
    print();
    bi = BigInt("-1234567890"); // 10 digits
    print();


    /*
    ->  Only prints the essential value in a block
    ->      If value is 1e9 + 1
    ->      It will print 1_1
    ->      Need '0' padding for better representation
    */
    bi = BigInt("1000004444");
    print();

    bi = BigInt("-1000004444");
    print();

    bi = BigInt("-12345600000000000000000000008900009765345678");
    print();
    bi = BigInt("-00000000000000000000008900009765345678");
    print();

    //❌  Don't give arguments which contains any character other then digits or sign
    bi = BigInt("123 4567890");
    print();
    bi = BigInt("123456_7890");
    print();


}
