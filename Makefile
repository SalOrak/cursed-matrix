CC=gcc

CFLAGS= -Wall -std=c99
LDFLAGS= -lncurses

SOURCES= main.c matrix.c utils.c
OBJECTS= $(SOURCES:.c=.o)

TARGET= main
.PHONY: all
all: $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(SOURCES:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< > $@ $(LDFLAGS)

include $(SOURCES:.c=.d)

.PHONY: run
run: $(TARGET)
	@./$<


.PHONY: clean
clean: 
	@rm -f *.d *.o $(TARGET)


