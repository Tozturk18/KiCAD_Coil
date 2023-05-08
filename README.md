# KiCAD_Coil

# About
KiCAD_Coil is a tool that generates coils for KiCAD using native KiCAD Footprint language.
Unfortunately, currently original KiCAD cannot draw arced traces, however with small enough straigth wire segments, we can emulate a crooked arc. 

coil.c generates multiple lines of output on the terminal winow (command prompt) that corresponds to the definition of each infinidesimal line segment using KiCAD's Footprint file language.

# Example
```
./coil.o 1
```
Generates a coil with:
* 1 Turns
* 0 Inner Radius
* 0.25 Spacing
* (0,0) Starting Coordinates
* 1 Layer
* CounterClockWise Direction
* 0.25 Width

(Units are dependent on KiCAD units)

# Install
Download the coil.c file and use the C compiler to compile it into a executable file.

## For Unix Systems (Mac & Linux)
After downloading the file, put into a suitable folder and then go to your terminal and run the code below.
If it gives an error, it might be due to C compiler not existing on your computer.
```
gcc coil.c -o coil.o
```

## For Windows


# Instructions

Once you downloaded the coil.c and compiled it into coil.o. You can run it by executing it on the terminal (command prompt).

```
./coil.o
```

The code should work without any parameters given to it. It has default values saved to it.

In total there are 8 different parameters:

## Parameters
The parameters are:
* ```turns```: Determines the number of turns per coil. Ranges 0 to indefinite. (Default: 10 turns)
* ```innerRadius```: Determines the inner radius of the coils. Ranges 0 to indefinite (Default: 0)
* ```spacing```: Determines the spacing between each turn in the coil. Ranges 0 to indefinite (Default 0.25)
* ```start_X```: Determines the X value for the starting coordinate. Ranges -indefinite to indefinite (Default 0)
* ```start_Y```: Determines the Y value for the starting coordinate. Ranges -indefinite to indefinite (Default 0)
* ```layers```: Determines the number of layers to generate the coil. Ranges 1 to indefinite (Default 1)
* ```directions```: Determines the direction of the initial coil and hence all. Ranges -1 to 1 (Default 1)
* ```width```: Determines the width of each wire segment creating the coil. Ranges 0 to inefinite (Default 0.25)

## Usage
The order of parameters are important and has to be given in order. You can enter as many as you want (0 to 8).

```
./coil.o turns innerRadius spacing start_X start_Y layers direction(1 or -1) width
```

# Additionaly
coil.c is going to be updated to include auto generated vias, support multiple layers, and directly write into KiCAD Footprint file.

Additionally, this reprository is going to house a website which can generate and visualize coils in real time with the given parameters.
