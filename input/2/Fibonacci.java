public class Fibonacci{
	public static void main(String args[])
	{
	    int a=0,b=1,t=a+b,m;
	    System.out.print(" "+a+" "+b);
		while(t<=100)
		{
            System.out.print(" "+t);
            m=t;
            t=t+b;
            b=m;
		}
	}
}
