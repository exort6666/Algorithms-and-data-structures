//внешняя многофазная
#include <fstream>

int main()
{
    std::ifstream in, in1, in2;
    std::ofstream out, out1, out2;

    int a, b, size = 0, countA, countB, count;
    bool flag = true, Afull, Bfull;

    in.open("input.txt");
    out.open("result.txt");
    while (in >> a) // считываю размер массива
    {
        out << a << " ";
        size++;
    }
    in.close();
    out.close();
    /*длина серий фиксируется на каждом шаге.
    В исходном файле все серии имеют длину 1,
    после первого шага она равна 2, после второго – 4,
    после третьего – 8, после k -го шага – 2k*/
    for (int partSize = 1; partSize < size; partSize *= 2)
    {
        //Исходный файл f разбивается на два вспомогательных файла 
        in.open("result.txt");
        out1.open("A.txt");
        out2.open("B.txt");
        count = 0;
        while (in >> a)
        {
            count++;
            if (flag) out1 << a << " ";
            else
                out2 << a << " ";
            if (count == partSize)
            {
                count = 0;
                flag = !flag;
            }
        }
        in.close();
        out1.close();
        out2.close();

        in1.open("A.txt");
        in2.open("B.txt");
        out.open("result.txt");
        //вспомогательные файлы сливаются в файл 
        // при этом одиночные элементы образуют упорядоченные пары.
        if (in1 >> a)
            Afull = true;
        else
            Afull = false;
        if (in2 >> b)
            Bfull = true;
        else
            Bfull = false;
        //Полученный файл  вновь обрабатывается
        //При этом упорядоченные пары переходят в упорядоченные четверки.
        for (int i = 0; i < size; i += 2 * partSize)
        {
            countA = 0; countB = 0;
            while (countA < partSize && Afull && countB < partSize && Bfull)
                if (a < b)
                {
                    out << a << " ";
                    if (in1 >> a)
                        Afull = true;
                    else
                        Afull = false;
                    countA++;
                }
                else
                {
                    out << b << " ";
                    if (in2 >> b)
                        Bfull = true;
                    else
                        Bfull = false;
                    countB++;
                }
            //Повторяя шаги, сливаем четверки в восьмерки и т.д.,
            //каждый раз удваивая длину слитых последовательностей до тех пор, пока не будет упорядочен целиком весь файл
            while (countA < partSize && Afull)
            {
                out << a << " ";
                if (in1 >> a)
                    Afull = true;
                else
                    Afull = false;
                countA++;
            }
            while (countB < partSize && Bfull)
            {
                out << b << " ";
                if (in2 >> b)
                    Bfull = true;
                else
                    Bfull = false;
                countB++;
            }

        }

        in1.close();
        in2.close();
        out.close();
    }
    return 0;
}
