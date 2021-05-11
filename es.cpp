#include "ofp.h"

#include <openssl/aes.h>
#include <openssl/des.h>

#include <openssl/rsa.h>  
#include<openssl/pem.h>  
#include<openssl/err.h>  
#include <openssl/bio.h> 

#pragma comment(lib,"libeay32MT.lib")

#include <vector>

std::string aes_encrypt(const std::string& clearText, const std::string& _key)
{
	if (_key.length() != 16 && _key.length() != 24 && _key.length() != 32)
	{
		printf("invalid key");
		return "";
	}
	std::string cipherText;

	AES_KEY aes;
	int result = AES_set_encrypt_key((unsigned char*)_key.c_str(), 128, &aes);
	if (result < 0)
		return "";

	std::vector<unsigned char> vecCiphertext;
	unsigned char inputText[AES_BLOCK_SIZE] = { 0 };
	unsigned char outputText[AES_BLOCK_SIZE] = { 0 };

	for (int i = 0; i < clearText.length() / AES_BLOCK_SIZE; i++)
	{
		memcpy(inputText, clearText.c_str() + i * AES_BLOCK_SIZE, AES_BLOCK_SIZE);
		AES_ecb_encrypt(inputText, outputText, &aes, AES_ENCRYPT);

		for (int j = 0; j < AES_BLOCK_SIZE; j++)
			vecCiphertext.push_back(outputText[j]);
	}

	int n = clearText.length() % AES_BLOCK_SIZE;

	if (n != 0)
	{
		int tmp1 = clearText.length() / AES_BLOCK_SIZE * AES_BLOCK_SIZE;
		int tmp2 = clearText.length() - tmp1;

		memset(inputText, AES_BLOCK_SIZE - tmp2, AES_BLOCK_SIZE);  	//
		memcpy(inputText, clearText.c_str() + tmp1, tmp2);

		//
		AES_ecb_encrypt(inputText, outputText, &aes, AES_ENCRYPT);

		for (int j = 0; j < AES_BLOCK_SIZE; j++)
			vecCiphertext.push_back(outputText[j]);
	}
	else
	{
		//
		memset(inputText, AES_BLOCK_SIZE, AES_BLOCK_SIZE);
		AES_ecb_encrypt(inputText, outputText, &aes, AES_ENCRYPT);

		for (int j = 0; j < AES_BLOCK_SIZE; j++)
			vecCiphertext.push_back(outputText[j]);
	}

	cipherText.clear();
	cipherText.assign(vecCiphertext.begin(), vecCiphertext.end());

	return cipherText;
}


std::string aes_encrypt_cfb(const std::string& clearText, const std::string& _key, const std::string& _iv)
{
	if (_key.length() != 16 && _key.length() != 24 && _key.length() != 32)
	{
		printf("invalid key");
		return "";
	}
	std::string cipherText; //  
	unsigned char iv[AES_BLOCK_SIZE] = { 0 };

	if (_iv.length() != AES_BLOCK_SIZE)
	{
		printf("invalid iv");
		return "";
	}
	for (int i = 0; i < AES_BLOCK_SIZE; i++)
	{
		iv[i] = _iv[i];
	}

	AES_KEY aes;
	int result = AES_set_encrypt_key((unsigned char*)_key.c_str(), 128, &aes);//
	if (result < 0)
		return "";

	std::vector<unsigned char> vecCiphertext;
	unsigned char inputText[AES_BLOCK_SIZE] = { 0 };
	unsigned char outputText[AES_BLOCK_SIZE] = { 0 };

	for (int i = 0; i < clearText.length() / AES_BLOCK_SIZE; i++)
	{
		memcpy(inputText, clearText.c_str() + i * AES_BLOCK_SIZE, AES_BLOCK_SIZE);
	//	AES_ecb_encrypt(inputText, outputText, &aes, AES_ENCRYPT);

		int num = 0;
		AES_cfb128_encrypt(inputText, outputText, AES_BLOCK_SIZE,&aes, iv, &num, AES_DECRYPT);

		for (int j = 0; j < AES_BLOCK_SIZE; j++)
			vecCiphertext.push_back(outputText[j]);
	}

	/*
	int n = clearText.length() % AES_BLOCK_SIZE;

	if (n != 0)
	{
		int tmp1 = clearText.length() / AES_BLOCK_SIZE * AES_BLOCK_SIZE;
		int tmp2 = clearText.length() - tmp1;

		memset(inputText, AES_BLOCK_SIZE - tmp2, AES_BLOCK_SIZE);  	//
		memcpy(inputText, clearText.c_str() + tmp1, tmp2);

		//
	//	AES_ecb_encrypt(inputText, outputText, &aes, AES_ENCRYPT);
		AES_cbc_encrypt(inputText, outputText, AES_BLOCK_SIZE, &aes, iv, AES_ENCRYPT);

		for (int j = 0; j < AES_BLOCK_SIZE; j++)
			vecCiphertext.push_back(outputText[j]);
	}
	else
	{
		//
		memset(inputText, AES_BLOCK_SIZE, AES_BLOCK_SIZE);
		AES_ecb_encrypt(inputText, outputText, &aes, AES_ENCRYPT);

		for (int j = 0; j < AES_BLOCK_SIZE; j++)
			vecCiphertext.push_back(outputText[j]);
	}
	*/
	cipherText.clear();
	cipherText.assign(vecCiphertext.begin(), vecCiphertext.end());

	return cipherText;
}


