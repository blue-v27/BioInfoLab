#include <iostream>
#include <unordered_map>

std::string fromStartToStop(std::string input)
{
    std::unordered_map<std::string, std::string> table;
    
    table["UUU"] = "Phe";
    table["UUC"] = "Phe";
    table["UUA"] = "Leu";
    table["UUG"] = "Leu";
    
    table["UCU"] = "Ser";
    table["UCC"] = "Ser";
    table["UCA"] = "Ser";
    table["UCG"] = "Ser";
    
    table["UAU"] = "Tyr";
    table["UAC"] = "Tyr";
    table["UAA"] = "Stop";
    table["UAG"] = "Stop";
    
    table["UGU"] = "Cys";
    table["UGC"] = "Cys";
    table["UGA"] = "Stop";
    table["UGG"] = "Trp";
    
    table["CUU"] = "Leu";
    table["CUC"] = "Leu";
    table["CUA"] = "Leu";
    table["CUG"] = "Leu";
    
    table["CCU"] = "Pro";
    table["CCC"] = "Pro";
    table["CCA"] = "Pro";
    table["CCG"] = "Pro";
    
    table["CAU"] = "His";
    table["CAC"] = "His";
    table["CAA"] = "Gln";
    table["CAG"] = "Gln";
    
    table["CGU"] = "Arg";
    table["CGC"] = "Arg";
    table["CGA"] = "Arg";
    table["CGG"] = "Arg";
    
    table["AUU"] = "Ile";
    table["AUC"] = "Ile";
    table["AUA"] = "Ile";
    table["AUG"] = "Met";
    
    table["ACU"] = "Thr";
    table["ACC"] = "Thr";
    table["ACA"] = "Thr";
    table["ACG"] = "Thr";
    
    table["AAU"] = "Asn";
    table["AAC"] = "Asn";
    table["AAA"] = "Lys";
    table["AAG"] = "Lys";
    
    table["AGU"] = "Ser";
    table["AGC"] = "Ser";
    table["AGA"] = "Arg";
    table["AGG"] = "Arg";
    
    table["GUU"] = "Val";
    table["GUC"] = "Val";
    table["GUA"] = "Val";
    table["GUG"] = "Val";
    
    table["GCU"] = "Ala";
    table["GCC"] = "Ala";
    table["GCA"] = "Ala";
    table["GCG"] = "Ala";
    
    table["GAU"] = "Asp";
    table["GAC"] = "Asp";
    table["GAA"] = "Glu";
    table["GAG"] = "Glu";
    
    table["GGU"] = "Gly";
    table["GGC"] = "Gly";
    table["GGA"] = "Gly";
    table["GGG"] = "Gly";
    
    std::string output;
    
    bool foundStart = false;
    
    for (int i = 0; i < input.length() - 2; foundStart ? i += 3 :++i)
    {
        std::string pair;
        pair    += input[i]   == 'T' ? 'U' : input[i];
        pair    += input[i+1] == 'T' ? 'U' : input[i+1];
        pair    += input[i+2] == 'T' ? 'U' : input[i+2];
        
        if(pair != "AUG" && !foundStart)
            continue;
            
            foundStart = true;
        
        if(pair == "UAA" || pair == "UAG" || pair == "UGA")
            break;
        
        output  += table[pair];
    }
    
    return output;
}


std::string toAmino(std::string input)
{
    std::unordered_map<std::string, std::string> table;
    
    table["UUU"] = "Phe";
    table["UUC"] = "Phe";
    table["UUA"] = "Leu";
    table["UUG"] = "Leu";
    
    table["UCU"] = "Ser";
    table["UCC"] = "Ser";
    table["UCA"] = "Ser";
    table["UCG"] = "Ser";
    
    table["UAU"] = "Tyr";
    table["UAC"] = "Tyr";
    table["UAA"] = "Stop";
    table["UAG"] = "Stop";
    
    table["UGU"] = "Cys";
    table["UGC"] = "Cys";
    table["UGA"] = "Stop";
    table["UGG"] = "Trp";
    
    table["CUU"] = "Leu";
    table["CUC"] = "Leu";
    table["CUA"] = "Leu";
    table["CUG"] = "Leu";
    
    table["CCU"] = "Pro";
    table["CCC"] = "Pro";
    table["CCA"] = "Pro";
    table["CCG"] = "Pro";
    
    table["CAU"] = "His";
    table["CAC"] = "His";
    table["CAA"] = "Gln";
    table["CAG"] = "Gln";
    
    table["CGU"] = "Arg";
    table["CGC"] = "Arg";
    table["CGA"] = "Arg";
    table["CGG"] = "Arg";
    
    table["AUU"] = "Ile";
    table["AUC"] = "Ile";
    table["AUA"] = "Ile";
    table["AUG"] = "Met";
    
    table["ACU"] = "Thr";
    table["ACC"] = "Thr";
    table["ACA"] = "Thr";
    table["ACG"] = "Thr";
    
    table["AAU"] = "Asn";
    table["AAC"] = "Asn";
    table["AAA"] = "Lys";
    table["AAG"] = "Lys";
    
    table["AGU"] = "Ser";
    table["AGC"] = "Ser";
    table["AGA"] = "Arg";
    table["AGG"] = "Arg";
    
    table["GUU"] = "Val";
    table["GUC"] = "Val";
    table["GUA"] = "Val";
    table["GUG"] = "Val";
    
    table["GCU"] = "Ala";
    table["GCC"] = "Ala";
    table["GCA"] = "Ala";
    table["GCG"] = "Ala";
    
    table["GAU"] = "Asp";
    table["GAC"] = "Asp";
    table["GAA"] = "Glu";
    table["GAG"] = "Glu";
    
    table["GGU"] = "Gly";
    table["GGC"] = "Gly";
    table["GGA"] = "Gly";
    table["GGG"] = "Gly";
    
    std::string output;
    
    for (int i = 0; i < input.length() - 2; i+=3)
    {
        std::string pair;
        pair    += input[i]   == 'T' ? 'U' : input[i];
        pair    += input[i+1] == 'T' ? 'U' : input[i+1];
        pair    += input[i+2] == 'T' ? 'U' : input[i+2];
        output  += table[pair];
    }
    
    return output;
}


std::string toSingleLetter(std::string input)
{
    std::unordered_map<std::string, std::string> table = 
    {
        {"Phe", "F"},
        {"Leu", "L"},
        {"Ser", "S"},
        {"Tyr", "Y"},
        {"Stop", "*"},
        {"Cys", "C"},
        {"Trp", "W"},
        {"Pro", "P"},
        {"His", "H"},
        {"Gln", "Q"},
        {"Arg", "R"},
        {"Ile", "I"},
        {"Met", "M"},
        {"Thr", "T"},
        {"Asn", "N"},
        {"Lys", "K"},
        {"Val", "V"},
        {"Ala", "A"},
        {"Asp", "D"},
        {"Glu", "E"},
        {"Gly", "G"}
    };

    std::string output;
    
    for (int i = 0; i < input.length() - 2; i+=3)
    {
        std::string pair;
        pair    += input[i];
        pair    += input[i+1];
        pair    += input[i+2];
        output  += table[pair];
    }
    
    return output;
}


int main()
{
    std::string input;
    std::cin >> input;

    std::string amino = fromStartToStop(input);
    std::string singleLetter = toSingleLetter(amino);
    
    std::cout << amino << '\n' << singleLetter;

return 0;

}