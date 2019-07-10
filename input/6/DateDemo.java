import java.util.*;
import java.text.DateFormat;

public class DateDemo {
    public static void main(String[] args) {
        Date today = new Date();
        Calendar now;
        DateFormat f1, f2;
        String s1, s2;

        System.out.println("�ַ�����ʽ�Ľ���: " + today.toString());//�ַ�����ʽ
        f1 = DateFormat.getInstance();//��Ĭ�ϸ�ʽ���ɸ�ʽ����
        s1 = f1.format(today);//������ת��Ϊ�ַ���
        System.out.println("��Ĭ�ϸ�ʽ������ת���ĸ�ʽ�Ľ���: " + s1);//ϵͳ��ʽ

        f1 = DateFormat.getDateInstance(DateFormat.LONG, Locale.CHINA);
        //���ɳ���ʽ���й����ڸ�ʽ����
        f2 = DateFormat.getTimeInstance(DateFormat.LONG, Locale.CHINA);
        //���ɳ���ʽ���й�ʱ���ʽ����
        s1 = f1.format(today);//������ת��Ϊ�����ַ���
        s2 = f2.format(today);//������ת��Ϊʱ���ַ���
        System.out.println("�ó���ʽ���й����ڸ�ʽ������ת��ת���Ľ������ں�ʱ��: " + s1 + " " + s2);

        now = Calendar.getInstance();//��ȡϵͳʱ��
        s1 = now.get(now.HOUR) + " ʱ" + now.get(now.MINUTE) + " ��"
        + now.get(now.SECOND) + " ��";
        System.out.println("��Calendar��ȡϵͳʱ��: " + s1);
    }
}

