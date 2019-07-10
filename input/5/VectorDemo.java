import java.util.*;

public class VectorDemo {
    public static void main(String[] args) {
        Vector v = new Vector();
        v.addElement("1");
        System.out.println("v.addElement('1');        之后第0号元素为: " + v.elementAt(0) );
        v.insertElementAt("2", 0);
        System.out.println("v.insertElementAt('2', 0);之后第0号元素为: " + v.elementAt(0) + "第1号元素为：" + v.elementAt(1) );
        v.setElementAt("5", 1);
        System.out.println("v.setElementAt('5', 1);   之后第0号元素为: " + v.elementAt(0) + "第1号元素为：" + v.elementAt(1) );
        v.removeElementAt(0);
        System.out.println("v.removeElementAt(0);     之后第0号元素为: " + v.elementAt(0) );
    }
}
