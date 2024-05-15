# SPI_Driver_TM4C123

SPI communication modules of TM4C123 microcontroller using Tiva C Launchpad. As per the nomenclature of the TM4C123x microcontroller, the name used for SPI modules is a synchronous serial interface(SSI). But it is popularly referred to as a serial peripheral interface. That is why we will use the term SPI instead of SSI.

# SPI Modules Pins

TM4C123 microcontroller has four SPI modules. In order for SPI based devices to communicate with each other, four pins are required such as clock, serial data in, serial data out and frame signal. 

![image](https://user-images.githubusercontent.com/17765258/120492458-63c32980-c3ba-11eb-8015-8e04348f82da.PNG)

# TM4C123 SPI Configuration Registers 

These registers are used to configure SPI modules of TM4C123 in master and slave mode. This table lists configuration registers and their functions. 

![image](https://user-images.githubusercontent.com/17765258/120492349-48f0b500-c3ba-11eb-9d38-167f9346704d.PNG)


# Testing 

The driver has been tested using Tiva C as master and Arduino UNO as Slave 
Sending a series of Characters from Tiva C to Arduino UNO and showing the output on the Serial Monitor of arduino IDE

![image](https://user-images.githubusercontent.com/17765258/120497962-24e3a280-c3bf-11eb-8e4f-de6ac48a13e6.jpg)

# Video

[![Everything Is AWESOME](https://img.youtube.com/vi/PooC-7zyMpU/0.jpg)](https://www.youtube.com/watch?v=PooC-7zyMpU "Everything Is AWESOME")
