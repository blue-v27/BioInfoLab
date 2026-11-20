#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

int main()
{
    std::string s1 = "ATCCGAATTAC";
    std::string s2 = "CGAT";

    int matchScore = 2;
    int mismatchScore = -1;
    int gapPenalty = -1;

    int rows = static_cast<int>(s1.length()) + 1;
    int cols = static_cast<int>(s2.length()) + 1;

    std::vector<std::vector<int>> dp(rows, std::vector<int>(cols, 0));

    for (int i = 0; i < rows; i++) dp[i][0] = i * gapPenalty;
    for (int j = 0; j < cols; j++) dp[0][j] = j * gapPenalty;

    for (int i = 1; i < rows; i++)
    {
        for (int j = 1; j < cols; j++)
        {
            int s    = (s1[i - 1] == s2[j - 1]) ? matchScore : mismatchScore;
            int diag = dp[i - 1][j - 1] + s;
            int up   = dp[i - 1][j] + gapPenalty;
            int left = dp[i][j - 1] + gapPenalty;

            dp[i][j] = std::max({diag, up, left});
        }
    }

    std::cout << "Scoring Matrix:\n";
    std::cout << "      -   ";
    for (size_t j = 0; j < s2.length(); j++) std::cout << std::setw(4) << s2[j];
    std::cout << "\n";

    for (int i = 0; i < rows; i++)
    {
        if (i == 0) std::cout << "  - ";
        else std::cout << "  " << s1[i - 1] << " ";

        for (int j = 0; j < cols; j++)
        {
            std::cout << std::setw(4) << dp[i][j];
        }
        std::cout << "\n";
    }

    std::string aligned1 = "";
    std::string aligned2 = "";
    int i = rows - 1;
    int j = cols - 1;

    while (i > 0 || j > 0)
    {
        int s = (i > 0 && j > 0 && s1[i - 1] == s2[j - 1]) ? matchScore : mismatchScore;

        if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + s)
        {
            aligned1 = s1[i - 1] + aligned1;
            aligned2 = s2[j - 1] + aligned2;
            i--;
            j--;
        }
        else if (i > 0 && dp[i][j] == dp[i - 1][j] + gapPenalty)
        {
            aligned1 = s1[i - 1] + aligned1;
            aligned2 = '-' + aligned2;
            i--;
        }
        else
        {
            aligned1 = '-' + aligned1;
            aligned2 = s2[j - 1] + aligned2;
            j--;
        }
    }

    std::cout << "\nOptimal Global Alignment:\n";
    std::cout << "S1: " << aligned1 << "\n";
    std::cout << "S2: " << aligned2 << "\n";
    std::cout << "Alignment Score: " << dp[rows - 1][cols - 1] << "\n";

    return 0;
}
