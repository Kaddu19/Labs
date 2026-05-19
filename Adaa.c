Lab1

"""

#include <stdio.h>

#define INF 999
#define MAX 100

int p[MAX], c[MAX][MAX], t[MAX][2];

int find(int v)
{
    while (p[v])
        v = p[v];
    return v;
}

void union1(int i, int j)
{
    p[j] = i;
}

void kruskal(int n)
{
    int i, j, k, u, v, min, res1, res2, sum = 0;

    for (k = 1; k < n; k++)
    {
        min = INF;

        for (i = 1; i <= n; i++)
        {
            for (j = 1; j <= n; j++)
            {
                if (i == j) 
                    continue;

                if (c[i][j] < min)
                {
                    u = find(i);
                    v = find(j);

                    if (u != v)
                    {
                        res1 = i;
                        res2 = j;
                        min = c[i][j];
                    }
                }
            }
        }

        union1(res1, find(res2));

        t[k][1] = res1;
        t[k][2] = res2;

        sum = sum + min;

        c[res1][res2] = c[res2][res1] = INF;   // remove used edge
    }

    printf("\nCost of spanning tree is = %d", sum);
    printf("\nEdges of spanning tree are:\n");

    for (i = 1; i < n; i++)
        printf("%d -> %d\n", t[i][1], t[i][2]);
}

int main()
{
    int i, j, n;

    printf("\nEnter the n value:");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
        p[i] = 0;

    printf("\nEnter the graph data:\n");

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &c[i][j]);

    kruskal(n);

    return 0;
}

"""

Lab 2

"""

#include <stdio.h>
#define INF 999

int prim(int c[10][10], int n, int s) {
  int v[10], i, j, sum = 0, ver[10], d[10], min, u;
  for (i = 1; i <= n; i++) {
    ver[i] = s;
    d[i] = c[s][i];
    v[i] = 0;
  }
  v[s] = 1;
  for (i = 1; i <= n - 1; i++) {
    min = INF;
    for (j = 1; j <= n; j++)
      if (v[j] == 0 && d[j] < min) {
        min = d[j];
        u = j;
      }
    v[u] = 1;
    sum = sum + d[u];
    printf("\n%d -> %d sum=%d", ver[u], u, sum);
    for (j = 1; j <= n; j++)
      if (v[j] == 0 && c[u][j] < d[j]) {
        d[j] = c[u][j];
        ver[j] = u;
      }
  }
  return sum;
}

void main() {
  int c[10][10], i, j, res, s, n;

  printf("\nEnter n value:");
  scanf("%d", &n);

  printf("\nEnter the graph data:\n");
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      scanf("%d", &c[i][j]);

  printf("\nEnter the souce node:");
  scanf("%d", &s);

  res = prim(c, n, s);

  printf("\nCost=%d", res);
  getchar();
}

"""

Lab 3A

"""

#include<stdio.h>
#define INF 999
int min(int a,int b)
{
    return(a<b)?a:b;
}
void floyd(int p[][10],int n)
{
    int i,j,k;
    for(k=1; k<=n; k++)
        for(i=1; i<=n; i++)
            for(j=1; j<=n; j++)
                p[i][j]=min(p[i][j],p[i][k]+p[k][j]);
}
void main()
{
    int a[10][10],n,i,j;
    printf("\nEnter the n value:");
    scanf("%d",&n);
    printf("\nEnter the graph data:\n");
    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
            scanf("%d",&a[i][j]);
    floyd(a,n);
    printf("\nShortest path matrix\n");
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
    getchar();
}

"""

Lab 3b

"""

#include<stdio.h>
void warsh(int p[][10],int n)
{
    int i,j,k;
    for(k=1; k<=n; k++)
        for(i=1; i<=n; i++)
            for(j=1; j<=n; j++)
                p[i][j]=p[i][j] || p[i][k] && p[k][j];
}
int main()
{
    int a[10][10],n,i,j;
    printf("\nEnter the n value:");
    scanf("%d",&n);
    printf("\nEnter the graph data:\n");
    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
            scanf("%d",&a[i][j]);
    warsh(a,n);
    printf("\nResultant path matrix\n");
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
    return 0;
}


"""

Lab 4

"""

#include<stdio.h>

#define INF 999

void dijkstra(int c[10][10], int n, int s, int d[10])
{
    int v[10], min, u, i, j;

    // Initialize distances and visited array
    for(i = 0; i < n; i++)
    {
        d[i] = c[s][i];
        v[i] = 0;
    }

    v[s] = 1; // mark source as visited

    // Repeat n-1 times
    for(i = 0; i < n - 1; i++)
    {
        min = INF;
        u = -1;

        // Find minimum distance vertex
        for(j = 0; j < n; j++)
        {
            if(v[j] == 0 && d[j] < min)
            {
                min = d[j];
                u = j;
            }
        }

        if(u == -1) break; // no reachable vertex

        v[u] = 1;

        // Update distances
        for(j = 0; j < n; j++)
        {
            if(v[j] == 0 && c[u][j] != INF && (d[u] + c[u][j] < d[j]))
            {
                d[j] = d[u] + c[u][j];
            }
        }
    }
}

int main()
{
    int c[10][10], d[10], i, j, s, n;

    printf("Enter n value: ");
    scanf("%d", &n);

    printf("Enter the graph data:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &c[i][j]);

            // Replace 0 with INF (except diagonal)
            if(i != j && c[i][j] == 0)
                c[i][j] = INF;
        }
    }

    printf("Enter the source node (0 to %d): ", n-1);
    scanf("%d", &s);

    dijkstra(c, n, s, d);

    printf("\nShortest distances:\n");
    for(i = 0; i < n; i++)
    {
        printf("From %d to %d = %d\n", s, i, d[i]);
    }

    return 0;
}


"""

