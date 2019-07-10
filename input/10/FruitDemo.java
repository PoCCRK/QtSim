//import java.util.*;

class Fruit{
    Fruit () {}
    void getColor () {}
};
class Apple extends Fruit{
    private String color;
    Apple () {
        color = "red";
        System.out.println("There is an apple.");
    }
    Apple ( String color ) {
        this.color = color;
        System.out.println("There is an apple.");
    }
    void getColor () {
        System.out.println("The color of this apple is:" + color + ".");
    }
};
class Orange extends Fruit{
    private String color;
    Orange () {
        color = "orange";
        System.out.println("There is an orange.");
    }
    Orange ( String color ) {
        this.color = color;
        System.out.println("There is an orange.");
    }
    void getColor () {
        System.out.println("The color of this orange is:" + color + ".");
    }
};
public class FruitDemo{
    public static void main (String[] args){
        new Apple().getColor();
        new Orange().getColor();
        new Apple("green").getColor();
        new Orange("yellow").getColor();
    }
}
