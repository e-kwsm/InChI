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

 /**
  * Aromatic-bond classification utilities.
  *
  * Self-contained predicates and helpers that classify/transform bonds of
  * type BOND_TYPE_ALTERN ("aromatic") on inp_ATOM arrays. Extracted from
  * ichinorm.c (and a revived dead helper from strutil.c) so they can be
  * unit-tested independently of the normalization/underivatize code.
  *
  * NOT included here (kept in their own domains): the core aromatic-bond
  * perception mark_alt_bonds_and_taut_groups() (BNS engine, ichi_bns.c),
  * the stereo bond classifier (ichister.c), the tautomer-solver inline
  * BOND_ALTERN checks (ichitaut.c), the metal-disconnection aromatic-bond
  * counting (strutil.c), and parser bond-type mapping (mol2atom.c/readinch.c).
  */

#ifndef _ICHIAROM_H_
#define _ICHIAROM_H_

#include "mode.h"
#include "inpdef.h"

#ifndef COMPILE_ALL_CPP
#ifdef __cplusplus
extern "C" {
#endif
#endif

struct tagINCHI_CLOCK;
struct tagCANON_GLOBALS;

/* Charge a neutral 2-valent aromatic O or S (bond_type sum == 3). Returns 1 if changed. */
int FixAromaticOxygenAndSulfur( inp_ATOM *atom );

/* True if at[i] is an unsaturated (has a real double bond) but non-aromatic carbon. */
int is_C_unsat_not_arom( inp_ATOM *at, int i );

/* True if the attachment point is an aromatic aryl carbon (two BOND_ALTERN bonds to C/N). */
int is_Aryl( inp_ATOM *at, int outside_point, int attachment_pont );

/* Walk an all-BOND_ALTERN CH chain of exactly len atoms from cur to last. */
int check_arom_chain( inp_ATOM *at, int cur, int from, int last, int len );

/* Copy resolved bond types from reference array at2 onto residual aromatic bonds in at. */
int replace_arom_bonds( inp_ATOM *at, int num_atoms, inp_ATOM *at2, int num_atoms2 );

/* Thin wrapper: run alternating-bond/tautomer marking with default flags. */
int mark_arom_bonds( struct tagINCHI_CLOCK *ic, struct tagCANON_GLOBALS *pCG, inp_ATOM *at, int num_atoms );

#ifndef COMPILE_ALL_CPP
#ifdef __cplusplus
}
#endif
#endif

#endif /* _ICHIAROM_H_ */
