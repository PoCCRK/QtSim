import java.util.Arrays;

public class BubbleSort{
    public static void main(String[] args) {
        int array[] = {25, 30, 2, 85, 1};
        int temp;
        System.out.println("����ǰ����Ϊ:" + Arrays.toString(array));
        for(int i = 0; i < array.length - 1; i++)
            for(int j = 0; j < array.length - 1; j++)
                if(array[i] > array[j]) {
                    temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
        System.out.println("���������Ϊ:" + Arrays.toString(array));
    }
}
