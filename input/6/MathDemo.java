import java.util.*;

public class MathDemo {
    public static void main(String[] args) {
        Random rand = new Random();
        System.out.println("100����һ���������:" + rand.nextInt(100));
        System.out.println("һ�����˫���ȸ�����:" + rand.nextDouble());
        System.out.println("30���ȵ�����ֵ:" + Math.sin(Math.toRadians(30.0)));
        System.out.println("e�Ķ���ֵ��" + Math.log(Math.E));
        System.out.println("2��3�η���" + Math.pow(2.0, 3.0));
        System.out.println("33.6F�������룺" + Math.round(33.6F));
    }
}
