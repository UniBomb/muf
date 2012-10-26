#include <avr/io.h>
#include <util/atomic.h>
#include <avr/interrupt.h>
#include "super_timer.h"
//------------------------------------------------------------------------------
static uint32_t _Ticks;
/**  
*    Например у нас частота мк 7372800 Гц, предделитель 64.
*    1мс обеспечивается за 7372800/64*0,001 = 115,2 тактов таймера.
*    Т.к. дробные числа записывать нельзя, то обеспечим точность 5 мс
*
*    5 * 115,2 = 576; 576 = 115 + 115 + 116 + 115 + 115;
*
*    256 - 115 = 141
*    256 - 116 = 140
*
*/
static uint8_t tcntValues[5] = {141, 141, 140, 141, 141};
static uint8_t tcntCnt = 1;
//------------------------------------------------------------------------------
ISR(TIMER0_OVF_vect)
{
    /* Этот таймер всегда должен быть настроен на период 1 мс!!! */
    _Ticks++;
    TCNT0 = tcntValues[tcntCnt];
    tcntCnt++;
    if(tcntCnt >= 5) 
        tcntCnt = 0;
}
//------------------------------------------------------------------------------
uint32_t GetSystemTicks(void)
{
    uint32_t temp;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        temp = _Ticks;           // установить значение системного времени
    }
    return temp;
}
//------------------------------------------------------------------------------
void StartTimer(STimer *timer)
{
    timer->started = 1;
    timer->paused = 0;
    timer->startTicks = GetSystemTicks();
}
//------------------------------------------------------------------------------
void StopTimer(STimer *timer)
{
    timer->started = 0;
    timer->paused = 0;
}
//------------------------------------------------------------------------------
void PauseTimer(STimer *timer)
{
    if((timer->started) && (!timer->paused))
    {
        timer->paused = 1;
        timer->pausedTicks = GetSystemTicks() - timer->startTicks;
    }
}
//------------------------------------------------------------------------------
void ResumeTimer(STimer *timer)
{
    if((timer->started) && (timer->paused))
    {
        timer->paused = 0;
        timer->startTicks = GetSystemTicks() - timer->pausedTicks;
    }
}
//------------------------------------------------------------------------------
uint8_t IsTimerStart(STimer timer)
{
    return timer.started;
}
//------------------------------------------------------------------------------
uint32_t GetTimerTicks(STimer timer)
{
    if(timer.started)
    {
        if(timer.paused)
            return timer.pausedTicks;
        else
            return GetSystemTicks() - timer.startTicks;
    }
    return 0;
}