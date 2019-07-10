import java.util.*;

public class MathDemo {
    public static void main(String[] args) {
        Random rand = new Random();
        System.out.println("100以内一个随机整数:" + rand.nextInt(100));
        System.out.println("一个随机双精度浮点数:" + rand.nextDouble());
        System.out.println("30弧度的正弦值:" + Math.sin(Math.toRadians(30.0)));
        System.out.println("e的对数值：" + Math.log(Math.E));
        System.out.println("2的3次方：" + Math.pow(2.0, 3.0));
        System.out.println("33.6F四舍五入：" + Math.round(33.6F));
    }
}
