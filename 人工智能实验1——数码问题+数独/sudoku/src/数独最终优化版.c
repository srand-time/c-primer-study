#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<time.h>
int result=0; //�����
int save[9][9][11];
int count=81;//���ж��ٸ���λ
int cishu=0;
int temp;
clock_t start,end;
int main()
{
    start=clock();
    int i,j,k;

    void shudu(int n,FILE *f);
    //������⺯��,n����λ��0<=n<81��
    //��Ҫ��������ѧ֪ʶ�ĺ���

    int update_yueshu(int x,int y,int z,int flag);
    //��x,yλ������������ȥ��x,yλ�õ���֮��
    //����Լ������
    //flag=1ʱ������
    //flag=-1ʱ��ȥ����

    int getAllTestcase(char filename[][256]);
    //�õ����еĲ����������ļ���������ֵΪ�ļ�������

    char filename[50][256];
    int filenum=getAllTestcase(filename);
    printf("%d\n",filenum);
    printf("input file name\n");
    for(i=0;i<filenum;i++)
        printf("%s\n",filename[i]);

        printf("��ȡ�����ļ������������\n");
            for(k=0;k<filenum;k++)
            {
                cishu=0;
                count=81;
                memset(save,0,sizeof(save));
                for(i=0;i<9;i++)
                    for(j=0;j<9;j++)
                        save[i][j][10]=9;
                result=0;
                FILE *f1;//�ļ�ָ��
                char i_f_name[256]="../input/";//�����ļ���
                char o_f_name[256]="../output/final_";//����ļ�
                strcat(i_f_name,filename[k]);
                f1=fopen(i_f_name,"r");
                printf("%s",i_f_name);
                printf("�����е�ԭʼ���ݣ�û�����ݵ���0���档\n");
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
                fclose(f1);//���ļ��ж�ȡ���ݲ�������

                strcat(o_f_name,filename[k]);
                f1=fopen(o_f_name,"w");
                for(i=0;i<9;i++)
                    {for(j=0;j<9;j++)
                        {
                            printf("%d ",save[i][j][0]);
                        }
                    printf("\n");
                    }
                printf("ʣ���λ��%d\n",count);
                printf("�����Ľ�Ϊ��\n\n");
                shudu(get_max_yueshu(),f1);
                if(result==0)
                    {
                        printf("�������޽�!");
                        fprintf(f1,"�������޽�!\n");
                    }
                fclose(f1);
                result=0;
                printf("\n\n\n");
            }
    end=clock();
    printf("\n ��������ʱ��%d ms",end-start);
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
        printf("�ó����ս�����ݹ������%d\n",cishu);
        fprintf(f,"�ó����ս�����ݹ������%d\n",cishu);
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
		//����д��temp[4],������û����ֹ���ˡ�
		int len=strlen(entry->d_name);
		int i;
        if(len<4)
            continue;
		for (i=0;i<4;i++)
		{
			temp[i]=entry->d_name[len-4+i];
		}
		if (!strcmp(temp,".txt")){
            //������strcmp����0������Ҫ��'!'��
			strcpy(filename[m],entry->d_name);
			m++;
		}
	}
	closedir(dir);
	return m;
}



int update_yueshu(int x,int y,int z,int flag)
    //��x,yλ��������z֮�� ����ȥ��x,yλ�õ���z֮��
    //����Լ������
    //flag=1ʱ������
    //flag=-1ʱ��ȥ����
    //����ֵ������������ʱ����Ч��
    //�������������֮��ĳ��λ���޿������֮��
    //ֱ�ӷ���0�����򷵻�1
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

            int hang=x/3;int lie=y/3;//λ���ĸ��Ź�����
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
                //ȥ��ĳ��λ�õ���
                //���¼���save����ǰλ�õ�save����֮������save
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

            int hang=x/3;int lie=y/3;//λ���ĸ��Ź�����
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
    //�ҵ������������ٵĵ�
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
