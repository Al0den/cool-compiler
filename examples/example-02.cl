class Main {
    factorial(n: Int): Int {
        if n = 0 then 1 else n * self.factorial(n - 1) fi
    };
    main(): IO {
        {
            let result: Int <- self.factorial(5) in
            out_string("Factorial of 5 is ");
            out_int(result);
            out_string("\n")
        }
    };
};

