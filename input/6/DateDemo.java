import java.util.*;
import java.text.DateFormat;

public class DateDemo {
    public static void main(String[] args) {
        Date today = new Date();
        Calendar now;
        DateFormat f1, f2;
        String s1, s2;

        System.out.println("字符串格式的今天: " + today.toString());//字符串格式
        f1 = DateFormat.getInstance();//以默认格式生成格式化器
        s1 = f1.format(today);//将日期转换为字符串
        System.out.println("用默认格式生成器转换的格式的今天: " + s1);//系统格式

        f1 = DateFormat.getDateInstance(DateFormat.LONG, Locale.CHINA);
        //生成长格式的中国日期格式化器
        f2 = DateFormat.getTimeInstance(DateFormat.LONG, Locale.CHINA);
        //生成长格式的中国时间格式化器
        s1 = f1.format(today);//将日期转换为日期字符串
        s2 = f2.format(today);//将日期转换为时间字符串
        System.out.println("用长格式的中国日期格式生成器转换转换的今天日期和时间: " + s1 + " " + s2);

        now = Calendar.getInstance();//获取系统时间
        s1 = now.get(now.HOUR) + " 时" + now.get(now.MINUTE) + " 分"
        + now.get(now.SECOND) + " 秒";
        System.out.println("用Calendar获取系统时间: " + s1);
    }
}

