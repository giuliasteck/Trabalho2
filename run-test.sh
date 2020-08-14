for i in {1..3}; 
	do (./src/main.o ; ./src/thread.o ; ./src/process.o) | grep tempo ; 
done;

