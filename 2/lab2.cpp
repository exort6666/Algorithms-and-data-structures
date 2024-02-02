#include <iostream>
#include <vector>
#include <string>

// 2+73*(32/9)-5=
bool checkParentheses(std::vector<char> & str)//как в первой лабе
{
    int unclosed = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '(')
            unclosed += 1;
        else if (str[i] == ')')
            unclosed -= 1;
        if (unclosed == -1)
            break;
    }
    if (unclosed != 0 || str[str.size()-1] != '=')
        return false;
    return true;
}

bool inalphabet(std::vector<char>& alphabet, char symbol) //проверка на содержания символа
{
    for (int i = 0; i < alphabet.size(); i++)
    {
        if (alphabet[i] == symbol)
            return true;
    }
    return false;
}

int priority(char operand)
{
    int out=0;
    switch (operand)
    {
    case 43:  // сложение
        out = 1;
        break;
    case 45: // вычитание
        out = 1;
        break;
    case 42: // умножение
        out = 2;
        break;
    case 47: // деление
        out = 2;
        break;
    }
    return out;
}



int main()
{
    std::vector<char> signlist{'+', '-', '=', '*', '/', '(', ')'};
    std::vector<char> numberlist{'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    std::vector<char> list;

    std::string stroka;
    std::cout << "Enter str: ";
    std::cin >> stroka;
    std::cout << std::endl;
    std::string tempNumber{};

    for (int i = 0; i < stroka.size(); i++)
    {
        //Проверка на два знака подряд(кроме скобок)
        if (i > 0 && inalphabet(signlist, stroka[i]) && inalphabet(signlist, stroka[i - 1]))
        {
            if (!(stroka[i] == '(' || stroka[i - 1] == ')'))
            {
                std::cout << "err: 2 signs in a row" << std::endl;
                return -11111;
            }
        }
        //Проверка деления на 0
        if (i > 0 && stroka[i - 1] == '/' && stroka[i] == '0')
        {
            std::cout << "err: zero division" << std::endl;
            return -11111;
        }
        //Проверка на то,существуют ли помимо чисел и нужных знаков другие ненужные символы
        if (!(inalphabet(signlist, stroka[i]) || inalphabet(numberlist, stroka[i])))
        {
            std::cout << "err: intorrect symbol" << std::endl;
            return -11111;
        }
        if (inalphabet(signlist, stroka[i]))
        {
            if (tempNumber.size() != 0)
            {
                int tint = std::atoi(tempNumber.c_str());
                //std::cout << tint << std::endl;
                list.push_back((char)tint);
                tempNumber.clear(); // Очистим tempNumber для следующего числа
            }            
            list.push_back(stroka[i]);           
        }      
        if (inalphabet(numberlist, stroka[i])) {  tempNumber.push_back(stroka[i]);  }
    }
    //Проверка на скобки
    if (!(checkParentheses(list)))
    {
        std::cout << "Error : ()";
        return -11111;
    }


    std::vector<float> numbersQ;
    int numberQtop = -1;

    std::vector<char> signQ;
    int signQtop = -1;
    int countskob = 0;

    for (int i = 0; i < list.size()-1; i++)
    {
        if (!(inalphabet(signlist, list[i])))
        {
            numbersQ.push_back(float(list[i]));
            numberQtop += 1;
        }
        else
        {
            if (list[i] == '(' || signQtop == -1 ) //отдельная обработка скобок тк у них нет присвоенного приоритета
            {
                signQ.push_back(list[i]);
                signQtop += 1;
                if (list[i] == '(')
                {
                    countskob += 1;
                }
            }

            else  // проверка на наличие 2 элементов в стеке с числами заведомо выполнится
            {
                if (signQ[signQtop] == '(' || (signQ[signQtop] != '(' && list[i] != ')' && (priority(list[i]) > priority(signQ[signQtop]))))
                {
                    signQ.push_back(list[i]);
                    signQtop += 1;
                }

                else if ( list[i] == ')') 
                {
                    while (signQ[signQtop] != '(')
                    {
                        //найти к
                        int pointer; //ищем закрывающую скобку
                        for (int p = signQ.size()-1; p >= 0; p--)
                        {
                            if (signQ[p] == '(')
                            {
                                pointer = p;
                                break;
                            }
                        }
                        int maxPrior = 0;
                        for (int k = pointer+1; k < signQ.size(); k++)
                        {
                            if (priority(signQ[k - 1]) <= priority(signQ[k]))
                            {
                                maxPrior = k; // оператор максимального приоритета
                            }
                        }
                        float temp1 = numbersQ[maxPrior-countskob];
                        float temp2 = numbersQ[maxPrior+1-countskob];
                        float tempout;
                        numbersQ.erase(numbersQ.begin() + (maxPrior- countskob));
                        numbersQ.erase(numbersQ.begin() + (maxPrior-countskob));
                        switch (signQ[maxPrior])
                        {
                        case 43:
                            tempout = temp1 + temp2;
                            break;
                        case 45:
                            tempout = temp1 - temp2;
                            break;
                        case 42:
                            tempout = temp1 * temp2;
                            break;
                        case 47:
                            if (temp2 == 0)
                            {
                                std::cout << "error: zero division!!!!!" << std::endl;
                                return -11111;
                            }
                            tempout = temp1 / temp2;
                            break;
                        }
                        numbersQ.insert(numbersQ.begin() + (maxPrior-countskob), tempout);
                        numberQtop -= 1;
                        signQtop -= 1;
                        signQ.erase(signQ.begin() + (maxPrior));
                    }

                    signQ.pop_back();

                    countskob -= 1;
                    signQtop -= 1;
                }
                else
                {
                    float temp1 = numbersQ[numberQtop - 1];
                    float temp2 = numbersQ[numberQtop];
                    float tempout;
                    numbersQ.pop_back();
                    numbersQ.pop_back();
                    switch (signQ[signQtop])
                    {
                    case 43:
                        tempout = temp1 + temp2;
                        break;
                    case 45:
                        tempout = temp1 - temp2;
                        break;
                    case 42:
                        tempout = temp1 * temp2;
                        break;
                    case 47:
                        if (temp2 == 0)
                        {
                            std::cout << "error: zero division!!!!!" << std::endl;
                            return -11111;
                        }
                        tempout = temp1 / temp2;
                        break;
                    }
                    numbersQ.push_back(tempout);
                    numberQtop -= 1;

                    signQ[signQtop] = list[i]; // инд не изменится
                }               
            }           
        }      
    }

    while (numberQtop != 0)
    {
        int maxPrior = 0;
        for (int i = 1; i < signQ.size(); i++)
        {
            if (priority(signQ[i - 1]) <= priority(signQ[i]))
            {
                maxPrior = i;
            }
        }
        float temp1 = numbersQ[maxPrior];
        float temp2 = numbersQ[maxPrior+1];
        float tempout;
        numbersQ.erase(numbersQ.begin() +(maxPrior + 1));
        numbersQ.erase(numbersQ.begin() + maxPrior);
        switch (signQ[maxPrior])
        {
        case 43:
            tempout = temp1 + temp2;
            break;
        case 45:
            tempout = temp1 - temp2;
            break;
        case 42:
            tempout = temp1 * temp2;
            break;
        case 47:
            if (temp2 == 0)
            {
                std::cout << "error: zero division!!!!!" << std::endl;;
                return -11111;
            }
            tempout = temp1 / temp2;
            break;
        }
        numbersQ.insert(numbersQ.begin() + maxPrior, tempout);
        numberQtop -= 1;
        signQtop -= 1;
        signQ.erase(signQ.begin() + maxPrior);
    }

    std::cout << "Answer = " <<numbersQ[0];
    return 0;
}