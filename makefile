
create: build-dir
	cd build && cmake .. && make && mv cpp-graph-json-driver ..

build-dir:
	mkdir -p build

clean:
	rm -rf cpp-graph-json-driver build

