#pragma once
/**
 *  https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki
 *
 **/

#include <QRandomGenerator>
#include<QIODevice>
#include<QDataStream>
#include<QCryptographicHash>
#include <QPasswordDigestor>

#include"crypto/dictionaries.hpp"

namespace qcrypto
{

using namespace qwords;

enum Security:quint8
{
    veryLow,
    low,
    medium,
    high,
    veryHigh
};

template<Language Tlg=Language::en>
class Mnemonic
{

public:
    const QStringList m_words;
    bool isValid()const{return !m_words.isEmpty();}


    Mnemonic(Security Tsec=Security::veryHigh):m_words(getWords(getRandomEntropy(Tsec))){};


    Mnemonic(QByteArray entropy):m_words(getWords(entropy)){};
    Mnemonic(QStringList words):m_words(checkWords(words)){};

    QByteArray getSeed(const QString& passphrase="") const
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
private:

    static QByteArray getRandomEntropy(Security sec)
    {
        QByteArray var;
        auto buffer=QDataStream(&var,QIODevice::WriteOnly | QIODevice::Append);
        for(auto i=0;i<sec+4;i++)
        {
            quint32 value = QRandomGenerator::global()->generate();
            buffer<<value;
        }
        return var;
    }
    QStringList checkWords(const QStringList& list)const
    {
        QStringList var;
        const auto MS=list.size();
        if(MS!=12&&MS!=15&&MS!=18&&MS!=21&&MS!=24)
            return var;
        const Dictionary<Tlg> dictionary;
        for(const auto& str:list)
        {
            if(!dictionary.contains(str))
                return var;
        }
        var=list;
        return var;

    }
    QStringList getWords(QByteArray entropy)const
    {
        QStringList var;
        const quint8 size=entropy.size();
        const size_t ENT=size*8;
        const size_t CS=ENT/32;
        const size_t MS=(ENT+CS)/11;

        if(ENT!=128&&ENT!=160&&ENT!=192&&ENT!=224&&ENT!=256)
            return var;

        const Dictionary<Tlg> dictionary;

        auto hash=QCryptographicHash::hash(entropy, QCryptographicHash::Sha256);
        auto catenation=entropy.append(hash.at(0));


        quint16 rest=0;
        quint8 need=11;

        for(auto i=0;i<MS;i++)
        {
            quint16 index;
            auto catbuffer=QDataStream(&catenation,QIODevice::ReadOnly);
            catbuffer.setByteOrder(QDataStream::BigEndian);

            if(catenation.size()<2)
            {
                index=quint16(catenation.front());
                index=index<<8;
            }
            else
            {
                catbuffer>>index;
            }

            if(need>8)
            {
                catenation.removeFirst();
                catenation.removeFirst();
            }
            else
            {
                catenation.removeFirst();
            }

            const quint16 newindex=(index>>(16-need))|rest;

            rest=(index<<(need));
            rest=rest>>need;
            if(need<=8)rest=rest>>8;


            need=11-((need>8)?16:8)+need;
            rest=rest<<need;

            index=newindex;

            var.append(dictionary.at(index));
        }
        return var;
    }

};

};
