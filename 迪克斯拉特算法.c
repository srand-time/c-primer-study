#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MaxSize 20
#define INFINITY 65535//定义infinity 为无限大
 //定义图的邻接矩阵表示法结构
struct Map
{
	char point[MaxSize+1];
	int edg[MaxSize][MaxSize];
};

//邻接矩阵法图的生成函数
void CreateMap( struct Map *g )
{
	int i = 0,j = 0,totalpoint;//总节点数
	char inputpoint;//输入的节点的名称
	printf("请输入图的顶点名称（不要打空格）:\n");
	while( (inputpoint=getchar())!='\n' )
		g->point[i++] = inputpoint;
	g->point[i] = '\0';
	totalpoint = strlen(g->point);
	printf("请输入相应的的邻接矩阵:\n");
	for( i=0; i<totalpoint; i++ )
		for( j=0; j<totalpoint; j++ )
			scanf("%d", &g->edg[i][j]);}

//将不邻接的顶点之间的权值设置为INFINITY
void SetWeight( struct Map *g )
{int i,j;
	for(  i=0; i<strlen(g->point); i++ )
		for( j=0; j<strlen(g->point); j++ )
			if( 0 == g->edg[i][j] )
				g->edg[i][j] = INFINITY;
}




//Dijkstra求最短路径函数
void Dijkstra( struct Map g )
{
	int VertexNum = strlen(g.point);
	int i,j,k;
	int mini;
	int index = 0;
	int *used = (int *)malloc(sizeof(int)*VertexNum);
	int *distance = (int *)malloc(sizeof(int)*VertexNum);
	int *parent = (int *)malloc(sizeof(int)*VertexNum);
	int *last = (int *)malloc(sizeof(int)*VertexNum);

	SetWeight( &g );					//设置权值

	for( i=0; i<VertexNum; i++ )
    {
		used[i] = 0;
		distance[i] = g.edg[0][i];   //初始化为与编号为0的顶点的距离
		last[i] = 0;
	}
    distance[0]=0;
	used[0] = 1;
	parent[index++] = 0;


	for( i=0; i<VertexNum-1; i++ )
    {
		j = 0;
		mini = INFINITY;

		for( k=0; k<VertexNum; k++ )
			if( (0 == used[k]) && (distance[k] < mini) )
            {
				mini = distance[k];
				j = k;			//j为刚刚找到的V-U中到源点路径最短的顶点
			}

		used[j] = 1;

		for(k=0; k<VertexNum; k++ )
			if( (0 == used[k]) && (distance[k] > distance[j] + g.edg[j][k]) )
            {   //由于有顶点新加入U集合，对距离数组distance进行更新，比较原路径长度与以新加入的顶点为中间点的路径长度
				distance[k] = distance[j] + g.edg[j][k];
			}

		parent[index++] = j;
	}

    //输出最短路径
	printf("%c到%c的最短路径经过顶点依次为:\n", g.point[0], g.point[VertexNum-1]);
	printf("%c\n",g.point[VertexNum-1]);
	j=VertexNum-1;
	distance[0]=0;
	while(i!=0)
        for(i=j-1;;i--)
        if((distance[i]!=65536)&&((distance[j]-g.edg[i][j])==distance[i]))
        {
            printf("%c\n",g.point[i]);
            j=i;
            break;
        }
	printf("最短路径长度为: %d\n", distance[VertexNum-1]);

}

int main()
{
	struct Map g;
	CreateMap( &g );
	Dijkstra( g );
	return 0;
}
/*
abcdefg
0 1 1 0 0 0 0
1 0 0 2 0 0 0
1 0 0 2 3 0 0
0 2 2 0 0 0 3
0 0 3 0 0 2 0
0 0 0 0 2 0 400
0 0 0 3 0 400 0
*/
