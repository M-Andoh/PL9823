#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"

#include "color.h"
#include "pl9823.pio.h"

#define IS_RGBW false
#define NUM_PIXELS 9

// GPIO defines
// Example uses GPIO 2
#define GPIO_PIN 2

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 16) |
            ((uint32_t) (g) << 8) |
            (uint32_t) (b);
}

//void pattern_snakes(uint len, uint t) {
//    for (uint i = 0; i < len; ++i) {
//        uint x = (i + (t >> 1)) % 64;
//        if (x < 10)
//            put_pixel(urgb_u32(0xff, 0, 0));
//        else if (x >= 15 && x < 25)
//            put_pixel(urgb_u32(0, 0xff, 0));
//        else if (x >= 30 && x < 40)
//            put_pixel(urgb_u32(0, 0, 0xff));
//        else
//            put_pixel(0);
//    }
//}

//void pattern_random(uint len, uint t) {
//    if (t % 8)
//        return;
//    for (int i = 0; i < len; ++i)
//        put_pixel(rand());
//}

//void pattern_sparkle(uint len, uint t) {
//    if (t % 8)
//        return;
//    for (int i = 0; i < len; ++i)
//        put_pixel(rand() % 16 ? 0 : 0xffffffff);
//}

//void pattern_greys(uint len, uint t) {
//    int max = 100; // let's not draw too much current!
//    t %= max;
//    for (int i = 0; i < len; ++i) {
//        put_pixel(t * 0x10101);
//        if (++t >= max) t = 0;
//    }
//}

//typedef void (*pattern)(uint len, uint t);
//const struct {
//    pattern pat;
//    const char *name;
//} pattern_table[] = {
//        {pattern_snakes,  "Snakes!"},
//        {pattern_random,  "Random data"},
//        {pattern_sparkle, "Sparkles"},
//        {pattern_greys,   "Greys"},
//};


int main()
{
    stdio_init_all();
    printf("PL9823 Smoke Test, using pin %d", GPIO_PIN);

    // todo get free sm
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &pl9823_program);

    // freq = 350 (ns) + 1360 (ns) = 1710 (ns) 
    pl9823_program_init(pio, sm, offset, GPIO_PIN, 1.0f/0.00000171, IS_RGBW);

    int t = 0;

    color c;

    int angle = 0;
    while (1) {
//        int pat = rand() % count_of(pattern_table);
//        int dir = (rand() >> 30) & 1 ? 1 : -1;
//        puts(pattern_table[pat].name);
//        puts(dir == 1 ? "(forward)" : "(backward)");
//        for (int i = 0; i < 1000; ++i) {
//            pattern_table[pat].pat(NUM_PIXELS, t);
//            sleep_ms(10);
//            t += dir;
//        }
        for(int i = 0;i<NUM_PIXELS; ++i){
            float v0 = 2*M_PI*((float)angle+10.0f*i)/360.0f;
            float v1 = (sinf(v0) + 1.0f) / 2.0f;
            c.setHSV((
                float)angle+5.0f*i, 
                1.0f, 
                v1
                );
            put_pixel(urgb_u32(c.getR(), c.getG(), c.getB()));
        }

        sleep_ms(10);
        angle = (angle + 5) % 360;
    }

    return 0;
}
