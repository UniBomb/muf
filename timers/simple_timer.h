#ifndef SIMPLE_TIMER_H_
#define SIMPLE_TIMER_H_
//---------------------------------------------------------------------------
#include <avr/io.h>
#include <util/atomic.h>
//---------------------------------------------------------------------------
#define STATEPAUSE 0x10
#define STATERUN   0x01
#define STATESTOP  0x00
//---------------------------------------------------------------------------
typedef struct 
{
    uint16_t startTicks;
    uint16_t pausedTicks;
    uint8_t  state;
} STimer;
//---------------------------------------------------------------------------
static inline void      IncrementSystemTicks(void);
static inline uint16_t  GetSystemTicks(void);
//---------------------------------------------------------------------------
uint16_t _Ticks;
//---------------------------------------------------------------------------
static inline void IncrementSystemTicks(void)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        _Ticks++;
    }
}
//---------------------------------------------------------------------------
static inline uint16_t GetSystemTicks(void)
{
    uint16_t temp;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        temp = _Ticks;
    }
    return temp;

}
//---------------------------------------------------------------------------
#define StartTimer(timer) do {                                          \
    time.state = STATERUN;                                              \
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)                                   \
    {                                                                   \
        timer.startTicks = GetSystemTicks();                            \
    }                                                                   \
    } while(0)
//---------------------------------------------------------------------------
#define StopTimer(timer) do {                                           \
    time.state = STATESTOP;                                             \
    } while(0)
//---------------------------------------------------------------------------
#define PauseTimer(timer) do {                                          \
    if((timer.started) && (!timer->paused))                             \
    {                                                                   \
        time.state = STATEPAUSE;                                        \
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)                               \
        {                                                               \
            timer.pausedTicks = GetSystemTicks() - timer.startTicks;    \
        }                                                               \
    }                                                                   \
    } while(0)
//---------------------------------------------------------------------------
#define ResumeTimer(timer) do {                                         \
    if((timer.started) && (timer.paused))                               \
    {                                                                   \
        time.state = STATERUN;                                          \
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE)                               \
        {                                                               \
            timer.startTicks = GetSystemTicks() - timer.pausedTicks;    \
        }                                                               \
    }                                                                   \
    } while(0)    
//---------------------------------------------------------------------------
#define IsTimerStart(timer) (timer.state == STATERUN ? 1 : 0)
//---------------------------------------------------------------------------
#define GetTimerTicks(timer) (timer.state == STATERUN ? (time.state == STATEPAUSE ? timer.pausedTicks : ((GetSystemTicks()) - timer.startTicks)) : 0)
//---------------------------------------------------------------------------
#define SetTimerTicks(timer, value) timer.startTicks = value
//---------------------------------------------------------------------------
#define RestartTimer(timer) StartTimer(timer)
//---------------------------------------------------------------------------
#endif /* SIMPLE_TIMER_H_ */