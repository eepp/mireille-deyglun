#ifndef _MIREILLE_DEYGLUN_OUTPUT_DRIVER_HPP
#define _MIREILLE_DEYGLUN_OUTPUT_DRIVER_HPP

#include <stdint.h>

#include "output-driver.hpp"
#include "static-span.hpp"

struct RgbLedState
{
    bool red;
    bool green;
    bool blue;
};

template <uint8_t RgbLedCount>
class OutputDriver
{
protected:
    OutputDriver() = default;

public:
    OutputDriver(const OutputDriver&) = delete;
    OutputDriver& operator=(const OutputDriver&) = delete;

    virtual ~OutputDriver()
    {
    }

    void setRgbLedStates(const StaticSpan<const RgbLedState, RgbLedCount>& states)
    {
        this->_setRgbLedState(states);
    }

    void setPiezoFreq(const uint16_t freq)
    {
        this->_setPiezoFreq(freq);
    }

    void setPiezoIsEnabled(const bool isEnabled)
    {
        this->_setPiezoIsEnabled(isEnabled);
    }

protected:
    virtual void _setRgbLedStates(const StaticSpan<const RgbLedState, RgbLedCount>& states) = 0;
    virtual void _setPiezoFreq(uint16_t freq) = 0;
    virtual void _setPiezoIsEnabled(bool isEnabled) = 0;
};

#endif // _MIREILLE_DEYGLUN_OUTPUT_DRIVER_HPP
