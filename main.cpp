#include<iostream>
#include<fstream>
#include"virtualcpu.hpp"

bool Memory::read_file(char *filename) {
    std::fstream file;
    file.open(filename,std::ios::binary);
    if(file.is_open()){
        return false;
    }
    size_t size = file.tellg();
    uint16_t *buffer;
    buffer = (uint16_t *)malloc(size+1);
    file.read((char *)buffer,size);
    file.close();
    memcpy((void*)memory,buffer,size+1);
    return true;
}

int main(int argc, char **argv) {
    if(argc < 2){

    }
    Memory *memory = new Memory();
    
    memory->read_file(argv[1]);

    VirtualCpu vcpu;

    for(;;){
        

    }

}
