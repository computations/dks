all:
	@cmake -Bbuild -H. && cd build && make

clean:
	rm -rf build
