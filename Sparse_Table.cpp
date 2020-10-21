/// Problem Link : 
/// https://codeforces.com/problemset/problem/359/D

#include<bits/stdc++.h>
using namespace std ;

# define line cout << "\n" ;

struct NODE
{
    int minn = 1e6 + 10 ;
    int gcd = 0 ;
};

const int N = 3e5 + 2 , L = 20 ;
vector < vector < NODE > > up ( N , vector < NODE > ( L ) ) ;

int n ;

void read ()
{
    cin >> n ;

    for ( int i = 1 ; i <= n ; i ++ )
    {
        int val ;
        cin >> val ;

        up[i][0].minn = val ;
        up[i][0].gcd  = val ;
    }
}

int len[N] ;

void build ( )
{
    for ( int j = 1 ; j < L ; j ++ )
    {
        for ( int i = 1 ; i <= n ; i ++ )
        {
            int next = (1 << ( j - 1 )) + i ;
            if ( next > n ) break ;

            up[i][j].minn = min ( up[i][j - 1].minn , up[next][j - 1].minn ) ;
            up[i][j].gcd = __gcd ( up[i][j - 1].gcd , up[next][j - 1].gcd ) ;
        }
    }

    len[0] = -1 ;
    for ( int i = 1 ; i <= n ; i ++ )
    {
        len[i] = len[i - 1] ;
        if ( (i&(i-1)) == 0 )
            len[i] ++ ;
    }
}

NODE query ( int l , int r , int z )
{
    int j = len[z] ;

    NODE ans ;

    ans.minn = min ( up[l][j].minn , up[r][j].minn ) ;
    ans.gcd = __gcd ( up[l][j].gcd , up[r][j].gcd ) ;

    return ans ;
}

void solve()
{
    vector < int > ans_indx ;
    int ans_mid = -1 ;

    for ( int lo = 1 , hi = n ; lo <= hi ; )
    {
        int mid = lo + hi >> 1 ;
        int &z = mid ;

        bool ok = false ;

        for ( int i = 1 ; i + z - 1 <= n ; i ++ )
        {
            int l = i ;

            int r = i + z - 1 ;
            r = r - ( 1 << len[z] ) + 1 ;

            NODE ans = query ( l , r , z ) ;

            if ( ans.minn == ans.gcd )
            {
                if ( ok == false )
                {
                    ok = 1 ;
                    ans_indx.clear() ;
                }

                ans_indx.push_back ( i ) ;
            }
        }

        if ( ok )
            ans_mid = mid , lo = mid + 1 ;

        else hi = mid - 1 ;
    }

    assert ( ans_mid != -1 ) ;

    cout << ans_indx.size() << " " << ans_mid - 1 << "\n" ;

    for ( auto &l_values : ans_indx )
        cout << l_values << " " ;

    cout << "\n" ;
}

int main()
{
    ios_base :: sync_with_stdio ( false ) ; cin.tie ( 0 ) ;

    read () ;
    build () ;

    solve() ;
}
