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


#include <windows.h>
#include "calculations.h"
#include <iostream>


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
                                   float* i_max)
{
    *u_max = u2 * U_CMAX;
    *u_sr = u2 * 0.45f;
    *r_n = *u_sr / i_n;
    *p_tip = 3.5f * *u_sr * i_n;
    *u_obr = M_PI * *u_sr;
    *c_f = (i_n * pow(10, 6))/(f * du);
    *u_c = *u_max * 2;

    *i2 = 1.57f * i_n;
    *i_max = *i2 * I_CMAX;

    /*std::cout << *i2 << std::endl;
    std::cout << *i_max << std::endl;*/

    return 0;
}


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
                                                float* i_max)
{
    *u_max = u2 * U_CMAX;
    *u_sr = u2 * 0.9f;
    *r_n = *u_sr / i_n;
    *p_tip = 1.48f * *u_sr * i_n;
    *u_obr = M_PI * *u_sr;
    *c_f = (i_n * pow(10, 6))/(2.0f * f * du);
    *u_c = *u_max * 2;

    *i2 = 0.785f * i_n;
    *i_max = *i2 * I_CMAX;

    /*std::cout << *i2 << std::endl;
    std::cout << *i_max << std::endl;*/

    return 0;
}


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
                                                    float* i_max)
{
    *u_max = u2 * U_CMAX;
    *u_sr = u2 * 0.9f;
    *r_n = *u_sr / i_n;
    *p_tip = 1.23f * *u_sr * i_n;
    *u_obr = 1.57f * *u_sr;
    *c_f = (i_n * pow(10, 6))/(2.0f * f * du);
    *u_c = *u_max * 2;

    *i2 = 1.11f * i_n;
    *i_max = *i2 * I_CMAX;

    /*std::cout << *i2 << std::endl;
    std::cout << *i_max << std::endl;*/

    return 0;
}
