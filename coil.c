/* coil.c
 * Created by Ozgur Tuna Ozturk on 4 May 2023
 * Last updated on 20 June 2023
 * 
 * Description:
 * This script is created to create copper coil footprint traces for KiCAD.
 * This script allows users to enter the coil parameters while running the script on the
 * terminal window (command prompt) and generates coils by creating really small straight wire segments.
 * This script creates a new file that contains the KiCAD Footprint code, from where the user can copy and paste it into the .kicad_pcb file.
 * 
 * Parameters:
 *  -   -f:         Determines the file address to write footprint code into
 *  -   -t:         Determines the number of turns per coil
 *  -   -i:         Determines the inner radius of the coil
 *  -   -s:         Determines the spacing between each spiral in the coil
 *  -   -x:         Determines the X value of the starting coordinate of the center of the coil
 *  -   -y:         Determines the Y value of the starting coordinate of the center of the coil
 *  -   -l:         Determines the number of layers, which determines the number of coils
 *  -   -d:         Determines the direction of the initial layer, hence the rest
 *  -   -r:         Determines the angle of rotation in radians to turn the coil counterclockwise
 *  -   -w:         Determines the width of the wire segments making up the coil
 *  -   -n:         Determines the netID of the footprint file
 *  -   -v:         Determines the via size
 */


/* --- IMPORTS --- */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
/* --- End of IMPORTS --- */

