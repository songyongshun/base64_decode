#include "assert.h"
#include "CEncryptBase64.h"
#include <iostream>
#include <string>
#include "myhex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//
// Construction/Destruction
//
const char EnBase64Tab[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; 
const char DeBase64Tab[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    62,                                                        // '+'
    0, 0, 0,
    63,                                                        // '/'
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61,                    // '0'-'9'
    0, 0, 0, 0, 0, 0, 0,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
    13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,        // 'A'-'Z'
    0, 0, 0, 0, 0, 0,
    26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
    39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,        // 'a'-'z'
};

CEncryptBase64::CEncryptBase64()
{

}

CEncryptBase64::~CEncryptBase64()
{

}

/*here 4 variables, */
int CEncryptBase64::Encode(const unsigned char* pSrc, char* pDst, int nSrcLen, int nMaxLineLen)
{
    unsigned char c1, c2, c3;    // ���뻺��������3���ֽ�
    int nDstLen = 0;             // ������ַ�����
    int nLineLen = 0;            // ������г��ȼ���
    int nDiv = nSrcLen / 3;      // �������ݳ��ȳ���3�õ��ı���
    int nMod = nSrcLen % 3;      // �������ݳ��ȳ���3�õ�������

    //std::cout << nDiv << std::endl;
    // error is in here!
    // ÿ��ȡ3���ֽڣ������4���ַ�
    for (int i = 0; i < nDiv; i ++)
    {
        // ȡ3���ֽ�
        c1 = *pSrc++;
        c2 = *pSrc++;
        c3 = *pSrc++;
        //std::cout << c1 << c2 << c3 << i << std::endl;
 
        // �����4���ַ�
        *pDst++ = EnBase64Tab[c1 >> 2];
        //int a = (c1 >> 2);
        //std::cout << a << std::endl;
        *pDst++ = EnBase64Tab[((c1 << 4) | (c2 >> 4)) & 0x3f];
        *pDst++ = EnBase64Tab[((c2 << 2) | (c3 >> 6)) & 0x3f];
        *pDst++ = EnBase64Tab[c3 & 0x3f];
        nLineLen += 4;
        nDstLen += 4;
        //std::cout << EnBase64Tab[c1 >> 2] << EnBase64Tab[((c1 << 4) | (c2 >> 4)) & 0x3f] << EnBase64Tab[((c2 << 2) | (c3 >> 6)) & 0x3f] << EnBase64Tab[c3 & 0x3f] << std::endl;
 
        // ������У�
        if (nLineLen > nMaxLineLen - 4)
        {
            *pDst++ = '\r';
            *pDst++ = '\n';
            nLineLen = 0;
            nDstLen += 2;
        }
    }
    //std::cout << "bb\n" << std::endl;
 
    // �������µ��ֽ�
    if (nMod == 1)
    {
        c1 = *pSrc++;
        *pDst++ = EnBase64Tab[(c1 & 0xfc) >> 2];
        *pDst++ = EnBase64Tab[((c1 & 0x03) << 4)];
        *pDst++ = '=';
        *pDst++ = '=';
        nLineLen += 4;
        nDstLen += 4;
    }
    else if (nMod == 2)
    {
        c1 = *pSrc++;
        c2 = *pSrc++;
        *pDst++ = EnBase64Tab[(c1 & 0xfc) >> 2];
        *pDst++ = EnBase64Tab[((c1 & 0x03) << 4) | ((c2 & 0xf0) >> 4)];
        *pDst++ = EnBase64Tab[((c2 & 0x0f) << 2)];
        *pDst++ = '=';
        nDstLen += 4;
    }
 
    // ����Ӹ�������
    *pDst = '\0';
 
    return nDstLen;
}
 
int CEncryptBase64::Decode(const char* pSrc, unsigned char* pDst, int nSrcLen)
{
    int nDstLen;            // ������ַ�����
    int nValue;             // �����õ��ĳ�����
    int i;
 
    i = 0;
    nDstLen = 0;

    // ȡ4���ַ������뵽һ�����������پ�����λ�õ�3���ֽ�
    while (i < nSrcLen)
    {
        // get the first one
        if (*pSrc != '\r' && *pSrc!='\n')
        {
            nValue = DeBase64Tab[*pSrc++] << 18;
            nValue += DeBase64Tab[*pSrc++] << 12;
            *pDst++ = (nValue & 0x00ff0000) >> 16;
            nDstLen++;
            std::cout << DecStrToHexStr(std::to_string((nValue & 0x00ff0000) >> 16));
            //std::cout << DecStrToHexStr((char*)((nValue & 0x00ff0000) >> 16)) << std::endl;
            
            if (*pSrc != '=')
            {
                nValue += DeBase64Tab[*pSrc++] << 6;
                *pDst++ = (nValue & 0x0000ff00) >> 8;
                nDstLen++;
                std::cout << DecStrToHexStr(std::to_string((nValue & 0x0000ff00) >> 8));
                //std::cout << DecStrToHexStr((char*)((nValue & 0x0000ff00) >> 8)) << std::endl;
 
                if (*pSrc != '=')
                {
                    nValue += DeBase64Tab[*pSrc++];
                    *pDst++ =nValue & 0x000000ff;
                    nDstLen++;
                    std::cout << DecStrToHexStr(std::to_string(nValue & 0x000000ff));
                    //std::cout << DecStrToHexStr((char*)(nValue & 0x000000ff)) << std::endl;
                    
                }
            }
            // next four chars!
            i += 4;
        }
        else        // �س����У�����
        {
            pSrc++;
            i++;
        }
     }
 
    // ����Ӹ�������
    *pDst = '\0'; 
    return nDstLen;
}

int CEncryptBase64::SafeDecode(const char* pSrc, int nSrcLen, unsigned char* pDst, int nDestLen)
{
    int nCurDstLen;            // ������ַ�����
    int nValue;             // �����õ��ĳ�����
    int i;

    i = 0;
    nCurDstLen = 0;

    // ȡ4���ַ������뵽һ�����������پ�����λ�õ�3���ֽ�
    while (i < nSrcLen)
    {
        if (*pSrc != '\r' && *pSrc!='\n' && *pSrc < (sizeof(DeBase64Tab)))
        {
            nValue = DeBase64Tab[*pSrc++] << 18;
            nValue += DeBase64Tab[*pSrc++] << 12;
            *pDst++ = (nValue & 0x00ff0000) >> 16;
            nCurDstLen++;
            assert(nCurDstLen<nDestLen);
            if(nCurDstLen >= nDestLen)
                break;

            if (*pSrc != '=')
            {
                nValue += DeBase64Tab[*pSrc++] << 6;
                *pDst++ = (nValue & 0x0000ff00) >> 8;
                nCurDstLen++;
                if(nCurDstLen >= nDestLen)
                    break;

                if (*pSrc != '=')
                {
                    nValue += DeBase64Tab[*pSrc++];
                    *pDst++ =nValue & 0x000000ff;
                    nCurDstLen++;
                    if(nCurDstLen >= nDestLen)
                        break;
                }
            }

            i += 4;
        }
        else        // �س����У�����
        {
            pSrc++;
            i++;
        }
    }

    // ����Ӹ�������
    if(nCurDstLen < nDestLen)
    *pDst = '\0'; 
    return nCurDstLen;
}
