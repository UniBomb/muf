#ifndef _IOPORTS_H_
#define _IOPORTS_H_
//------------------------------------------------------------------------------
#include <avr/io.h>
//------------------------------------------------------------------------------
/* Базовые макросы */
#define rP(sym,  num)     (((PIN##sym)&(1<<num))>>(num))
#define rPA(sym, num)     ((PIN##sym)&(1<<num))
#define sP(sym,  num)     do { (PORT##sym) |=   1 << (num);  } while(0)
#define cP(sym,  num)     do { (PORT##sym) &= ~(1 << (num)); } while(0)
#define iP(sym,  num)     do { (PORT##sym) ^=   1 << (num);  } while(0)
#define sDi(sym, num)     do { (DDR##sym)  &= ~(1 << (num)); } while(0)
#define sDo(sym, num)     do { (DDR##sym)  |=   1 << (num);  } while(0)
#define gPORTn(sym, num)  PORT##sym
#define gPINn(sym, num)   num
//------------------------------------------------------------------------------
/* Обёртки над базовыми макросами для использования в программах */
#define readPin(x)               rP(x)
#define readPinAbs(x)            rPA(x)
#define readPinBuf(buf, x)       rPB(buf,  x)
#define readPinBufAbs(buf, x)    rPBA(buf, x)
#define setPin(x)                sP(x)
#define clearPin(x)              cP(x)
#define invertPin(x)             iP(x)
#define reversePin(x)            iP(x)
#define setDDRout(x)             sDo(x)
#define setDDRin(x)              sDi(x)

#define on(x)                    sP(x)
#define off(x)                   cP(x)

#define setRX(x)                 cP(x)
#define setTX(x)                 sP(x)

#define getPortName(x)           gPORTn(x)
#define getPinName(x)            gPINn(x)

#define setRX(x)                 cP(x)
#define setTX(x)                 sP(x)

#if defined debugLEDs
    #define debugLedOn(x)        sP(x)
    #define debugLedOff(x)       cP(x)
    #define debugLedInvert(x)    iP(x)
#else
    #define debugLedOn(x)        
    #define debugLedOff(x)       
    #define debugLedInvert(x)    
#endif
//------------------------------------------------------------------------------
////#ifdef PORTA
    #define pA0 A, 0
    #define pA1 A, 1
    #define pA2 A, 2
    #define pA3 A, 3
    #define pA4 A, 4
    #define pA5 A, 5
    #define pA6 A, 6
    #define pA7 A, 7
////#endif
//------------------------------------------------------------------------------
//#ifdef PORTB
    #define pB0 B, 0
    #define pB1 B, 1
    #define pB2 B, 2
    #define pB3 B, 3
    #define pB4 B, 4
    #define pB5 B, 5
    #define pB6 B, 6
    #define pB7 B, 7
//#endif
//------------------------------------------------------------------------------
//#ifdef PORTC
    #define pC0 C, 0
    #define pC1 C, 1
    #define pC2 C, 2
    #define pC3 C, 3
    #define pC4 C, 4
    #define pC5 C, 5
    #define pC6 C, 6
    #define pC7 C, 7
//#endif
//------------------------------------------------------------------------------
//#ifdef PORTD
    #define pD0 D, 0
    #define pD1 D, 1
    #define pD2 D, 2
    #define pD3 D, 3
    #define pD4 D, 4
    #define pD5 D, 5
    #define pD6 D, 6
    #define pD7 D, 7
//#endif
//------------------------------------------------------------------------------
//#ifdef PORTE
    #define pE0 E, 0
    #define pE1 E, 1
    #define pE2 E, 2
    #define pE3 E, 3
    #define pE4 E, 4
    #define pE5 E, 5
    #define pE6 E, 6
    #define pE7 E, 7
//#endif
//------------------------------------------------------------------------------
//#ifdef PORTF
    #define pF0 F, 0
    #define pF1 F, 1
    #define pF2 F, 2
    #define pF3 F, 3
    #define pF4 F, 4
    #define pF5 F, 5
    #define pF6 F, 6
    #define pF7 F, 7
//#endif
//------------------------------------------------------------------------------
//#ifdef PORTG
    #define pG0 G, 0
    #define pG1 G, 1
    #define pG2 G, 2
    #define pG3 G, 3
    #define pG4 G, 4
    #define pG5 G, 5
    #define pG6 G, 6
    #define pG7 G, 7
//#endif
//------------------------------------------------------------------------------
//#ifdef PORTH
    #define pH0 H, 0
    #define pH1 H, 1
    #define pH2 H, 2
    #define pH3 H, 3
    #define pH4 H, 4
    #define pH5 H, 5
    #define pH6 H, 6
    #define pH7 H, 7
//#endif
//------------------------------------------------------------------------------
//#ifdef PORTI
    #define pI0 I, 0
    #define pI1 I, 1
    #define pI2 I, 2
    #define pI3 I, 3
    #define pI4 I, 4
    #define pI5 I, 5
    #define pI6 I, 6
    #define pI7 I, 7
//#endif
//------------------------------------------------------------------------------
//#ifdef PORTJ
    #define pJ0 J, 0
    #define pJ1 J, 1
    #define pJ2 J, 2
    #define pJ3 J, 3
    #define pJ4 J, 4
    #define pJ5 J, 5
    #define pJ6 J, 6
    #define pJ7 J, 7
//#endif
//------------------------------------------------------------------------------
//#ifdef PORTK
    #define pK0 K, 0
    #define pK1 K, 1
    #define pK2 K, 2
    #define pK3 K, 3
    #define pK4 K, 4
    #define pK5 K, 5
    #define pK6 K, 6
    #define pK7 K, 7
//#endif
//------------------------------------------------------------------------------
//#ifdef PORTL
    #define pL0 L, 0
    #define pL1 L, 1
    #define pL2 L, 2
    #define pL3 L, 3
    #define pL4 L, 4
    #define pL5 L, 5
    #define pL6 L, 6
    #define pL7 L, 7
//#endif
//------------------------------------------------------------------------------
#endif