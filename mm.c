#include<stdio.h>
#include<memory.h>
#include<unistd.h>    //for getpagesize()
#include<sys/mman.h>  //for mmap() and munmap()

//static vm_page_for_families_t *first_vm_page_for_families = NULL;
static size_t SYSTEM_PAGE_SIZE = 0;

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

int main(int argc, char **argv){
    mm_init();
    
    printf("VM Page Size = %lu bytes\n", SYSTEM_PAGE_SIZE);
    void *addr1 = allocateVMPage_from_kernel(1);
    void *addr2 = allocateVMPage_from_kernel(1);
    deallocateVMPage_from_kernel(addr1,1);
    deallocateVMPage_from_kernel(addr2,1);
    return 0;
}
