#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <mpi.h>

int size=8;    //当前范围0-->size-1
int total=64;   //总球数
double ball[64][6];
//0-->x方向位置,  1-->y方向位置
//2-->x方向速度,  3-->y方向速度
//4-->x方向加速度,5-->y方向加速度

const double GM=6.67E-7; //万有引力常数
int step=10000;           //模拟多少个时间间隔
double split_time=0.01; //假设一个时间间隔有0.01s
double min_r=0.01;        //设置计算万有引力时最小距离为0.01m

void main(int argc,char *argv[]){
    init();
    int myid, numprocs;
    double start,stop;
    int i,j;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    double* mpi_buffer=malloc(8*1000000);
    MPI_Buffer_attach(mpi_buffer,8*1000000);
    //printf("%d %d",sizeof(double)*6,sizeof(ball));
    if(myid == 0)
    {
		//MPI_Wtime返回一个用浮点数表示的秒数,计时
		start = MPI_Wtime();
	}
	for(i=0;i<step;i++){
        for(j=0;j<numprocs;j++)
        {
        if(j!=myid)
            MPI_Bsend((ball+(total/numprocs)*myid),48*total/numprocs,MPI_BYTE,j,i*10+myid,MPI_COMM_WORLD);
            //向所有其他线程发送本线程所拥有的数据
		}
		int k;
        for(j=0;j<numprocs;j++)
		{
			if(j!=myid)
			{
				MPI_Status status;
				MPI_Recv((ball+(total/numprocs)*j),48*total/numprocs,MPI_BYTE,j,i*10+j,MPI_COMM_WORLD,&status);
                //从所有其他线程接收其他线程拥有的数据
			}
		}

        for(j=(total/numprocs)*myid;j<(total/numprocs)*(myid+1);j++)
            compute_force(j);
        MPI_Barrier(MPI_COMM_WORLD);
        for(j=(total/numprocs)*myid;j<(total/numprocs)*(myid+1);j++)
        {
            compute_velocities(j);
			compute_positions(j);
        }
        MPI_Barrier(MPI_COMM_WORLD);
	}

	if(myid!=0)
	{
		MPI_Send((ball+(total/numprocs)*myid),48*total/numprocs,MPI_BYTE,0,myid,MPI_COMM_WORLD);
	}

	if(myid==0)
	{
		for(i=1;i<numprocs;i++)
		{
			MPI_Status status;
			MPI_Recv((ball+(total/numprocs)*i),48*total/numprocs,MPI_BYTE,i,i,MPI_COMM_WORLD,&status);
		}
		print();
	}
	MPI_Finalize();
}

void init()//初始化ball数组,第0个时间间隔的时候
{
    int i,j;
    for(i=0;i<size;i++)
        for(j=0;j<size;j++)
        {
        ball[i*size+j][0]=i*0.01;ball[i*size+j][1]=j*0.01;
        ball[i*size+j][2]=0;ball[i*size+j][3]=0;
        ball[i*size+j][4]=0;ball[i*size+j][5]=0;
        }

    /*for(i=0;i<size;i++)
        for(j=0;j<size;j++)
            printf("%d %lf %lf\n",i*size+j,ball[i*size+j][0],ball[i*size+j][1]);
    */
}


void compute_positions(int index)
//计算index这个序号的球的位置
{
	ball[index][0]+=ball[index][2]*split_time;
	if(ball[index][0]>((size-1)/100.0))
        ball[index][0]=(size-1)/100.0;
	if(ball[index][0]<0)
        ball[index][0]=0;
	ball[index][1]+=ball[index][3]*split_time;
	if(ball[index][1]>((size-1)/100.0))
        ball[index][1]=(size-1)/100.0;
	if(ball[index][1]<0)
        ball[index][1]=0;
}

void compute_velocities(int index)
{
	ball[index][2]+=ball[index][4]*split_time;
	ball[index][3]+=ball[index][5]*split_time;
}


void compute_force(int index)
{
    ball[index][4]=0;
	ball[index][5]=0;
	//计算力并重新计算加速度
	int i;
	//printf("\n\n\n index: %8.lf %8.lf",ball[index][0],ball[index][1]);
	for(i=0;i<total;i++)
    {
		if(i!=index)
		{
			double dx=ball[i][0]-ball[index][0];
			double dy=ball[i][1]-ball[index][1];
			double d=(dx*dx+dy*dy);
			//半径平方

			if(d<min_r*min_r)
			//如果两球之间距离太小就按最小距离来算
                d=min_r*min_r;
            //printf("\n i=%d %8.lf %8.lf %.8lf",i,dx,dy,d);
            double cos=dx/sqrt(d);
            double sin=dy/sqrt(d);
			ball[index][4]+=(GM*cos)/d;
			ball[index][5]+=(GM*sin)/d;
			//printf("%lf\n",ball[index][5]);
		}
	}
	//printf("%d a: %lf %lf\n",index,ball[index][4],ball[index][5]);
}


void print()
{
    int i;
	for(i=0;i<total;i++)
        printf("%lf,%lf \n",ball[i][0],ball[i][1]);
}
