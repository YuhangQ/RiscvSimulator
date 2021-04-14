simulator: debug/main.o debug/test.o debug/logger.o debug/register.o debug/filehandler.o
	g++ $^ -o $@

debug/main.o: src/main.cpp include/main.h
	g++ -c $< -o $@

debug/test.o: src/test.cpp include/test.h
	g++ -c $< -o $@

debug/logger.o: src/logger.cpp include/logger.h
	g++ -c $< -o $@

debug/register.o: src/modules/register.cpp include/modules/register.h
	g++ -c $< -o $@

debug/filehandler.o: src/utils/filehandler.cpp src/utils/filehandler.h
	g++ -c $< -o $@