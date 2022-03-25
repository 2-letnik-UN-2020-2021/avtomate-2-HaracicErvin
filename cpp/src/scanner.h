#ifndef TASK_SCANNER_H
#define TASK_SCANNER_H
#include <string>
#include <iostream>
#include "token.h"

using namespace std;

class Scanner
{//
private:
    istream* input;
    Token lastToken;
    int row;
    int column;
    const static int maxState = 31;
    const static int startState = 0;
    const static int noEdge = -1;
    int automata[maxState + 1][256];
    int finite[maxState + 1];

    void initAutomata() {

        for (int i = 0; i <= maxState; i++) {
            for (int j = 0; j < 256; j++) {
                automata[i][j] = noEdge;
            }
        }

        finite[0] = 0;

        finite[1] = 1;  //variable
        finite[2] = 2;  //variable

        finite[3] = 3;  //float
        finite[4] = -4;  //float (ni koncno stanje)
        finite[5] = 5;  //float

        finite[6] = 6;      //+
        finite[7] = 7;      //-
        finite[8] = 8;      //*
        finite[9] = 9;      // /
        finite[10] = 10;    // ^
        finite[11] = 11;    //)
        finite[12] = 12;    //(

        finite[13] = 0;     //space

        //----------NEOBVEZNA-----------------//

        finite[14] = 14;    //:
        finite[15] = 15;    // =
        finite[16] = 16;    // ;

        finite[17] = 17;    //f
        finite[18] = 18;    //o
        finite[19] = 19;    //r

        finite[20] = 20;    //t
        finite[21] = 21;    //o

        finite[22] = 22;    //d
        finite[23] = 23;    //o
        finite[24] = 24;    //n
        finite[25] = 25;    //e

        finite[26] = 26;    //w
        finite[27] = 27;    //r
        finite[28] = 28;    //i
        finite[29] = 29;    //t
        finite[30] = 30;    //e


        //Velike crke
        for (int j = 'A'; j <= 'Z'; j++) {
            automata[0][j] = 1;
            automata[1][j] = 1;
            automata[2][j] = 2;

            //----------NEOBVEZNA-----------------//
            automata[16][j] = 2;
            automata[17][j] = 2;
            automata[18][j] = 2;
            automata[19][j] = 2;
            automata[20][j] = 2;
            automata[21][j] = 2;
            automata[22][j] = 2;
            automata[23][j] = 2;
            automata[24][j] = 2;
            automata[25][j] = 2;
            automata[26][j] = 2;
            automata[27][j] = 2;
            automata[28][j] = 2;
            automata[29][j] = 2;
            automata[30][j] = 2;
        }

        //Male crke
        for (int j = 'a'; j <= 'z'; j++) {
            automata[0][j] = 1;
            automata[1][j] = 1;
            automata[2][j] = 2;

            //----------NEOBVEZNA-----------------//
            automata[16][j] = 2;
            automata[17][j] = 2;
            automata[18][j] = 2;
            automata[19][j] = 2;
            automata[20][j] = 2;
            automata[21][j] = 2;
            automata[22][j] = 2;
            automata[23][j] = 2;
            automata[24][j] = 2;
            automata[25][j] = 2;
            automata[26][j] = 2;
            automata[27][j] = 2;
            automata[28][j] = 2;
            automata[29][j] = 2;
            automata[30][j] = 2;
        }

        //Stevilo (0-9)
        for (int j = '0'; j <= '9'; j++) {
            automata[0][j] = 3;
            automata[1][j] = 2;
            automata[2][j] = 2;
            automata[3][j] = 3;
            automata[4][j] = 5;
            automata[5][j] = 5;

            //----------NEOBVEZNA-----------------//
            automata[16][j] = 2;
            automata[17][j] = 2;
            automata[18][j] = 2;
            automata[19][j] = 2;
            automata[20][j] = 2;
            automata[21][j] = 2;
            automata[22][j] = 2;
            automata[23][j] = 2;
            automata[24][j] = 2;
            automata[25][j] = 2;
            automata[26][j] = 2;
            automata[27][j] = 2;
            automata[28][j] = 2;
            automata[29][j] = 2;
            automata[30][j] = 2;
        }

        //SIMBOLI +,-,*,/,^,),(
        automata[0]['+'] = 6;
        automata[0]['-'] = 7;
        automata[0]['*'] = 8;
        automata[0]['/'] = 9;
        automata[0]['^'] = 10;
        automata[0][')'] = 11;
        automata[0]['('] = 12;
        automata[3]['.'] = 4;

        //preverim ali je znak presledek ali nova vrstica
        automata[0][' '] = automata[0]['\n'] = automata[0]['\t'] = 13;
        automata[13][' '] = automata[13]['\n'] = automata[13]['\t'] = 13;

        //----------NEOBVEZNA-----------------//
        automata[0][':'] = 14; // :
        automata[14]['='] = 15; // :=
        automata[0][';'] = 16;  // ;

        //for
        automata[0]['f'] = 17;
        automata[17]['o'] = 18;
        automata[18]['r'] = 19;

        //to
        automata[0]['t'] = 20;
        automata[20]['o'] = 21;

        //done
        automata[0]['d'] = 22;
        automata[22]['o'] = 23;
        automata[23]['n'] = 24;
        automata[24]['e'] = 25;

        //WRITE
        automata[0]['W'] = 26;
        automata[26]['R'] = 27;
        automata[27]['I'] = 28;
        automata[28]['T'] = 29;
        automata[29]['E'] = 30;

    }

protected:
    int getNextState(int aState, int aChar) const {
        if (aChar == -1)
            return noEdge;
        return automata[aState][aChar];
    }

    bool isFiniteState(int aState) const {
        return finite[aState] != 0;
    }

    int getFiniteState(int aState) const {
        return finite[aState];

    }

private:
    int peek() {
        return input->peek();
    }

    int read() {
        int temp = input->get();
        column++;
        if (temp == '\n')
        {
            row++;
            column = 1;
        }
        return temp;
    }

    bool eof() {
        return peek() == -1;
    }

    Token nextTokenImp() {
        int currentState = startState;
        string lexem;
        int startColumn = column;
        int startRow = row;
        do
        {
            int tempState = getNextState(currentState, peek());


            if (tempState != noEdge)
            {
                currentState = tempState;
                lexem += (char)read();
            }
            else {
                if (isFiniteState(currentState))
                {
                    Token token(lexem, startColumn, startRow, getFiniteState(currentState), eof());
                    if (token.getToken() == tIgnore)
                        return nextToken();
                    else return token;
                }
                else {
                    return Token("", startColumn, startRow, 0, eof());
                }
            }
        } while (true);
    }

public:
    const static int tLexError = -1;
    const static int tIgnore = 0;
    const static int tInteger = 1;
    const static int tOperator = 2;
    const static int tSeparator = 3;

    Scanner(istream* aInput) {
        row = 1;
        column = 1;
        initAutomata();
        input = aInput;
    }

    Token nextToken() {
        return lastToken = nextTokenImp();
    }

    Token currentToken() {
        return lastToken;
    }

};


#endif //TASK_SCANNER_H
