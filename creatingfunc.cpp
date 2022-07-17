#include "creatingfunc.h"

CreatingFunc::CreatingFunc()
{
  connect(Maker, SIGNAL(H_show()), this, SLOT(H_in()) );
}

void CreatingFunc::set_value(QString buff, int M_ALL, int MaxV, int MinV, double STP, bool chan)
{

    Maker->show();
    num_X.clear(); num_Y.clear();
    qDebug() << "IN CreatingFunc" << buff << endl;

    ///////////////////////////////////////////
    ///////////////////////////////////////////
    QString::iterator it = buff.begin();    ///
    for(int i = 0; i < 500; i++, it++)      ///
    {                                       ///
        G_dig[i] = *it;                     ///
    }                                       ///
    ///////////////////////////////////////////
    ///////////////////////////////////////////
    for(int i = 0;G_dig[i] != '\0'; i++)    ///
    {                                       ///
        qDebug() << G_dig[i];               ///
    }                                       ///
                                            ///
    ///////////////////////////////////////////
    ///////////////////////////////////////////

    num_X.push_back(MinV);
    ////////////////////////////////////////////
    ////////////////////////////////////////////
    QString redir;
    QRegExp reg("[0-9]");


    for(register int i = 0, ju = 1 ;   ju < M_ALL    ;   i++, ju++ )
    {
            //qDebug() << num_X[i];

            for(register int d = 0; G_dig[d] != '\0'; d++)
            {
//////////////////////////////////////////////////////////////////
                if(G_dig[d] == 'Y'){
                    G_dig[d] = 'X';
                }

                if(!reg.indexIn(G_dig[d]) || G_dig[d] == '.') //ПРОВЕРКА НА ЧИСЛО
                {
                  redir+=G_dig[d];
                  //qDebug() << "+ DIG" <<redir << "---" << G_dig[d] << endl;
                  //qDebug() << "DIGIT: " << redir << endl;
                  if(G_dig[d+1] == '\0')
                  {
                      digit.push(redir.toDouble());
                      redir.clear();
                  }

                }


                else if(G_dig[d] == '-' && G_dig[d-1] != 'X' && !reg.indexIn(G_dig[d+1]) && (d == 0 || G_dig[d-1] == '(' || reg.indexIn(G_dig[d-1])) )
                {

                 //   qDebug() << "here" << endl;
                    redir+=G_dig[d];

                }



/////////////////
                else if(G_dig[d] == 'X' && G_dig[d-1] == '-' && G_dig[d+1] != '^' && ( (d-1)  == 0 || G_dig[d-2] == '(' || reg.indexIn(G_dig[d-2])) )
                {
                    symbol.pop();
                    double on_time = 0;
                   // qDebug() << "tyta";
                        if(num_X[i] < 0)
                    {

                       on_time =  qAbs(num_X[i]);
                     //  qDebug() << "X  < 0";
                    }

                    else {
                       on_time =  num_X[i] * -1;
                      //  qDebug() << "X > 0 ";
                        }

                        digit.push(on_time);
                       // qDebug() << "ON_TIME" << on_time << "DIGIT MINUS: " << digit.top();




              }
/////////




                else
                {

                    if(d != 0 && redir != '\0')
                    {
                    digit.push(redir.toDouble());
                    //qDebug() <<"IN SET" << redir << endl;
                    redir.clear();
                    }


                     if(G_dig[d] == 'X') //ПРОВЕРКА НА Х
                    {
                      //qDebug() << "X == " << num_X[i] << endl;
                        //redir += QString::number(num_X[i]);
                        digit.push(num_X[i]);
                    //    digit.push(redir.toDouble());
                    }
                     ///*/



                     else if(G_dig[d] == '+')
                     {
                         symbol.push(plus);
                     }

                     else if(G_dig[d] == '-')
                     {
                         symbol.push(minus);
                     }

                     else if(G_dig[d] == '*')
                     {
                         symbol.push(mult);
                     }

                     else if(G_dig[d] == '/')
                     {
                         symbol.push(div);
                     }

                     else if(G_dig[d] == '^')
                     {
                         symbol.push(deg);
                     }

                     else if(G_dig[d] == 'C')
                     {
                         symbol.push(Esin);
                         d+=2;
                     }

                     else if(G_dig[d] == 'S')
                     {
                         symbol.push(Ecos);
                         d+=2;
                     }

                     else if(G_dig[d] == 's')
                     {
                         symbol.push(Esqrt);
                         d+=3;
                     }





                     else if(G_dig[d] == '(')
                     {
                         symbol.push(closeSK);
                     }

                     else if(G_dig[d] == ')')
                     {
                         symbol.push(openSK);
                     }


                   /*plus = 1, //    ПЛЮС             1
                     minus,    //    МИНУС            2
                     mult ,    //    УМНОЖЕНИЕ        3
                     div  ,    //    ДЕЛЕНИЕ          4
                     deg  ,    //    СТЕПЕНЬ          5
                     Esin  ,   //    СИНУС            6
                     Ecos  ,   //    КОСИНУС          7
                     Esqrt ,   //    КОРЕНЬ           8
                     FE   ,    //    ЗАМЕНЕННЫЙ       9
                     Eend  ,   //    КОНЕЦ            10
                     closeSK,  //    ЗАКРЫТАЯ СКОБКА  11
                     openSK    //    ОТКРЫТАЯ СКОБКА  12
                   */

                }

/////////////////////////////////////////////////////////////////////



            }


           // show_values();
            num_Y.push_back(set_value(digit, symbol));                                       //УСТАНОВКА ЗНАЧЕНИЯ у
            num_X.push_back(num_X[ju - 1] + STP);
            qDebug() << "X = " << num_X[i] << '\t' << "Y = " << num_Y[i] << endl;

    }

    Maker->setGraphSS(num_X, num_Y, chan);



}


