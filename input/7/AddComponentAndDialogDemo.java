import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class MyDialog extends JDialog{
	MyDialog(JFrame parent, Boolean modal){
		super(parent, modal);
		setLayout(new FlowLayout());
		setTitle("确认退出");
		setSize(200, 100);
		setResizable(false);

		JButton b1 = new JButton("确定");
		b1.addActionListener(
			new ActionListener(){
				public void actionPerformed(ActionEvent e) {
					parent.dispose();
                }
			}
		);
		add(b1);

		JButton b2 = new JButton("取消");
		b2.addActionListener(
			new ActionListener(){
				public void actionPerformed(ActionEvent e){
					dispose();
				}
			}
		);
		add(b2);
	}
}

public class AddComponentAndDialogDemo{
	public static void main(String[] args) {
		JFrame win = new JFrame("Hello JFrame!");
		win.setLayout(new FlowLayout()); //设置窗口布局

		JTextArea ta = new JTextArea(6, 33);
		win.add(ta);

		JTextField tf1 = new JTextField();
		tf1.setColumns(30);
		JTextField tf2 = new JTextField();
		tf2.setColumns(30);
		win.add(new JLabel("姓名: "));
		win.add(tf1);
		win.add(new JLabel("年龄: "));
		win.add(tf2);

		JButton b1 = new JButton("添加");
		b1.addActionListener(
			new ActionListener(){
				public void actionPerformed(ActionEvent e){
					ta.append("姓名: " + tf1.getText() + " 年龄: " + tf2.getText() + "\n");
				}
			}
		);
		win.add(b1);

		JButton b2 = new JButton("清空");
		b2.addActionListener(
			new ActionListener(){
				public void actionPerformed(ActionEvent e){
					ta.setText("");
				}
			}
		);
		win.add(b2);

        JButton b3 = new JButton("退出");
		b3.addActionListener(
			new ActionListener(){
				public void actionPerformed(ActionEvent e){
                    MyDialog dialog = new MyDialog(win, true);
                    dialog.setModal(true);
                    dialog.setVisible(true);
				}
			}
		);
		win.add(b3);


		win.setSize(400, 300);
		win.setVisible(true);
		win.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}
