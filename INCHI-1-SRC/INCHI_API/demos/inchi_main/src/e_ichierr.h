/*
 * International Chemical Identifier (InChI)
 * Version 1
 * Software version 1.07
 * April 30, 2024
 *
 * MIT License
 *
 * Copyright (c) 2024 IUPAC and InChI Trust
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*
* The InChI library and programs are free software developed under the
 * auspices of the International Union of Pure and Applied Chemistry (IUPAC).
 * Originally developed at NIST.
 * Modifications and additions by IUPAC and the InChI Trust.
 * Some portions of code were developed/changed by external contributors
 * (either contractor or volunteer) which are listed in the file
 * 'External-contributors' included in this distribution.
 *
 * info@inchi-trust.org
 *
*/


#ifndef __INCHIERR_H__
#define __INCHIERR_H__

#define _IS_OKAY    0
#define _IS_WARNING 1
#define _IS_ERROR   2    /* Microsoft defined its own IS_ERROR() macro */
#define _IS_FATAL   3
#define _IS_UNKNOWN 4    /* unknown error: used in INChI DLL only */
#define _IS_EOF    -1    /* end of file */
#define _IS_SKIP   -2



#define INCHI_INP_ERROR_ERR   40
#define INCHI_INP_ERROR_RET  (-1)

#define INCHI_INP_FATAL_ERR    1
#define INCHI_INP_FATAL_RET    0

#define INCHI_INP_EOF_ERR     11
#define INCHI_INP_EOF_RET      0

#define LOG_MASK_WARN  1
#define LOG_MASK_ERR   2
#define LOG_MASK_FATAL 4

#define LOG_MASK_ALL     (LOG_MASK_WARN | LOG_MASK_ERR | LOG_MASK_FATAL)
#define LOG_MASK_NO_WARN (LOG_MASK_ERR | LOG_MASK_FATAL)

#endif /* __INCHIERR_H__ */
