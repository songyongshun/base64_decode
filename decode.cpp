#include "assert.h"
#include "EncryptBase64.h" 
#include <iostream>
#include <string>
using namespace std;

int length(const char *s)  
{  
    int i=0;
    while(*s!='\0')
    {  
        i++;   
        s++;  
    }  
    return i;  
}

int main()
{   
    const char* pSrc = (const char*)"1+mwscvh0N64xLjlvLCyubPktcTKtdHpyv2+3Q==";
    //const char* pSrc = (const char*)"TWFu";
    
    unsigned char* pDst=(unsigned char*)malloc(sizeof(char));
    int nSrcLen;
    nSrcLen = length(pSrc);
    int nMaxLineLen = 100;

    CEncryptBase64 s1;

    //s1.Encode(pSrc, pDst, nSrcLen, nMaxLineLen);
    // todo: here should minus the number of "=";
    cout << "the input length is: " << nSrcLen << endl;
    cout << "the original bits is: ";
    //int CEncryptBase64::Decode(const char* pSrc, unsigned char* pDst, int nSrcLen)
    s1.Decode(pSrc, pDst, nSrcLen);
    cout << endl << "the original gbk word is: " << pDst << endl;
}
