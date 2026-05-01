/*
* Copyright (C) Leonid Kostikov
*
* This file is part of Single_phase_rectifiers
*
* Single_phase_rectifiers is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Single_phase_rectifiers is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Foobar.
If not, see <https://www.gnu.org/licenses/>.
*/


#ifndef CALCULATIONS_H_
#define CALCULATIONS_H_

#include <math.h>

#define U_CMAX 1.41f
#define I_CMAX 1.41f

float single_half_period_rectifier(float u2,
                                   float f,
                                   float i_n,
                                   float du,
                                   float* u_max,
                                   float* u_sr,
                                   float* r_n,
                                   float* p_tip,
                                   float* u_obr,
                                   float* c_f,
                                   float* u_c,
                                   float* i2,
                                   float* i_max);


float two_half_period_rectifier_with_a_midpoint(float u2,
                                                float f,
                                                float i_n,
                                                float du,
                                                float* u_max,
                                                float* u_sr,
                                                float* r_n,
                                                float* p_tip,
                                                float* u_obr,
                                                float* c_f,
                                                float* u_c,
                                                float* i2,
                                                float* i_max);


float bridge_circuit_of_a_two_half_period_rectifier(float u2,
                                                    float f,
                                                    float i_n,
                                                    float du,
                                                    float* u_max,
                                                    float* u_sr,
                                                    float* r_n,
                                                    float* p_tip,
                                                    float* u_obr,
                                                    float* c_f,
                                                    float* u_c,
                                                    float* i2,
                                                    float* i_max);

#endif /* CALCULATIONS_H_ */
