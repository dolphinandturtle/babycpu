all:
	gcc -o writeme writeme.c lib/babycpu.c
	gcc -o build/load_add_store example/load_add_store.c lib/babycpu.c
	gcc -o build/sum example/sum.c lib/babycpu.c

clean:
	rm -f writeme
	rm -f build/load_add_store
	rm -f build/sum
