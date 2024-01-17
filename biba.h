//
// Created by dejabatg on 16.01.24.
//

#ifndef SP_4_BIBA_H
#define SP_4_BIBA_H

///* Standard file descriptors.  */
//#define	STDIN_FILENO	0	/* Standard input.  */
//#define	STDOUT_FILENO	1	/* Standard output.  */
//#define	STDERR_FILENO	2	/* Standard error output.  */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>


#ifndef E_EMPTY_STRING
#define E_EMPTY_STRING "Empty string was given\n"
#endif

#ifndef E_INVALID_PARAMETER
#define E_INVALID_PARAMETER "Invalid parameter given\nUsage: ./elf number_of_simbols[unsigned int]\n"
#endif

#ifndef E_INVALID_NUMBER
#define E_INVALID_NUMBER "Invalid number given\nCheck argument, it has to be positive integer\n"
#endif


#ifndef OK
#define OK 0
#endif

#ifndef FAIL
#define FAIL -1
#endif



char * get_string_from_input();
void write_n_sym(char * src, size_t n);
int from_string_to_int(char * arg);



#endif //SP_4_BIBA_H
