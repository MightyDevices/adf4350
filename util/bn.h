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



#endif /* BN_H_ */
