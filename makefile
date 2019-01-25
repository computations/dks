all:
	@cmake -DCMAKE_BUILD_TYPE=Debug -Bbuild -H. && cd build && make

clean:
	rm -rf build
