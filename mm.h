#define MM_MAX_STRUCT_NAME 32
typedef struct pageFamily{
	char struct_name[MM_MAX_STRUCT_NAME]; 
	uint32_t struct_size;
}vm_page_family;

typedef struct pageFamilies{
    struct pageFamilies *next;
    pageFamily vmPageFamily[0];
}vm_page_families;

#define MAX_FAMILIES_PER_VM_PAGE 							\
    (SYSTEM_PAGE_SIZE - sizeof(pageFamilies *)/sizeof(pageFamily)) 
    
#define ITERATE_PAGE_FAMILIES_BEGIN(vm_page_for_families_ptr, curr) 		        \
{											\
	uint32_t count=0;								\
	for(curr = (pageFamily *)&vm_page_for_families_ptr->vmpageFamily[0];	        \
	curr->struct size && count < MAX_FAMILIES_PER_VM_PAGE;				\
	curr++;count++;){								\
 
#define ITERATE_PAGE_FAMILIES_BEGIN(vm_page_for_families_ptr, curr) }}

#endif 
 















