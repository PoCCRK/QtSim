import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class AddMenuDemo {
    public static void main(String[] args) {
        JFrame win = new JFrame("Hello JFrame!");

        Menu m1 = new Menu("File");
        Menu m2 = new Menu("Edit");
        MenuItem mi1 = new MenuItem("Open");
        MenuItem mi2 = new MenuItem("Copy");
        MenuItem mi3 = new MenuItem("Cut");
        MenuItem mi4 = new MenuItem("Paste");
        MenuItem mi5 = new MenuItem("Exit");
        m2.add(mi2);
        m2.add(mi3);
        m2.add(mi4);
        m1.add(mi1);
        m1.add(m2);
        m1.addSeparator();
        m1.add(mi5);

        MenuBar mb = new MenuBar();
        mb.add(m1);
        win.setMenuBar(mb);

        win.setSize(400, 300);
        win.setVisible(true);
        win.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
