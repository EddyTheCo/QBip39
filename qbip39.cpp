#include"crypto/qbip39.hpp"
#include <QPasswordDigestor>


namespace qcrypto
{
QByteArray Mnemonic::getSeed(const QString& passphrase) const
{
    const auto data=m_words.join(" ").toUtf8();
    const auto salt=QString("mnemonic"+passphrase).toUtf8();
    return QPasswordDigestor::deriveKeyPbkdf2(
        QCryptographicHash::Sha512,
        data,
        salt,
        2048,
        64);
}

}
