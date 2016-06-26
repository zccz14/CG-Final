#pragma once
#ifndef NAME_H
#define NAME_H

#include <cmath>
#include <float.h>


#if 0

#define SINGLE_PRECISION
	typedef float real;
#define REAL_MAX FLT_MAX
#define real_sqrt sqrtf
#define real_abs fabsf
#define real_sin sinf
#define real_cos cosf	
#define real_exp expf
#define real_pow powf
#define real_fmod fmodf
#define R_PI 3.14159f
#define GRAV 9.8
#else

#define DOUBLE_PRECISION
	typedef double real;
#define REAL_MAX DBL_MAX
#define real_sqrt sqrt
#define real_abs fabs
#define real_sin sin
#define real_cos cos
#define real_exp exp
#define real_pow pow
#define real_fmod fmod
#define R_PI 3.14159265358979
#define GRAV 9.8

#endif


#endif
