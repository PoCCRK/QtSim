import javax.swing.JFrame;

public class JFrameDemo {
    public static void main(String[] args) {
        JFrame win = new JFrame("Hello JFrame!");//�������ڶ���
        win.setSize(400, 300);//���ô��ڴ�С
        win.setVisible(true);//���ô��ڿɼ�
        win.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//���ô��ڹرղ���
    }
}
