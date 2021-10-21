#include<stdio.h>
#include<memory.h>
#include<unistd.h>    //for getpagesize()
#include<sys/mman.h>  //for mmap() and munmap()
#include<assert.h>    //for assert()
#include "mm.h"

//Head to the linked list that stores various page family
static vm_page_for_families_t *first_vm_page_for_families = NULL;

//Variable to store the virtual memory page size of the system
static size_t SYSTEM_PAGE_SIZE = 0;

//Function to get size of 1 virual memory page
void mm_init(){
    SYSTEM_PAGE_SIZE = getpagesize();
}

//Function to allocate a page
void *mm_get_vm_page_from_kernel(int units){
    char *vm_page = mmap(0, units*SYSTEM_PAGE_SIZE, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_ANON|MAP_PRIVATE, 0 ,0);
    
    if(vm_page == MAP_FAILED){
        printf("Error: VM Page ALlocation Failed\n");
        return NULL;
    }   
    
    memset(vm_page, 0, units*SYSTEM_PAGE_SIZE);
    printf("Page Allocation Successful\n");
    return (void *)vm_page;
}

//Function to deallocate a page
void mm_return_vm_page_to_kernel(void *vm_page, int units){
    if(munmap(vm_page, units*SYSTEM_PAGE_SIZE)){
        printf("Error: VM Page Deallocation Failed\n");
    }  
    printf("Page DeAllocation Successful\n");
}

//Instantiate a Page 
void mm_instantiate_new_page_family(char *struct_name, uint32_t struct_size){
        vm_page_family_t *vm_page_family_curr = NULL;
        vm_page_for_families_t *new_vm_page_for_families = NULL;
        if(struct_size > SYSTEM_PAGE_SIZE){
                printf("Error: Size requested exceed the system page size");
                return;
        }
        
        if(!first_vm_page_for_families){
                first_vm_page_for_families = (vm_page_for_families_t *)mm_get_vm_page_from_kernel(1);
                first_vm_page_for_families->next = NULL;
                strncpy(first_vm_page_for_families->vm_page_family[0].struct_name, struct_name, MM_MAX_STRUCT_NAME);
                first_vm_page_for_families->vm_page_family[0].struct_size = struct_size;
	}
        
        uint32_t count=0;
        ITERATE_PAGE_FAMILIES_BEGIN(first_vm_page_for_families, vm_page_family_curr){
                if(strncmp(vm_page_family_curr->struct_name, struct_name, MM_MAX_STRUCT_NAME)!=0){
                        count++;
                        continue;
                }
                assert(0);
        } ITERATE_PAGE_FAMILIES_END(first_vm_page_for_families, vm_page_family_curr);
       
        if(count == MAX_FAMILIES_PER_VM_PAGE){
                new_vm_page_for_families = (vm_page_for_families_t *)mm_get_vm_page_from_kernel(1);
                new_vm_page_for_families->next = first_vm_page_for_families;
                first_vm_page_for_families = new_vm_page_for_families;
                vm_page_family_curr = &first_vm_page_for_families->vm_page_family[0];
         }
         
         strncpy(vm_page_family_curr->struct_name, struct_name, MM_MAX_STRUCT_NAME);
         vm_page_family_curr->struct_size=struct_size;
         //vm_page_family_curr->first_page=NULL;
}

static void mm_union_free_blocks(block_meta_data_t *first, block_meta_data_t *second) {
        assert(first->is_free == MM_TRUE && second->is_free == MM_TRUE);
        first->block_size += sizeof(block_meta_data_t)+second->block_size;
        first -> next_block = second -> next_block;
        if(second -> next_block)
           second->next_block->prev_block = first;
}

void mm_print_registered_page_families(){
	vm_page_family_t *vm_page_family_curr = NULL;
	vm_page_for_families_t *vm_page_for_families_curr = NULL;

	for(vm_page_for_families_curr = first_vm_page_for_families; vm_page_for_families_curr; vm_page_for_families_curr = vm_page_for_families_curr -> next) {

		ITERATE_PAGE_FAMILIES_BEGIN(vm_page_for_families_curr, vm_page_family_curr) {

			printf("Page family : %s, size = %u\n", vm_page_family_curr -> struct_name, vm_page_family_curr -> struct_size); 

		} ITERATE_PAGE_FAMILIES_END(vm_page_for_families_curr, vm_page_family_curr);
	}
}

/*int main(int argc, char **argv){
    mm_init();
    printf("VM Page Size = %lu\n", SYSTEM_PAGE_SIZE);
    void *addr1 = mm_get_vm_page_from_kernel(1);
    void *addr2 = mm_get_vm_page_from_kernel(1);
    mm_return_vm_page_to_kernel(addr1,1);
    mm_return_vm_page_to_kernel(addr2,1);
    return 0;
}*/
    
            
    
