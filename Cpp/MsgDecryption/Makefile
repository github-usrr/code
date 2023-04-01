TARGET = MsgDecryption

CC = g++
CFLAGS = -Wall -std=c++17

PREF_SRC = ./src/
PREF_OBJ = ./obj/

SRC = $(wildcard $(PREF_SRC)*.cpp)
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp
	$(CC) -c $< -o $@

.PHONY: clean

clean:
	rm $(TARGET) $(PREF_OBJ)*.o