std::string aes_encrypt_cbc(const std::string& clearText, const std::string& _key, const std::string& _iv)
{
	if (_key.length() != 16 && _key.length() != 24 && _key.length() != 32)
	{
		printf("invalid key");
		return "";
	}
	std::string cipherText;
	unsigned char iv[AES_BLOCK_SIZE] = { 0 };

	if (_iv.length() != AES_BLOCK_SIZE)
	{
		printf("invalid iv");
		return "";
	}
	for (int i = 0; i < AES_BLOCK_SIZE; i++)
	{
		iv[i] = _iv[i];
	}

	AES_KEY aes;
	int result = AES_set_encrypt_key((unsigned char*)_key.c_str(), 128, &aes);
	if (result < 0)
		return "";

	std::vector<unsigned char> vecCiphertext;
	unsigned char inputText[AES_BLOCK_SIZE] = { 0 };
	unsigned char outputText[AES_BLOCK_SIZE] = { 0 };

	for (int i = 0; i < clearText.length() / AES_BLOCK_SIZE; i++)
	{
		memcpy(inputText, clearText.c_str() + i * AES_BLOCK_SIZE, AES_BLOCK_SIZE);
	//	AES_ecb_encrypt(inputText, outputText, &aes, AES_ENCRYPT);

		AES_cbc_encrypt(inputText, outputText, AES_BLOCK_SIZE,&aes, iv, AES_ENCRYPT);

		for (int j = 0; j < AES_BLOCK_SIZE; j++)
			vecCiphertext.push_back(outputText[j]);
	}

	int n = clearText.length() % AES_BLOCK_SIZE;

	if (n != 0)
	{
		int tmp1 = clearText.length() / AES_BLOCK_SIZE * AES_BLOCK_SIZE;
		int tmp2 = clearText.length() - tmp1;

		memset(inputText, AES_BLOCK_SIZE - tmp2, AES_BLOCK_SIZE); 
		memcpy(inputText, clearText.c_str() + tmp1, tmp2);

	//	AES_ecb_encrypt(inputText, outputText, &aes, AES_ENCRYPT);
		AES_cbc_encrypt(inputText, outputText, AES_BLOCK_SIZE, &aes, iv, AES_ENCRYPT);

		for (int j = 0; j < AES_BLOCK_SIZE; j++)
			vecCiphertext.push_back(outputText[j]);
	}
	else
	{
		memset(inputText, AES_BLOCK_SIZE, AES_BLOCK_SIZE);
		AES_ecb_encrypt(inputText, outputText, &aes, AES_ENCRYPT);

		for (int j = 0; j < AES_BLOCK_SIZE; j++)
			vecCiphertext.push_back(outputText[j]);
	}

	cipherText.clear();
	cipherText.assign(vecCiphertext.begin(), vecCiphertext.end());

	return cipherText;
}
