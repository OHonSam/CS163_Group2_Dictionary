#ifndef WORD_H
#define WORD_H

#include <string>
#include <vector>

namespace POS
{
    enum Type
    {
        Noun            = 1 << 0,
        Verb            = 1 << 1,
        Adjective       = 1 << 2,
        Adverb          = 1 << 3,
        Pronoun         = 1 << 4,
        Preposition     = 1 << 5,
        Conjunction     = 1 << 6,
        Interjection    = 1 << 7,
        Other           = 1 << 8,
        Count           = 9
    };

    const std::string TypeString[] = {
        "Noun",
        "Verb",
        "Adjective",
        "Adverb",
        "Pronoun",
        "Preposition",
        "Conjunction",
        "Interjection",
        "Other"
    };

    const std::string TypeStringViet[] = {
        "danh tu",
        "dong tu",
        "tinh tu",
        "trang tu",
        "dai tu",
        "giap tu",
        "lien tu",
        "thanh tu",
        "khac"
    };

    const std::string TypeStringVE[] = {
        "noun",
        "verb",
        "adj",
        "adverb",
        "pronoun",
        "prep",
        "conj",
        "interj",
        "other"
    };

    const std::string TypeShort[] = {
        "n.",
        "v.",
        "adj.",
        "adv.",
        "pron.",
        "prep.",
        "conj.",
        "interj.",
        "Other"
    };

    unsigned int getIndex(unsigned int type);
    unsigned int getType(const std::string& str);
    unsigned int getTypeViet(const std::string& str);
    unsigned int getTypeVE(const std::string& str);
    std::string getTypeString(unsigned int type);
}

struct Word
{
    std::string word;
    unsigned int type;
    std::vector<std::string> def[POS::Count];

    Word();
    Word(const std::string& word);
    Word(const std::string& word, unsigned int type);
    Word(const std::string& word, unsigned int type, const std::string& def);

    bool checkDef(const std::string& def);
    std::string getRandDef();
};

#endif // WORD_H