
#include <iostream>
#include <vector>
#include <string>

bool checkSkobochki(std::vector<char> & str)
{
    int cnt = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '(') { cnt += 1; }
        else if (str[i] == ')') { cnt -= 1; }
        if (cnt == -1) { break; }   
    }
    if (cnt != 0 or str[str.size()-1] != '=') { return false; }
    return true;
}

bool inalphabet(std::vector<char>& alphabet, char symbol)
{
    for (int i = 0; i < alphabet.size(); i++)
    {
        if (alphabet[i] == symbol) { return true; }
    }
    return false;
}

int prior(char operand)
{
    int out=0;
    switch (operand)
    {
    case 43:   // сложение
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
    
    std::string s;
    std::cout << "Enter str: ";
    std::cin >> s;
    std::cout << std::endl;
    std::string tempNumber{};
    
    for (int i = 0; i < s.size(); i++)
    {
        if (i > 0 and inalphabet(signlist, s[i]) and inalphabet(signlist, s[i - 1]))
        {
            if (not(s[i] == '(' or s[i - 1] == ')'))
            {
                std::cout << "err: 2 signs in a row" << std::endl;
                return -11111;
            }
        }

        if (i > 0 and s[i - 1] == '/' and s[i] == '0') //деление на 0
        {
            std::cout << "err: zero division" << std::endl;
            return -11111;
        }

        if (not(inalphabet(signlist, s[i]) or inalphabet(numberlist, s[i]))) // символа не должно быть по условию
        {
            std::cout << "err: intorrect symbol" << std::endl;
            return -11111;
        }

        if (inalphabet(signlist, s[i]))
        {
            if (tempNumber.size() != 0)
            {
                int tint = std::atoi(tempNumber.c_str());
                //std::cout << tint << std::endl;
                list.push_back((char)tint);
                tempNumber.clear(); // Очистим tempNumber для следующего числа
            }            
            list.push_back(s[i]);           
        }      
        if (inalphabet(numberlist, s[i])) {  tempNumber.push_back(s[i]);  }
    }

    if (not checkSkobochki(list)) // любая ошибка связанная со скобками
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
        if (not inalphabet(signlist, list[i]))
        {
            numbersQ.push_back(float(list[i]));
            numberQtop += 1;
        }
        else
        {
            if (list[i] == '(' or signQtop == -1 ) //отдельная обработка скобок тк у них нет присвоенного приоритета
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
                if (signQ[signQtop] == '(' or (signQ[signQtop] != '(' and list[i] != ')' and (prior(list[i]) > prior(signQ[signQtop]))))
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
                            if (prior(signQ[k - 1]) <= prior(signQ[k]))
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
            if (prior(signQ[i - 1]) <= prior(signQ[i]))
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
   
    std::cout << "answer " <<numbersQ[0];
    return 0;

}


