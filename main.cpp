#include "mbed.h"
#include <cmath>
#include <cstdint>
#include <cstdio>

AnalogOut aout(PA_4);
Thread amp;
int pocket;

void Amp() {
    int value[200];

    for (int i = 0; i < 50; i++) {
        //rads = (pi * i) / 180.0f;
        value[i] = (int)(3 * 65535 / 3.3 * i / 50);
    }
    for (int i = 50; i < 100; i++) {
        value[i] = (int)(3 * (65535 - (65535 * 0.4 *(i - 50) / 50)) / 3.3);
    }
    for (int i = 100; i < 150; i++) {
        value[i] = (int)(3 * (65535 * 0.6) / 3.3);
    }
    for (int i = 150; i < 200; i++) {
        value[i] = (int)(3 *(65535 * 0.6 - (65535 * 0.6 * (i - 150) / 50)) / 3.3);   
    }
    while (1) {
        for (int i = 0; i < 200; i++) {
            pocket = value[i];
            wait_us(1000);
        }
    }    
}

const double pi = 3.141592653589793238462;
const double amplitude = 0.5f;

int main()
{
    amp.start(Amp);
    const float C4=261.6;
    const float B3=246.9;
    const float A3=220.0;
    const float G3=196.0;
    const float F3=174.6;
    const float E3=164.8;
    const float D3=146.8;
    const float C3=130.8;
    float period[8] = {0};
    period[0] = 1000000 / C4 / 128;
    period[1] = 1000000 / B3 / 128;
    period[2] = 1000000 / A3 / 128;
    period[3] = 1000000 / G3 / 128;
    period[4] = 1000000 / F3 / 128;
    period[5] = 1000000 / E3 / 128;
    period[6] = 1000000 / D3 / 128;
    period[7] = 1000000 / C3 / 128;
    int wave[128];
    double rads = 0.0;
    uint16_t sample = 0;
    for (int i = 0; i < 128; i++) {
        rads = (pi * i) / 64.0f;
        wave[i] = (uint16_t)(65535 * (cos(rads + pi))); 
    }
    while (1) {
        for (int i = 0; i < 128; i++) {
            aout.write_u16(pocket * wave[i] / 65535);
            wait_us(period[0]);
        }
    }



}

