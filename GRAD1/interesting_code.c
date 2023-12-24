#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <time.h>

/*
    Create a number of randomly chosen thorn fractals
    Note this has been "minimalised" to convey the algorithm
*/

// The number of random images to create
#define N 10

// Generally create the image large and subsample down for higher dynamic range
#define NX 10000
#define NY 10000

int main(int argc, char **argv)
{
    int i, j, k, im;
    double ir, ii, a, b, zi, zr;
    char fname[64];
    FILE *fptr;
    short int *density = NULL;
    double xmin, xmax, ymin, ymax;
    double escape = 10000;
    int iterations = 255;
    double ci, cr;

    // Range on the plane for the image
    xmin = -M_PI;
    xmax = M_PI;
    ymin = -M_PI;
    ymax = M_PI;

    // Random seed
    srand(time(NULL));

    // Create the image
    density = malloc(NX * NY * sizeof(short));

    for (im = 0; im < N; im++)
    {                                       // Random choice of c_x and c_y
        cr = (rand() % 10000) / 500.0 - 10; // -10 -> 10;
        ci = (rand() % 10000) / 500.0 - 10;

        fprintf(stderr, "Creating image %d, (c_x,c_y) = (%g,%g)\n", im, cr, ci);

        for (i = 0; i < NX; i++)
        {
            zr = xmin + i * (xmax - xmin) / NX;

            for (j = 0; j < NY; j++)
            {
                zi = ymin + j * (ymax - ymin) / NY;

                ir = zr;
                ii = zi;
                for (k = 0; k < iterations; k++)
                {
                    a = ir;
                    b = ii;
                    ir = a / cos(b) + cr;
                    ii = b / sin(a) + ci;
                    if (ir * ir + ii * ii > escape)
                        break;
                }

                density[j * NX + i] = k;
            }
        }

        // Write the image to a raw file
        sprintf(fname, "%03d.raw", im);
        if ((fptr = fopen(fname, "w")) == NULL)
        {
            fprintf(stderr, "Unable to create image file\n");
            exit(0);
        }
        for (j = 0; j < NY; j++)
        {
            for (i = 0; i < NX; i++)
            {
                fputc(density[j * NX + i], fptr);
            }
        }
        fclose(fptr);

    } // im

    exit(0);
}
