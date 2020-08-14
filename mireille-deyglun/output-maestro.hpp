#ifndef _MIREILLE_DEYGLUN_OUTPUT_MAESTRO_HPP
#define _MIREILLE_DEYGLUN_OUTPUT_MAESTRO_HPP

#include <stdint.h>

#include "output-driver.hpp"
#include "static-array.hpp"

template <uint8_t RgbLedCount, uint8_t CommandBufferSize = 64>
class OutputMaestro
{
public:
    explicit OutputMaestro(OutputDriver<RgbLedCount>& driver) :
        _driver {driver}
    {
    }

    OutputMaestro(const OutputMaestro&) = delete;
    OutputMaestro& operator=(const OutputMaestro&) = delete;

    void tick()
    {
        // TODO
        StaticArray<RgbLedState, RgbLedCount> ledStates;
        this->_driver->setRgbLedStates(StaticSpan<RgbLedState, RgbLedCount> {ledStates});
    }

private:
    struct _Command
    {
    };

private:
    OutputDriver<RgbLedCount>& _driver;
    StaticArray<_Command, CommandBufferSize> _commands;
};

#endif // _MIREILLE_DEYGLUN_OUTPUT_MAESTRO_HPP
