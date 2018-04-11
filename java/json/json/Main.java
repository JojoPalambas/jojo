// File: Main.java
package json;

import java.util.Random;


public class Main {
    public static void main(String[] args) {
        GsonExo.AddToJson("nico", "las");
        GsonExo.AddToJson("al", "vin");
        GsonExo.AddToJson("ro", "ger");

        // use the following for to test random number
        /*for (int i = 0; i < 42; ++i) {
            GsonExo.AddToJson(Long.toString(new Random().nextLong()), Long.toString(new Random().nextLong()));
        }*/
    }
}