Lab 5

"""

#include<stdio.h>
int temp[10],k=0;
void sort(int a[][10],int id[],int n)
{
    int i,j;
    for(i=1; i<=n; i++)
    {
        if(id[i]==0)
        {
            id[i]=-1;
            temp[++k]=i;
            for(j=1; j<=n; j++)
            {
                if(a[i][j]==1 && id[j]!=-1)
                    id[j]--;
            }
            i=0;
        }
    }
}
void main()
{
    int a[10][10],id[10],n,i,j;
    printf("\nEnter the n value:");
    scanf("%d",&n);
    for(i=1; i<=n; i++)
        id[i]=0;
    printf("\nEnter the graph data:\n");
    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
        {
            scanf("%d",&a[i][j]);
            if(a[i][j]==1)
                id[j]++;
        }
    sort(a,id,n);
    if(k!=n)
        printf("\nTopological ordering not possible");
    else
    {
        printf("\nTopological ordering is:");
        for(i=1; i<=k; i++)
            printf("%d ",temp[i]);
    }
    getchar();
}



"""

LAB 6

"""

#include <stdio.h>

int w[10], p[10], n;

int max(int a, int b)
{
    return a > b ? a : b;
}

int knap(int i, int m)
{
    if (i == n)
        return w[i] > m ? 0 : p[i];

    if (w[i] > m)
        return knap(i + 1, m);

    return max(knap(i + 1, m), knap(i + 1, m - w[i]) + p[i]);
}

int main()
{
    int m, i, max_profit;

    printf("\nEnter the no. of objects:");
    scanf("%d", &n);

    printf("\nEnter the knapsack capacity:");
    scanf("%d", &m);

    printf("\nEnter profit followed by weight:\n");

    for (i = 1; i <= n; i++)
        scanf("%d %d", &p[i], &w[i]);

    max_profit = knap(1, m);

    printf("\nMax profit=%d", max_profit);

    return 0;
}

"""

Lab 7

"""

#include <stdio.h>
#define MAX 50
int p[MAX], w[MAX], x[MAX];
double maxprofit;
int n, m, i;
void greedyKnapsack(int n, int w[], int p[], int m)
{
    double ratio[MAX];

// Calculate the ratio of profit to weight for each item
    for (i = 0; i < n; i++)
    {
        ratio[i] = (double)p[i] / w[i];
    }
// Sort items based on the ratio in non-increasing order
    for (i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (ratio[i] < ratio[j])
            {
                double temp = ratio[i];
                ratio[i] = ratio[j];
                ratio[j] = temp;

                int temp2 = w[i];
                w[i] = w[j];
                w[j] = temp2;

                temp2 = p[i];
                p[i] = p[j];
                p[j] = temp2;
            }
        }
    }
    int currentWeight = 0;
    maxprofit = 0.0;
// Fill the knapsack with items
    for (i = 0; i < n; i++)
    {
        if (currentWeight + w[i] <= m)
        {
            x[i] = 1; // Item i is selected
            currentWeight += w[i];
            maxprofit += p[i];
        }
        else
        {
// Fractional part of item i is selected
            x[i] = (m - currentWeight) / (double)w[i];
            maxprofit += x[i] * p[i];
            break;
        }
    }
    printf("Optimal solution for greedy method: %.1f\n", maxprofit);
    printf("Solution vector for greedy method: ");
    for (i = 0; i < n; i++)
        printf("%d\t", x[i]);
}
int main()
{
    printf("Enter the number of objects: ");
    scanf("%d", &n);
    printf("Enter the objects' weights: ");
    for (i = 0; i < n; i++)
        scanf("%d", &w[i]);
    printf("Enter the objects' profits: ");
    for (i = 0; i < n; i++)
        scanf("%d", &p[i]);
    printf("Enter the maximum capacity: ");
    scanf("%d", &m);
    greedyKnapsack(n, w, p, m);
    return 0;
}

"""

Lab 8

"""

#include<stdio.h>
#define MAX 10
int s[MAX],x[MAX],d;
void sumofsub(int p,int k,int r)
{
    int i;
    x[k]=1;
    if((p+s[k])==d)
    {
        for(i=1; i<=k; i++)
            if(x[i]==1)
                printf("%d ",s[i]);
        printf("\n");
    }
    else if(p+s[k]+s[k+1]<=d)
        sumofsub(p+s[k],k+1,r
                 -s[k]);
    if((p+r
            -s[k]>=d) && (p+s[k+1]<=d))
    {
        x[k]=0;
        sumofsub(p,k+1,r
                 -s[k]);
    }
}
int main()
{
    int i,n,sum=0;
    printf("\nEnter the n value:");
    scanf("%d",&n);
    printf("\nEnter the set in increasing order:");
    for(i=1; i<=n; i++)
        scanf("%d",&s[i]);
    printf("\nEnter the max subset value:");
    scanf("%d",&d);
    for(i=1; i<=n; i++)
        sum=sum+s[i];
    if(sum<d || s[1]>d)
        printf("\nNo subset possible");
    else
        sumofsub(0,1,sum);
    return 0;
}


"""