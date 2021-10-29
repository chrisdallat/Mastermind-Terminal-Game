CC = gcc

CFLAGS += -Wall -Wextra  

DEPS += ./include/list.h

OBJFILES = src/main.o src/mastermind.o


TARGET = my_mastermind

all: $(TARGET)

$(TARGET): $(OBJFILES) $(DEPS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

.PHONY: clean
clean:
	rm -f src/*.o *.out $(TARGET)