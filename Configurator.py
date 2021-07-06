from tkinter import *
import tkinter as ttk

root = Tk()
root.title("System Interface Config")
root.minsize(500, 500)
        # Add a grid
root.columnconfigure(0, weight=1)
root.columnconfigure(1, weight=4)

Sensor_Type_Choices = { 'Temperature Sensor','Humidity Sensor','Light Sensor','CO2 Sensor','PIR Sensor'}
Sensor_Model_Choice = [["LM35", "DHT11", "DHT22", "LM135", "LM335"], ["DHT11", "DHT22"], ["TSL2561","VEML7700","SI1145"], ["MG811"], ["Digital PIR"]]

Temperature =0
Humidity=0
Light =0
CO2 =0
PIR =0
i=0
temp_flag =FALSE
hum_flag =FALSE
light_flag =FALSE
co2_flag =FALSE
pir_flag =FALSE

vars = []
def Initialize() :
    Label(root, text="Select Type of Sensors").grid(column = 1, row = 4, padx=5, pady=5)
    for i in range(int(get_number_of_clusters.get())):
        tkvar = StringVar(root)
        vars.append(tkvar)

    for i in range(int(get_number_of_clusters.get())):
        popupMenu = OptionMenu(root, vars[i], *Sensor_Type_Choices)
        popupMenu.grid(column = 1, row = i+5, padx=5, pady=5)
    
    for i in range(int(get_number_of_clusters.get())):
        vars[i].trace("w", add_number_of_sensor_option)
    
    Button(root, text = "Generate Code", command = set_value).grid(column = 2, row = i, padx=5, pady=5)
        


get_number_of_clusters = Entry (root)
Label(root, text="Enter the number of sensor clusters used").grid(column =1, row = 1, padx=5, pady=5)
get_number_of_clusters.grid(column = 1, row = 2, padx=5, pady=5)
Button(root, text = "Initialize", command = Initialize).grid(column = 1, row = 3, padx=5, pady=5)





#         # on change dropdown value
def add_number_of_sensor_option(*args):
    global i
    global temp_flag, light_flag, co2_flag, pir_flag, hum_flag
    Label(root, text="Enter the number of sensors used").grid(column = 2, row = 4, padx=5, pady=5)
    if vars[i].get() == "Temperature Sensor":
        add_number_of_sensor_option.entry1 = Entry (root) 
        add_number_of_sensor_option.entry1.grid(column = 2, row = i+5, padx=5, pady=5)
        temp_flag =TRUE
    if vars[i].get() == "Humidity Sensor":
        add_number_of_sensor_option.entry2 = Entry (root) 
        add_number_of_sensor_option.entry2.grid(column = 2, row = i+5, padx=5, pady=5)
        hum_flag = TRUE
    if vars[i].get() == "Light Sensor":
        add_number_of_sensor_option.entry3 = Entry (root) 
        add_number_of_sensor_option.entry3.grid(column = 2, row = i+5, padx=5, pady=5)
        light_flag = TRUE
    if vars[i].get() == "CO2 Sensor":
        add_number_of_sensor_option.entry4 = Entry (root) 
        add_number_of_sensor_option.entry4.grid(column = 2, row = i+5, padx=5, pady=5)
        co2_flag = TRUE
    if vars[i].get() == "PIR Sensor":
        add_number_of_sensor_option.entry5 = Entry (root) 
        add_number_of_sensor_option.entry5.grid(column = 2, row = i+5, padx=5, pady=5)
        pir_flag = TRUE
    i += 1

        
def set_value():
    if temp_flag and int(add_number_of_sensor_option.entry1.get()) != 0 and int(add_number_of_sensor_option.entry1.get()) > 0 :
            global Temperature
            Temperature = int(add_number_of_sensor_option.entry1.get())
            print(Temperature)    
    if hum_flag and int(add_number_of_sensor_option.entry2.get()) != 0 and int(add_number_of_sensor_option.entry2.get()) > 0 :
            global Humidity
            Humidity = int(add_number_of_sensor_option.entry2.get())
            print(Humidity)   
    if light_flag and int(add_number_of_sensor_option.entry3.get()) != 0 and int(add_number_of_sensor_option.entry3.get()) > 0 :
            global Light
            Light = int(add_number_of_sensor_option.entry3.get())
            print(Light)   
    if co2_flag and int(add_number_of_sensor_option.entry4.get()) != 0 and int(add_number_of_sensor_option.entry4.get()) > 0 :
            global CO2
            CO2 = int(add_number_of_sensor_option.entry4.get())
            print(CO2)   
    if pir_flag and int(add_number_of_sensor_option.entry5.get()) != 0 and int(add_number_of_sensor_option.entry5.get()) > 0 :
            global PIR
            PIR = int(add_number_of_sensor_option.entry5.get())
            print(PIR)   

    GenerateCode()
        # link function to change dropdown

def GenerateCode() :
    global Temperature
    global Humidity
    global Light
    global CO2
    global PIR
    print(Temperature)
    print(Humidity)
    print(Light)
    print(CO2)
    print(PIR)


root.mainloop()


