import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

public class SimpleCalculator{
	public static void main(String[] args) {
		JFrame calulator = new JFrame("A Simple Calulator");
		calulator.setLayout(new FlowLayout()); //设置窗口布局

        JTextArea ta = new JTextArea(1, 15);
		calulator.add(ta);

		JButton b9 = new JButton("9");
		b9.addActionListener( new ActionListener(){
            public void actionPerformed(ActionEvent e){
                ta.append("9");
            }
        });
		JButton b8 = new JButton("8");
		b8.addActionListener( new ActionListener(){
            public void actionPerformed(ActionEvent e){
                ta.append("8");
            }
        });
        JButton b7 = new JButton("7");
		b7.addActionListener( new ActionListener(){
            public void actionPerformed(ActionEvent e){
                ta.append("7");
            }
        });
        JButton b6 = new JButton("6");
		b6.addActionListener( new ActionListener(){
            public void actionPerformed(ActionEvent e){
                ta.append("6");
            }
        });
        JButton b5 = new JButton("5");
		b5.addActionListener( new ActionListener(){
            public void actionPerformed(ActionEvent e){
                ta.append("5");
            }
        });
        JButton b4 = new JButton("4");
		b4.addActionListener( new ActionListener(){
            public void actionPerformed(ActionEvent e){
                ta.append("4");
            }
        });
        JButton b3 = new JButton("3");
		b3.addActionListener( new ActionListener(){
            public void actionPerformed(ActionEvent e){
                ta.append("3");
            }
        });
		JButton b2 = new JButton("2");
		b2.addActionListener( new ActionListener(){
            public void actionPerformed(ActionEvent e){
                ta.append("2");
            }
        });
        JButton b1 = new JButton("1");
		b1.addActionListener( new ActionListener(){
            public void actionPerformed(ActionEvent e){
                ta.append("1");
            }
        });
        JButton b0 = new JButton("0");
		b0.addActionListener( new ActionListener(){
            public void actionPerformed(ActionEvent e){
                ta.append("0");
            }
        });
        JButton bdot = new JButton(".");
		bdot.addActionListener( new ActionListener(){
            public void actionPerformed(ActionEvent e){
                ta.append(".");
            }
        });
		JButton badd = new JButton("+");
		badd.addActionListener( new ActionListener(){
            public void actionPerformed(ActionEvent e){
                ta.append(" + ");
            }
        });
		JButton bsub = new JButton("-");
		bsub.addActionListener( new ActionListener(){
            public void actionPerformed(ActionEvent e){
                ta.append(" - ");
            }
        });
        JButton bmul = new JButton("*");
		bmul.addActionListener( new ActionListener(){
            public void actionPerformed(ActionEvent e){
                ta.append(" * ");
            }
        });
        JButton bdiv = new JButton("/");
		bdiv.addActionListener( new ActionListener(){
            public void actionPerformed(ActionEvent e){
                ta.append(" / ");
            }
        });
		JButton bequ = new JButton("=");
		bequ.addActionListener( new ActionListener(){
            public void actionPerformed(ActionEvent e){
                String s = ta.getText();
                Double o1 = new Double(0);
                Double o2 = new Double(0);
                Double o = new Double(0);
                String or = "";
                Scanner scanner = new Scanner(s);
                try {
                    o1 = scanner.nextDouble();
                    or = scanner.next();
                    o2 = scanner.nextDouble();
                }catch(InputMismatchException exp){
                    ta.setText("Error (negative unavailable)");
                }

                    System.out.println( o1 + or + o2 );
                if (scanner.hasNext())
                    ta.setText("Error (negative unavailable)");
                else{
                    if ( or.equals("+") ){
                        o = new Double( o1.doubleValue() + o2.doubleValue() );
                        ta.setText( o.toString() );
                        System.out.println( o1 + or + o2 + "=" + o);
                    }else System.out.println("e");
                    if ( or.equals("-") ){
                        o = new Double( o1.doubleValue() - o2.doubleValue() );
                        ta.setText( o.toString() );
                        System.out.println( o1 + or + o2 + "=" + o);
                    }else System.out.println("e");
                    if ( or.equals("*") ){
                        o = new Double( o1.doubleValue() * o2.doubleValue() );
                        ta.setText( o.toString() );
                        System.out.println( o1 + or + o2 + "=" + o);
                    }else System.out.println("e");
                    if ( or.equals("/") ){
                        if ( o2.doubleValue()==0 )
                            ta.setText("Error");
                        else {
                            o = new Double( o1.doubleValue() / o2.doubleValue() );
                            ta.setText( o.toString() );
                            System.out.println( o1 + or + o2 + "=" + o);
                        }
                    }else System.out.println("e");
                }
            }
        });
		JButton bclear = new JButton("C");
		bclear.addActionListener( new ActionListener(){
            public void actionPerformed(ActionEvent e){
                ta.setText("");
            }
        });

        calulator.add(b7);calulator.add(b8);calulator.add(b9);calulator.add(badd);
        calulator.add(b4);calulator.add(b5);calulator.add(b6);calulator.add(bsub);
        calulator.add(b1);calulator.add(b2);calulator.add(b3);calulator.add(bmul);
        calulator.add(b0);calulator.add(bdot);calulator.add(bequ);calulator.add(bdiv);
        calulator.add(bclear);
		calulator.setSize(210, 300);
		calulator.setVisible(true);
		calulator.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}