void CreatingFunc::show_values()  //ВЫЧИСЛЕНИЕ КООРДИНАТЫ Y
{
    /////////////// СОДЕРЖАНИЕ ДВУХ СТЕКОВ ////////////////
    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    while(!digit.empty()){                         ////////
    qDebug() << "ЧИСЛО: " << digit.pop() << endl;  ////////
    }                                              ////////
                                                   ////////
    while(!symbol.empty())                         ////////
    {                                              ////////
    qDebug() << "СИМВОЛ: " << symbol.pop() << endl;////////
    }                                              ////////
    ///////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////
    ///
    ///


}

double CreatingFunc::set_value(QStack<double> &dig, QStack<signs> &sym)
{
     symbols = Eend;
     Buff_symbols = Eend;

     // qDebug() << "IN FUNCTION SET_VALUE\n";
     double    rezult       = 0,
               A_op     =     0,
               B_op     =     0;

               if(!sym.empty() )
               {
                   symbols = sym.top();
                   sym.pop();
                   if(!sym.empty() )
                   {
                       Buff_symbols = sym.top();

                   }
               }

        if(symbols != openSK && symbols != FE)
        {
        A_op = dig.top(); dig.pop();
        }



        switch(symbols)
        {
            case plus:    rezult = set_value(dig, sym) + A_op; break;

            case minus:  // rezult = set_value(dig, sym) - A_op; break;

                          if(Buff_symbols == Eend && dig.empty())
                          {
                              rezult = A_op * -1;
                          }
                          else if(Buff_symbols == closeSK && dig.size() <= sym.size())
                          {
                              //rezult = set_value(dig, sym) - (A_op * -1);
                              A_op = A_op * -1;
                              dig.push(A_op);
                              rezult = set_value(dig, sym);
                          }
                          else{
                            rezult = set_value(dig, sym) - A_op;
                          }
            break;

            case div:
                if(Buff_symbols == plus || Buff_symbols == minus)
                {
                    A_op = dig.top() / A_op; dig.pop();
                    dig.push(A_op);
                    rezult = set_value(dig, sym);
                }

                else if(Buff_symbols == openSK )
                {
                    sym.pop();
                    sym.push(FE);
                    A_op = set_value(dig, sym) / A_op;
                    //cout << "Y" << A_op << endl;
                    dig.push(A_op);
                    rezult = set_value(dig, sym);
                }

                else{
                    rezult = set_value(dig, sym) / A_op;
                }
                break;

            case mult:
                if(Buff_symbols == plus || Buff_symbols == minus )
                {
                    A_op = dig.top() * A_op;  dig.pop();
                    dig.push(A_op);
                    rezult = set_value(dig, sym);
                }
                else if(Buff_symbols == openSK )
                {
                    sym.pop();
                    sym.push(FE);
                    A_op = set_value(dig, sym) * A_op;
                    //cout << "Y" << A_op << endl;
                    dig.push(A_op);
                    rezult = set_value(dig, sym);

                }
                else{
                    rezult = set_value(dig, sym) * A_op;
                }
                break;

            case openSK:
                     A_op = set_value(dig, sym);

                     switch(Buff_symbols)
                     {
                     case Ecos:
                          A_op =  cos(A_op); sym.pop();
                          break;
                     case Esin:
                          A_op = sin(A_op); sym.pop();
                          break;
                     case Esqrt:
                          A_op = sqrt(A_op); sym.pop();
                          break;
                          case deg:
                          A_op = pow(dig.top(), A_op ); dig.pop(); sym.pop();
                          break;
                     }
                       dig.push(A_op);

                       rezult = set_value(dig, sym);
                       //cout <<
                       //rezult = A_op;
                       break;

            case FE:
                       A_op = set_value(dig, sym);
                       //dig.push(A_op);
                       //cout << "! " << A_op << endl;

                       switch(Buff_symbols)
                       {
                           case Ecos:
                                A_op =  cos(A_op); sym.pop();
                                break;
                           case Esin:
                                A_op = sin(A_op); sym.pop();
                                break;
                           case Esqrt:
                                A_op = sqrt(A_op); sym.pop();
                                break;
                           case deg:
                                A_op = pow(dig.top(), A_op ); dig.pop(); sym.pop();
                                break;
                       }

                       rezult = A_op;
                       break;

            case closeSK:  rezult = A_op;  break;
            case Eend:  rezult = A_op;  break;
            case Ecos:
                A_op =  cos(A_op);
                dig.push(A_op);
                rezult = set_value(dig, sym);
                break;
            case Esin:
                A_op = sin(A_op);
                dig.push(A_op);
                rezult = set_value(dig, sym);
                break;
            case Esqrt:
                A_op = sqrt(A_op);
                dig.push(A_op);
                rezult = set_value(dig, sym);
                break;
            case deg:
                if(Buff_symbols == openSK)
                {
                    sym.pop();
                    sym.push(FE);
                    B_op = set_value(dig, sym);
                    A_op = pow(B_op, A_op);
                    //cout << "Y" << A_op << endl;
                    dig.push(A_op);
                    rezult = set_value(dig, sym);

                }

                else{
                A_op = pow(dig.top(), A_op );
                dig.pop();
                dig.push(A_op);
                rezult = set_value(dig, sym);
                }
                break;
        }
        //qDebug() << "THE REZ: " << rezult << endl;
        return rezult;

}


void CreatingFunc::H_in()
{
    emit in_CT();
}