/* --- MAIN --- */
int main(int argc, char *argv[]) {

    /* --- FAILSAFE --- */
    /* Make sure the program does not fail due to any unforseen user errors
     */

    // Check if correct amount of arguments entered
    if(argc % 2 == 0) {
        printf("Usage: %s flags parameters\n\r",argv[0]);
        printf("\t-f file_address\t(Default ./coil_text)\n\t-t turns\t(Default 10)\n\t-i innerRadius\t(Default 0)\n\t-s spacing\t(Default 0.25)\n\t-x start_X\t(Default 0)\n\t-y start_Y\t(Default 0)\n\t-l layers\t(Default 1)\n\t-d direction(±1)(Default 1)\n\t-r rotation\t(Default 0 radians)\n\t-w width\t(Default 0.25)\n\t-n netID\t(Default 0)\n\t-v viaSize\t(Default 0.8)\n\rThe order of the inputs does not matter\n\r");
        return 1;
    }
    /* --- End of FAILSAFE --- */

    /* --- CONSTANTS --- */
    /* Below are the initial coil parameters used to create a coil
     * even if the user only enters one or two parameters. This ensures
     * that the program will be able to create a coil even without any user
     * defined parameters. When run without any user defined parameters, it
     * will create a basic coil using the constants defined below. This will
     * allow for debuging and easy learning curve for beginner users.
     */

    // kicad_pcb file address on your computer.
    // This is footprint file to overwrite the coil into
    char* filename = "./coil_text";

    // Amount of Turns around the center
    float turns = 10;               // Default 10 rotations

    // Inner Radius of the spiral
    float innerRadius = 0.00;       // Default 0 inner radius

    // Width of the copper trace
    float width = 0.25;             // Default 0.25 width

    // Spacing between each curl
    float spacing = 0.25 + width;   // Default 0.25 spacing

    // Initial Start Coordinates
    float startX = 0.00;            // Default X: 0.00
    float startY = 0.00;            // Default Y: 0.00

    // Amount of Layers
    int layers = 1;                 // Default 1 Layer (F.Cu)

    // Direction of Rotation
    int direction = 1;              // Default 1 (CounterClockWise - CCW), -1 would mean CW

    // Rotation
    float rotate = 0.00;            // Default 0 radians, rotates counterclockwise (units of radians. Not degrees!)

    // netID of the kicad_pcb file
    int netID = 0;                  // Default (net 0 "")

    // Via Size
    float viaSize = 0.8;            // Defualt via size 0.8
    /* --- End of CONSTANTS --- */

    /* --- ARGUMENTS --- */
    /* Iterate through each of the users arguments and make sure that the user has enetered
     * the arguments using the appopriate flags. The order of the flag and parameter pair does not matter.
     * The user can enter any flag followed by the appopriate parameter in any order.
     * For example: ./coil.o -w 0.5 -i 10 -f Spiral.kicad_pcb
     * This will create a coil with default parameters except with 0.5 width (whichever unit KiCAD is using),
     * 10 inner radius, and write the results to a file called Spiral.kicad_pcb.
     */

    // Iterate through each argument and check which parameter to populate
    for (int i = 1; i < argc; i++) {
        // Check which parameter user wants to populate
        if (!strcmp(argv[i],"-f")) {
            filename = argv[i+1];                                       // Update the filename

        } else if (!strcmp(argv[i],"-t")) {
            turns = atof(argv[i+1]);                                    // Update the Turns
            if (turns < 1) { turns = 1; }                               // Failsafe for turns

        } else if (!strcmp(argv[i],"-i")) {
            innerRadius = atof(argv[i+1]);                              // Update the Inner Radius
            if (innerRadius < 0) { innerRadius = 0; }                   // Failsafe for innerRadius

        } else if (!strcmp(argv[i],"-s")) {
            spacing = atof(argv[i+1]) + width;                          // Update the Spacing
            if (spacing < 0) { spacing = width; }                       // Failsafe for spacing

        } else if (!strcmp(argv[i],"-x")) {
            startX = atof(argv[i+1]);                                   // Update the Start Coordinate X value

        } else if (!strcmp(argv[i],"-y")) {
            startY = atof(argv[i+1]);                                   // Update the Start Coordinate Y value

        } else if (!strcmp(argv[i],"-l")) {
            layers = atoi(argv[i+1]);                                   // Update the Layers
            if (layers < 1) { layers = 1; }                             // Failsafe for layers

        } else if (!strcmp(argv[i],"-d")) {
            direction = atoi(argv[i+1]);                                // Update the Direction
            if (direction != 1 && direction != -1) { direction = 1; }   // Failsafe for direction

        } else if (!strcmp(argv[i],"-r")) {
            rotate = atof(argv[i+1]);                                   // Update the Rotate

        } else if (!strcmp(argv[i],"-w")) {
            width = atof(argv[i+1]);                                    // Update the Width
            if (width < 0) { width = 0.25; }                            // Failsafe for width

        } else if (!strcmp(argv[i],"-n")) {
            netID = atoi(argv[i+1]);                                    // Update the netID
            if (netID < 0) { netID = 0; }                               // Failsafe for netID

        } else if (!strcmp(argv[i],"-h")) {
            // Print out help statement
            printf("Usage: %s flags parameters\n\r",argv[0]);
            printf("\t-f file_address\t(Default ./coil_text)\n\t-t turns\t(Default 10)\n\t-i innerRadius\t(Default 0)\n\t-s spacing\t(Default 0.25)\n\t-x start_X\t(Default 0)\n\t-y start_Y\t(Default 0)\n\t-l layers\t(Default 1)\n\t-d direction(±1)(Default 1)\n\t-r rotation\t(Default 0 radians)\n\t-w width\t(Default 0.25)\n\t-n netID\t(Default 0)\n\t-v viaSize\t(Default 0.8)\n\rThe order of the inputs does not matter\n\r");

        } else if (i % 2 == 1) {
            // Print out an error message
            printf("\n\rThe program has encountered an error in the parameters.\nThe program will continue with all the correct parameters.\nPlease make sure that all parameters.\n");
            printf("Usage: %s flags parameters\n\r",argv[0]);
            printf("\t-f file_address\t(Default ./coil_text)\n\t-t turns\t(Default 10)\n\t-i innerRadius\t(Default 0)\n\t-s spacing\t(Default 0.25)\n\t-x start_X\t(Default 0)\n\t-y start_Y\t(Default 0)\n\t-l layers\t(Default 1)\n\t-d direction(±1)(Default 1)\n\t-r rotation\t(Default 0 radians)\n\t-w width\t(Default 0.25)\n\t-n netID\t(Default 0)\n\t-v viaSize\t(Default 0.8)\n\rThe order of the inputs does not matter\n\r");
        }
    }

    /* --- End of ARGUMENTS --- */

    /* --- kicad_pcb Footprint File --- */
    /* Open or create a new file in write mode to write all the segment and via coordinates.
     * IF THE DOCUMENT ALREADY HVE DATA IN IT, IT WILL BE OVERWRITTEN.
     */

    // Create a file variable
    FILE *fp;

    // Open the file in write mode
    fp = fopen(filename,"w");

    // Check if the file opened
    if (fp == NULL) {
        printf("Error opening kicad_pcb file! kicad_pcb file address entered wrong!\n\r");   
        return(1);             
    }

    // Set the cursor to the very beginning of the file
    fseek(fp, 0, SEEK_SET);
    /* --- End of kicad_pcb Footprint File --- */

    /* --- Start & End Positions ---  */
    float start = innerRadius + viaSize*ceilf((float)(layers-1)/2);    // Start Position
    float end = turns * spacing + start;    // End Position
    /* --- End of Start & End Positions --- */

    /* --- ANGLE --- */
    /* Calculate the angle difference between the original spiral and the spaced one.
     * Adjust the angle direction according to the final y position on the spaced coil.
     * Include the user rotation into the coil angle.
     */

    // Find the start coordinates of the initial spiral
    float xInit = end;
    float yInit = 0;

    // Find the start coordinates of the spaced spiral
    float xSpaced = cos(2*M_PI*xInit/spacing)*xInit;
    float ySpaced = sin(2*M_PI*xInit/spacing)*xInit;

    // Create an angle variable to calculate the angle difference between a normal spiral and a spacing adjusted one
    float angle = acosf( ( (xInit * xSpaced) + (yInit * ySpaced) ) / ( sqrt( powf(xInit,2) + powf(yInit,2) ) * sqrt( powf(xSpaced,2) + powf(ySpaced,2) ) ) );

    // Adjust the angle orientation according to spacing adjusted y-coordinate
    ySpaced < 0 ? angle *= -1 : angle;

    // Adjust the angle according to user's rotation preference
    angle += rotate;    // In radians
    /* --- End of ANGLE --- */

    /* --- GENERATE COIL --- */
    /* Generate the coils with the given parameters per each layer.
     * Every two layers is rotated with an angle (viaAngle) associated with the 
     * number of layers. This ensures for better placement of vias and better wiring.
     */

    // Print out the User Parameters used to create the coils.
    printf("\n --- Parameters Entered: --- \n");
    printf("turns:\t\t%.3f\nInner Radius:\t%.3f\nSpacing:\t%.3f\nStart_X:\t%.3f\nStart_Y:\t%.3f\nLayers:\t\t%d\nDirection:\t%d\nRotation:\t%.3f\nWidth:\t\t%.3f\nnetID:\t\t%d\nviaSize:\t%.3f\n\r",turns,innerRadius,spacing-width,startX,startY,layers,direction,rotate,width,netID,viaSize);
    printf(" --------------------------- \n");

    // Print out the loading screen
    printf("\n --- Generating Coils --- \n");

    // Step size of the coil generator
    float step = ( (float)0.01 / (start) );

    // Calculate the angle between the via positions for different layer combinations
    float viaAngle = ( 2*M_PI ) / ( ceilf( (float)(layers-0.5)/2 ) );

    // Initialize the Position Arrays
    float xPos[layers][(int)((end+(layers-1)*viaAngle*(spacing)/(2*M_PI)-start)/step + 1)];
    float yPos[layers][(int)((end+(layers-1)*viaAngle*(spacing)/(2*M_PI)-start)/step + 1)];

    // Dummy variables for the loop
    float x, coilInitX, coilInitY, coilFixedX, coilFixedY, coilAngledX, coilAngledY;

    // Layer Adjuster
    int layerCode;

    // Iterate through each copper layer
    for (int i = 0; i < layers; i++) {

        // Print out progress tag
        printf("Progress:\e[s");

        // Adjust the layer numbering for specfic end locations required per layer
        layerCode = floor( i/2 );
        
        // Loop through each step to find the position
        for (int j = 0; j < (int)(((end+pow(-1, i)*(layerCode)*viaAngle*(spacing)/(2*M_PI))-start)/step + 1); j++) {

            x = j*step + start;   // Respective position (can think of it as x variable in a calculator while plotting this.)

            // X & Y coordinate variables for the initial coil with spacing
            coilInitX = cos(2*M_PI*x/spacing)*x;
            coilInitY = sin(2*M_PI*x/spacing)*x;

            // Adjusted X & Y coordinate variables for the angle adjusted coil with spacing
            coilFixedX = direction * (cos(angle)*coilInitX + sin(angle)*coilInitY);
            coilFixedY = pow(-1, i) * (-sin(angle)*coilInitX + cos(angle)*coilInitY);

            // Correctly orient the coil on each layer to have a nice via layout
            coilAngledX = cos((layerCode)*viaAngle)*coilFixedX + sin((layerCode)*viaAngle)*coilFixedY;
            coilAngledY = -sin((layerCode)*viaAngle)*coilFixedX + cos((layerCode)*viaAngle)*coilFixedY;

            // Store the final X & Y coordinates plus initial position coordinate.
            xPos[i][j] = coilAngledX + startX;
            yPos[i][j] = coilAngledY + startY;

            // Print out the progress
            printf(" %d %2d (%.2f%%)\e[u", i+1, j, roundf(((float) j / (((end+pow(-1, i)*(layerCode)*viaAngle*(spacing)/(2*M_PI))-start)/step + 1)) * 100));
        }
        printf("\n");
    }

    printf(" ------------------------ \n");
    printf("End of generating coils\n");
    /* --- End of GENERATE COIL --- */

    /* --- WRITE --- */
    /* Using the xPos & yPos 2D arrays write all the coordinates generated
     * into the file opened using KiCAD footprint format.
     * Adjust the locations of the vias and write the coordinates of the vias
     * into the file using the KiCAD footprint format.
     */

    // Print out the loading screen
    printf("\n --- Writing into File --- \n");

    // Iterate through each copper layer
    for (int i = 0; i < layers; i++) {
        // Print out progress tag
        printf("Progress:\e[s");

        // Adjust the layer numbering for specfic end locations required per layer
        layerCode = floor( i/2 );

        // Iterate through each position on the coil
        for (int j = 0; j < (int)(((end+pow(-1, i)*(layerCode)*viaAngle*(spacing)/(2*M_PI))-start)/step); j++) {
            // Print out the wire segments according to KiCAD Footprint File.

            // Check for copper layers
            if (i == 0) {
                fprintf(fp, "(segment (start %f %f) (end %f %f) (width %f) (layer \"F.Cu\") (net %d) (tstamp 4efbfedb-0d6a-488e-863f-1beaaa%dba%d))\n", xPos[i][j], yPos[i][j], xPos[i][j+1], yPos[i][j+1], width, netID, j, i);
            } else if (i == layers-1) {
                fprintf(fp, "(segment (start %f %f) (end %f %f) (width %f) (layer \"B.Cu\") (net %d) (tstamp 4efbfedb-0d6a-488e-863f-1beaaa%dba%d))\n", xPos[i][j], yPos[i][j], xPos[i][j+1], yPos[i][j+1], width, netID, j, i);
            } else {
                fprintf(fp, "(segment (start %f %f) (end %f %f) (width %f) (layer \"In%d.Cu\") (net %d) (tstamp 4efbfedb-0d6a-488e-863f-1beaaa%dba%d))\n", xPos[i][j], yPos[i][j], xPos[i][j+1], yPos[i][j+1], width, i, netID, j, i);
            }
            // Print out the progress
            printf(" %d %2d (%.2f%%)\e[u", i+1, j, roundf(((float) j / (((end+pow(-1, i)*(layerCode)*viaAngle*(spacing)/(2*M_PI))-start)/step)) * 100));
        }
        printf("\n");
    }

    // Create a unit vector pointing to the via locations
    float unitVector[2] = {xPos[0][0]/(sqrt(powf(xPos[0][0],2) + powf(yPos[0][0],2))), yPos[0][0]/(sqrt(powf(xPos[0][0],2) + powf(yPos[0][0],2)))};

    // Create vias at specific locations while biasing the location towards the center of the coil
    if (layers == 1) { 
        // Add a via adjusted using the unit vector
        fprintf(fp,"(via (at %f %f) (size 0.8) (drill 0.4) (layers \"F.Cu\" \"B.Cu\") (free) (net %d) (tstamp e5f06cd2-492e-41b2-8ded-13a3fa1042b%d))\n", xPos[0][0] + ( unitVector[0] * (-viaSize/2 + width/2) ), yPos[0][0] + ( unitVector[1] * (-viaSize/2 + width/2) ), netID, 0);

    } else {
        for (int i = 0; i < layers-1; i++) {
            // Add vias
            if ((i+1) % 2) {
                // Adjust the unit vector for the new via position
                unitVector[0] = xPos[i][0]/(sqrt(powf(xPos[i][0],2) + powf(yPos[i][0],2)));
                unitVector[1] = yPos[i][0]/(sqrt(powf(xPos[i][0],2) + powf(yPos[i][0],2)));

                // Adjust the via position using the new unit vector
                fprintf(fp,"(via (at %f %f) (size 0.8) (drill 0.4) (layers \"F.Cu\" \"B.Cu\") (free) (net %d) (tstamp e5f06cd2-492e-41b2-8ded-13a3fa1042b%d))\n", xPos[i][0] + ( unitVector[0] * (-viaSize*2/3 + width/2) ), yPos[i][0] + ( unitVector[1] * (-viaSize*2/3 + width/2) ), netID, 0);
            }
        }
    }

    printf(" ------------------------- \n");
    printf("End of writing.\n\n\r");
    /* --- End of WRITE --- */

    /* --- DISPLAY --- */
    /* Display any additional information.
     */

    // Give a warning message to warn the user for adjusting the number of copper layers on KiCAD
    if (layers > 2) {
        printf("\n\rYou have selected more than 2 copper layers.\n\rPlease make sure to change the number of copper layers on KiCAD and make sure the copper layer names matches.\n\n\r");
    }
    /* --- End of DISPLAY --- */

    // Close the File
    fclose(fp);

    // End script
    return 0;
}
/* --- End of MAIN --- */