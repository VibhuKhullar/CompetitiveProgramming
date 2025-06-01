#include <bits/stdc++.h>
using namespace std;


class FunctionalGraph
{
    public:
    //Class Members
    int n;  // 1-index
    vector<int> next;
    vector<int> comp;
    vector<vector<int>> jump;

    /*
    ->  Clarification
    ->  comp
    ->      -2 -> not visiteed
    ->      -1 -> part of tree
    ->       0 -> part of cycle
    ->

    */


    FunctionalGraph(int n) : n(n)
    {
        next.assign(n+1, 0);
        comp.assign(n+1, -2);
    }

    FunctionalGraph(int n, const vector<int>& arr) : n(n)
    {
        next = arr;
        comp.assign(n+1, -2);
    }


    // Assign Components
    void assign_components(int u)
    {
        if(comp[u] == -1)
        {
            //-> Mark circle components
            int v = u;
            do
            {
                comp[v] = 0;
                v = next[v];
            } while (v != u);

            return;
        }

        //-> Will only happen when finding a new cycle,
        //-> otherwise you encouter either -2 or >= 0

        comp[u] = -1;

        assign_components(next[u]);
        //-> Mark tree components
        if(comp[u] == -1)   comp[u] = comp[next[u]] ? comp[next[u]] : next[u];
    }


    void assign_components()
    {
        for(int i=1; i<=n; i++) if(comp[i] == -2)   assign_components(i);
    }



    // Binary Jump
    void binary_jump_init(int d)
    {
        jump.assign(d, vector<int>(n+1));

        for(int i=1; i<=n; i++) jump[0][i] = next[i];

        for(int i=1; i<d; i++)
            for(int j=1; j<=n; j++)
                jump[i][j] = jump[i-1][jump[i-1][j]];
    }
};


int main()
{
    int n, m;

    vector<int> adj = {0, 2, 3, 4, 5, 1, 1, 1, 3, 8, 8, 4};

    FunctionalGraph graph(11, adj);

    graph.assign_components();

    for(int i:graph.comp)   cout << i << " ";   cout << endl;

    graph.binary_jump_init(10);

    for(int i=1; i<10; i++)
    {for(int j=0; j<5; j++)  cout << graph.jump[j][i] << " "; cout << endl;}
}
