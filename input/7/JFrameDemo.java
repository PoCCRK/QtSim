import javax.swing.JFrame;

public class JFrameDemo {
    public static void main(String[] args) {
        JFrame win = new JFrame("Hello JFrame!");//创建窗口对象
        win.setSize(400, 300);//设置窗口大小
        win.setVisible(true);//设置窗口可见
        win.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//设置窗口关闭操作
    }
}
