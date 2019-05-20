#ifndef INTER_H
#define INTER_H

#include "lexer.h"
#include <vector>

namespace Inter
{

class Stmt
{
public:
    Stmt();
    virtual ~Stmt();
    virtual std::string gen();
};

class Expr
{
public:
    Expr(CompLexer::Token *op);
    virtual ~Expr();
    virtual double calc(double *arg);
    CompLexer::Token *m_op;
};

class Id : public Expr
{
public:
    Id(CompLexer::Token *w, unsigned long d);
    virtual ~Id();
    virtual double calc(double *arg);
private:
    unsigned long m_offset;
};

class Constant : public Expr
{
public:
    Constant(CompLexer::Token *op);
    virtual ~Constant();
    virtual double calc(double *);
private:
    double m_val;
};

class Op : public Expr
{
public:
    Op(CompLexer::Token *op);
    virtual ~Op();
};

class Unary : public Op
{
public:
    Unary(CompLexer::Token *op, Expr *expr);
    virtual ~Unary();
    virtual double calc(double *arg);
private:
    Expr *m_expr;
};

class Arith : public Op
{
public:
    Arith(CompLexer::Token *op, Expr *lexpr, Expr *rexpr);
    virtual ~Arith();
    virtual double calc(double *arg);
private:
    Expr *m_lexpr;
    Expr *m_rexpr;
};

class Call : public Op
{
public:
    Call(CompLexer::Token *op, std::vector<Expr *> &args);
    virtual ~Call();
    virtual double calc(double *arg);
private:
    std::vector<Expr *> m_args;
};

}
#endif // INTER_H



















