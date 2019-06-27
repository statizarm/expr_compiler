#ifndef LINKER_INTER_H_
#define LINKER_INTER_H_

#include <string>
#include "comp/cpp/include/lexer.h"

namespace LinkerObject
{
    class SymTable;
}

namespace LinkerInter
{

class Code
{
public:
    Code();
    virtual ~Code();
    virtual const std::string gen() const;
    virtual const Code *reduce(LinkerObject::SymTable *sym,
                               int16_t offset) const;
    virtual size_t size() const;
};

class ByteCode : public Code
{
public:
    ByteCode(const std::string &bytes);
    virtual ~ByteCode();
    virtual const std::string gen() const;
    virtual const Code *reduce(LinkerObject::SymTable *sym,
                               int16_t offset) const;
    virtual size_t size() const;
private:
    const std::string m_bytes;
};

class Sym : public Code
{
public:
    Sym(const CompLexer::Token *tok);
    virtual ~Sym();
    virtual const std::string gen() const;
    virtual const Code *reduce(LinkerObject::SymTable *sym,
                               int16_t offset) const;
    const CompLexer::Token *tok() const;
    virtual size_t size() const;
protected:
    const CompLexer::Token *m_tok;
};

class SymCode : public Code
{
public:
    SymCode(const Code *code, const Sym *sym);
    virtual ~SymCode();
    virtual const std::string gen() const;
    virtual const Code *reduce(LinkerObject::SymTable *sym,
                               int16_t offset) const;
    virtual size_t size() const;
private:
    const Code *m_code;
    const Sym *m_sym;
};

class CodeSeq : public Code
{
public:
    CodeSeq(const Code *pref_code, const Code *post_code);
    virtual ~CodeSeq();
    virtual const std::string gen() const;
    virtual const Code *reduce(LinkerObject::SymTable *sym,
                               int16_t offset) const;
    virtual size_t size() const;
protected:
    const Code *m_pref_code;
    const Code *m_post_code;
};

class CodeTmpSeq : public CodeSeq
{
public:
    CodeTmpSeq(const Code *pref_code,
               const Code *post_code);
    virtual ~CodeTmpSeq();
    virtual const Code *reduce(LinkerObject::SymTable *symtab,
                               int16_t offset) const;
};

}


#endif // LINKER_INTER_H_
