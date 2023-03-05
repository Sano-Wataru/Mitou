PO			= ./object
PS			= ./source
PH			= ./header
PE			= ./exec
NS			= server
NC			= client
NGCO		= gb_common
NGSE		= gb_server
NGCL		= gb_client

CC					= gcc

all: server client

server: servero
	$(CC) $(PO)/$(NS).o $(PO)/$(NGCO).o $(PO)/$(NGSE).o -o $(PE)/$(NS)

servero:
	$(CC) -c $(PS)/$(NS).c -o $(PO)/$(NS).o -g3
	$(CC) -c $(PS)/$(NGCO).c -o $(PO)/$(NGCO).o -g3
	$(CC) -c $(PS)/$(NGSE).c -o $(PO)/$(NGSE).o -g3

client: cliento
	$(CC) $(PO)/$(NC).o $(PO)/$(NGCO).o $(PO)/$(NGCL).o -o $(PE)/$(NC)

cliento:
	$(CC) -c $(PS)/$(NC).c -o $(PO)/$(NC).o -g3
	$(CC) -c $(PS)/$(NGCO).c -o $(PO)/$(NGCO).o -g3
	$(CC) -c $(PS)/$(NGCL).c -o $(PO)/$(NGCL).o -g3


clean:
	${RM} object/*.o
	${RM} exec/*