LINEAR_FLAGS=-lfreeimage -Wextra
THREAD_FLAGS=-lfreeimage -lpthread -Wextra
PROCESS_FLAGS=-lfreeimage -Wextra

all: src/main.o src/thread.o src/process.o

src/main.o: src/main.c
	gcc -o src/main.o src/main.c src/imageprocessing.c -I./ $(LINEAR_FLAGS)
src/thread.o: src/thread.c
	gcc -o src/thread.o src/thread.c src/imageprocessing.c -I./ $(THREAD_FLAGS)
src/process.o: src/process.c
	gcc -o src/process.o  src/process.c src/imageprocessing.c -I./ $(PROCESS_FLAGS)


clean:
	rm src/*.o

test:all
	sh run-test.sh 
