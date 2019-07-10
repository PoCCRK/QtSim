public class Test{
    public static void main(String[] args){
        int [] a = {1, 2, 3};
        for ( int i : a )
            System.out.println(i);
        try{
            System.out.println(a[3]);
            System.out.println("try end.");
        }
        catch (ArrayIndexOutOfBoundsException ex) {
            System.out.println("try error.");
            System.out.println(ex.toString());
            System.out.println(ex.getMessage());
        }

        System.out.println("end.");
    }
};
