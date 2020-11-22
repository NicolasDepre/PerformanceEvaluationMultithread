all: phil p-c r-w
phil : philosophes.c
	gcc philosophes.c -o phil.o -lpthread

p-c : consumer-producer.c
	gcc consumer-producer.c -o p-c.o -lpthread

r-w: reader-writer.c
	gcc reader-writer.c -o r-w.o -lpthread
clean:
	rm -rf *.o