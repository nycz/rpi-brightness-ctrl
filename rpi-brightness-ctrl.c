/* MIT License
 *
 * Copyright (c) 2017 nycz
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include  "config.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

char *program_name;

void change_brightness(int step) {
    int brightness;
    int result;
    FILE *fp = fopen(brightness_path, "r+");
    if (fp == NULL) {
        fprintf(stderr, "error: cannot open brightness file\n");
        exit(1);
    }
    result = fscanf(fp, "%d", &brightness);
    if (result <= 0) {
        fprintf(stderr, "error: cannot read brightness\n");
        fclose(fp);
        exit(1);
    }
    brightness = MIN(MAX(brightness + step, MIN_BRIGHTNESS), MAX_BRIGHTNESS);
    rewind(fp);
    fprintf(fp, "%d", brightness);
    fflush(fp);
    fclose(fp);
}

void usage() {
    printf("usage: %s [-h] [+-] [+STEP | -STEP]\n\n  -h   show this message\n STEP  how much to change brightness",
            program_name);
}

int main(int argc, char *argv[]) {
    int i = 1;
    int step;
    char *arg;
    program_name = argv[0];
    while (i < argc) {
        arg = argv[i];
        if (strcmp(arg, "-h") == 0) {
            usage();
            return 0;
        } else if (strcmp(arg, "+") == 0) {
            change_brightness(DEFAULT_STEP);
        } else if (strcmp(arg, "-") == 0) {
            change_brightness(-DEFAULT_STEP);
        } else if ((arg[0] == '+' || arg[0] == '-')) {
            step = atoi(arg + 1);
            if (step == 0) {
                fprintf(stderr, "error: invalid step size or argument\n");
            } else {
                if (arg[0] == '-') {
                    step = -step;
                }
                change_brightness(step);
            }
        } else {
            fprintf(stderr, "error: invalid argument\n");
            return 1;
        }
        i++;
    }
    return 0;
}
