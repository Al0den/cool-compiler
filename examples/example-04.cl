class Animal {
    speak(): String {
        "Some generic sound"
    };
};

class Dog inherits Animal {
    speak(): String {
        "Woof!"
    };
};

class Main {
    main(): IO {
        {
            let my_animal: Animal <- new Animal,
                my_dog: Animal <- new Dog in
            out_string("Animal says: ");
            out_string(my_animal.speak());
            out_string("\n");
            out_string("Dog says: ");
            out_string(my_dog.speak());
            out_string("\n")
        }
    };
};

