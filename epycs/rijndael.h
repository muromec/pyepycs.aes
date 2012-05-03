#include <Python.h> 
#ifndef __RIJNDAEL_H_
#define __RIJNDAEL_H_

#ifndef u32
	#define u32		PY_UINT32_T
#endif

void aes_256_setkey (const void * const key, u32 * ks);
void aes_256_encrypt (const u32 * const pt, u32 * const ct, const u32 * const ks);

#endif
