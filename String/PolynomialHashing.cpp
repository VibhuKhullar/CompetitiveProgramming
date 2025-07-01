#include <bits/stdc++.h>
using namespace std;


//TODO -> call precompute_power_table


int table_size = 2e6 + 1;

const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;
// int p1 = 31;
int p1 = 137;   // When not using compression for characters
// int p2 = 37;
int p2 = 277;   // When not using compression for characters
int ip1, ip2;
vector<int> pow1(table_size);
vector<int> pow2(table_size);
vector<int> invpow1(table_size);
vector<int> invpow2(table_size);


int modexp(long long a, long long b, long long mod)
{
    int res = 1;
    a %= mod;

    if(a < 0)   a += mod;

    while(b)
    {
        if(b & 1)   res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }return res;
}


void precompute_power_table()
{
    ip1 = modexp(p1, MOD1 - 2, MOD1);
    ip2 = modexp(p2, MOD2 - 2, MOD2);
    pow1[0] = 1;
    pow2[0] = 1;
    invpow1[0] = 1;
    invpow2[0] = 1;
    for(int i=1; i<table_size; i++)
    {
        pow1[i] = (long long) pow1[i-1] * p1 % MOD1;
        pow2[i] = (long long) pow2[i-1] * p2 % MOD2;

        invpow1[i] = (long long) invpow1[i-1] * ip1 % MOD1;
        invpow2[i] = (long long) invpow2[i-1] * ip2 % MOD2;
    }


}


class Hash
{
    public:


    int n;
    string s;
    vector<int> hash1, hash2;

    Hash(string& s)
    {
        n = s.size();
        hash1.resize(n);
        hash2.resize(n);


        for(int i=0; i<n; i++)
        {
            hash1[i] = (s[i] - 'a' + 1LL) * pow1[i] % MOD1;
            hash2[i] = (s[i] - 'a' + 1LL) * pow2[i] % MOD2;
        }


        for(int i=1; i<n; i++)
        {
            hash1[i] += hash1[i-1];
            hash2[i] += hash2[i-1];


            hash1[i] %= MOD1;
            hash2[i] %= MOD2;
        }
    }


    pair<int, int> get_hash(int l, int r)
    {
        if(l < 0 or r >= n) return {-1, -1};    // Error
        if(l >= n or r < 0) return {0, 0};


        int res1 = hash1[r];
        int res2 = hash2[r];


        if(l > 0)
        {
            res1 = (res1 - hash1[l-1] + MOD1) % MOD1;
            res2 = (res2 - hash2[l-1] + MOD2) % MOD2;


            res1 = (long long) res1 * invpow1[l] % MOD1;
            res2 = (long long) res2 * invpow2[l] % MOD2;
        }return {res1, res2};
    }

    pair<int, int> get_hash()   {return get_hash(0, n-1);}
};




int32_t main()
{
    precompute_power_table();
    for(int i=0; i<12; i++)  cout << pow1[i] << " " << pow2[i] << endl;
    for(int i=0; i<5; i++)  cout << invpow1[i] << " " << invpow2[i] << endl;

    string s = "abcabcnabc";
    Hash hash(s);

    auto [l, r] = hash.get_hash(1, 2);
    auto [a, b] = hash.get_hash(8, 9);

    cout << l << " " << r << endl << a << " " << b;

}
