all: main parser.wasm

parser.wasm:main.cpp parser.h
	emcc main.cpp -o parser.js -s EXPORTED_FUNCTIONS='["_parseInput"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -sINITIAL_HEAP=0KB -sINITIAL_MEMORY=1024MB  --preload-file sql.gram
	mv parser.wasm ..
	mv parser.js ..
	mv parser.data ..
main:main.cpp parser.h
	g++ -D STAND_ALONE main.cpp -g -I. -std=c++17 -o main -O3 -Wall

clean:
	rm -fr main 