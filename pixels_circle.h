
#ifndef __PIXELS_CIRCLE_H__
#define __PIXELS_CIRCLE_H__

#include <stdint.h>
#include "mbed.h"
#include "color_pixels.h"

class PixelsCircle
{
public:
    PixelsCircle(PinName pin, uint16_t num);

    void off();

    void on();

    void set_color(uint32_t c);

    void change_arc(uint16_t angle);

    void change_orientation(uint16_t angle);

    void spin(int dir);

    void loop();

    int get_state();

    uint32_t get_color(uint32_t position);

private:
    ColorPixels pixels;
    uint16_t pixels_n;
    color_t color;
    uint16_t position;
    uint16_t space;
    uint16_t pixels_space;
    int target_position;
    int state;
    int count_to_idle;
};

#endif // __PIXELS_CIRCLE_H__
