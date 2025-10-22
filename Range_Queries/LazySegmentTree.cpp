#include <bits/stdc++.h>
using namespace std;


template<typename T, typename L>
struct SegTree
{
    #define mid ((l+r)>>1)
    #define ln 2*i+1
    #define rn 2*i+2
    #define vt vector<T>

    int n;
    T def;
    L lazydef;
    T* tree;
    L* lazy;



    SegTree(int n, T def, L lazydef) : n(n), def(def), lazydef(lazydef)     // * Constructor
    {
        int size = 4*n;
        tree = new T[size];
        lazy = new L[size];
        fill(lazy, lazy + size, lazydef);
        // for(int i=0; i<size; i++)   tree[i] = def;      // Not needed tho
    }


    void print()                                        // * Print like binary tree
    {
        int size = 4*n;

        for(int i=0; i<size; i++)
        {
            if(lazy[i] == lazydef)  cout << tree[i] << " ";
            else    cout << '(' << tree[i] << ", " << lazy[i] << ") ";
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


    void push(int i, int l, int r)
    {
        if(lazydef == lazy[i])  return;

        auto lazymerge = [&](L& a, L& b) -> void     // ~change
        {
            // lazymerge
            a += b;
        };

        tree[i] += lazy[i] * (r - l + 1); // ~change  // lazynodemerge


        if(l != r)  lazymerge(lazy[ln], lazy[i]), lazymerge(lazy[rn], lazy[i]);
        lazy[i] = lazydef;
    }


    T query(int i, int l, int r, int lower, int upper)
    {
        push(i, l, r);
        if(r<lower || upper<l)  return def;

        if(lower<=l and r<=upper)   return tree[i];

        return merge(query(ln, l, mid, lower, upper), query(rn, mid+1, r, lower, upper));

    }


    void lazyupdate(int i, int l, int r, int lower, int upper, L val)
    {
        push(i, l, r);
        if(r<lower || upper<l)  return;

        if(lower<=l and r<=upper)
        {
            lazy[i] = val;
            push(i, l, r);
            return;
        }

        lazyupdate(ln, l, mid, lower, upper, val);
        lazyupdate(rn, mid+1, r, lower, upper, val);
        tree[i] = merge(tree[ln], tree[rn]);
    }


    void build(vt& arr) {build(0, 0, n-1, arr);}
    T query(int lower, int upper) {return query(0, 0, n-1, lower, upper);}
    void lazyupdate(int lower, int upper, L val)    {lazyupdate(0, 0, n-1, lower, upper, val);}


    #undef mid
    #undef ln
    #undef rn
    #undef vt
};


int main()
{
    int n = 5;
    vector<int> arr = {1, 20, 3, 4, 5};

    SegTree<int, int> segtree(5, 0, 0);

    segtree.build(arr);
    segtree.print();


    cout << endl << segtree.query(1, 4) << endl;
    cout << endl << segtree.lazy[0] << endl;
    segtree.lazyupdate(1, 3, 2);
    segtree.print();




}



// Rules of Lazy
// Check merge, lazymerge and lazynodemerge
// Sometime l and r is needed for push
// Make sure to check if l and r is needed in lazyupdate to change the val for deeper recursion, like walk of segment tree
// Print isn't updated for lazy yet
// lazydef and init lazy can be different
// While walking make sure to push on ln and rn
// While walking, always handle edge cases first (where you ahve to return -1) (case)(retunr -1);   if(l == r)(return l);
// Making pair of lazy is also great
