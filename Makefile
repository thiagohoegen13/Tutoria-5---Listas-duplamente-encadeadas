CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99
TARGET  = lista_ex
SRCS    = main.c nodo.c lista.c lista_aluno.c
OBJS    = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build com AddressSanitizer para verificar memory leaks
asan:
	$(CC) $(CFLAGS) -fsanitize=address -fsanitize=leak \
	      -o $(TARGET)_asan $(SRCS)

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET)_asan

.PHONY: all asan clean
