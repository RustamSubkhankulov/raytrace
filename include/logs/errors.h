#pragma once

//===================================================================

#define DEF_ERR(code, name, string) 								 \
																	 \
	name  = code,													 \

//===================================================================

enum error_code {

	#include "../../codegen/err_descr.txt"
};

#undef DEF_ERR

