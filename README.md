# KiCAD_Coil

## About
KiCAD_Coil is a tool that generates coils for KiCAD using native KiCAD Footprint language.
Currently KiCAD can draw arced traces however, drawing spiral coils is not possible on native KiCAD, however with small enough straigth wire segments, we can emulate a crooked arc. This allows us to generate a spiral coil segment by segment and stitch them together to create a KiCAD spiral using copper traces.

coil.c generates a new file called "coil_text" which contains all the KiCAD Footprint definitions needed for the segments and vias required for connecting layers. From this file, you can select all the lines (on MAC: cmd_A or on Win: ctrl_A), copy (on MAC: cmd_C or on Win: ctrl_C), and then paste (on MAC: cmd_V or on Win: ctrl_V) it below the '(net 0 "")' line.

## Examples

### Example 1
```
./coil.o
```
Generates a coil with:
* Turns: 10
* Inner Radius: 0 .00
* Spacing: 0.25
* Starting Coordinates:(0.00,0.00)
* Layers: 1
* Direction: CounterClockWise
* Rotation: 0.00 rad
* Width: 0.25
* netID: 0
* viaSize: 0.8

(Units are dependent on KiCAD units)

### Example 2
```
./coil.o -l 8 -i 5 -t 20 -w 0.5 -r 3.14 -s 1.23 -d -1
```
Generates a coil with:
* Turns: 20
* Inner Radius: 5.00
* Spacing: 1.23
* Starting Coordinates:(0,0)
* Layers: 8
* Direction: ClockWise
* Rotation: 3.14 rad
* Width: 0.5
* netID: 0
* viaSize: 0.8

(The order of input parameters does not matter as long as a flag is followed by a parameter)
(Units are dependent on KiCAD units)

## Install
Download the coil.c file and use the C compiler to compile it into a executable file.
Or download the coil.o file and try to run in like in the Example "./coil.o"

### For Unix Systems (Mac & Linux)
After downloading the file, put into a suitable folder and then go to your terminal and run the code below.
If it gives an error, it might be due to C compiler not existing on your computer.
```
gcc coil.c -o coil.o
```
This should compile the coil.c source code to coil.o executable.
### For Windows


## Instructions

Once you downloaded the coil.c and compiled it into coil.o. You can run it by executing it on the terminal (command prompt).

```
./coil.o
```

The code should work without any parameters given to it. It has default values saved to it.

In total there are 11 different parameters:

## Parameters
The parameters are:
* ```turns```: Determines the number of turns per coil. Ranges 0 to indefinite. (Default: 10 turns)
* ```innerRadius```: Determines the inner radius of the coils. Ranges 0 to indefinite (Default: 0)
* ```spacing```: Determines the spacing between each turn in the coil. Ranges 0 to indefinite (Default 0.25)
* ```start_X```: Determines the X value for the starting coordinate. Ranges -indefinite to indefinite (Default 0)
* ```start_Y```: Determines the Y value for the starting coordinate. Ranges -indefinite to indefinite (Default 0)
* ```layers```: Determines the number of layers to generate the coil. Ranges 1 to indefinite (Default 1)
* ```directions```: Determines the direction of the initial coil and hence all. Ranges -1 to 1 (Default 1)
* ```rotation```: Determines the angle in radians to rotate the spiral coil. Ranges from -pi to pi. (Default 0)
* ```width```: Determines the width of each wire segment creating the coil. Ranges 0 to inefinite (Default 0.25)
* ```netID```: Determines the netID number for KiCAD Foorpting. Ranges 0 to inf. (Default 0)
* ```viaSize```: Determines the diameter size of vias to generate to combine coil layers. Ranges 0 to inf. (Default 0.8)

## Usage
The order of the parameters is not important as long as a flag (-x) is followed by a parameter (#) such as "./coil.o -x #"
For more information call the ```HELP``` function. It prints out the help dialog. To call use ```-h``` flag with no parameter following it.
```
./coil.o -h
```

This should print out:

```
Usage: ./coil.o flags parameters
        -f file_address (Default ./coil_text)
        -t turns        (Default 10)
        -i innerRadius  (Default 0)
        -s spacing      (Default 0.25)
        -x start_X      (Default 0)
        -y start_Y      (Default 0)
        -l layers       (Default 1)
        -d direction(±1)(Default 1)
        -r rotation     (Default 0 radians)
        -w width        (Default 0.25)
        -n netID        (Default 0)
        -v viaSize      (Default 0.8)
The order of the inputs does not matter
```

## Additionaly

Additionally, this reprository is going to house a website which can generate and visualize coils in real time with the given parameters.
