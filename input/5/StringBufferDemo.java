import java.util.Arrays;

public class StringBufferDemo{
    public static void main(String[] args) {
        String str = "Hello Java";
        StringBuffer buffer = new StringBuffer();
        buffer.append(str);
        System.out.println(buffer.toString());
    }
}
