/* coil.c
 * Created by Ozgur Tuna Ozturk on 4 May 2023
 * Last updated on 7 May 2023
 * 
 * Description:
 * This script is created to create copper coil footprint traces for KiCAD.
 * This script allows users to enter the coil parameters while running the script on the
 * terminal window (command prompt) and generates coils by creating really small straight wire segments.
 * Currently, this script prints out the KiCAD Footprint code on to the terminal window, where the user can copy and paste it.
 * However, it is still under work so that the user can input the KiCAD Footprint while, 
 * and then this file will directly into it.
 * 
 * Parameters:
 *  -   turns:          Determines the number of turns per coil
 *  -   innerRadius:    Determines the inner radius of the coil
 *  -   spacing:        Determines the spacing between each spiral in the coil
 *  -   start_X:        Determines the X value of the starting coordinate of the coil
 *  -   start_Y:        Determines the Y value of the starting coordinate of the coil
 *  -   layers:         Determines the number of layers, which determines the number of coils
 *  -   direction:      Determines the direction of the initial layer, hence the rest
 *  -   width:          Determines the width of the wire segments making up the coil
 */


/* --- IMPORTS --- */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* --- End of IMPORTS --- */

/* --- MAIN --- */
int main(int argc, char *argv[]) {

    /* --- FAILSAFE --- */
    if(argc > 9) {
        printf("Usage: %s turns innerRadius spacing start_X start_Y layers direction(1 or -1) width(default 0.25)) \n",argv[0]);
        return 1;
    }
    /* --- End of FAILSAFE --- */

    /* --- CONSTANTS --- */
    // Amount of Turns around the center
    float turns = 10;           // Default 10 rotations

    // Inner Radius of the spiral
    float innerRadius = 0.00;   // Default 0 inner radius

    // Width of the copper trace
    float width = 0.25;         // Default 0.25 width

    // Spacing between each curl
    float spacing = 0.25 + width;       // Default 0.25 spacing

    // Initial Start Coordinates
    float startX = 0.00;        // Default X: 0.00
    float startY = 0.00;        // Default Y: 0.00

    // Amount of Layers
    int layers = 1;             // Default 1 Layer (F.Cu)

    // Direction of Rotation
    int direction = 1;          // Default 1 (CounterClockWise - CCW), -1 would mean CW
    /* --- End of CONSTANTS --- */

    /* --- ARGUMENTS --- */
    /* The Switch Statement does not have breaks because it allows the user to be able to
     * put a range of inputs. This allows for shorter and more consize code.
     * If the user enters ./spiral.o 1 That will change only the Turns, but if the user enters
     * ./spiral.o 1 1 That will change the turns and the inner radius. 
     */
    switch (argc){
        case 9:
            // Run all the Switch Statement below until the break if 9 arguments entered
            width = atof(argv[8]);      // Update the Width
        case 8:
            // Run all the Switch Statement below until the break if 8 arguments entered
            direction = atoi(argv[7]);  // Update the Direction
        case 7:
            // Run all the Switch Statement below until the break if 7 arguments entered
            layers = atoi(argv[6]);     // Update the Layers
        case 6:
            // Run all the Switch Statement below until the break if 6 arguments entered
            startX = atof(argv[4]);     // Update the Start Coordinate X value
            startY = atof(argv[5]);     // Update the Start Coordinate Y value
        case 4:
            // Run all the Switch Statement below until the break if 4 arguments entered
            spacing = atof(argv[3]);    // Update the Spacing
            if (spacing == 0) { spacing = 0.0001; }
        case 3:
            // Run all the Switch Statement below until the break if 3 arguments entered
            innerRadius = atof(argv[2]);// Update the Inner Radius
        case 2:
            // Run all the Switch Statement below until the break if 2 arguments entered
            turns = atof(argv[1]);      // Update the Turns
            break;
        case 5:
            // If 5 arguments entered then, the start position is entered wrongly. Send an error message
            printf("Usage: %s turns innerRadius spacing start_X start_Y layers direction(1 or -1) width(default 0.25)) \n",argv[0]);
            return 1;
    }
    /* --- End of ARGUMENTS --- */

    /* --- Start & End Positions ---  */
    float start = innerRadius;              // Start Position
    float end = turns * spacing + start;    // End Position
    /* --- End of Start & End Positions --- */

    /* --- ANGLE --- */
    // Calculate the angle difference between the original spiral and the spaced one

    // Find the start coordinates of the initial spiral
    float xInit = cos(2*M_PI*start)*start;
    float yInit = sin(2*M_PI*start)*start;

    // Find the start coordinates of the spaced spiral
    float xSpaced = cos(2*M_PI*start/spacing)*start;
    float ySpaced = sin(2*M_PI*start/spacing)*start;

    // Create an angle variable to hold the angle
    float angle = 0.00;

    // Fail safe to not get NaN angle by diving by 0
    if (xInit-xSpaced + yInit-ySpaced != 0) {
        // Calculate the Angle between two vectors (Coordinates)
        angle = acosf( ( (xInit * xSpaced) + (yInit * ySpaced) ) / ( sqrt( powf(xInit,2) + powf(yInit,2) ) * sqrt( powf(xSpaced,2) + powf(ySpaced,2) ) ) );
    }
    /* --- End of ANGLE --- */

    /* --- GENERATE COIL --- */
    // Step size of the coil generator
    float step = 0.01;

    // Initialize the Position Arrays
    float xPos[(int)((end-start)/step + 1)];
    float yPos[(int)((end-start)/step + 1)];

    // Loop through each step to find the position
    for (int i = 0; i < (int)((end-start)/step + 1); i++) {

        float x = i*step + start;   // Respective position

        // Use the spiral formula 
        xPos[i] = direction * (cos(angle)*cos(2*M_PI*x/spacing)*x + sin(angle)*sin(2*M_PI*x/spacing)*x) + startX;
        yPos[i] = direction * (-sin(angle)*cos(2*M_PI*x/spacing)*x + cos(angle)*sin(2*M_PI*x/spacing)*x) + startY;
    }
    /* --- End of GENERATE COIL --- */

    /* --- DISPLAY --- */
    // Itterate through each position on the coil
    for (int i = 0; i < (int)((end-start)/step); i++) {
        // Print out the wire segments according to KiCAD Footprint File.
        printf("(segment (start %f %f) (end %f %f) (width %f) (layer \"F.Cu\") (net 1) (tstamp 4efbfedb-0d6a-488e-863f-1beaaa36ba%d))\n\r", xPos[i], yPos[i], xPos[i+1], yPos[i+1], width, i);
    }
    /* --- End of DISPLAY --- */
    
    // End script
    return 0;
}
/* --- End of MAIN --- */