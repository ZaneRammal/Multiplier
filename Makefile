CC = nasm
CFLAGS = -f
FILE = multiplier

all: multiplier

$(FILE).o: $(FILE).asm
	$(CC) $(CFLAGS) elf64 $(FILE).asm -o $(FILE).o

$(FILE): $(FILE).o
	ld $(FILE).o -o $(FILE)

clean:
	rm $(FILE)

test:
	./$(FILE) 2 2
