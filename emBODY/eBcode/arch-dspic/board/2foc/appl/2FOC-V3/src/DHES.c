//
// Hall Effect sensor related routines
//

//#include "UserParms.h"
#include "Faults.h"
#include "DHES.h"

#define IMPOSSIBLE 2

// the HES activation sequence is 1,3,2,6,4,5

// note: zero is init val for "old" dhes value
// this LUT gives 0 if no turn has been done
//  1 if one positive step has to be counted
// -1 if one negative step has to be counted
//  2 if an invalid transition happened

                                 //old new
char DHES_TRANSITION_LUT[7][7] =
{ 
 //to 0  1  2  3  4  5  6
    { 0, 0, 0, 0, 0, 0, 0}, // from 0 all ok (init val)
    { 2, 0, 2, 1, 2,-1, 2}, // from 1 (ok 1 3 5)
    { 2, 2, 0,-1, 2, 2, 1}, // from 2 (ok 2 3 6)
    { 2,-1, 1, 0, 2, 2, 2}, // from 3 (ok 3 1 2)
    { 2, 2, 2, 2, 0, 1,-1}, // from 4 (ok 4 6 5)
    { 2, 1, 2, 2,-1, 0, 2}, // from 5 (ok 5 1 4)
    { 2, 2,-1, 2, 1, 2, 0}, // from 6 (ok 6 2 4)
};

static long dhes_position = 0;
static int  dhes_velocity = 0;
static int  dhes_step = 0;

void DHESInit(int step)
{
    dhes_step = step;
}

inline long DHESPosition() __attribute__((always_inline));
inline long DHESPosition()
{
    return dhes_position;
}

inline int DHESVelocity() __attribute__((always_inline));
inline int DHESVelocity()
{
    static int index = 0;
    static long buffer[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    static const int UNDERSAMPLING = PWMFREQUENCY / 1000;
    static int undersampler = 0;

    if (++undersampler == UNDERSAMPLING) // we obtain ticks per ms
    {
        undersampler = 0;

        buffer[index++] = dhes_position;

        index %= 32;

        dhes_velocity = (int)((dhes_position - buffer[index])>>5);
    }

    return dhes_velocity;
}

inline unsigned char DHESRead() __attribute__((always_inline));
unsigned char DHESRead()
{
    static unsigned char dhes_state = 0;

    //#ifdef DHES_CONNECTED_TO_P1_P6
    // HU==RP3==RB3, HV==RP8==RB8, HW==RP9==RB9
    //unsigned char port_read = (PORTBbits.RB3) | (PORTBbits.RB8<<2) | (PORTBbits.RB9<<1);
    unsigned char port_read = (PORTBbits.RB3<<2) | (PORTBbits.RB8<<1) | (PORTBbits.RB9);
    //#else
    // Read DHES vaue from the uC pins of choice
    // mask the port where the DHES are connected (RP5, RP6, RP7)
    //unsigned char port_read = (PORTB & 0b011100000) >> 5;
    //#endif

    if((port_read == 0) || (port_read == 7))
    {
        dhes_state = 0; // next time do not make assumption
        SysError.DHESInvalidValue=1;
        FaultConditionsHandler();
        return 0;
    }

    if (dhes_state == port_read) return dhes_state;

    // if 0 no turn has been done
    // if 1 or -1 a CW or CCW turn has been done
    // if 2 error: invalid transition
    char transition = DHES_TRANSITION_LUT[dhes_state][port_read];
               
    if (transition == IMPOSSIBLE)
    {
        dhes_state = 0; // next time do not make assumption
        SysError.DHESInvalidSequence = 1;
        FaultConditionsHandler();
        return 0;
    }

    if (transition==1)
    {
        dhes_position += dhes_step;
    }
    else if (transition==-1)
    {
        dhes_position -= dhes_step;
    }

    dhes_state = port_read;

    return dhes_state;
}
