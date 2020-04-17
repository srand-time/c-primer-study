#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MaxSize 20
#define INFINITY 65535//����infinity Ϊ���޴�
 //����ͼ���ڽӾ����ʾ���ṹ
struct Map
{
	char point[MaxSize+1];
	int edg[MaxSize][MaxSize];
};

//�ڽӾ���ͼ�����ɺ���
void CreateMap( struct Map *g )
{
	int i = 0,j = 0,totalpoint;//�ܽڵ���
	char inputpoint;//����Ľڵ������
	printf("������ͼ�Ķ������ƣ���Ҫ��ո�:\n");
	while( (inputpoint=getchar())!='\n' )
		g->point[i++] = inputpoint;
	g->point[i] = '\0';
	totalpoint = strlen(g->point);
	printf("��������Ӧ�ĵ��ڽӾ���:\n");
	for( i=0; i<totalpoint; i++ )
		for( j=0; j<totalpoint; j++ )
			scanf("%d", &g->edg[i][j]);}

//�����ڽӵĶ���֮���Ȩֵ����ΪINFINITY
void SetWeight( struct Map *g )
{int i,j;
	for(  i=0; i<strlen(g->point); i++ )
		for( j=0; j<strlen(g->point); j++ )
			if( 0 == g->edg[i][j] )
				g->edg[i][j] = INFINITY;
}




//Dijkstra�����·������
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

	SetWeight( &g );					//����Ȩֵ

	for( i=0; i<VertexNum; i++ )
    {
		used[i] = 0;
		distance[i] = g.edg[0][i];   //��ʼ��Ϊ����Ϊ0�Ķ���ľ���
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
				j = k;			//jΪ�ո��ҵ���V-U�е�Դ��·����̵Ķ���
			}

		used[j] = 1;

		for(k=0; k<VertexNum; k++ )
			if( (0 == used[k]) && (distance[k] > distance[j] + g.edg[j][k]) )
            {   //�����ж����¼���U���ϣ��Ծ�������distance���и��£��Ƚ�ԭ·�����������¼���Ķ���Ϊ�м���·������
				distance[k] = distance[j] + g.edg[j][k];
			}

		parent[index++] = j;
	}

    //������·��
	printf("%c��%c�����·��������������Ϊ:\n", g.point[0], g.point[VertexNum-1]);
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
	printf("���·������Ϊ: %d\n", distance[VertexNum-1]);

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
