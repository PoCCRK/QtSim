import java.util.*;

public class VectorDemo {
    public static void main(String[] args) {
        Vector v = new Vector();
        v.addElement("1");
        System.out.println("v.addElement('1');        ֮���0��Ԫ��Ϊ: " + v.elementAt(0) );
        v.insertElementAt("2", 0);
        System.out.println("v.insertElementAt('2', 0);֮���0��Ԫ��Ϊ: " + v.elementAt(0) + "��1��Ԫ��Ϊ��" + v.elementAt(1) );
        v.setElementAt("5", 1);
        System.out.println("v.setElementAt('5', 1);   ֮���0��Ԫ��Ϊ: " + v.elementAt(0) + "��1��Ԫ��Ϊ��" + v.elementAt(1) );
        v.removeElementAt(0);
        System.out.println("v.removeElementAt(0);     ֮���0��Ԫ��Ϊ: " + v.elementAt(0) );
    }
}
