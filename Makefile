all:
	gcc -std=c99 ./src/wc.c -o wc -lpthread -O2

debug:
	gcc -std=c99 ./src/wc.c -o wc -lpthread -g

test:
	./wc $(INPUT) > $(INPUT).output
	cmp $(INPUT).output $(SAMPLE)
