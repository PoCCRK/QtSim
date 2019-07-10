import java.util.*;
import java.io.*;

class Goods {
    private int quantity = 100;
    public void getwork (int x){
        quantity -= x;
        System.out.println("货物储量 = " + quantity + " kg" );
        try{
            FileWriter out = new FileWriter("Log.txt", true);
            out.write("货物储量 = " + quantity + " kg\n");
            out.close();
        }
        catch(IOException exp){System.out.println(exp.toString());}
    }
    public void setQuantity(int q){quantity = q;}
    public int getQuantity() {return quantity;}
}

class Work implements Runnable {
    Goods g;
    Random rand;
    Work() {
        rand = new Random();
        g = new Goods();
    }
    public void run() {
        while ( g.getQuantity() > 0 ){
            synchronized(g) {
                int x = rand.nextInt(10);
                if ( x>g.getQuantity() )
                    x = g.getQuantity();
                String name = Thread.currentThread().getName();
                try{
                    FileWriter out = new FileWriter("Log.txt", true);
                    out.write( name + " 搬运了 " + x + " kg\n");
                    out.close();
                }
                catch(IOException exp){System.out.println(exp.toString());}
                System.out.println( name + " 搬运了 " + x + " kg" );
                g.getwork(x);
                try {
                    Thread.currentThread().sleep( 1000 );
                } catch (InterruptedException e) {System.out.println(e.toString());}
            }
        }
    }
}

public class Demo {
    public static void main (String[] args) {

    try {
        FileWriter out = new FileWriter("Log.txt");
        Work c = new Work();
        System.out.println("货物储量 = " + c.g.getQuantity() + " kg" );
        out.write("货物储量 = " + c.g.getQuantity() + " kg\n" );
        out.close();
        Thread A = new Thread(c);A.setName("A");
        Thread B = new Thread(c);B.setName("B");
        Thread C = new Thread(c);C.setName("C");
        A.start();
        B.start();
        C.start();
    }catch(IOException exp){System.out.println(exp.toString());}
}
}
