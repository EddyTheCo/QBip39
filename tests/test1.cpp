#include"crypto/qbip39.hpp"

#include<QDebug>
#undef NDEBUG
#include <assert.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

using namespace qcrypto;

int main(int argc, char** argv)
{

    QFile file("tests/vectors.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file";
    }
    QJsonDocument doc=QJsonDocument::fromJson(file.readAll());
    QJsonObject root_obj = doc.object();

    auto english_vectors=root_obj.value("english").toArray();

    for(const auto v:english_vectors)
    {
        auto test=v.toArray();
        auto entropy=QByteArray::fromHex(test.at(0).toString().toUtf8());
        const auto mnemonic=Mnemonic(entropy);
        const auto str=mnemonic.m_words.join(QChar::Space);
        qDebug()<<"sentence:"<<str;
        assert(str==test.at(1).toString());
        const auto seed=mnemonic.getSeed("TREZOR").toHex();
        qDebug()<<"seed:"<<seed;
        assert(seed==test.at(2).toString());

    }

	return 0;
}
