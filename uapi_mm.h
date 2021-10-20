#ifndef __UAPI_MM__
#define __UAPI_MM__

#include<stdint.h>

//Intialization Function
void mm_init();

//Registration function
void mm_instantiate_new_page_family(char *struct_name, uint32_t struct_size);

#define MM_REG_STRUCT(struct_name) \
	(mm_instantiate_new_page_family(#struct_name, sizeof(struct_name)))

#endif /* __UAPI_MM__*/
