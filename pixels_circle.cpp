
#include "pixels_circle.h"
#include "mbed.h"

uint32_t PixelsCircle::get_color(uint32_t position)
{
    color_t c;

    c.rgb = 0;
    if (position < 256) {
        c.r = color.r * position / 255;
        c.g = color.g * position / 255;
        c.b = color.b * position / 255;
    } else if (position < 512) {
        c.r =  color.r * (511 - position) / 255;
        c.g =  color.g * (511 - position) / 255;
        c.b =  color.b * (511 - position) / 255;
    }

    return c.rgb;
}

PixelsCircle::PixelsCircle(PinName pin, uint16_t num): pixels(pin, num)
{
    pixels_n = num;
    color.rgb = 0x0000FF;
    position = 0;
    space = 128;
    pixels_space = pixels_n * space;
    state = 0;
    target_position = 0;
    count_to_idle = 6000;
}

void PixelsCircle::off()
{
    state = 0;
    pixels.clear();
}

void PixelsCircle::on()
{
    state = 0;
    pixels.update();
}

void PixelsCircle::set_color(uint32_t c)
{
    color.rgb = c;
}

void PixelsCircle::change_arc(uint16_t angle)
{
    angle = angle % 360;

    if (position < pixels_space) {
        position += pixels_space;
    }
    target_position = angle * pixels_space / 360;
    state = 1;
}

void PixelsCircle::change_orientation(uint16_t angle)
{
    angle = angle % 360;

    target_position = angle * pixels_space / 360;
    state = 2;
}

void PixelsCircle::spin(int dir)
{
    if (dir) {
        space = -space;
    }
    state = 3;
}

void PixelsCircle::loop()
{
    if (state == 1) {
        if (target_position != position) {
            for (int i = 0; i < pixels_n; i++) {
                pixels.set_color(i, get_color((position + pixels_space + i * space) % pixels_space));
            }
            pixels.update();

            position++;
            if (position >= (2 * pixels_space)) {
                position = 0;
            }
        } else {

        }
    } else if (state == 2) {
        if (target_position != position) {
            for (int i = 0; i < pixels_n; i++) {
                pixels.set_color(i, get_color((position + pixels_space + i * space) % pixels_space));
            }
            pixels.update();

            position++;
            if (position >= pixels_space) {
                position = 0;
            }
        } else {

        }

    } else if (state == 3) {
        for (int i = 0; i < pixels_n; i++) {
            pixels.set_color(i, get_color((position + pixels_space + i * space) % pixels_space));
        }
        pixels.update();

        position++;
        if (position >= (2 * pixels_space)) {
            position = 0;
        }
    }
}

int PixelsCircle::get_state()
{
    return state;
}
