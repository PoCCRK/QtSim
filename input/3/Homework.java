class Shape {
    Shape(){
        System.out.println("There is a new shape.");
    }
    void GetArea(){
        System.out.println("The area of this shape is:  .");
    }
};
class Circle extends Shape {
    private double radius;

    Circle(){
        radius = 2;
        System.out.println("There is a new circle.");
    }
    Circle(double r){
        radius = r;
        System.out.println("There is a new circle.");
    }
    void GetArea(){
        double s;
        s = 3.14 * radius * radius;
        System.out.println("The area of this circle is: "+s+".");
    }
};
class Rectangle extends Shape {
    private double width;
    private double length;

    Rectangle () {
        width = 4;
        length = 3;
        System.out.println("There is a new rectangle.");
    }
    Rectangle (double w, double l){
        width = w;
        length = l;
        System.out.println("There is a new rectangle.");
    }
    void GetArea(){
        double s;
        s = width * length;
        System.out.println("The area of this rectangle is: "+s+".");
    }
};

public class Homework{
    public static void main(String[] args) {
        Shape s = new Shape();
        s.GetArea();

        Circle c1 = new Circle();
        c1.GetArea();
        Circle c2 = new Circle(1);
        c2.GetArea();

        Rectangle r1 = new Rectangle();
        r1.GetArea();
        Rectangle r2 = new Rectangle(1, 2);
        r2.GetArea();
    }
}
