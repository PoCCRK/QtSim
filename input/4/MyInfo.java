import Jhomework.MyDate;

public class MyInfo{
    private String name;
    private MyDate birthday;
    MyInfo(){}
    MyInfo(String n,int y, int m, int d){
        name=n;
        birthday=new MyDate(y,m,d);
    }
    void getInfo(){
        System.out.println(name);
        System.out.println(birthday.getYear()+" "+birthday.getMonth()+" "+birthday.getDay());
    }
    public static void main(String[] args){
        MyInfo a = new MyInfo("test",2016,11,1);
        a.getInfo();
    }
};
