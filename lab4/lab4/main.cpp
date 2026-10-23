#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

std::vector<std::string> sampleGenome(const std::string& input, int numSamples = 20000)
{
    std::vector<std::string> samples;
    samples.reserve(numSamples);
    std::srand(static_cast<unsigned int>(std::time(0)));

    for (int s = 0; s < numSamples; s++)
    {
        int sampleLen = 100 + (std::rand() % 51);
        if (input.length() < static_cast<size_t>(sampleLen)) continue;

        int maxStart = static_cast<int>(input.length()) - sampleLen;
        int startPos = std::rand() % (maxStart + 1);

        samples.push_back(input.substr(startPos, sampleLen));
    }
    return samples;
}

int findOverlap(const std::string& a, const std::string& b, int minOverlap = 20)
{
    int maxOverlap = 0;
    int maxLen = std::min(a.length(), b.length());

    for (int len = minOverlap; len <= maxLen; len++)
    {
        if (a.substr(a.length() - len) == b.substr(0, len))
        {
            maxOverlap = len;
        }
    }
    return maxOverlap;
}

std::vector<std::string> assembleAllContigs(std::vector<std::string> reads)
{
    std::vector<std::string> contigs;

    while (!reads.empty())
    {
        std::string currentGenome = reads[0];
        reads.erase(reads.begin());

        bool merged = true;
        while (merged && !reads.empty())
        {
            merged = false;
            int bestOverlap = 0;
            size_t bestIndex = 0;
            bool appendToRight = true;

            for (size_t i = 0; i < reads.size(); i++)
            {
                int rightOverlap = findOverlap(currentGenome, reads[i]);
                if (rightOverlap > bestOverlap)
                {
                    bestOverlap = rightOverlap;
                    bestIndex = i;
                    appendToRight = true;
                }

                int leftOverlap = findOverlap(reads[i], currentGenome);
                if (leftOverlap > bestOverlap)
                {
                    bestOverlap = leftOverlap;
                    bestIndex = i;
                    appendToRight = false;
                }
            }

            if (bestOverlap >= 20)
            {
                if (appendToRight)
                {
                    currentGenome += reads[bestIndex].substr(bestOverlap);
                }
                else
                {
                    currentGenome = reads[bestIndex].substr(0, reads[bestIndex].length() - bestOverlap) + currentGenome;
                }
                reads.erase(reads.begin() + bestIndex);
                merged = true;
            }
        }
        contigs.push_back(currentGenome);
    }

    return contigs;
}

int main()
{
    std::ifstream file("GCF_000591035.1_ASM59103v1_cds_from_genomic.fna");

    if (!file.is_open())
    {
        std::cerr << "File failed to open!\n";
        return 1;
    }

    std::string line, fullSequence = "";
    while (std::getline(file, line))
    {
        if (!line.empty() && line[0] != '>')
            fullSequence += line;
    }
    file.close();

    std::vector<std::string> samples = sampleGenome(fullSequence, 20000);

    std::vector<std::string> subset(samples.begin(), samples.begin() + std::min<size_t>(500, samples.size()));

    std::vector<std::string> reconstructedGenomes = assembleAllContigs(subset);

    std::cout << "Reconstructed Genomes/Contigs from Samples:\n";
    std::cout << "===========================================\n";

    for (size_t i = 0; i < reconstructedGenomes.size(); i++)
    {
        std::cout << ">Reconstructed_Contig_" << i + 1 << "\n";
        std::cout << reconstructedGenomes[i] << "\n\n";
    }

    return 0;
}
