#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<time.h>
int result=0; //结果数
char cc;//是否需要求出所有解
int cishu=0;
int save[9][9];
int yueshu[9][9];//当前位置被多少个条件所约束
clock_t start,end;
int main()
{
    start=clock();
    //int a[9][9];
    int i,j,k,way;
    int check(int a[9][9],int i,int j,int k);
    //检验i,j这个位置能不能摆放k这个数字

    void shudu(int a[9][9],int n,FILE *f);
    //数独求解函数,n代表位置0<=n<81。
    //主要运用了所学知识的函数

    int getAllTestcase(char filename[][256]);
    //得到所有的测试样例的文件名，返回值为文件个数。

    char filename[50][256];
    int filenum=getAllTestcase(filename);
    printf("%d\n",filenum);
    printf("input file name\n");
    for(i=0;i<filenum;i++)
        printf("%s\n",filename[i]);

        printf("读取输入文件数独计算机解\n");
        memset(save,0,sizeof(save));
            for(k=0;k<filenum;k++)
            {
                cishu=0;
                FILE *f1;//文件指针
                char i_f_name[256]="../input/";//输入文件名
                char o_f_name[256]="../output/";//输出文件
                strcat(i_f_name,filename[k]);
                f1=fopen(i_f_name,"r");
                printf("%s",i_f_name);
                printf("数独中的原始数据，没有数据的用0代替。\n");
                for(i=0;i<9;i++)
                    {
                        for(j=0;j<9;j++)
                            fscanf(f1,"%d",&save[i][j]);
                        fscanf(f1,"\n");
                    }
                fclose(f1);
                strcat(o_f_name,filename[k]);
                f1=fopen(o_f_name,"w");
                for(i=0;i<9;i++)
                    {for(j=0;j<9;j++)
                        printf("%d ",save[i][j]);
                    printf("\n");
                    }
                printf("数独的解为：\n\n");
                cc='y';
                shudu(save,0,f1);
                if(result==0)
                    {
                        printf("此数独无解!");
                        fprintf(f1,"此数独无解!\n");
                    }
                fclose(f1);
                result=0;
                printf("\n\n\n");
            }
    end=clock();
    printf("\n 程序运行时间%d ms",end-start);
    return 0;
}



    //输出可行的解
void print(int a[9][9],FILE *f)
{
    int i,j;
    result++;
    if(a[5][5]!=0)
    {
        printf("搜索次数:%d \n",cishu);
        fprintf(f,"搜索次数:%d \n",cishu);
        cishu=0;
        printf("第%d个填法为：\n",result);
        fprintf(f,"第%d个填法为：\n",result);
        for(i=0;i<9;i++)
        {
        for(j=0;j<9;j++)
            {
                    printf("%d ",a[i][j]);
                    fprintf(f,"%d ",a[i][j]);
                if((j==2)||(j==5))
                    {
                        //printf(" ");
                        fprintf(f," ");
                    }
            }
        printf("\n");
        fprintf(f,"\n");
        if((i==2)||(i==5))
            {
                //printf("\n");
                fprintf(f,"\n");
            }
        }
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
        save[i][j]=a[i][j];
    }
    printf("\n\n\n");
    fprintf(f,"\n\n\n");
}




//判断是否可以将第i行、第j列的数设为k
int check(int a[9][9],int i,int j,int k)
{
    int m,n;
    //判断行
    for(n=0;n<9;n++)
    {
    if(a[i][n] == k)
    return 0;
    }
    //判断列
    for(m=0;m<9;m++)
    {
    if(a[m][j] == k)
    return 0;
    }
    //判断所在小九宫格
    int t1=(i/3)*3,t2=(j/3)*3;
    for(m=t1;m<t1+3;m++)
    {
    for(n=t2;n<t2+3;n++)
        {
        if(a[m][n] == k)
        return 0;
        }
    }

    //判断对角线
    if(i==j)
    for(m=0;m<9;m++)
    {
        if(a[m][m]==k)
            return 0;
    }
    if(i==8-j)
    for(m=0;m<9;m++)
    {
        if(a[m][8-m]==k)
            return 0;
    }
//可行，返回true
return 1;
}



//数独求解函数
void shudu(int a[9][9],int n,FILE *f)
{
    cishu++;
    int temp[9][9];
    int i,j,k;
    if(result<1)
    //cc='y'的意思是求出所有解,至少也要给出一个解
    {
        for(i=0;i<9;i++)
        {
        for(j=0;j<9;j++)
        temp[i][j]=a[i][j];
        }
        i=n/9; j=n%9; //求出第n个数的行数和列数
        if(a[i][j] != 0) //已经有原始数据
        {
            if(n == 80) //是最后一个格子，输出可行解
                print(temp,f);
            else //不是最后一个格子，求下一个格子
                shudu(temp,n+1,f);
        }
        else //没有数据
        {
            for(k=1;k<=9;k++)
            {
            int flag=check(temp,i,j,k);
                if(flag) //第i行、第j列可以是k
                {
                temp[i][j]=k; //设为k
                if(n == 80)
                    print(temp,f);
                else
                    shudu(temp,n+1,f);
                    temp[i][j]=0; //恢复为0，判断下一个k
                }
            }
        }
    }
}



int getAllTestcase(char filename[][256])
{
	DIR *dir;
	struct dirent *entry;
	int m=0;
	if (!(dir=opendir("../input"))){
		printf("[ERR] No input file\n");
		exit(1);
	}

	while(entry=readdir(dir)){
		char temp[5];
		//不能写成temp[4],这样就没有终止符了。
		int len=strlen(entry->d_name);
		int i;
        if(len<4)
            continue;
		for (i=0;i<4;i++)
		{
			temp[i]=entry->d_name[len-4+i];
		}
		if (!strcmp(temp,".txt")){
            //如果相等strcmp返回0，所以要加'!'。
			strcpy(filename[m],entry->d_name);
			m++;
		}
	}
	closedir(dir);
	return m;
}
