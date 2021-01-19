/**
 * This file declares unit converters for version 2 of the Unidata UDUNITS
 * package.
 *
 *  @file:  converter.h
 * @author: Steven R. Emmerson
 *
 *    Copyright 2021 University Corporation for Atmospheric Research
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CV_CONVERTER_H_INCLUDED
#define CV_CONVERTER_H_INCLUDED

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EXTERNL
#define EXTERNL extern
#endif

typedef union cv_converter	cv_converter;

/*
 * Returns the trivial converter (i.e., y = x).
 * When finished with the converter, the client should pass the converter to
 * cv_free().
 * RETURNS:
 *	The trivial converter.
 */
EXTERNL cv_converter*
cv_get_trivial(void);

/*
 * Returns the reciprocal converter (i.e., y = 1/x).
 * When finished with the converter, the client should pass the converter to
 * cv_free().
 * RETURNS:
 *	The reciprocal converter.
 */
EXTERNL cv_converter*
cv_get_inverse(void);

/*
 * Returns a scaling converter (i.e., y = ax).
 * When finished with the converter, the client should pass the converter to
 * cv_free().
 * RETURNS:
 *	The scaling converter.
 */
EXTERNL cv_converter*
cv_get_scale(
    const double	slope);

/*
 * Returns a converter that adds a number to values (i.e., y = x + b).
 * When finished with the converter, the client should pass the converter to
 * cv_free().
 * ARGUMENTS:
 *	intercept	The number to be added.
 * RETURNS:
 *	NULL	Necessary memory couldn't be allocated.
 *	else	A converter that adds the given number to values.
 */
EXTERNL cv_converter*
cv_get_offset(
    const double	intercept);

/*
 * Returns a Galilean converter (i.e., y = ax + b).
 * When finished with the converter, the client should pass the converter to
 * cv_free().
 * ARGUMENTS:
 *	slope		The number by which to multiply values.
 *	intercept	The number to be added.
 * RETURNS:
 *	NULL	Necessary memory couldn't be allocated.
 *	else	A Galilean converter corresponding to the inputs.
 */
EXTERNL cv_converter*
cv_get_galilean(
    const double	slope,
    const double	intercept);

/*
 * Returns a logarithmic converter (i.e., y = log(x) in some base).
 * When finished with the converter, the client should pass the converter to
 * cv_free().
 * ARGUMENTS:
 *	base		The logarithmic base (e.g., 2, M_E, 10).  Must be
 *                      greater than one.
 * RETURNS:
 *	NULL		"base" is not greater than one or necessary
 *			memory couldn't be allocated.
 *	else		A logarithmic converter corresponding to the inputs.
 */
EXTERNL cv_converter*
cv_get_log(
    const double	base);

/*
 * Returns an exponential converter (i.e., y = pow(b, x) in some base "b").
 * When finished with the converter, the client should pass the converter to
 * cv_free().
 *
 * Arguments:
 *	base		The desired base.  Must be positive.
 * Returns:
 *	NULL		"base" is invalid or necessary memory couldn't be
 *			allocated.
 *	else		An exponential converter corresponding to the inputs.
 */
EXTERNL cv_converter*
cv_get_pow(
    const double	base);

/*
 * Returns a converter corresponding to the sequential application of two
 * other converters.
 * ARGUMENTS:
 *	first	The converter to be applied first.
 *	second	The converter to be applied second.
 * RETURNS:
 *	NULL	Either "first" or "second" is NULL or necessary memory couldn't
 *		be allocated.
 *      else    A converter corresponding to the sequential application of the
 *              given converters.  If one of the input converters is the trivial
 *              converter, then the returned converter will be the other input
 *              converter.
 */
EXTERNL cv_converter*
cv_combine(
    cv_converter* const	first,
    cv_converter* const	second);

/*
 * Frees resources associated with a converter.
 * ARGUMENTS:
 *	conv	The converter to have its resources freed or NULL.
 */
EXTERNL void
cv_free(
    cv_converter* const	conv);

/*
 * Converts a float.
 * ARGUMENTS:
 *	converter	The converter.
 *	value		The value to be converted.
 * RETURNS:
 *	The converted value.
 */
EXTERNL float
cv_convert_float(
    const cv_converter*	converter,
    const float		value);

/*
 * Converts a double.
 * ARGUMENTS:
 *	converter	The converter.
 *	value		The value to be converted.
 * RETURNS:
 *	The converted value.
 */
EXTERNL double
cv_convert_double(
    const cv_converter*	converter,
    const double	value);

/*
 * Converts an array of floats.
 * ARGUMENTS:
 *	converter	The converter.
 *	in		The values to be converted.
 *	count		The number of values to be converted.
 *	out		The output array for the converted values.  May
 *			be the same array as "in" or overlap it.
 * RETURNS:
 *	NULL	"out" is NULL.
 *	else	A pointer to the output array.
 */
EXTERNL float*
cv_convert_floats(
    const cv_converter*	converter,
    const float* const	in,
    const size_t	count,
    float*		out);

/*
 * Converts an array of doubles.
 * ARGUMENTS:
 *	converter	The converter.
 *	in		The values to be converted.
 *	count		The number of values to be converted.
 *	out		The output array for the converted values.  May
 *			be the same array as "in" or overlap it.
 * RETURNS:
 *	NULL	"out" is NULL.
 *	else	A pointer to the output array.
 */
EXTERNL double*
cv_convert_doubles(
    const cv_converter*	converter,
    const double* const	in,
    const size_t	count,
    double*		out);

/*
 * Returns a string representation of a converter.
 * ARGUMENTS:
 *	conv		The converter.
 *	buf		The buffer into which to write the expression.
 *	max		The size of the buffer.
 *	variable	The string to be used as the input value for the
 *			converter.
 * RETURNS
 *	<0	An error was encountered.
 *	else	The number of bytes formatted excluding the terminating null.
 */
EXTERNL int
cv_get_expression(
    const cv_converter* const	conv,
    char* const			buf,
    size_t			max,
    const char* const		variable);

#ifdef __cplusplus
}
#endif

#endif
