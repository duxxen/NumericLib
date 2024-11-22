#pragma once

/*************************************************************
 *
 *		 NumericLib configuration file
 *
 * You can edit this file by hand, changing the flags below
 * To set flag, just replace the pre-processor directive
 * 'if 0' by 'if 1' to enable the flag.
 * 'if 1' by 'if 0' to disable the flag.
 *
 *************************************************************/

#if 0
#define BASIC_COMP_TYPE_FLOAT32

 /*
  *	BASIC COMPUTATION TYPE - type, which will be returned after
  * every computation. By default 'float64' is the basic type.
  *
  *	Of course, some functions returns other types if it declared.
  *
  * (!!!) if enabled this - must disable other BASIC_COMP_TYPE_ flags (!!!)
  */


#endif

#if 1
#define BASIC_COMP_TYPE_FLOAT64

  /*
   * BASIC COMPUTATION TYPE - type, which will be returned after
   * every computation. By default 'float64' is the basic type.
   *
   * Of course, some functions returns other types if it declared.
   *
   * (!!!) if enabled this - must disable other BASIC_COMP_TYPE_ flags (!!!)
   */

#endif