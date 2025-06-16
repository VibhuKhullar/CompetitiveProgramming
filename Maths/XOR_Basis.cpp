#include <bits/stdc++.h>
using namespace std;


template<typename T>
class XOR_Basis
{
    public:
    int n;
    vector<T> arr;
    int basis = 0;
    int msb = 0;


    XOR_Basis(vector<T> arr) : n(arr.size()), arr(arr), msb(sizeof(T) * 8 - 1) {}

    XOR_Basis(vector<T> arr, int msb) : n(arr.size()), arr(arr), msb(msb) {}


    void binary_gaussian_elimination()
    {
        for(int i = msb; i > -1; i--)
        {
            int ind = basis;    // pivot
            // while(++ind < n)    if((arr[ind] >> i) & 1) break;   // same
            while(ind < n and !((arr[ind] >> i) & 1)) ind++;    // Find new pivot
            if(ind == n)  continue;   // If no ind found, continue to find next ind


            swap(arr[basis], arr[ind]);


            for(int j = 0; j < n; j++)
            {
                if(j == basis or !((arr[j] >> i) & 1))  continue;
                arr[j] ^= arr[basis];
            }
            basis++;
        }
    }


    int k_smallest_xor(int k, int def)  // return def if number of distinct xors are less than k
    {
        if(k > (1 << basis))    return def;

        int res = 0;

        int part_size = 1 << (basis - 1);   // size of common part after the first (0 or 1)

        for(int i=0; i<basis; i++)
        {
            if(k > part_size)
            {
                res ^= arr[i];
                k -= part_size;
            }
            part_size >>= 1;
        }

        return res;
    }
};

int main()
{
    vector<int> arr = {9, 8, 5};

    XOR_Basis<int> x(arr);
    cout << x.n << endl;

    cout << x.msb << endl;

    cout << x.basis << endl;

    x.binary_gaussian_elimination();

    for(int i:x.arr)    cout << i << " ";   cout << endl;

    cout << x.k_smallest_xor(1, -1) << endl;
    cout << x.k_smallest_xor(2, -1) << endl;
    cout << x.k_smallest_xor(3, -1) << endl;
}
