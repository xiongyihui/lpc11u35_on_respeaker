/**
 * USB to UART Bridge
 */

#include "mbed.h"
#include "USBSerial.h"
#include "BufferedSerial.h"
#include "pixels_circle.h"

#define LOG(args...)        //pc.printf(args)

#define PIXELS_N    12
#define TOUCH_N     4
#define TOUCH_THRESHOLD     1

USBSerial pc(0x1f00, 0x2012, 0x0001, false);
BufferedSerial uart(P0_19, P0_18, 512);
PixelsCircle pixels(P1_19, PIXELS_N);

DigitalInOut *p_touch_io[TOUCH_N];
PinName touch_pin[TOUCH_N] = {P0_22, P0_13, P0_14, P0_15};
uint8_t touch_data[TOUCH_N] = {0,};
uint32_t touch_status = 0;



void tick()
{
    pixels.loop();
}


void detect(void)
{
    uint32_t last_status = touch_status;

    for (int i = 0; i < TOUCH_N; i++) {
        uint8_t count = 0;
        DigitalInOut *ptr = p_touch_io[i];

        ptr->input();
        touch_data[i] <<= 1;
        while (!ptr->read()) {
            count++;
            if (count >= TOUCH_THRESHOLD) {
                touch_data[i] |= 0x01;
                break;
            }
        }
        ptr->output();
        ptr->write(0);

        if (0x01 == touch_data[i]) {            // a measurement is about the threshold, get a touch
            if (!(touch_status & (1 << i))) {
                touch_status |= 1 << i;
                LOG("No %d key is touched\n", i);


                if (i == 0) {
                    pixels.off();
                } else if (i == 1) {
                    pixels.on();
                } else if (i == 2) {
                    pixels.spin(0);
                } else {
                    pixels.spin(1);
                }
            }
        } else if (0x80 == touch_data[i]) {     // last 7 measurement is under the threshold, touch is released
            if (touch_status & (1 << i)) {
                touch_status &= ~(1 << i);
                LOG("No %d key is released\r\n", i);
            }
        }
    }

    if (last_status != touch_status) {

    }
}

void handle_settings_change(int baud, int bits, int parity, int stop);

int main()
{
    Ticker pixel_ticker;
    Ticker touch_ticker;

    pixel_ticker.attach_us(tick, 1000);

    pixels.spin(0);

    for (int i = 0; i < TOUCH_N; i++) {
        p_touch_io[i] = new DigitalInOut(touch_pin[i]);
        p_touch_io[i]->mode(PullUp);
        p_touch_io[i]->output();
        p_touch_io[i]->write(0);
    }

    touch_ticker.attach_us(detect, 10000);

    pc.attach(handle_settings_change);

    while (1) {
        if (uart.readable()) {
            char r = uart.getc();
            pc.putc(r);
        }

        if (pc.readable()) {
            char r = pc.getc();
            uart.putc(r);
        }
    }
}

void handle_settings_change(int baud, int bits, int parity, int stop)
{
    const Serial::Parity parityTable[] = {Serial::None, Serial::Odd, Serial::Even, Serial::Forced0, Serial::Forced1};

    if (stop != 2) {
        stop = 1;   // stop bit(s) = 1 or 1.5
    }
    uart.baud(baud);
    uart.format(bits, parityTable[parity], stop);
}
