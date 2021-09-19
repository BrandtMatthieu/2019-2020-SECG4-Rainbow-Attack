.PHONY : build

run: build ./gen-passwd
	@./gen-passwd --threads=1

valgrind: build ./gen-passwd
	valgrind --tool=memcheck --gen-suppressions=all --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./gen-passwd

build: objects objects/hashing_thread.o objects/help.o objects/infos.o objects/main.o objects/sha256.o objects/synchronized_writer.o objects/utils.o
	@g++ -o gen-passwd objects/hashing_thread.o objects/help.o objects/infos.o objects/main.o objects/sha256.o objects/synchronized_writer.o objects/utils.o -lpthread -O3 -fdata-sections -ffunction-sections
	@chmod +x ./gen-passwd

objects/hashing_thread.o: src/hashing_thread.cpp src/hashing_thread.h
	@g++ -lpthread -Wpedantic -Wall -Wextra -O3 -std=c++14 -fdata-sections -ffunction-sections -c src/hashing_thread.cpp -o objects/hashing_thread.o

objects/help.o: src/help.cpp src/help.h
	@g++ -lpthread -Wpedantic -Wall -Wextra -O3 -std=c++14 -fdata-sections -ffunction-sections -c src/help.cpp -o objects/help.o

objects/infos.o: src/infos.cpp src/infos.h
	@g++ -lpthread -Wpedantic -Wall -Wextra -O3 -std=c++14 -fdata-sections -ffunction-sections -c src/infos.cpp -o objects/infos.o

objects/main.o: src/main.cpp
	@g++ -lpthread -Wpedantic -Wall -Wextra -O3 -std=c++14 -fdata-sections -ffunction-sections -c src/main.cpp -o objects/main.o

objects/sha256.o: src/sha256.cpp src/sha256.hpp
	@g++ -lpthread -Wpedantic -Wall -Wextra -O3 -std=c++14 -fdata-sections -ffunction-sections -c src/sha256.cpp -o objects/sha256.o

objects/synchronized_writer.o: src/synchronized_writer.cpp src/synchronized_writer.hpp
	@g++ -lpthread -Wpedantic -Wall -Wextra -O3 -std=c++14 -fdata-sections -ffunction-sections -c src/synchronized_writer.cpp -o objects/synchronized_writer.o

objects/utils.o: src/utils.cpp src/utils.h
	@g++ -lpthread -Wpedantic -Wall -Wextra -O3 -std=c++14 -fdata-sections -ffunction-sections -c src/utils.cpp -o objects/utils.o

test: build-test ./gen-passwd-test
	@./gen-passwd-test --color_output=false --report_format=HRF --show_progress=yes --log_level=all

valgrind-test: build-test ./gen-passwd-test
	valgrind --tool=memcheck --gen-suppressions=all --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./gen-passwd-test


build-test: objects objects/tests.o objects/utils.o
	@g++ -o gen-passwd-test objects/tests.o objects/utils.o -lpthread -O3 -fdata-sections -ffunction-sections
	@chmod +x ./gen-passwd-test

objects/tests.o:
	@g++ -lpthread -Wpedantic -Wall -Wextra -O3 -std=c++14 -fdata-sections -ffunction-sections -c tests/tests.cpp -o objects/tests.o

objects:
	@mkdir -p objects

clean:
	@rm -fr objects
