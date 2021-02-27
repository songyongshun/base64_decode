class CEncryptBase64  
{
public:
    CEncryptBase64();
    virtual ~CEncryptBase64();

    int Encode(const unsigned char* pSrc, char* pDst, int nSrcLen, int nMaxLineLen);
    int Decode(const char* pSrc, unsigned char* pDst, int nSrcLen);
    int SafeDecode(const char* pSrc, int nSrcLen, unsigned char* pDst, int nDestLen);
};

