#include <bits/stdc++.h>
using namespace std;

class UnionFind
{
private:
    vector<int> parent;
    vector<int> findsizes;
    int numberofcomponents = 0;
public:
    UnionFind(int size): parent(vector<int>(size)), findsizes(vector<int>(size, 1)) 
    {
        for(int index = 0; index < parent.size(); index++){
            parent[index] = index;
        }
    }

    int findroot(int a){
        if(parent[a] == a) return a;
        parent[a] = findroot(parent[a]);
        return parent[a];
    }

    void unite(int a, int b){
        int ra = findroot(a);
        int rb = findroot(b);
        if(ra != rb){
            if(findsizes[ra]>findsizes[rb]){
                parent[rb] = parent[ra];
                findsizes[ra] += findsizes[rb];
                findsizes[rb] = 0;
            }
            else {
                parent[ra] = parent[rb];
                findsizes[rb] += findsizes[ra];
                findsizes[ra] = 0;
            }
        }
    }
};
