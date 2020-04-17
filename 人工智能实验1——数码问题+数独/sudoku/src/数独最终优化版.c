#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<time.h>
int result=0; //结果数
int save[9][9][11];
int count=81;//还有多少个空位
int cishu=0;
int temp;
clock_t start,end;
int main()
{
    start=clock();
    int i,j,k;

    void shudu(int n,FILE *f);
    //数独求解函数,n代表位置0<=n<81。
    //主要运用了所学知识的函数

    int update_yueshu(int x,int y,int z,int flag);
    //在x,y位置填上数或者去掉x,y位置的数之后
    //更新约束数组
    //flag=1时是填数
    //flag=-1时是去掉数

    int getAllTestcase(char filename[][256]);
    //得到所有的测试样例的文件名，返回值为文件个数。

    char filename[50][256];
    int filenum=getAllTestcase(filename);
    printf("%d\n",filenum);
    printf("input file name\n");
    for(i=0;i<filenum;i++)
        printf("%s\n",filename[i]);

        printf("读取输入文件数独计算机解\n");
            for(k=0;k<filenum;k++)
            {
                cishu=0;
                count=81;
                memset(save,0,sizeof(save));
                for(i=0;i<9;i++)
                    for(j=0;j<9;j++)
                        save[i][j][10]=9;
                result=0;
                FILE *f1;//文件指针
                char i_f_name[256]="../input/";//输入文件名
                char o_f_name[256]="../output/final_";//输出文件
                strcat(i_f_name,filename[k]);
                f1=fopen(i_f_name,"r");
                printf("%s",i_f_name);
                printf("数独中的原始数据，没有数据的用0代替。\n");
                for(i=0;i<9;i++)
                    {
                        for(j=0;j<9;j++)
                            {
                                fscanf(f1,"%d",&temp);
                                if(temp==0)
                                    continue;
                                else
                                {
                                    count--;
                                    update_yueshu(i,j,temp,1);
                                }
                            }
                        fscanf(f1,"\n");
                    }
                fclose(f1);//从文件中读取数据操作结束

                strcat(o_f_name,filename[k]);
                f1=fopen(o_f_name,"w");
                for(i=0;i<9;i++)
                    {for(j=0;j<9;j++)
                        {
                            printf("%d ",save[i][j][0]);
                        }
                    printf("\n");
                    }
                printf("剩余空位数%d\n",count);
                printf("数独的解为：\n\n");
                shudu(get_max_yueshu(),f1);
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

void shudu(int n,FILE *f)
{
    cishu++;
    int i,j,k;
    if(result==1)
        return;
    if(count==0)
    {
        result=1;
        printf("得出最终解所需递归次数：%d\n",cishu);
        fprintf(f,"得出最终解所需递归次数：%d\n",cishu);
        for(i=0;i<9;i++)
            {

            for(j=0;j<9;j++)
                {
                    printf("%2d",save[i][j][0]);
                    fprintf(f,"%2d",save[i][j][0]);
                }
            printf("\n");
            fprintf(f,"\n");
            }
        return;
    }
    int x,y;
    x=n/9;y=n%9;
    for(i=1;i<=9;i++)
    {
        if(save[x][y][i]==0)
        {
            count--;
            if(update_yueshu(x,y,i,1)!=0)
                shudu(get_max_yueshu(),f);
            count++;
            update_yueshu(x,y,i,-1);
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



int update_yueshu(int x,int y,int z,int flag)
    //在x,y位置填上数z之后 或者去掉x,y位置的数z之后
    //更新约束数组
    //flag=1时是填数
    //flag=-1时是去掉数
    //返回值仅仅在填数的时候生效，
    //如果出现填完数之后某个位置无可填的数之后
    //直接返回0，否则返回1
    {
        int i,j;
        int res=1;
            if(flag==1)
            {
                save[x][y][0]=z;
                save[x][y][10]=10000;

                for(i=0;i<9;i++)
                {
                if(i!=x)
                    {
                    if(save[i][y][z]==0)
                        save[i][y][10]--;
                    if(save[i][y][10]==0)
                        res=0;
                    save[i][y][z]=save[i][y][z]+flag;
                    }
                }

                for(i=0;i<9;i++)
                {
                if(i!=y)
                    {
                    if(save[x][i][z]==0)
                        save[x][i][10]--;
                    if(save[x][i][10]==0)
                        res=0;
                    save[x][i][z]=save[x][i][z]+flag;
                    }
                }

                if(x==y)
                {
                    for(i=0;i<9;i++)
                    {
                    if(x!=i)
                        {
                            if(save[i][i][z]==0)
                                save[i][i][10]--;
                            if(save[i][i][10]==0)
                                res=0;
                            save[i][i][z]=save[i][i][z]+flag;
                        }
                    }
                }
            if(x==8-y)
                {
                    for(i=0;i<9;i++)
                        if(x!=i)
                            {
                                if(save[i][8-i][z]==0)
                                    save[i][8-i][10]--;
                                if(save[i][8-i][10]==0)
                                    res=0;
                                save[i][8-i][z]=save[i][8-i][z]+flag;
                            }
                }

            int hang=x/3;int lie=y/3;//位于哪个九宫格中
            for(i=hang*3;i<(hang+1)*3;i++)
                for(j=lie*3;j<(lie+1)*3;j++)
                    if(x!=i&&y!=j)
                    {
                        if(save[i][j][z]==0)
                            save[i][j][10]--;
                        if(save[i][j][10]==0)
                            res=0;
                        save[i][j][z]=save[i][j][z]+flag;
                    }
                return res;
            }



            if(flag==-1)
                //去掉某个位置的数
                //重新计算save，当前位置的save和与之关联的save
            {
                save[x][y][0]=0;
                save[x][y][10]=0;
                for(i=1;i<=9;i++)
                    if(save[x][y][i]==0)
                        save[x][y][10]++;
                for(i=0;i<9;i++)
                {
                if(i!=x)
                    {
                    save[i][y][z]=save[i][y][z]+flag;
                    if(save[i][y][z]==0)
                        save[i][y][10]++;
                    }
                }

                for(i=0;i<9;i++)
                {
                if(i!=y)
                    {
                    save[x][i][z]=save[x][i][z]+flag;
                    if(save[x][i][z]==0)
                        save[x][i][10]++;
                    }
                }

                if(x==y)
                {
                    for(i=0;i<9;i++)
                    {
                    if(x!=i)
                        {
                            save[i][i][z]=save[i][i][z]+flag;
                             if(save[i][i][z]==0)
                                save[i][i][10]++;
                        }
                    }
                }
            if(x==8-y)
                {
                    for(i=0;i<9;i++)
                        if(x!=i)
                            {
                                save[i][8-i][z]=save[i][8-i][z]+flag;
                                if(save[i][8-i][z]==0)
                                    save[i][8-i][10]++;
                            }
                }

            int hang=x/3;int lie=y/3;//位于哪个九宫格中
            for(i=hang*3;i<(hang+1)*3;i++)
                for(j=lie*3;j<(lie+1)*3;j++)
                    if(x!=i&&y!=j)
                    {
                        save[i][j][z]=save[i][j][z]+flag;
                        if(save[i][j][z]==0)
                            save[i][j][10]++;
                    }
                return res;
            }

            return res;
    }

    int get_max_yueshu()
    //找到能填数字最少的点
    {
        int min,minp;
        min=100000;
        int i,j,k;
        for(i=0;i<9;i++)
            for(j=0;j<9;j++)
            {
                if(save[i][j][10]<min)
                {
                    min=save[i][j][10];
                    minp=i*9+j;
                }
            }
        return minp;
    }
