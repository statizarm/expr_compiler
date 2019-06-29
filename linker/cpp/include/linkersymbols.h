#ifndef LIKER_INTER_H_
#define LIKER_INTER_H_
#include "linkerinter.h"
#include "cont/cpp/include/containers.h"


namespace LinkerSymbols {

enum SymTag
{
    DEFINED, UNDEFINED
};

class SymLink : public LinkerInter::Sym
{
public:
    SymLink(const std::string &tok,
            SymTag tag = SymTag::UNDEFINED);
    virtual ~SymLink();
    virtual int16_t offset() const;
    SymTag tag() const;
private:
    const SymTag m_tag;
};

class DefinedSymLink : public SymLink
{
public:
    DefinedSymLink(const std::string &tok, int16_t offset);
    virtual ~DefinedSymLink();
    virtual int16_t offset() const;
private:
    const int16_t m_offset;
};


class Env
{
public:
    Env();
    ~Env();
    const LinkerInter::Sym *get(const CompLexer::Token *tok) const;
    void set(const CompLexer::Token *tok,
                       const LinkerInter::Sym *sym);
private:
    Containers::Table<const LinkerInter::Sym> *m_tab;
};


}

#endif // LIKER_INTER_H_
