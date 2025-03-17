class Main {
    main(): IO {
        {
            let i: Int <- 0 in
            while i < 5 loop {
                out_int(i);
                out_string("\n");
                i <- i + 1;
            }
        }
    };
};

