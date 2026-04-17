all:
	gcc -o writeme writeme.c lib/babycpu.c
	gcc -o build/add example/add.c lib/babycpu.c
	gcc -o build/loop example/loop.c lib/babycpu.c

clean:
	rm -f writeme
	rm -f build/add
	rm -f build/sum
