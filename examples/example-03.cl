class Main {
    fib(n: Int): Int {
        if n < 2 then n else self.fib(n - 1) + self.fib(n - 2) fi
    };
    main(): IO {
        {
            let result: Int <- self.fib(10) in
            out_string("Fibonacci of 10 is ");
            out_int(result);
            out_string("\n")
        }
    };
};

