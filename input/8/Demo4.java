import java.io.*;

public class Demo4 implements Serializable {
    String Name;
    int Age;

    Demo4(String Name, int Age) {
        this.Name = Name;
        this.Age = Age;
    }
    void save(String FileName) {
        try {
            FileOutputStream fout = new FileOutputStream(FileName);
            ObjectOutputStream out = new ObjectOutputStream(fout);
            out.writeObject(this);
            out.close();
        }
        catch (FileNotFoundException fe) {}
        catch (IOException ioe) {}
    }

    public static void main(String arg[]) {
        String FileName = "stu.obj";
        Demo4 demo1= new Demo4("Jack Mao", 22);
        demo1.save(FileName);

        try {
            FileInputStream fin = new FileInputStream(FileName);
            ObjectInputStream in = new ObjectInputStream(fin);
            Demo4 demo2 = (Demo4)in.readObject();
            System.out.println(demo2.getClass().getName() + " "
                               + demo2.getClass().getInterfaces()[0]);
            System.out.println("Name:" + demo2.Name + "Age:" + demo2.Age );
            in.close();
        }
        catch (FileNotFoundException fe) {}
        catch (IOException ioe) {}
        catch (ClassNotFoundException ioe) {}
    }
}
