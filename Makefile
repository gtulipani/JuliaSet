CC = gcc
C_INITIAL_FLAGS = -Wall
C_FINAL_FLAGS = -lm
TARGET = tp0
DESTINY_DIR = target
SOURCE_DIR = src
LIB_DIR = lib

default: tp0

tp0:		Argument ComplexNumber CustomString IntVector main Resolution SimpleList TypeConverter
		$(CC) $(C_INITIAL_FLAGS) -o tp0 $(DESTINY_DIR)/Argument.o $(DESTINY_DIR)/ComplexNumber.o $(DESTINY_DIR)/CustomString.o $(DESTINY_DIR)/IntVector.o $(DESTINY_DIR)/main.o $(DESTINY_DIR)/Resolution.o $(DESTINY_DIR)/SimpleList.o $(DESTINY_DIR)/TypeConverter.o $(C_FINAL_FLAGS)

Argument:	$(SOURCE_DIR)/Argument.c $(LIB_DIR)/Argument.h
		$(CC) $(C_INITIAL_FLAGS) -c $(SOURCE_DIR)/Argument.c -o $(DESTINY_DIR)/Argument.o $(C_FINAL_FLAGS)

ComplexNumber:	$(SOURCE_DIR)/ComplexNumber.c $(LIB_DIR)/ComplexNumber.h
		$(CC) $(C_INITIAL_FLAGS) -c $(SOURCE_DIR)/ComplexNumber.c -o $(DESTINY_DIR)/ComplexNumber.o $(C_FINAL_FLAGS)

CustomString:	$(SOURCE_DIR)/CustomString.c $(LIB_DIR)/CustomString.h
		$(CC) $(C_INITIAL_FLAGS) -c $(SOURCE_DIR)/CustomString.c -o $(DESTINY_DIR)/CustomString.o $(C_FINAL_FLAGS)

IntVector:	$(SOURCE_DIR)/IntVector.c $(LIB_DIR)/IntVector.h
		$(CC) $(C_INITIAL_FLAGS) -c $(SOURCE_DIR)/IntVector.c -o $(DESTINY_DIR)/IntVector.o $(C_FINAL_FLAGS)

main:		$(SOURCE_DIR)/main.c
		$(CC) $(C_INITIAL_FLAGS) -c $(SOURCE_DIR)/main.c -o $(DESTINY_DIR)/main.o $(C_FINAL_FLAGS)

Resolution:	$(SOURCE_DIR)/Resolution.c $(LIB_DIR)/Resolution.h
		$(CC) $(C_INITIAL_FLAGS) -c $(SOURCE_DIR)/Resolution.c -o $(DESTINY_DIR)/Resolution.o $(C_FINAL_FLAGS)

SimpleList:	$(SOURCE_DIR)/SimpleList.c $(LIB_DIR)/SimpleList.h
		$(CC) $(C_INITIAL_FLAGS) -c $(SOURCE_DIR)/SimpleList.c -o $(DESTINY_DIR)/SimpleList.o $(C_FINAL_FLAGS)

TypeConverter:	$(SOURCE_DIR)/TypeConverter.c $(LIB_DIR)/TypeConverter.h
		$(CC) $(C_INITIAL_FLAGS) -c $(SOURCE_DIR)/TypeConverter.c -o $(DESTINY_DIR)/TypeConverter.o $(C_FINAL_FLAGS)

clean:
		$(RM) tp0 $(DESTINY_DIR)/*.0
