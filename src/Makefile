CC = gcc
EXEC = simple_web_server
OBJS = simple_web_server.o get_time.o http_session.o init_socket.o
all: $(EXEC)
$(EXEC): $(OBJS)
	$(CC) -o ../$@ $^
clean:
	rm -f ../$(EXEC) $(OBJS)
