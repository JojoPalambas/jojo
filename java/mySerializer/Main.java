public class Main {
    public static void main(String[] args) throws Exception {
        try {
            Person person = (Person) MySerializer.fromString("{sibling:{test:[10,20,30],name:\"michel\",year:12},name:\"jean\",age:10}", Person.class);
            System.out.println(person.getAge()); //10
            System.out.println(person.getName()); //jean
            System.out.println(person.getSibling().getName()); //michel
            System.out.println(MySerializer.fromClass(person)); //{test:null,sibling:{test:[10,20,30],sibling:null,name:"michel",age:12},name:"jean",age:10}
            System.out.println(person.getSibling().getTest()); //[10, 20, 30]
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InstantiationException e) {
            e.printStackTrace();
        }
    }
}
