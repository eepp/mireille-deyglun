#ifndef _MIREILLE_DEYGLUN_OUTPUT_MAESTRO_HPP
#define _MIREILLE_DEYGLUN_OUTPUT_MAESTRO_HPP

#include <stdlib.h>
#include <stdint.h>

#include "static-array.hpp"
#include "static-span.hpp"

struct RgbLedState
{
    bool red;
    bool green;
    bool blue;
};

template <size_t RgbLedCount>
struct OutputMaestroOrder
{
    StaticArray<RgbLedState, RgbLedCount> rgbLedStates;
    bool piezoIsEnabled;
    uint16_t piezoFreq;
};

template <typename OutputDriverT, size_t RgbLedCount, size_t CmdBufSize = 64>
class OutputMaestro
{
public:
    using Order = OutputMaestroOrder<RgbLedCount>;

private:
    enum class _State
    {
        PLAYING_ONCE,
        PLAYING_LOOP,
        STOPPED,
    };

    struct _Cmd
    {
        uint32_t tickDuration;
        Order order;
    };

public:
    explicit OutputMaestro(OutputDriverT& driver) :
        _driver {driver}
    {
    }

    OutputMaestro(const OutputMaestro&) = delete;
    OutputMaestro& operator=(const OutputMaestro&) = delete;

    void clearOrders()
    {
        this->stop();
        _cmdSize = 0;
    }

    void appendOrder(const Order& order, const uint32_t tickDuration)
    {
        this->stop();
        _cmds.data()[_cmdSize] = {tickDuration, order};
        ++_cmdSize;
    }

    void play(const bool loop = false)
    {
        if (_cmdSize == 0) {
            // nothing to play
            _state = _State::STOPPED;
            return;
        }

        // set new state
        if (loop) {
            _state = _State::PLAYING_LOOP;
        } else {
            _state = _State::PLAYING_ONCE;
        }

        // execute first command immediately
        _nextCmdIndex = 0;
        this->_execNextCmd();
    }

    void stop()
    {
        _state = _State::STOPPED;
    }

    void tick()
    {
        if (_state == _State::STOPPED) {
            return;
        }

        --_remTicks;

        if (_remTicks == 0) {
            // no more ticks
            this->_execNextCmd();
        }
    }

private:
    void _execNextCmd()
    {
        // execute next command
        this->_execCmd(_cmds[_nextCmdIndex]);

        // set next command's index or stop playing
        ++_nextCmdIndex;

        if (_nextCmdIndex == _cmdSize) {
            if (_state == _State::PLAYING_ONCE) {
                _state = _State::STOPPED;
                return;
            } else {
                _nextCmdIndex = 0;
            }
        }

        // set new remaining tick count
        _remTicks = _cmds[_nextCmdIndex].tickDuration;
    }

    void _execCmd(const _Cmd& cmd) const
    {
        _driver.setRgbLedStates(StaticSpan<const RgbLedState, RgbLedCount> {cmd.order.rgbLedStates.data()});
        _driver.setPiezoIsEnabled(cmd.order.piezoIsEnabled);

        if (cmd.order.piezoIsEnabled) {
            _driver.setPiezoFreq(cmd.order.piezoFreq);
        }
    }

private:
    OutputDriverT& _driver;
    StaticArray<_Cmd, CmdBufSize> _cmds;
    size_t _cmdSize = 0;
    _State _state = _State::STOPPED;
    uint32_t _remTicks;
    size_t _nextCmdIndex;
};

#endif // _MIREILLE_DEYGLUN_OUTPUT_MAESTRO_HPP
