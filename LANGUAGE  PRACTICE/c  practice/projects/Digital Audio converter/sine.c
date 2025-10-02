#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define SAMPLE_RATE 44100   // samples per second
#define DURATION    5       // seconds
#define FREQUENCY   440.0   // Hz

int main() {
    FILE *f = fopen("sine.raw", "wb");   // open file for writing
    if (!f) {
        printf("Error: could not open file.\n");
        return 1;
    }

    int samples = SAMPLE_RATE * DURATION;   // total samples

    for (int i = 0; i < samples; i++) {
        double t = (double)i / SAMPLE_RATE;       // current time
        double value = sin(2 * M_PI * FREQUENCY * t); // sine wave value (-1..+1)
        int16_t sample = (int16_t)(value * 30000);    // scale to 16-bit number
        fwrite(&sample, sizeof(sample), 1, f);        // write to file
    }

    fclose(f);   // close file
    printf("Done! File saved as sine.raw\n");
    return 0;
}
