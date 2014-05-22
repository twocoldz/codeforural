#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 512;

const int dx[] = { -1, 0, 1, 0, -1, -1, 1, 1, -1 };
const int dy[] = { 0, -1, 0, 1, -1, 1, 1, -1, -1 };

struct Point
{
    int x, y;
    Point( int x = 0, int y = 0 ): x(x), y(y) { }
};

Point Q[MAXN * MAXN ];
char G[MAXN][MAXN];
bool vis[MAXN][MAXN];
int R, C, X, Y;

bool check( int x, int y, bool wh )
{
    if ( wh ) return x > 0 && x <= R && y > 0 && y <= C;
    else return x >= 0 && x <= R + 1 && y >= 0 && y <= C + 1;
}

void FloodFill( Point st, char ch1, char ch2, char ch3, int dir )
{
    int front = 0, rear = 0;
    bool wh = false;
    if ( dir == 8 ) wh = true;

    Q[rear++] = st;

    while ( front < rear ){
        Point p = Q[front];

        G[ p.x ][ p.y ] = ch3;
        vis[ p.x ][ p.y ] = true;
        //printf( "%d %d\n", p.x, p.y );
        for ( int i = 0; i < dir; ++i ){
            int xx = p.x + dx[i];
            int yy = p.y + dy[i];
            //printf( "vis[%d][%d] = %d\n", xx, yy, vis[xx][yy] );
            if ( check( xx, yy, wh ) && !vis[xx][yy] && ( G[xx][yy] == ch1 || G[xx][yy] == ch2 ) ){
                vis[xx][yy] = true;
                Q[rear++] = Point( xx, yy );
            }
        }

        ++front;
    }
    return;
}

int main()
{
    //freopen("in", "r", stdin );
    while ( ~scanf( "%d%d%d%d", &C, &R, &Y, &X ) ){
        memset( G, '.', sizeof(G) );
        G[0][ C + 2 ] = '\0';
        for ( int i = 1; i <= R; ++i ){
            scanf( "%s", &G[i][1] );
            G[i][ C + 2 ] = '\0';
        }
        memset( vis, false, sizeof(vis) );
        FloodFill( Point( X, Y ), '.', '.', '*', 8 );
        memset( vis, false, sizeof(vis) );
        FloodFill( Point( 0, 0 ),   '.', '#', ' ', 4 );

        memset( vis, false, sizeof(vis) );
        int ans = 0;
        for ( int i = 1; i <= R; ++i )
        for ( int j = 1; j <= C; ++j )
        if ( G[i][j] == '#' ){
            ++ans;
            FloodFill( Point( i, j ), '#', '#', '$', 4 );
        }
        printf( "%d\n", ans );
    }
    return 0;
}
