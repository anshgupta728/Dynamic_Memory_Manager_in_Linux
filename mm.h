#define MM_MAX_STRUCT_NAME 32
typedef struct pageFamily{
	char struct_name[MM_MAX_STRUCT_NAME]; 
	uint32_t struct_size;
}vm_page_family;

typedef struct pageFamilies{
    struct pageFamilies *next;
    pageFamily vmPageFamily[0];
}vm_page_families;









