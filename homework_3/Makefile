CC=	gcc
RM=	rm -fv
CFLAGS=	-Wall -Wextra
LDFLAGS=

SRV_NAME=	server
SRV_SRC=	src/server.c
SRV_OBJ=	$(SRV_SRC:.c=.o)

CLI_NAME=	client
CLI_SRC=	src/client.c
CLI_OBJ=	$(CLI_SRC:.c=.o)

all:	server client

server:	$(SRV_OBJ)
	$(CC) -o $(SRV_NAME) $(SRV_OBJ) $(CFLAGS) $(LDFLAGS)

client:	$(CLI_OBJ)
	$(CC) -o $(CLI_NAME) $(CLI_OBJ) $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(SRV_OBJ) $(CLI_OBJ)

fclean:	clean
	$(RM) $(SRV_NAME) $(CLI_NAME)

re:	clean all

.PHONY:	clean fclean
