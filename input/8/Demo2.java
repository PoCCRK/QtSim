import java.io.*;

public class Demo2 {
    public static void main(String args[]) {
        String str[] = { "First line\n", "Second line\n", "Last line\n" };
        try {
            RandomAccessFile rf = new RandomAccessFile( "file2.txt", "rw" );
            System.out.println( "\n文件指针位置为：" + rf.getFilePointer() );
            System.out.println( "文件的长度为：" + rf.length() );
            rf.seek(rf.length());
            System.out.println( "文件指针现在的位置为：" + rf.getFilePointer() );
            for(int i = 0; i < 3; i++)
                rf.writeChars(str[i]);
            rf.seek(10);
            System.out.println( "\n选择显示的文件内容：" );
            String s;
            while( (s = rf.readLine()) != null )
                System.out.println(s);
            rf.close();
        }
        catch(FileNotFoundException fnoe) {}
        catch(IOException ioe) {}
    }
}
