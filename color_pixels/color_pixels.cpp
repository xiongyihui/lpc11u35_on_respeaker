/** Color pixels library using WS2812B and LPC11Uxx (48MHz)
 *  It's for
 *    + http://www.seeedstudio.com/depot/Digital-RGB-LED-FlexiStrip-60-LED-1-Meter-p-1666.html
 *    + http://www.seeedstudio.com/depot/WS2812B-Digital-RGB-LED-Waterproof-FlexiStrip-144-LEDmeter-2-meter-p-1869.html
 *    + http://www.seeedstudio.com/depot/WS2812B-RGB-LED-with-Integrated-Driver-Chip-10-PCs-pack-p-1675.html
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Seeed Technology Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "color_pixels.h"
#include "mbed.h"

// Generate a high level pulse (0.81us) of WS2812B's 0 code (0.8us +- 0.15us), low 0.45us
static void __INLINE generate_one(DigitalOut &out)
{
    out = 1;
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    out = 0;
}

// Generate a high level pulse (0.31us) of WS2812B's 0 code (0.4us +- 0.15us), low 0.85us
static void __INLINE generate_zero(DigitalOut &out)
{
    out = 1;
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    out = 0;
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
}

ColorPixels::ColorPixels(PinName pin, uint16_t num): output(pin)
{
    this->num = num;

    colors = new _color_t[num];
    for (int i = 0; i < num; i++) {
        colors[i].c = 0;
    }
}

ColorPixels::~ColorPixels()
{
    delete colors;
}


void ColorPixels::set_color(uint16_t index, uint8_t r, uint8_t g, uint8_t b)
{
    if (index < num) {
        colors[index].r = r;
        colors[index].g = g;
        colors[index].b = b;
    }
}

void ColorPixels::set_color(uint16_t index, uint32_t rgb)
{
    color_t c;

    c.rgb = rgb;
    if (index < num) {
        colors[index].r = c.r;
        colors[index].g = c.g;
        colors[index].b = c.b;
    }
}

void ColorPixels::update()
{
    output = 0;
    wait_us(50);
    __disable_irq();
    for (int i = 0; i < num; i++) {
        uint32_t color = colors[i].c;
        for (int bit = 0; bit < 24; bit++) {
            if (color & (1 << 23)) {
                generate_one(output);
            } else {
                generate_zero(output);
            }
            color <<= 1;
        }
    }
    __enable_irq();
}

void ColorPixels::clear()
{
    for (int i = 0; i < num; i++) {
        colors[i].c = 0;
    }

    update();
}
