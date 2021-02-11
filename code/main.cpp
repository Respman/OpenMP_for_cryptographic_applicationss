#include <vector>
#include <cstdio>
#include <cstring>
#include <stdint.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include "to_bytes.h"
#include "brute.h"
#include "defines.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#include <omp.h>

using namespace std;

uint8_t buf[BUF_SIZE];
uint8_t salt[SALT_LEN];
uint32_t rounds_num; 
uint8_t iv[IV_LEN]; 
uint8_t enc_data[ENC_LEN+1]; 
FILE* f_log;

struct struct_password {
	uint8_t passw[8];
    uint8_t tmp;
}__attribute__((packed));


int main (void){
	int fd;
    long long int i;
	struct stat st;
	char* ptr;
    int ctr = 0;
    ostringstream stream;

//make log file
    f_log = fopen("./log.txt", "w");

//parsing data
    char data[] = "4B4B5330313701000000140000004CB213E6352856C414D74B8F7C238680D5074A9F30000000DD59AC338EA1ECB99E91FEB71C13F2FF709F85E8334EF430168DD8274ADEAD1992DC5AF12CFB3D48470B2D12118F5F3F269B5EDB91362AA2A109D680A87B9F7197A94F5BFE25A7854AF47DF5BED7BF351DA543957C5E988814196A7C52096D7090BA2C97491DC93D8A623FAC725CA5E7F4260D13" ;

    if (to_bytes(data, buf))
		return ERR_PARSE_DATA ;
	 
	memcpy(salt, buf + BLOCK_START, SALT_LEN) ; 
    rounds_num = *((uint32_t*)(buf + BLOCK_START + SALT_LEN)) ;
	memcpy(iv, buf + BLOCK_START + HEADER_LEN, IV_LEN) ;
    memcpy(enc_data, buf + BLOCK_START + HEADER_LEN + IV_LEN, ENC_LEN) ;
    enc_data[ENC_LEN] = '\0';

//open all files with keys consistently

    for (ctr=0; ctr<NUMBER_OF_FILES; ctr++){
        stream.str("");
        stream << ctr;
        string cstr = "./keys/file"+stream.str()+".txt";
        char *name = new char[cstr.length() + 1];
        strcpy(name, cstr.c_str());
    	
        fd = open(name,O_RDWR);
        if (fd == -1){
            fprintf(f_log, "[-] can't open %s\n", cstr.c_str());
            fclose(f_log);
            return 1;
        }

//mmaping currnet file with keys

        fstat (fd, &st);//sizeof_file
        ptr = (char*)mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
	    if ((long int)ptr == -1){
            fprintf(f_log, "[-] mmap failed for file %s\n", cstr.c_str());
            fclose(f_log);
            return 1;
        }

        long long int amount_keys = st.st_size/9;
        struct struct_password* all_pass;
        all_pass = (struct_password*) ptr;

        #pragma omp parallel for
        for (i = 0; i < amount_keys; i++){
            brute((char*)all_pass[i].passw);
        }
		
        munmap(ptr, st.st_size);
    	close(fd);
        fprintf(f_log, "[+] end with %s\n", cstr.c_str());
        free(name);

        if ((ctr % 100) == 0){
            cout<<"ctr = "<< ctr <<endl;
        }
    }
    
    fclose(f_log);
    return 0;
}
