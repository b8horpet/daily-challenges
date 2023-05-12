all:
fern:
	$(CXX) fern.cpp -DL=1000000 -DW=1024 -DH=1024 -O3
	./a.out > out.ppm

all: fern

clean:
	rm -f a.out out.ppm
