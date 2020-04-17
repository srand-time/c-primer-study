import java.util.*;
import java.io.*;

public class solve{
	public static void main(String args[])
	{
		int i,j,k;
		System.out.println("请输入测试数据，仅仅只用空格隔开数字,不要打逗号!");
		int []input=new int [va.n*va.n];//输入数组
		Scanner sc=new Scanner(System.in);
		for(i=0;i<va.n;i++)
			for(j=0;j<va.n;j++)
				input[i*va.n+j]=sc.nextInt();
		String s="";
		for(i=0;i<va.n;i++)
			for(j=0;j<va.n;j++)
				s=s+(char)(input[i*va.n+j]+'a');
		va.map.put(s,1);
        va.init_d=compute_distant(input);
        System.out.println("初始状态的曼哈顿距离:");
        System.out.println(va.init_d);
        va.result=0;
        try_to_solve(s);//对问题进行求解尝试的函数
        if(va.result==0)
            System.out.println("问题求解失败");
	}


    private static void try_to_solve(String s)
    {
        List <String> state=new LinkedList<>();
        List <Integer> distant=new LinkedList<>();
        List <String> action=new LinkedList<>();//都是用了什么动作
        String act="";
        state.add(s);
        distant.add(va.init_d);
        action.add(act);
        int i,j,k;
        int []t=new int [va.n*va.n];
        System.out.println(s);
        for(k=0;k<20000 && !distant.isEmpty();k++)//到底循环求解多少次
        {
            String temp=state.get(0);
            //System.out.println(temp);
            if(distant.get(0)==0)
                {   
                va.result=1;   
                System.out.println("success!!!");    
                System.out.println("现在队列长度"+distant.size());
                System.out.println("循环次数k="+k);
                System.out.println(action.get(0));
                return;  
                }
            int pos_zero=0;//零所在的位置
            int pos_x,pos_y;
            for(i=0;i<va.n*va.n;i++)
                if(temp.charAt(i)=='a')
                    {pos_zero=i;break;}
            pos_x=pos_zero/va.n;pos_y=pos_zero%va.n;
                if(pos_x>0)
                {
                    temp=exchange(temp,pos_zero,pos_zero-va.n);
                    //System.out.println(temp);
                    if(va.map.get(temp)==null)
                        {                  
                            va.map.put(temp,1);
                            state.add(temp);
                            for(j=0;j<va.n*va.n;j++)
                                t[j]=temp.charAt(j)-'a';
                            distant.add(compute_distant(t));
                            act=action.get(0);
                            act=act+t[pos_zero]+"_down ";
                            action.add(act);
                        }
                    temp=exchange(temp,pos_zero,pos_zero-va.n);
			    }

                if(pos_x<va.n-1)
                {
                    temp=exchange(temp,pos_zero,pos_zero+va.n);
                    //System.out.println(temp);
                    if(va.map.get(temp)==null)
                        {
                            va.map.put(temp,1);
                            state.add(temp);
                            for(j=0;j<va.n*va.n;j++)
                                t[j]=temp.charAt(j)-'a';
                            distant.add(compute_distant(t));
                            act=action.get(0);
                            act=act+t[pos_zero]+"_up ";
                            action.add(act);
                        }
                    temp=exchange(temp,pos_zero,pos_zero+va.n);
			    }

                if(pos_y>0)
                {
                    temp=exchange(temp,pos_zero,pos_zero-1);
                    //System.out.println(temp);
                    if(va.map.get(temp)==null)
                        {
                            va.map.put(temp,1);
                            state.add(temp);
                            for(j=0;j<va.n*va.n;j++)
                                t[j]=temp.charAt(j)-'a';
                            distant.add(compute_distant(t));
                            act=action.get(0);
                            act=act+t[pos_zero]+"_right ";
                            action.add(act);
                        }
                    temp=exchange(temp,pos_zero,pos_zero-1);
			    }

                if(pos_y<va.n-1)
                {
                    temp=exchange(temp,pos_zero,pos_zero+1);
                    //System.out.println(temp);
                    if(va.map.get(temp)==null)
                        {
                            va.map.put(temp,1);
                            state.add(temp);
                            for(j=0;j<va.n*va.n;j++)
                                t[j]=temp.charAt(j)-'a';
                            distant.add(compute_distant(t));
                            act=action.get(0);
                            act=act+t[pos_zero]+"_left ";
                            action.add(act);
                        }
                    temp=exchange(temp,pos_zero,pos_zero+1);
			    }
            state.remove(0);
            distant.remove(0);
            action.remove(0);
		}
        System.out.println("现在队列长度"+distant.size());
        System.out.println("循环次数k="+k);
    }

    private static String exchange(String s,int index1,int index2)
    {
        char temp1,temp2;
        char []res=s.toCharArray();
        temp1=s.charAt(index1);
        temp2=s.charAt(index2);
        res[index1]=temp2;res[index2]=temp1;
        String news="";
        for(int i=0;i<va.n*va.n;i++)
            news=news+res[i];
        return news;
	}
    
	private static int compute_distant(int b[])
    {
    int x,y;
    int i,j;
    int distant=0;
    int flag=0;
    int []temp={1,2,3,4,5,6,7,8,0};//定义目标状态
    for(x=0;x<va.n;x++)
        for(y=0;y<va.n;y++)
            {
            for(i=0;i<va.n;i++)
                {
                flag=0;
                    for(j=0;j<va.n;j++)
                    {
                        if(b[x*va.n+y]==temp[i*va.n+j])
                            {
                            distant+=Math.abs(x-i)+Math.abs(y-j);
                            temp[i*va.n+j]=-1;
                            flag=1;
                            break;
                            }
                    }
                    if(flag==1)
                        break;
                }
            }
    return distant;
    }
}


//一个用来定义全局变量的类
public class va{
	public static Map<String,Integer> map = new HashMap<>();
	//哈希表的定义
	//String代表某个数组状态，而将其key置为1表示这个状态已经用过了
    public static int n=3;//定义整个空间到底有多大
    public static int init_d;//初始状态的曼哈顿距离
    public static int result;//定义结果数目，如果没有结果，打印失败信息
}