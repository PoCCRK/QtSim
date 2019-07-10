public class Test2{
    public static void main(String[] args){
        Car c = new Car();
        Bicycle b = new Bicycle();
        System.out.println("The Max Speed of a car:"+c.getMaxSpeed());
        System.out.println("The number of Wheels on a car:"+c.getWheels());
        System.out.println("The Max Speed of a bicycle:"+b.getMaxSpeed());
        System.out.println("The number of Wheels on a bicycle:"+b.getWheels());
    }
};

interface Vehicle{
    public abstract int getMaxSpeed();
    public abstract int getWheels();
};

class Car implements Vehicle{
    public int getMaxSpeed(){return 150;}
    public int getWheels(){return 4;}
};

class Bicycle implements Vehicle{
    public int getMaxSpeed(){return 15;}
    public int getWheels(){return 2;}
};
