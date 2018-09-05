#include "tcRSA.h"

#include "cryptopp/rsa.h"
#include "cryptopp/hex.h"
#include "cryptopp/randpool.h"
#include "cryptopp/files.h"

#include <QUuid>

class TcRSAPrivate
{
public:
    TcRSAPrivate()
    {}

    static CryptoPP::RandomPool randomPool;

    QByteArray  privKey;
    QByteArray  pubKey;
};

CryptoPP::RandomPool TcRSAPrivate::randomPool;

// *********************************************************************************************************************

TcRSA::TcRSA()
    : d_ptr(new TcRSAPrivate())
{
}

TcRSA::~TcRSA()
{
    delete d_ptr;
}

QByteArray TcRSA::privateKey()
{
    return d_ptr->privKey;
}

QByteArray TcRSA::publicKey()
{
    return d_ptr->pubKey;
}

void TcRSA::setKey(const QByteArray& privKey, const QByteArray& pubKey)
{
    d_ptr->privKey = privKey;
    d_ptr->pubKey  = pubKey;
}

void TcRSA::GenerateKey(unsigned int KeyLength)
{
    QByteArray uuidSeed = QUuid::createUuid().toByteArray();
    uuidSeed.replace("{", "");
    uuidSeed.replace("-", "");
    uuidSeed.replace("}", "");

    CryptoPP::RandomPool randPool;
    randPool.IncorporateEntropy((byte*)uuidSeed.constData(), uuidSeed.length());

    std::string key;
    //generate private key
    CryptoPP::RSAES_OAEP_SHA_Decryptor priv(randPool, KeyLength);
    CryptoPP::HexEncoder PrivateEncoder(new CryptoPP::StringSink(key));
    d_ptr->privKey = QByteArray::fromStdString(key);
    priv.DEREncode(PrivateEncoder);
    PrivateEncoder.MessageEnd();

    //generate public key using private key
    CryptoPP::RSAES_OAEP_SHA_Encryptor pub(priv);
    CryptoPP::HexEncoder PublicEncoder(new CryptoPP::StringSink(key));
    d_ptr->pubKey = QByteArray::fromStdString(key);
    pub.DEREncode(PublicEncoder);
    PublicEncoder.MessageEnd();
}

QByteArray TcRSA::encryp(const QByteArray& data)
{
    QByteArray  ret;

    CryptoPP::StringSource publicKey(d_ptr->pubKey.toStdString(), true, new CryptoPP::HexDecoder());
    CryptoPP::RSAES_OAEP_SHA_Encryptor pub(publicKey);

    QByteArray uuidSeed = QUuid::createUuid().toByteArray();
    uuidSeed.replace("{", "");
    uuidSeed.replace("-", "");
    uuidSeed.replace("}", "");

    CryptoPP::RandomPool randPool;
    randPool.IncorporateEntropy((byte*)uuidSeed.constData(), uuidSeed.length());

    int MaxMsgLength = pub.FixedMaxPlaintextLength();
    for( int i = data.size(), j=0; i > 0; i -= MaxMsgLength, j += MaxMsgLength )
    {
        string PartPlaintext = data.mid(j, MaxMsgLength).toStdString();
        string PartCiphertext;
        CryptoPP::StringSource(PartPlaintext, true,
                               new CryptoPP::PK_EncryptorFilter(
                                   randPool, pub,
                                   new CryptoPP::HexEncoder(new CryptoPP::StringSink(PartCiphertext))));
        ret.append(QByteArray::fromStdString(PartCiphertext));
    }
    return ret;
}

QByteArray TcRSA::decryp(const QByteArray& data)
{
    QByteArray  ret;

    CryptoPP::StringSource privateKey(d_ptr->privKey.toStdString(), true, new CryptoPP::HexDecoder());
    CryptoPP::RSAES_OAEP_SHA_Decryptor priv(privateKey);

    int CiphertextLength = priv.FixedCiphertextLength() * 2;
    for (int i = data.size(), j=0; i > 0; i -= CiphertextLength, j += CiphertextLength)
    {
        string PartCiphertext = data.mid(j, CiphertextLength).toStdString();
        string PartPlaintext;
        CryptoPP::StringSource(PartCiphertext, true,
                               new CryptoPP::HexDecoder(
                                   new CryptoPP::PK_DecryptorFilter(d_ptr->randomPool, priv,
                                                                    new CryptoPP::StringSink(PartPlaintext))));
        ret.append(QByteArray::fromStdString(PartPlaintext));
    }
    return ret;
}


