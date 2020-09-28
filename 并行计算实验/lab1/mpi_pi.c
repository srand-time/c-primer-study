//由高数里的知识可知，根据上述公式可以求得pi/4。
#include<stdio.h>
#include<mpi.h>
int main(int argc,char *argv[]){
	int my_rank,num_procs;
	int i;
	int n=1000;//循环次数
	double sum,width,local,mypi,pi;
	double start =0.0,stop = 0.0;


	MPI_Init(&argc,&argv);
	//初始化
	//并行的部分全部放在MPI_Init(&argc,&argv)和MPI_Finalize()内部。

	MPI_Comm_size(MPI_COMM_WORLD,&num_procs);
		//MPI_COMM_WORLD是所有进程的集合，在执行完MPI_Init后自动产生
	/*
	int MPI_Comm_size (MPI_Comm comm ,int* size )
    获得进程个数 size。
    指定一个通信子,也指定了一组共享该空间的进程, 这些进程组成该通信子的group（组）。
    获得通信子comm中规定的group包含的进程的数量。
    */

	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	//得到本进程在通信空间中的rank值,即在组中的逻辑编号
	//(该 rank值为0到p-1间的整数,相当于进程的ID。)

	printf("Process rank:%d ,total process :%d\n",my_rank,num_procs);
	if(my_rank == 0)
    {
		//MPI_Wtime返回一个用浮点数表示的秒数,计时
		start = MPI_Wtime();
	}
	sum =0.0;
	width = 1.0/n;

	//每个进程my_rank，计算4.0/(1.0+local*local)放入sum
	for(i = my_rank;i<n;i+=num_procs)
    {
		local =width*((double)i+0.5);
		sum += 4.0/(1.0+local*local);
	}
	mypi = width*sum;
	MPI_Reduce(&mypi,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    //全局规约函数MPI_Reduce： 将所有的发送信息进行同一个操作。
    //int MPI_Reduce(
    //void *input_data, /*指向发送消息的内存块的指针 */
    //void *output_data, /*指向接收（输出）消息的内存块的指针 */
    //int count，/*数据量*/
    //MPI_Datatype datatype,/*数据类型*/
    //MPI_Op operator,/*规约操作*/
    //int dest，/*要接收（输出）消息的进程的进程号*/
    //MPI_Comm comm);/*通信器，指定通信范围*/

	//打印结果和运行时间
	if(my_rank == 0)
    {
        printf("循环次数: %d\n",n);
		printf("PI is %.20f\n",pi);
		stop = MPI_Wtime();
		printf("Time:%.4f ms\n",(stop-start)*1000);
	}
	MPI_Finalize();
	return 0;
}
