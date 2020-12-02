all:  p-c r-w phil

run-all: p-c-run r-w-run phil-run

phil: philosophes.c mySemTAS.c mySemTATAS.c TAS.c TATAS.c 
	gcc philosophes.c -lpthread -o philosophes.o 
	gcc philosophesTAS.c mySemTAS.c TAS.c -lpthread -o philosophesTAS.o
	gcc philosophesTATAS.c mySemTATAS.c TATAS.c -lpthread -o philosophesTATAS.o

p-c: consumer-producer.c mySemTAS.c mySemTATAS.c TAS.c TATAS.c
	gcc consumer-producer.c -lpthread -o consumer-producer.o
	gcc consumer-producerTAS.c mySemTAS.c TAS.c -lpthread -o consumer-producerTAS.o
	gcc consumer-producerTATAS.c mySemTATAS.c TATAS.c -lpthread -o consumer-producerTATAS.o

r-w: reader-writer.c mySemTAS.c mySemTATAS.c TAS.c TATAS.c
	gcc reader-writer.c -lpthread -o reader-writer.o
	gcc reader-writerTAS.c mySemTAS.c TAS.c -lpthread -o reader-writerTAS.o
	gcc reader-writerTATAS.c mySemTATAS.c TATAS.c -lpthread -o reader-writerTATAS.o

lock-run: TASTest.c TATASTest.c TAS.c TATAS.c
	gcc TASTest.c TAS.c -lpthread -o TASTest.o
	gcc TATASTest.c TATAS.c -lpthread -o TATASTest.o

phil-run: phil
	./script.bash ./philosophes.o philosophes.csv
	./script.bash ./philosophesTAS.o philosophesTAS.csv
	./script.bash ./philosophesTATAS.o philosophesTATAS.csv

p-c-run: p-c
	./script.bash ./consumer-producer.o consumer-producer.csv
	./script.bash ./consumer-producerTAS.o consumer-producerTAS.csv
	./script.bash ./consumer-producerTATAS.o consumer-producerTATAS.csv

r-w-run: r-w
	./script.bash ./reader-writer.o reader-writer.csv
	./script.bash ./reader-writerTAS reader-writerTAS.csv
	./script.bash ./reader-writerTATAS reader-writerTATAS.csv

clean:
	rm -rf *.o
clean-res:
	rm -rf *.csv