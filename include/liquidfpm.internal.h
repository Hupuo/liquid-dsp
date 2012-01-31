/*
 * Copyright (c) 2008, 2009, 2010, 2011, 2012 Joseph Gaeddert
 * Copyright (c) 2008, 2009, 2010, 2011, 2012 Virginia Polytechnic
 *                                Institute & State University
 *
 * This file is part of liquid.
 *
 * liquid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * liquid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with liquid.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __LIQUID_FPM_INTERNAL_H__
#define __LIQUID_FPM_INTERNAL_H__

#include "liquidfpm.h"
#include "config.h"

#ifndef M_PI
#  define M_PI 3.14159265358979
#endif

// generic conversion
static inline float qtype_fixed_to_float(int _x,
                                         unsigned int _intbits,
                                         unsigned int _fracbits)
{
    return (float) (_x) / (float)(1 << _fracbits);
};

static inline int qtype_float_to_fixed(float _x,
                                       unsigned int _intbits,
                                       unsigned int _fracbits)
{
    return (int) (_x * (float)(1 << _fracbits) + 0.5f);
};

static inline float qtype_angle_fixed_to_float(int _x,
                                               unsigned int _intbits,
                                               unsigned int _fracbits)
{
    return qtype_fixed_to_float(_x,_intbits,_fracbits) * (M_PI / (float)(1<<(_intbits-2)));
};

static inline int qtype64_angle_float_to_fixed(float _x,
                                               unsigned int _intbits,
                                               unsigned int _fracbits)
{
    return qtype_float_to_fixed(_x,_intbits,_fracbits) / (M_PI / (float)(1<<(_intbits-2)));
};

//
// bit-wise utilities
//

// leading zeros (8-bit)
extern const unsigned char liquidfpm_lz8[256];

// count leading zeros
#define clz8(_byte) (lz8[_byte])
unsigned int liquidfpm_clz(unsigned int _x);

// index of most significant bit
unsigned int liquidfpm_msb_index(unsigned int _x);

/* Internal API definition macro
 *
 * Q        :   name-mangling macro
 * T        :   primitive data type
 * TA       :   primitive data type (accumulator)
 * INTBITS  :   number of integer bits
 * FRACBITS :   number of fractional bits
 */
#define LIQUIDFPM_DEFINE_INTERNAL_API(Q,T,TA,INTBITS,FRACBITS)      \
                                                                    \
/* auto-generated look-up tables */                                 \
extern const Q(_t) Q(_log2_frac_gentab)[256];                       \

LIQUIDFPM_DEFINE_INTERNAL_API(LIQUIDFPM_MANGLE_Q16, int16_t, int32_t, LIQUIDFPM_Q16_INTBITS, LIQUIDFPM_Q16_FRACBITS)
LIQUIDFPM_DEFINE_INTERNAL_API(LIQUIDFPM_MANGLE_Q32, int32_t, int64_t, LIQUIDFPM_Q32_INTBITS, LIQUIDFPM_Q32_FRACBITS)

#endif // __LIQUID_FPM_INTERNAL_H__
