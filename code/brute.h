#include "defines.h"
#include "is_printable.h"

#include <iomanip>

#include <crypto++/aes.h>
#include <crypto++/modes.h>
#include <crypto++/filters.h>

#include <iostream>

using namespace std;
using namespace CryptoPP;

void decrypt(string ciphertext, unsigned char *key,
            unsigned char *iv, string* plaintext)
{
    CryptoPP::AES::Decryption aesDecryption(key, KEY_LEN);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( (*plaintext) ), StreamTransformationFilter::ZEROS_PADDING);
    stfDecryptor.Put( reinterpret_cast<const unsigned char*>( ciphertext.c_str() ), ciphertext.size() );
    stfDecryptor.MessageEnd();
}


int brute (char* password)
{

    uint8_t key[KEY_LEN] ;		
    string decrypted = "";
	uint8_t hash[DIGEST_LEN] ; 
	uint8_t buf[HEADER_LEN + ENC_LEN] ; 
    int decrypted_len ;
	string enc = "";

	for (int i = 0; i < (ENC_LEN); i++){
		enc += enc_data[i];
	}

	string passwd = "";
	for (int i = 0; i < PASS_LEN; i++){
		passwd += password[i];
	}

	if (!PKCS5_PBKDF2_HMAC_SHA1(password, PASS_LEN, salt, SALT_LEN, rounds_num, KEY_LEN, key))
	{
		fprintf(f_log, "[-] PBKDF ERROR! %s\n", passwd.c_str()) ;
		return ERR_KEY_DERIVE ;
	}

    decrypt(enc, key, iv, &decrypted);

    if (is_printable(decrypted) > 1){
		fprintf(f_log, "[!!!] CORRECT PASSWORD: %s\n", passwd.c_str());
		
		printf("password: %s\n", passwd.c_str()) ;

		cout << "decrypted text: "<<decrypted<<endl;
	}
	
	return 0 ;
}
