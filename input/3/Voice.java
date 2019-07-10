import java.util.*;

class Animal {
    void voice () {
        System.out.println("The voice of animal is:  .");
    }
};
class Cat extends Animal {
    void voice () {
        System.out.println("The voice of cat is:  Meow.");
    }
};
class Dog extends Animal {
    void voice () {
        System.out.println("The voice of dog is:  Woof.");
    }
};

public class Voice{
    public static void main(String[] args) {
        new Animal().voice();
        new Cat().voice();
        new Dog().voice();
    }
};
