# include <stdio.h>
# include <string.h>


int n, INF = 0x3f3f3f3f ;
int col[80010] ;
int g[2000][20000] ;
int max_col ;


int Value(char ch){
    if (ch >= '0' && ch <= '9')
        return ch-'0'+1 ;
    else // ch == 'a'-'z'
        return ch-'a'+11 ;
}


int GetValue(char s[])
{
    if (s[1] == '\0') return Value(s[0]) ;
    return  Value(s[0])*40 +  Value(s[1]) ;
}


int min(int a,int b){return a<b?a:b;}
int max(int a, int b){return a>b?a:b;}


void AddEdge(int a, int b, int c)
{
    int ca = col[a], cb = col[b] ;
    g[ca][cb] = min(g[ca][cb], c) ;
}



void floyd()
{
    int i,j,k, flag ;
    int max_n = max_col ;
    for (k = 1 ; k <= max_n ; k++)
    {
        for (i = 1 ; i <= max_n ; i++)
            for (j = 1 ; j <= max_n ; j++)
            {
                if (g[i][j] > g[i][k]+g[k][j])
                    g[i][j] = g[i][k]+g[k][j], flag = 1 ;
            }
    }
}


int work(int p, int q)
{
    p = col[p], q = col[q] ;
    if (g[p][q] >= INF-1000) return -1 ;
    return g[p][q] ;
}


int main ()
{
    int T, i, nCase = 1 ;
    int m, s, a, b, c, p, q ;
    char color[5] ;
    freopen ("", "r", stdin) ;
    freopen ("e_out.txt", "w", stdout) ;
    scanf ("%d", &T) ;
    while (T--)
    {
        scanf ("%d", &n) ;
        max_col = -1 ;
        for (i = 1 ; i <= n; i++)
        {
            scanf ("%s", color) ;
            col[i] = GetValue(color) ;
            max_col = max(max_col, col[i]) ;
        }

        //CreateGraph() ;
        memset (g, 0x3f, sizeof(g)) ;
        for (i = 0 ; i <= 40*40 ; i++) g[i][i] = 0 ;
        scanf ("%d", &m) ;
        while (m--)
        {
            scanf ("%d %d %d", &a, &b, &c) ;
            AddEdge(a,b,c) ;
        }
        floyd() ;
        printf ("Case #%d:\n", nCase++) ;
        scanf ("%d", &s) ;
        while (s--)
        {
            scanf ("%d %d", &p, &q) ;
            printf ("%d\n", work(p,q)) ;
        }
    }
    return 0 ;
}
