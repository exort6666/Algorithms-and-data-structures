#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <random>

// Функция для генерации входного файла со случайными числами
void generateInputFile(const std::string& inputFileName, int totalNumbers) {
    std::ofstream inputFile(inputFileName);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 100);

    for (int i = 0; i < totalNumbers; ++i) {
        inputFile << dis(gen) << " ";
    }
}

// Функция для разделения входного файла на отдельные фрагменты и их сортировки
void splitAndSortChunks(const std::string& inputFileName, int chunkSize) {
    std::ifstream inputFile(inputFileName);
    int chunkNumber = 1;

    while (!inputFile.eof()) {
        std::vector<int> chunk;
        chunk.reserve(chunkSize);

        for (int i = 0; i < chunkSize; ++i) {
            int number;
            if (inputFile >> number) {
                chunk.push_back(number);
            }
            else {
                break;
            }
        }

        std::sort(chunk.begin(), chunk.end());

        std::ofstream outputFile("chunk" + std::to_string(chunkNumber++) + ".txt");
        std::copy(chunk.begin(), chunk.end(), std::ostream_iterator<int>(outputFile, " "));
    }
}

// Функция для объединения отсортированных фрагментов в окончательный выходной файл
void mergeChunks(const std::string& outputFileName, int chunkSize, int totalChunks) {
    std::vector<std::ifstream> chunkFiles;
    chunkFiles.reserve(totalChunks);

    for (int i = 1; i <= totalChunks; ++i) {
        chunkFiles.emplace_back("chunk" + std::to_string(i) + ".txt");
    }

    std::vector<int> chunkBuffer(chunkSize);
    std::vector<bool> chunkEmpty(totalChunks, false);
    std::ofstream outputFile(outputFileName);

    while (true) {
        int minChunkIndex = -1;
        for (int i = 0; i < totalChunks; ++i) {
            if (!chunkEmpty[i]) {
                if (minChunkIndex == -1 || chunkBuffer[i] < chunkBuffer[minChunkIndex]) {
                    minChunkIndex = i;
                }
            }
        }

        if (minChunkIndex == -1) {
            // Все файлы объединены
            break;
        }

        outputFile << chunkBuffer[minChunkIndex] << " ";

        if (chunkFiles[minChunkIndex] >> chunkBuffer[minChunkIndex]) {
            chunkEmpty[minChunkIndex] = false;
        }
        else {
            chunkEmpty[minChunkIndex] = true;
        }
    }

    // Закрытие всех файлов
    for (auto& chunkFile : chunkFiles) {
        chunkFile.close();
    }
}

void multiPhaseSort(const std::string& inputFileName, const std::string& outputFileName, int chunkSize) {
    splitAndSortChunks(inputFileName, chunkSize);

    //Считает количество кусков,на которые делит
    std::ifstream inputFile(inputFileName);
    int totalNumbers = std::distance(std::istream_iterator<int>(inputFile), std::istream_iterator<int>());
    int totalChunks = (totalNumbers + chunkSize - 1) / chunkSize;

    mergeChunks(outputFileName, chunkSize, totalChunks);
}

void main() {
    std::string inputFileName = "input.txt";
    std::string outputFileName = "output.txt";
    int chunkSize = 5;
    int totalNumbers = 20;
    generateInputFile(inputFileName, totalNumbers);
    multiPhaseSort(inputFileName, outputFileName, chunkSize);
}
