/** Color pixels library using WS2812B and nRF51822 (16Hz)
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

#ifndef __COLOR_PIXELS_H__
#define __COLOR_PIXELS_H__

#include "mbed.h"

/** Color pixels class using WS2812B and nRF51822 (16Hz)
 *
 * Example:
 * @code
 * #include "mbed.h"
 * #include "color_pixels.h"
 *
 * ColorPixels pixels(1, 32);
 *
 * int main() {
 *    pixels.set_color(0, 0, 255, 0);
 *    pixels.update();
 *
 *    while(1) {
 *    }
 * }
 * @endcode
 */

typedef union {
    struct {
        uint8_t b, g, r;
    };
    uint32_t rgb;
} color_t;

class ColorPixels
{
public:
    /** Initilaze
     * \param pin    number of GPIO
     * \param num    number of pixels
     */
    ColorPixels(PinName pin, uint16_t num);

    ~ColorPixels();

    /** Set the color of a pixel (without update)
     * \param index  index of a pixel
     * \param r      red
     * \param g      green
     * \param b      blue
     */
    void set_color(uint16_t index, uint8_t r, uint8_t g, uint8_t b);

    /** Set the color of a pixel (without update)
     * \param index  index of a pixel
     * \param rgb    
     */
    void set_color(uint16_t index, uint32_t rgb);

    /** Update
     */
    void update();

    /** Turn off all pixels
     */
    void clear();

private:
    typedef union {
        struct {
            uint8_t b, r, g;
        };
        uint32_t c;
    } _color_t;

    DigitalOut output;
    uint16_t num;
    _color_t *colors;

};

#endif // __COLOR_PIXELS_H__
