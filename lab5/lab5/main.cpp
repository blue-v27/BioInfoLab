#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>

struct DnaFragment {
    int id;
    std::string sequence;
    int length;
    double migrationDist;
    int repeatCount;
};

int main()
{
    std::ifstream file("GCF_000591035.1_ASM59103v1_cds_from_genomic.fna");
    if (!file.is_open()) return 1;

    std::string line, fullGenome = "";
    while (std::getline(file, line) && fullGenome.length() < 3000)
    {
        if (!line.empty() && line[0] != '>')
            fullGenome += line;
    }
    file.close();

    if (fullGenome.length() > 3000) fullGenome = fullGenome.substr(0, 3000);
    if (fullGenome.length() < 1000) return 1;

    std::srand(static_cast<unsigned int>(std::time(0)));
    std::vector<DnaFragment> gelSamples;

    int genomeLen = static_cast<int>(fullGenome.length());
    double logMin = std::log10(100.0);
    double logMax = std::log10(3000.0);

    for (int i = 1; i <= 10; i++)
    {
        int maxPossibleLen = std::min(3000, genomeLen);
        int fragLen = 100 + (std::rand() % (maxPossibleLen - 100 + 1));
        int startPos = std::rand() % (genomeLen - fragLen + 1);

        std::string sampleSeq = fullGenome.substr(startPos, fragLen);
        double dist = 1.0 + ((logMax - std::log10(fragLen)) / (logMax - logMin)) * 8.5;

        int repeatMatches = 0;
        for (size_t pos = 0; pos < sampleSeq.length(); pos++)
        {
            for (int unitLen = 3; unitLen <= 5; unitLen++)
            {
                if (pos + unitLen > sampleSeq.length()) continue;

                std::string unit = sampleSeq.substr(pos, unitLen);
                int count = 1;

                while (pos + (count + 1) * unitLen <= sampleSeq.length() &&
                       sampleSeq.substr(pos + count * unitLen, unitLen) == unit)
                {
                    count++;
                }

                int totalLen = count * unitLen;
                if (totalLen >= 6 && totalLen <= 10)
                {
                    repeatMatches++;
                }
            }
        }

        gelSamples.push_back({i, sampleSeq, fragLen, dist, repeatMatches});
    }

    std::cout << "ID\tLength (bp)\tMigration Dist\t6-10bp Repeats Found\n";
    std::cout << "------------------------------------------------------------\n";
    for (const auto& sample : gelSamples)
    {
        std::cout << sample.id << "\t" << sample.length << "\t\t"
                  << sample.migrationDist << " cm\t\t" << sample.repeatCount << "\n";
    }

    return 0;
}
