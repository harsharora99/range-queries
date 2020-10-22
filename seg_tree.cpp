/// https://codeforces.com/problemset/problem/380/C

#include<bits/stdc++.h>
using namespace std;

struct data
{
    int close;
    int open;
    int match;
};

string s;
int n;
vector < data > tree;

data query ( int node , int start , int end , int l , int r )
{
    if ( l>end || r<start )
    {
        data temp;
        temp.open = 0;
        temp.close = 0;
        temp.match = 0;
        return temp;
    }

    if ( start>=l && end<=r )
    {
        return tree[node];
    }

    int mid = ( start+end )/2;
    data q1 = query ( 2*node+1 , start , mid , l, r );
    data q2 = query ( 2*node+2 , mid+1 , end , l , r );

    data q;

    int new_match = min(q1.open , q2.close );
    q.match = q1.match + q2.match + new_match;
    q.open = q1.open + q2.open - new_match;
    q.close = q1.close + q2.close - new_match;
    return q;
}

void build ( int node , int start , int end )
{
    if ( start==end )
    {
        data temp;
        temp.open = 0;
        temp.close = 0;
        temp.match = 0;
        if ( s[start]=='(' ) temp.open++;
        else temp.close++;

        tree[node] = temp;
        return;
    }

    else
    {
        int mid = ( start+end )/2;
        build ( 2*node+1 , start , mid );
        build ( 2*node+2 , mid+1 , end );

        int new_match = min(tree[2*node+1].open , tree[2*node+2].close );

        tree[node].match = tree[node*2+1].match + tree[2*node+2].match + new_match;
        tree[node].open = tree[2*node+1].open + tree[2*node+2].open - new_match;
        tree[node].close = tree[2*node+1].close + tree[2*node+2].close - new_match;
    }
}

int main()
{
    cin>>s;
    n = s.size();
    tree = vector < data > ( 4*n );

    build ( 0,0,n-1 );

    int q;
    cin>>q;

    while ( q-- )
    {
        int l,r;
        cin>>l>>r;

        l--; r--;

        data ans = query(0,0,n-1,l,r);
        cout<<ans.match*2<<"\n";
    }
    return 0;

}
