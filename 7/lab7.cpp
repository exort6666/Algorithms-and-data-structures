#include <iostream>
#include <vector>

template <typename T>
//шелла = усовершенствованная сортировка вставками
void shellSort(std::vector<T>& mas)
{
    int k = mas.size() - 1;
  
    for (k; k > 0; k = (int)(k / 2))
    {
        for (int j = 1; j < mas.size(); j+=k)
        {
            T temp = mas[j];
            int i = j - 1;
            while (i >= 0 && mas[i] > temp)
            {
                mas[i + 1] = mas[i];
                i = i - 1;
            }
            mas[i + 1] = temp;
        }

    }
}

int main()
{
    int n;
    std::vector<int> mas;
    std::cout << "Enter len mas: ";
    std::cin >> n;
    std::cout << std::endl << "cur mas: ";
    for (int i = 0; i < n; i++)
    {
        mas.push_back(rand() % 100);
        std::cout << mas[i] << " ";
    }
    shellSort(mas);
    std::cout << '\n' << "sorted: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << mas[i] << " ";
    }
}