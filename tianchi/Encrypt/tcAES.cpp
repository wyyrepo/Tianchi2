#include "tcAES.h"

#include "cryptopp/aes.h"

class TcAESPrivate
{
public:
    TcAESPrivate()
        : keyLength(CryptoPP::AES::MAX_KEYLENGTH)
    {}

    int                     keyLength;// = CryptoPP::AES::MAX_KEYLENGTH;
    CryptoPP::AESEncryption encryptor;
    CryptoPP::AESDecryption decryptor;
};

// *********************************************************************************************************************

TcAES::TcAES()
    : d_ptr(new TcAESPrivate())
{
    unsigned char key[CryptoPP::AES::DEFAULT_KEYLENGTH];
    for( int i=0; i<CryptoPP::AES::DEFAULT_KEYLENGTH; ++i )
    {
        key[i] = '0' + i;
    }
    d_func()->encryptor.SetKey(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    d_func()->decryptor.SetKey(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
}

TcAES::~TcAES()
{
    delete d_ptr;
}

void TcAES::setKey(const QByteArray& key)
{
    QByteArray password(CryptoPP::AES::MAX_KEYLENGTH, '\0');
    password.prepend(key);
    d_func()->keyLength = key.length() <= CryptoPP::AES::MIN_KEYLENGTH
            ? CryptoPP::AES::MIN_KEYLENGTH
            : CryptoPP::AES::MAX_KEYLENGTH;
    password.resize(d_func()->keyLength);
    d_func()->encryptor.SetKey((const byte*)password.data(), CryptoPP::AES::DEFAULT_KEYLENGTH);
    d_func()->decryptor.SetKey((const byte*)password.data(), CryptoPP::AES::DEFAULT_KEYLENGTH);
}

QByteArray TcAES::encryp(const QByteArray& data)
{
    QByteArray ret;
    QByteArray inputData = data;

    unsigned char* outBlock = new unsigned char[d_func()->keyLength];
    while(inputData.size() >= d_func()->keyLength)
    {
        QByteArray ba = inputData.left(d_func()->keyLength);
        inputData.remove(0, d_func()->keyLength);

        d_func()->encryptor.ProcessBlock((byte*)ba.data(), outBlock);
        ret.append((char*)outBlock, d_func()->keyLength);
    }
    if ( ! inputData.isEmpty() )
    {
        d_func()->encryptor.ProcessBlock((byte*)inputData.data(), outBlock);
        ret.append((char*)outBlock, d_func()->keyLength);
    }
    delete outBlock;
    return ret;
}

QByteArray TcAES::decryp(const QByteArray& data)
{
    QByteArray ret;
    QByteArray inputData = data;

    unsigned char* outBlock = new unsigned char[d_func()->keyLength];
    while(inputData.size() >= d_func()->keyLength)
    {
        QByteArray ba = inputData.left(d_func()->keyLength);
        inputData.remove(0, d_func()->keyLength);

        d_func()->decryptor.ProcessBlock((byte*)ba.data(), outBlock);
        ret.append((char*)outBlock, d_func()->keyLength);
    }
    if ( ! inputData.isEmpty() )
    {
        d_func()->decryptor.ProcessBlock((byte*)inputData.data(), outBlock);
        ret.append((char*)outBlock, d_func()->keyLength);
    }
    delete outBlock;
    return ret;
}




