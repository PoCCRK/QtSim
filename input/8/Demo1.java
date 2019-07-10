import java.io.*;

public class Demo1 {
    public static void main(String[] args) throws IOException {
        FileReader in = new FileReader("input.txt");
        BufferedReader reader = new BufferedReader(in);
        FileWriter out = new FileWriter("output.txt");

        String str;
        while((str = reader.readLine()) != null) {
            System.out.println(str);
            out.write(str+ "\n");
        }
        in.close();
        out.close();
    }
}
