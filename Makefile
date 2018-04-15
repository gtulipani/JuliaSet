CC = gcc
C_INITIAL_FLAGS = -Wall -std=c99
C_ASSEMBLY_FLAGS = -O0 -mrnames -S
C_FINAL_FLAGS = -lm
TARGET = juliaSet
DESTINY_DIR = target
SOURCE_DIR = src
LIB_DIR = lib
MKDIR_P = mkdir -p

default: 	$(TARGET)

$(TARGET):	Argument ComplexNumber CustomString IntVector main Resolution SimpleList TypeConverter
		$(CC) $(C_INITIAL_FLAGS) -O3 -o $(TARGET) $(DESTINY_DIR)/*.o $(C_FINAL_FLAGS)

assembly:		
		$(CC) $(C_INITIAL_FLAGS) $(C_ASSEMBLY_FLAGS) $(SOURCE_DIR)/*.c

Argument:	$(SOURCE_DIR)/Argument.c $(LIB_DIR)/Argument.h
		$(MKDIR_P) $(DESTINY_DIR)
		$(CC) $(C_INITIAL_FLAGS) -O3 -c $(SOURCE_DIR)/Argument.c -o $(DESTINY_DIR)/Argument.o

ComplexNumber:	$(SOURCE_DIR)/ComplexNumber.c $(LIB_DIR)/ComplexNumber.h
		$(CC) $(C_INITIAL_FLAGS) -O3 -c $(SOURCE_DIR)/ComplexNumber.c -o $(DESTINY_DIR)/ComplexNumber.o

CustomString:	$(SOURCE_DIR)/CustomString.c $(LIB_DIR)/CustomString.h
		$(CC) $(C_INITIAL_FLAGS) -O3 -c $(SOURCE_DIR)/CustomString.c -o $(DESTINY_DIR)/CustomString.o

IntVector:	$(SOURCE_DIR)/IntVector.c $(LIB_DIR)/IntVector.h
		$(CC) $(C_INITIAL_FLAGS) -O3 -c $(SOURCE_DIR)/IntVector.c -o $(DESTINY_DIR)/IntVector.o

main:		$(SOURCE_DIR)/main.c
		$(CC) $(C_INITIAL_FLAGS) -O3 -c $(SOURCE_DIR)/main.c -o $(DESTINY_DIR)/main.o

Resolution:	$(SOURCE_DIR)/Resolution.c $(LIB_DIR)/Resolution.h
		$(CC) $(C_INITIAL_FLAGS) -O3 -c $(SOURCE_DIR)/Resolution.c -o $(DESTINY_DIR)/Resolution.o

SimpleList:	$(SOURCE_DIR)/SimpleList.c $(LIB_DIR)/SimpleList.h
		$(CC) $(C_INITIAL_FLAGS) -O3 -c $(SOURCE_DIR)/SimpleList.c -o $(DESTINY_DIR)/SimpleList.o

TypeConverter:	$(SOURCE_DIR)/TypeConverter.c $(LIB_DIR)/TypeConverter.h
		$(CC) $(C_INITIAL_FLAGS) -O3 -c $(SOURCE_DIR)/TypeConverter.c -o $(DESTINY_DIR)/TypeConverter.o

clean:
		rm -rf $(TARGET) $(DESTINY_DIR)/*.o *.s $(DESTINY_DIR)
