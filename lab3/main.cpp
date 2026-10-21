#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

std::unordered_map<std::string, int> toAminoFreq(std::string input)
{
    std::unordered_map<std::string, std::string> table;
    std::unordered_map<std::string, int> freq;

    table["UUU"] = "Phe"; table["UUC"] = "Phe"; table["UUA"] = "Leu"; table["UUG"] = "Leu";
    table["UCU"] = "Ser"; table["UCC"] = "Ser"; table["UCA"] = "Ser"; table["UCG"] = "Ser";
    table["UAU"] = "Tyr"; table["UAC"] = "Tyr"; table["UAA"] = "Stop"; table["UAG"] = "Stop";
    table["UGU"] = "Cys"; table["UGC"] = "Cys"; table["UGA"] = "Stop"; table["UGG"] = "Trp";

    table["CUU"] = "Leu"; table["CUC"] = "Leu"; table["CUA"] = "Leu"; table["CUG"] = "Leu";
    table["CCU"] = "Pro"; table["CCC"] = "Pro"; table["CCA"] = "Pro"; table["CCG"] = "Pro";
    table["CAU"] = "His"; table["CAC"] = "His"; table["CAA"] = "Gln"; table["CAG"] = "Gln";
    table["CGU"] = "Arg"; table["CGC"] = "Arg"; table["CGA"] = "Arg"; table["CGG"] = "Arg";

    table["AUU"] = "Ile"; table["AUC"] = "Ile"; table["AUA"] = "Ile"; table["AUG"] = "Met";
    table["ACU"] = "Thr"; table["ACC"] = "Thr"; table["ACA"] = "Thr"; table["ACG"] = "Thr";
    table["AAU"] = "Asn"; table["AAC"] = "Asn"; table["AAA"] = "Lys"; table["AAG"] = "Lys";
    table["AGU"] = "Ser"; table["AGC"] = "Ser"; table["AGA"] = "Arg"; table["AGG"] = "Arg";

    table["GUU"] = "Val"; table["GUC"] = "Val"; table["GUA"] = "Val"; table["GUG"] = "Val";
    table["GCU"] = "Ala"; table["GCC"] = "Ala"; table["GCA"] = "Ala"; table["GCG"] = "Ala";
    table["GAU"] = "Asp"; table["GAC"] = "Asp"; table["GAA"] = "Glu"; table["GAG"] = "Glu";
    table["GGU"] = "Gly"; table["GGC"] = "Gly"; table["GGA"] = "Gly"; table["GGG"] = "Gly";

    for (int i = 0; i + 2 < input.length(); i += 3)
    {
        std::string pair;
        pair += input[i]   == 'T' ? 'U' : input[i];
        pair += input[i+1] == 'T' ? 'U' : input[i+1];
        pair += input[i+2] == 'T' ? 'U' : input[i+2];

        if (table.find(pair) != table.end())
            freq[pair]++;
    }

    return freq;
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

    std::unordered_map<std::string, int> freq = toAminoFreq(fullSequence);

    std::unordered_map<std::string, std::string> aaMap = {
        {"UUU", "Phe"}, {"UUC", "Phe"}, {"UUA", "Leu"}, {"UUG", "Leu"},
        {"UCU", "Ser"}, {"UCC", "Ser"}, {"UCA", "Ser"}, {"UCG", "Ser"},
        {"UAU", "Tyr"}, {"UAC", "Tyr"}, {"UAA", "Stop"}, {"UAG", "Stop"},
        {"UGU", "Cys"}, {"UGC", "Cys"}, {"UGA", "Stop"}, {"UGG", "Trp"},
        {"CUU", "Leu"}, {"CUC", "Leu"}, {"CUA", "Leu"}, {"CUG", "Leu"},
        {"CCU", "Pro"}, {"CCC", "Pro"}, {"CCA", "Pro"}, {"CCG", "Pro"},
        {"CAU", "His"}, {"CAC", "His"}, {"CAA", "Gln"}, {"CAG", "Gln"},
        {"CGU", "Arg"}, {"CGC", "Arg"}, {"CGA", "Arg"}, {"CGG", "Arg"},
        {"AUU", "Ile"}, {"AUC", "Ile"}, {"AUA", "Ile"}, {"AUG", "Met"},
        {"ACU", "Thr"}, {"ACC", "Thr"}, {"ACA", "Thr"}, {"ACG", "Thr"},
        {"AAU", "Asn"}, {"AAC", "Asn"}, {"AAA", "Lys"}, {"AAG", "Lys"},
        {"AGU", "Ser"}, {"AGC", "Ser"}, {"AGA", "Arg"}, {"AGG", "Arg"},
        {"GUU", "Val"}, {"GUC", "Val"}, {"GUA", "Val"}, {"GUG", "Val"},
        {"GCU", "Ala"}, {"GCC", "Ala"}, {"GCA", "Ala"}, {"GCG", "Ala"},
        {"GAU", "Asp"}, {"GAC", "Asp"}, {"GAA", "Glu"}, {"GAG", "Glu"},
        {"GGU", "Gly"}, {"GGC", "Gly"}, {"GGA", "Gly"}, {"GGG", "Gly"}
    };

    std::vector<std::pair<std::string, int>> list(freq.begin(), freq.end());
    std::sort(list.begin(), list.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });

    std::cout << "Top 10 Highest Frequency Codons:\n";
    for (int i = 0; i < 10 && i < list.size(); i++)
    {
        std::string rnaCodon = list[i].first;
        std::string dnaCodon = rnaCodon;
        for (char &c : dnaCodon) if (c == 'U') c = 'T';

        std::cout << i + 1 << ". DNA: " << dnaCodon
                  << " | RNA: " << rnaCodon
                  << " | Amino Acid: " << aaMap[rnaCodon]
                  << " | Count: " << list[i].second << '\n';
    }

    return 0;
}
