

//important!!
//����wasd���Ʒ��򣡣���
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>//Sleep������ͷ�ļ�
#include<conio.h>
#define h 16  //�߶�
#define w 20  //���
#define level  5     //�Ѷȵȼ���Խ��Խ��
char a[h+1][w+1];
void initial();//��ʼ��
void food();//����ʳ��
void draw();//��ͼ
void move();//�ƶ�
void getturn();//�õ�ת���ķ���
void turn(char direction);//ת��
void judge();//�ж��Ƿ��������Ƿ�Ե�����
int alive=1;//alive=1����û����alive=0��Ϸ����
int len=5;//̰���ߵĳ���
char left='w';
char right='s';
char front='d';
char back='a';
int nowheadx,nowheady;
int headx,heady;
char *body[(h+1)*(w+1)];
int main()
{
int i;
initial();//��ʼ����ͼ
food();
draw();
while(alive)
    {
    Sleep(100*level);
    getturn();
    judge();
    //move();
    system("cls");
    draw();
    }
}

void initial()
{int i=0,j=0,k=0;
for(j=0;j<=w;j++)
    a[0][j]='#';
for(j=0;j<=w;j++)
    a[h][j]='#';
for(i=1;i<h;i++)
      {    for(j=0;j<=w;j++)
                 {if((j==0)||(j==w))
                     a[i][j]='#';
                 else
                     a[i][j]=' ';
                   }
    }
i++;
for(i=h/2,j=w/2;j<=w/2+4;j++)
       a[i][j]='*';
a[h/2][w/2+4]='+';
body[0]=&a[h/2][w/2]; body[1]=&a[h/2][w/2+1];
body[2]=&a[h/2][w/2+2]; body[3]=&a[h/2][w/2+3];
}

void food()
{int i,j,flag;
flag=0;
for(i=0;i<=h&&!flag;i++)
    for(j=0;j<=w&&!flag;j++)
        if(a[i][j]=='-')
            flag=1;
srand (time(NULL));
while(!flag)
    {i=rand()%(h-1)+1;
     j=rand()%(w-1)+1;
    if(a[i][j]==' ')
        {a[i][j]='-';
        break;
        }
    else
        continue;
    }
}



void draw()
{int i,j;
for(i=0;i<=h;i++)
      {for(j=0;j<=w;j++)
           printf("%c",a[i][j]);
            printf("\n");
      }
}

void judge()
{
    if(a[nowheadx][nowheady]=='-')
        {
            a[nowheadx][nowheady]='+';
            len++;
            body[len-2]=&a[headx][heady];
            food();//������ʳ��
        }
    if(a[nowheadx][nowheady]=='#')
        {alive=0;
        printf("game over !!!");
        exit(0);
        }
    if(a[nowheadx][nowheady]=='*')
        {alive=0;
        printf("game over !!!");
        exit(0);
        }
    else move();
    if(alive==0)
        {
            printf("game over!!!");
            exit(0);
        }
}

void move()
{
    int i;
    a[nowheadx][nowheady]='+';
    a[headx][heady]='*';
    //headx=nowheadx;
    //heady=nowheady;
    printf("nowheadx=%d nowheady=%d",nowheadx,nowheady);
    *body[0]=' ';
    for(i=0;i<=len-2;i++)
        body[i]=body[i+1];
    body[len-2]=&a[headx][heady];
    printf("\n body[2]=%d  a[headx][heady-2]=%d",body[2],&a[headx][heady-2]);
}


void getturn()
{
char t;
while(kbhit())//khbit��������������ʱֵΪtrue,��û������ʱΪfalse
    {
    t=getch();//�õ�����,getchar()Ҫ���س��Ժ�ż������У���getch()���Բ���ʾ���Ҽ�������
    if(t==left)
        {
        turn(left);
        left=back;
        back=right;
        right=front;
        front=t;
        goto gett;
        }
    else if(t==right)
        {
        turn(right);
        right=back;
        back=left;
        left=front;
        front=t;
        goto gett;
        }
    }
turn(front);//û�����룬Ĭ��ǰ��
gett:;
while(kbhit())
    t=getch();
}

void turn(char direction)
{
int i,j,k,flag;
flag=0;
for(i=0;((i<=h)&&(!flag));i++)
    for(j=0;((j<=w)&&(!flag));j++)
        {
        if(a[i][j]=='+')
            {flag=1;
            headx=i;heady=j;
            printf("headx=%d heady=%d",i,j);
            }
        else if(i==w&&j==h)
            {printf("wrong");
            exit(0);
            }
        }
    switch(direction)
    {
    case 'w':
    nowheadx=headx-1;
    nowheady=heady;
    break;
    case 's':
    nowheadx=headx+1;
    nowheady=heady;
    break;
    case 'a':
    nowheady=heady-1;
    nowheadx=headx;
    break;
    case 'd':
    nowheady=heady+1;
    nowheadx=headx;
    break;
    }
}
