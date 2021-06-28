CC=g++
CFLAGS=-std=c++17
COMPILE_TARGET=NUCLEO_H743ZI2
FLASH_TARGET=NODE_F401RE1
EXECUTABLE_NAME=CPS_Interface_TOP

INCLUDRT_ARM_MBED=-I ../../cadmium/include
INCLUDEDESTIMES=-I ../../cadmium/DESTimes/include
INCLUDEBOOST=-I ../../boost_1_76_0


embedded:
	mbed compile --target $(COMPILE_TARGET) --toolchain GCC_ARM --profile ../cadmium.json

flash:
	sudo cp ../BUILD/$(COMPILE_TARGET)/GCC_ARM-CADMIUM/*.bin /media/$(USER)/$(FLASH_TARGET)/
	$(info *** FLASH MAKE TAKE ~10 Seconds! DO NOT RESET WHILE COM PORT LED IS FLASHING! ***)


all: main SensorMessage rearrange SorterMessage FusionMessage Sensor_Fusion AssignerMessage storeData
	$(CC) -g -o $(EXECUTABLE_NAME) main.o SensorMessage.o Rearrange.o SorterMessage.o FusedMessage.o SensorFusion.o AssignerMessage.o storeData.o

SensorMessage: ../data_structures/Sensor_Message.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDERT_ARM_MBED) $(INCLUDEDESTIMES) $(INCLUDEBOOST) ../data_structures/Sensor_Message.cpp -o SensorMessage.o

SorterMessage: ../data_structures/Sorter_Message.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDERT_ARM_MBED) $(INCLUDEDESTIMES) $(INCLUDEBOOST) ../data_structures/Sorter_Message.cpp -o SorterMessage.o

FusionMessage: ../data_structures/Fused_Message.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDERT_ARM_MBED) $(INCLUDEDESTIMES) $(INCLUDEBOOST) ../data_structures/Fused_Message.cpp -o FusedMessage.o

Sensor_Fusion: ../drivers/Sensor_Fusion_Algorithms/Algorithm.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDERT_ARM_MBED) $(INCLUDEDESTIMES) $(INCLUDEBOOST) ../drivers/Sensor_Fusion_Algorithms/Algorithm.cpp -o SensorFusion.o

AssignerMessage: ../data_structures/Assigner_Message.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDERT_ARM_MBED) $(INCLUDEDESTIMES) $(INCLUDEBOOST) ../data_structures/Assigner_Message.cpp -o AssignerMessage.o

rearrange: ../drivers/Rearrange.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDERT_ARM_MBED) $(INCLUDEDESTIMES) $(INCLUDEBOOST) ../drivers/Rearrange.cpp -o Rearrange.o

storeData: ../drivers/DataToStorage.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDERT_ARM_MBED) $(INCLUDEDESTIMES) $(INCLUDEBOOST) ../drivers/DataToStorage.cpp -o storeData.o

main: main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDRT_ARM_MBED) $(INCLUDEDESTIMES) $(INCLUDEBOOST) main.cpp -o main.o

# fusion: ../drivers/Algorithm.cpp
# 	$(CC) -g -c $(CFLAGS) $(INCLUDRT_ARM_MBED) $(INCLUDEDESTIMES) $(INCLUDEBOOST) ../drivers/Algorithm.cpp -o Algorithm.o

clean:
	rm -f $(EXECUTABLE_NAME) *.o *~

eclean:
	rm -rf ../BUILD
