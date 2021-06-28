
# CPS Interface in DEVS ###


### REAL TIME CADMIUM INSTALL ###

Clone this repo into an empty folder, ensure you download the MBed submodules:

> git submodule update --init --recursive

Run this to install dependencies

> CyberPhysical-Interface/install.sh


### SIMULATE MODELS ###

> cd CyberPhysical-Interface/top_model/

> make clean; make all

> ./CPS_Interface_TOP

This will run the standard Cadmium simulator. Cadmium logs will be generated in CyberPhysical-Interface/top_model/CPS_Interface_Cadmium_output.txt
The pin's inputs are stored in CyberPhysical-Interface/top_model/inputs.

The inputs to the model can be one of these following values (for now, can be added more)
 >               1) Temperature Sensor Values
 >               2) CO2 Sensor Values
 >               3) Light Sensor Values
 >               4) PIR Sensor Values
 >               5) Humidity Sensor Values

The inputs should be created in the CyberPhysical-Interface/top_model/inputs folder in given format format for each sensor.
               
> (Sensor Name)_Sens[the number of sensor] [sensor value]

> Example, Temp_Sens1 25

If more sensors, create new input files and use the same format.

The inputs will go through multiple layers (including a sensor fusion) of the interface and will be stored in the SD Card(attached) of the mbed device (during implementation) or will be stored in a csv file (during simulation) in format 
                
> TimeStamp, Sensor Name, Value, Units
                
> Example,    2021-06-28T11:43:19Z,Humidity,90.7851,RF

The interface waits for the communicator to communicate with the control system. The communicator inputs can be simulated using the CS_IN files in the inputs folder. First a status check is sent as an input to the interface communicator from the control system. Once the communicator reverts back with alive status, the input with the type and time of the sensor data required for the control system is provided. The communicator of the interface checks the csv(during simulation)/SD Card (during implementation) for the required data and once it is found, the data is sent to the control system. If there is an error finding the data, an error code is sent.

Once the control system decides an action, it sends the actuation command which is processed by the interface and given to the actuator.

All the logs can be seen in the CPS_Interface_Cadmium_output.txt for the given inputs.