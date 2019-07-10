import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class MyDialog extends JDialog{
	MyDialog(JFrame parent, Boolean modal){
		super(parent, modal);
		setLayout(new FlowLayout());
		setTitle("ȷ���˳�");
		setSize(200, 100);
		setResizable(false);

		JButton b1 = new JButton("ȷ��");
		b1.addActionListener(
			new ActionListener(){
				public void actionPerformed(ActionEvent e) {
					parent.dispose();
                }
			}
		);
		add(b1);

		JButton b2 = new JButton("ȡ��");
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
		win.setLayout(new FlowLayout()); //���ô��ڲ���

		JTextArea ta = new JTextArea(6, 33);
		win.add(ta);

		JTextField tf1 = new JTextField();
		tf1.setColumns(30);
		JTextField tf2 = new JTextField();
		tf2.setColumns(30);
		win.add(new JLabel("����: "));
		win.add(tf1);
		win.add(new JLabel("����: "));
		win.add(tf2);

		JButton b1 = new JButton("���");
		b1.addActionListener(
			new ActionListener(){
				public void actionPerformed(ActionEvent e){
					ta.append("����: " + tf1.getText() + " ����: " + tf2.getText() + "\n");
				}
			}
		);
		win.add(b1);

		JButton b2 = new JButton("���");
		b2.addActionListener(
			new ActionListener(){
				public void actionPerformed(ActionEvent e){
					ta.setText("");
				}
			}
		);
		win.add(b2);

        JButton b3 = new JButton("�˳�");
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
