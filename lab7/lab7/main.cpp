#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>

struct Enzyme {
    std::string name;
    std::string site;
    int cutOffset;
};

struct DigestResult {
    std::string enzymeName;
    std::vector<int> cutPositions;
    std::vector<int> fragmentLengths;
};

int main()
{
    std::ifstream file("GCF_000591035.1_ASM59103v1_cds_from_genomic.fna");
    if (!file.is_open()) return 1;

    std::string line, dnaSequence = "";
    while (std::getline(file, line) && dnaSequence.length() < 3000)
    {
        if (!line.empty() && line[0] != '>')
            dnaSequence += line;
    }
    file.close();

    if (dnaSequence.length() > 3000) dnaSequence = dnaSequence.substr(0, 3000);
    if (dnaSequence.empty()) return 1;

    std::vector<Enzyme> enzymes = {
        {"EcoRI",   "GAATTC", 1},
        {"BamHI",   "GGATCC", 1},
        {"HindIII", "AAGCTT", 1},
        {"TaqI",    "TCGA",   1},
        {"HaeIII",  "GGCC",   2}
    };

    std::vector<DigestResult> results;
    int seqLen = static_cast<int>(dnaSequence.length());

    for (size_t i = 0; i < enzymes.size(); i++)
    {
        std::vector<int> cuts;
        size_t pos = dnaSequence.find(enzymes[i].site, 0);

        while (pos != std::string::npos)
        {
            cuts.push_back(static_cast<int>(pos) + enzymes[i].cutOffset);
            pos = dnaSequence.find(enzymes[i].site, pos + 1);
        }

        std::vector<int> fragments;
        int prevCut = 0;
        for (size_t j = 0; j < cuts.size(); j++)
        {
            fragments.push_back(cuts[j] - prevCut);
            prevCut = cuts[j];
        }
        fragments.push_back(seqLen - prevCut);

        results.push_back({enzymes[i].name, cuts, fragments});
    }

    for (size_t i = 0; i < results.size(); i++)
    {
        std::cout << "Enzyme: " << results[i].enzymeName << "\n";
        std::cout << "1. Number of cleavages: " << results[i].cutPositions.size() << "\n";

        std::cout << "2. Cleavage positions: ";
        if (results[i].cutPositions.empty()) std::cout << "None";
        for (size_t j = 0; j < results[i].cutPositions.size(); j++)
        {
            std::cout << results[i].cutPositions[j] << " ";
        }
        std::cout << "\n";

        std::cout << "   Fragment lengths (bp): ";
        for (size_t j = 0; j < results[i].fragmentLengths.size(); j++)
        {
            std::cout << results[i].fragmentLengths[j] << " ";
        }
        std::cout << "\n--------------------------------------------------\n";
    }

    std::cout << "\n3. ELECTROPHORESIS GEL SIMULATION (5 LANES)\n";
    std::cout << "Dist(cm) | ";
    for (size_t i = 0; i < results.size(); i++)
    {
        std::cout << std::left << std::setw(10) << results[i].enzymeName << " | ";
    }
    std::cout << "\n----------------------------------------------------------------------\n";

    double logMin = std::log10(1.0);
    double logMax = std::log10(static_cast<double>(seqLen));

    for (int row = 1; row <= 15; row++)
    {
        double currentCm = (row / 15.0) * 10.0;
        std::cout << std::fixed << std::setprecision(1) << std::setw(6) << currentCm << "   | ";

        for (size_t i = 0; i < results.size(); i++)
        {
            std::string band = "";
            for (size_t j = 0; j < results[i].fragmentLengths.size(); j++)
            {
                int fragLen = results[i].fragmentLengths[j];
                double fragLog = std::log10(std::max(1, fragLen));
                double dist = 1.0 + ((logMax - fragLog) / (logMax - logMin)) * 9.0;

                if (std::abs(dist - currentCm) < 0.35)
                {
                    band = "===" + std::to_string(fragLen) + "===";
                    break;
                }
            }
            std::cout << std::left << std::setw(10) << band << " | ";
        }
        std::cout << "\n";
    }

    return 0;
}
