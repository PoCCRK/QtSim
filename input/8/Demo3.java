import java.io.*;

public class Demo3 {
    public static void main(String arg[]) {
        try {
            FileOutputStream fout = new FileOutputStream("file3.txt", true);
            DataOutputStream dout = new DataOutputStream(fout);
            dout.writeInt(1);
            dout.writeChars("ÂÞÂí"+"\n");
            dout.writeInt(2);
            dout.writeChars("±±¾©"+"\n");
            dout.close();
        }
        catch (IOException ioe) {}
        try {
            FileInputStream fin = new FileInputStream("file3.txt");
            DataInputStream din = new DataInputStream(fin);
            int i = din.readInt();
            while(i != -1) {
                System.out.print(i + " ");
                char ch;
                while((ch = din.readChar()) != '\n')
                    System.out.print(ch);
                System.out.println();
                i = din.readInt();
            }
            din.close();
        }
        catch(IOException ioe) {}
    }
}
