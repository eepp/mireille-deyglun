#include <avr/pgmspace.h>

#include "output-maestro.hpp"
#include "output-driver.hpp"

struct Test
{
    uint8_t a;
    uint8_t salut;
    int16_t lol;
};

const Test myData[] PROGMEM = {
    {1, 8, -23},
    {0, 0, 4503},
};

class MyOutputDriver :
    public OutputDriver<4>
{
public:
    MyOutputDriver() = default;

private:
    void _setRgbLedStates(const StaticSpan<const RgbLedState, 4>& states) override
    {
        // TODO
    }

    void _setPiezoFreq(const uint16_t freq) override
    {
        // TODO
    }

    void _setPiezoIsEnabled(const bool isEnabled) override
    {
        // TODO
    }
};

int main()
{
    MyOutputDriver myDriver;
    OutputMaestro<4> maestro {myDriver};
}
