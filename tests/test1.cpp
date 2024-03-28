#include"crypto/qbip39.hpp"

#include<QDebug>
#undef NDEBUG
#include <assert.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

using namespace qcrypto;

template <Language Tlg>
void testLanguage(const QJsonArray & vectors)
{
    for(const auto v:vectors)
    {
        auto test=v.toArray();
        auto entropy=QByteArray::fromHex(test.at(0).toString().toUtf8());
        const auto mnemonic=Mnemonic<Tlg>(entropy);
        const auto str=mnemonic.m_words.join((Tlg==Language::Ja)?"\u3000":" ");
        qDebug()<<"from lib:\t"<<str;
        qDebug()<<"from vector:\t"<<test.at(1).toString();
        assert(str==test.at(1).toString());
        const auto seed=mnemonic.getSeed("TREZOR").toHex();
        qDebug()<<"from lib:\t"<<seed;
        qDebug()<<"from vector:\t"<<test.at(2).toString();
        assert(seed==test.at(2).toString());

    }
}

int main(int argc, char** argv)
{

    QFile file("vectors.json");
    assert(file.open(QIODevice::ReadOnly | QIODevice::Text));

    QJsonDocument doc=QJsonDocument::fromJson(file.readAll());
    QJsonObject root_obj = doc.object();


    auto englishVectors=root_obj.value("english").toArray();

    testLanguage<Language::En>(englishVectors);

    const auto spanishVectors=root_obj.value("spanish").toArray();

    testLanguage<Language::Es>(spanishVectors);

    const auto itlianVectors=root_obj.value("italian").toArray();

    testLanguage<Language::It>(itlianVectors);

    const auto japaneseVectors=root_obj.value("japanese").toArray();

    testLanguage<Language::Ja>(japaneseVectors);

    const auto koreanVectors=root_obj.value("korean").toArray();

    testLanguage<Language::Ko>(koreanVectors);

	return 0;
}
