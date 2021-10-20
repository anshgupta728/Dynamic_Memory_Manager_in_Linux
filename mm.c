#include<stdio.h>
#include<string.h>
#include<memory.h>
#include<unistd.h>    //for getpagesize()
#include<sys/mman.h>  //for mmap() and munmap()

static size_t SYSTEM_PAGE_SIZE = 0;
static pageFamilies *firstPage=NULL; 

//Function to get size of 1 virual memory page
void mm_init(){
    SYSTEM_PAGE_SIZE = getpagesize();
}

//Function to allocate a page
void *allocateVMPage_from_kernel(int units){
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
void deallocateVMPage_from_kernel(void *vm_page, int units){
    if(munmap(vm_page, units*SYSTEM_PAGE_SIZE)){
        printf("Error: VM Page Deallocation Failed\n");
    }  
    printf("Page DeAllocation Successful\n");
}

//Page Instantiation Algorithm
void instantiatePage(char *struct_name, uint32_t size){
	pageFamily *current = NULL;
	pageFamilies *temp = NULL;
	if(struct_size > SYSTEM_PAGE_SIZE){
		//Limitation: We cannot allocate memory to a structure whose size is greater than the System page size
		printf("Cannot allocate memory for %s",struct_name);
		return;	
	}
	
	if(firstPage == NULL){
		firstPage=(pageFamilies *)allocateVMPage_from_kernel(1);
		firstPage->next=NULL;
		strncpy(firstPage->vmPageFamily[0].struct_name, struct_name, MM_MAX_STRUCT_NAME);
		firstPage->vmPageFamily[0].struct_size = struct_size;
		return;	
	}
	/*
	uint32_t count=0;
        ITERATE_PAGE_FAMILIES_BEGIN(first_vm_page_for_families, vm_page_family_curr){
                if(strncmp(vm_page_family_curr->struct_name, struct_name, MM_MAX_STRUCT_NAME)!=0){
                        count++;
                        continue;
                }
                assert(0);
        } ITERATE_PAGE_FAMILIES_BEGIN(first_vm_page_for_families, vm_page_family_curr);
        
        if(count == MAX_FAMILIES_PER_VM_PAGE){
                vm_page_for_families *new_vm_page_for_families = (vm_page_for_families *)mm_get_vm_page_from_kernel(1);
                new_vm_page_for_families->next = first_vm_page_for_families;
                first_vm_page_for_families = new_vm_page_families;
                vm_page_family_curr = &first_vm_page_for_families->vm_page_family[0];
         }
         
         strncpy(vm_page_family_curr->struct_names, struct_name, MM_MAX_STRUCT_NAME);
         vm_page_family_curr->struct_size=struct_size;
         vm_page_family_curr->first_page=NULL;
	*/
}

int main(int argc, char **argv){
    mm_init();
    
    printf("VM Page Size = %lu bytes\n", SYSTEM_PAGE_SIZE);
    void *addr1 = allocateVMPage_from_kernel(1);
    void *addr2 = allocateVMPage_from_kernel(1);
    deallocateVMPage_from_kernel(addr1,1);
    deallocateVMPage_from_kernel(addr2,1);
    return 0;
}
