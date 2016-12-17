all:
	mkdir -p bin
	g++ -DALIGNED_VECTOR_TEST_MAIN_ -o bin/main src/main.cc

clean:
	rm bin/main
