import java.util.ArrayList;

public class Person {
    public ArrayList<Integer> test;
    public Person sibling;
    @Required
    public String name;
    @CustName("year")
    public int age;

    public ArrayList<Integer> getTest() {
        return test;
    }

    public Person getSibling() {
        return sibling;
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }
}
