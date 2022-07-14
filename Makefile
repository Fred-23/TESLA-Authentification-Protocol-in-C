CC = gcc

CFLAGS = -Wall -Wextra -O3

md5: md5.c main.c sender.c
	@$(CC) $(CFLAGS) -o md5 md5.c main.c sender.c

clean:
	@$(RM) md5
