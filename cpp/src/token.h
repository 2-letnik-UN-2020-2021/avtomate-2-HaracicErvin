//
// Created by Ervin on 25. 03. 2022.
//

#ifndef TASK_TOKEN_H
#define TASK_TOKEN_H


#include <string>
#include <iostream>
using namespace std;

class Token
{
private:
    string lexem;
    int column;
    int row;
    int token;
    bool eof;

public:
    Token(const string& aLexem, int aColumn, int aRow, int aToken, bool aEof) :
            lexem(aLexem), column(aColumn), row(aRow), token(aToken), eof(aEof) {
    }
    Token() : lexem("") {
    }
    const string getLexem() const {
        return lexem;
    }
    const int getRow() const {
        return row;
    }
    const int getColumn() const {
        return column;
    }
    const int getToken() const {
        return token;
    }
    const bool isEof() const {
        return eof;
    }//
    friend std::ostream& operator<<(std::ostream& out, const Token& aToken) {
        std::string token = "";
        switch (aToken.getToken()) {
            case 1:
            case 2:
                token = "variable";
                break;
            case 3:
            case 5:
            case 17:
            case 18:
            case 20:
            case 22:
            case 24:
            case 26:
            case 27:
            case 28:
            case 29:
                token = "float";
                break;
            case 6:
                token = "plus";
                break;
            case 7:
                token = "minus";
                break;
            case 8:
                token = "times";
                break;
            case 9:
                token = "divide";
                break;
            case 10:
                token = "pow";
                break;
            case 11:
                token = "rparen";
                break;
            case 12:
                token = "lparen";
                break;
            case 15:
                token = "assign";
                break;
            case 16:
                token = "semi";
                break;
            case 19:
                token = "for";
                break;
            case 21:
                token = "to";
                break;
            case 23:
                token = "do";
                break;
            case 25:
                token = "done";
                break;
            case 30:
                token = "write";
                break;

        }
        if (aToken.getToken() != 0 && aToken.getToken()!=13)
            out << token << "(\""  << aToken.getLexem() << "\") " ;
        return out;
    }
};



#endif //TASK_TOKEN_H
