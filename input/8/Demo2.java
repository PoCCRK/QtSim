import java.io.*;

public class Demo2 {
    public static void main(String args[]) {
        String str[] = { "First line\n", "Second line\n", "Last line\n" };
        try {
            RandomAccessFile rf = new RandomAccessFile( "file2.txt", "rw" );
            System.out.println( "\n�ļ�ָ��λ��Ϊ��" + rf.getFilePointer() );
            System.out.println( "�ļ��ĳ���Ϊ��" + rf.length() );
            rf.seek(rf.length());
            System.out.println( "�ļ�ָ�����ڵ�λ��Ϊ��" + rf.getFilePointer() );
            for(int i = 0; i < 3; i++)
                rf.writeChars(str[i]);
            rf.seek(10);
            System.out.println( "\nѡ����ʾ���ļ����ݣ�" );
            String s;
            while( (s = rf.readLine()) != null )
                System.out.println(s);
            rf.close();
        }
        catch(FileNotFoundException fnoe) {}
        catch(IOException ioe) {}
    }
}
