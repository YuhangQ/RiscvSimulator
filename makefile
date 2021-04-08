simulator: debug/main.o debug/test.o
	cc $< -o $@

debug/main.o: src/main.cpp include/main.h
	cc -c $< -o $@

debug/test.o: src/test.cpp include/test.h
	cc -c $< -o $@