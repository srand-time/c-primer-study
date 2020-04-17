import java.util.*;
import java.io.*;

public class solve{
	public static void main(String args[])
	{
		int i,j,k;
		System.out.println("������������ݣ�����ֻ�ÿո��������,��Ҫ�򶺺�!");
		int []input=new int [va.n*va.n];//��������
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
        System.out.println("��ʼ״̬�������پ���:");
        System.out.println(va.init_d);
        va.result=0;
        try_to_solve(s);//�����������Ⳣ�Եĺ���
        if(va.result==0)
            System.out.println("�������ʧ��");
	}


    private static void try_to_solve(String s)
    {
        List <String> state=new LinkedList<>();
        List <Integer> distant=new LinkedList<>();
        List <String> action=new LinkedList<>();//��������ʲô����
        String act="";
        state.add(s);
        distant.add(va.init_d);
        action.add(act);
        int i,j,k;
        int []t=new int [va.n*va.n];
        System.out.println(s);
        for(k=0;k<20000 && !distant.isEmpty();k++)//����ѭ�������ٴ�
        {
            String temp=state.get(0);
            //System.out.println(temp);
            if(distant.get(0)==0)
                {   
                va.result=1;   
                System.out.println("success!!!");    
                System.out.println("���ڶ��г���"+distant.size());
                System.out.println("ѭ������k="+k);
                System.out.println(action.get(0));
                return;  
                }
            int pos_zero=0;//�����ڵ�λ��
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
        System.out.println("���ڶ��г���"+distant.size());
        System.out.println("ѭ������k="+k);
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
    int []temp={1,2,3,4,5,6,7,8,0};//����Ŀ��״̬
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


//һ����������ȫ�ֱ�������
public class va{
	public static Map<String,Integer> map = new HashMap<>();
	//��ϣ��Ķ���
	//String����ĳ������״̬��������key��Ϊ1��ʾ���״̬�Ѿ��ù���
    public static int n=3;//���������ռ䵽���ж��
    public static int init_d;//��ʼ״̬�������پ���
    public static int result;//��������Ŀ�����û�н������ӡʧ����Ϣ
}