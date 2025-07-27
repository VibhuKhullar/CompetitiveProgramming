#include <bits/stdc++.h>
using namespace std;


template<typename T>
struct SegTree
{
    #define mid ((l+r)>>1)
    #define ln 2*i+1
    #define rn 2*i+2
    #define vt vector<T>

    int n;
    T def;
    T* tree;



    SegTree(int n, T def) : n(n), def(def)              // * Constructor
    {
        int size = 4*n;
        tree = new T[size];
        // for(int i=0; i<size; i++)   tree[i] = def;      // Not needed tho
    }


    void print()                                        // * Print like binary tree
    {
        int size = 4*n;

        for(int i=0; i<size; i++)
        {
            cout << tree[i] << " ";
            if((i+1 & i+2) == 0)    cout << endl;
        }cout << endl << endl;
    }



    T merge(T a, T b)
    {
        // Write your merge logic here
        return a + b;
    }


    void build(int i, int l, int r, vt& arr)
    {
        if(l == r)  tree[i] = arr[l];
        else
        {
            build(ln, l, mid, arr);
            build(rn, mid+1, r, arr);
            tree[i] = merge(tree[ln], tree[rn]);
        }
    }


    void update(int i, int l, int r, int pos, T val)
    {
        if(l == r)  tree[i] = val;
        else
        {
            if(pos <= mid)  update(ln, l, mid, pos, val);
            else    update(rn, mid+1, r, pos, val);
            tree[i] = merge(tree[ln], tree[rn]);
        }
    }


    T query(int i, int l, int r, int lower, int upper)
    {
        if(r<lower || upper<l)  return def;

        if(lower<=l and r<=upper)   return tree[i];

        return merge(query(ln, l, mid, lower, upper), query(rn, mid+1, r, lower, upper));

    }


    void build(vt& arr) {build(0, 0, n-1, arr);}
    void update(int pos, T val) {update(0, 0, n-1, pos, val);}
    T query(int lower, int upper) {return query(0, 0, n-1, lower, upper);}


    #undef mid
    #undef ln
    #undef rn
    #undef vt
};


int main()
{
    int n = 5;
    vector<int> arr = {1, 20, 3, 4, 5};
    
    SegTree<int> segtree(5, 0);

    segtree.build(arr);
    segtree.print();
    segtree.update(3, 6);
    segtree.print();


    cout << endl << segtree.query(1, 4) << endl;


}