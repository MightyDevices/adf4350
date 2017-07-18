/*
 * bn.h
 *
 *  Created on: 10-05-2017
 *      Author: Tomek
 */

#ifndef UTIL_BN_H_
#define UTIL_BN_H_


/* helper macros */
#define BN0(x) 					((x) ?  0 : -1)
#define BN1(x) 					((x) >= 1 << 1  ?  1 + BN0((x) >> 1)  : BN0(x))
#define BN2(x) 					((x) >= 1 << 2  ?  2 + BN1((x) >> 2)  : BN1(x))
#define BN3(x) 					((x) >= 1 << 4  ?  4 + BN2((x) >> 4)  : BN2(x))
#define BN4(x) 					((x) >= 1 << 8  ?  8 + BN3((x) >> 8)  : BN3(x))

/* returns MSb position in 32 bit words */
#define BN(x) 					((x) >= 1 << 16 ? 16 + BN4((x) >> 16) : BN4(x))

#define LSB0(x)					( (x) & 0x0001 ? 0 : 1)
#define LSB1(x)					( (x) & 0x0003 ? LSB0(x) : 2  + LSB0((x) >> 2) )
#define LSB2(x)					( (x) & 0x000f ? LSB1(x) : 4  + LSB1((x) >> 4) )
#define LSB3(x)					( (x) & 0x00ff ? LSB2(x) : 8  + LSB2((x) >> 8) )
#define LSB4(x)					( (x) & 0xffff ? LSB3(x) : 16 + LSB3((x) >> 16) )
#define LSB(x)					( (x) ? LSB4(x) : -1 )

#endif /* BN_H_ */
