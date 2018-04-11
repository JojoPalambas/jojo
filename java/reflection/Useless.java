package reflection;

public class Useless {
    private int anInt;
    public String myString;

    public Useless() {
        anInt = 10;
    }

    public Useless(String myString) {
        this.myString = myString;
    }

    public void print() {
        System.out.println(myString);
    }

    public void setAnInt(int anInt) {
        this.anInt = anInt;
    }
}
