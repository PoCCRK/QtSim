import java.util.Scanner;
public class Leapyear {
   public static void main (String args[]) {
	Scanner input=new Scanner(System.in);
	System.out.print("请输入年份:");
	int year = input.nextInt();
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
	   {
		System.out.println("该年是闰年");
	   }
	else
	   {
		System.out.println("该年是平年");
	   }
	}

}
