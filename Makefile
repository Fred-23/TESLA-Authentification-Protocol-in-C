CC = gcc

CFLAGS = -Wall -Wextra -O3

md5: md5.c main.c sender.c receiver.c
	@$(CC) $(CFLAGS) -o md5 md5.c main.c sender.c receiver.c

clean:
	@$(RM) md5
