#ifndef SUPER_TIMER_H_
#define SUPER_TIMER_H_
//------------------------------------------------------------------------------
typedef struct 
{
    uint32_t startTicks;
    uint32_t pausedTicks;
    uint8_t paused;
    uint8_t started;
} STimer;
//------------------------------------------------------------------------------
uint32_t GetSystemTicks(void);
void StartTimer(STimer *timer);
void StopTimer(STimer *timer);
void PauseTimer(STimer *timer);
void ResumeTimer(STimer *timer);
uint32_t GetTimerTicks(STimer timer);
uint8_t IsTimerStart(STimer timer);
//------------------------------------------------------------------------------
#endif /* SUPER_TIMER_H_ */