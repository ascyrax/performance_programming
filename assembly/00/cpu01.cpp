#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <iterator>

const char *parseInstruction(std::vector<std::bitset<8>> rawInst)
{
    const char *parsedInst = "";
    const int byteCnt = rawInst.size();

    for (int i = 0; i < byteCnt; i++)
    {
        const std::bitset<8> byte = rawInst[i];
        for (int j = 0; j < 8; j++)
        {
            const int bit = byte[j];;

        }
    }
    return parsedInst;
}

int main(int argCnt, char **args)

{
    char *filename = args[1];

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file)
    {
        std::cout << "error: cannot open file: " << filename << std::endl;
        return 1;
    }

    std::streampos fileSize = file.tellg();

    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(fileSize);

    if (file.read(buffer.data(), fileSize))
    {
        std::vector<std::bitset<8>> binInstructs;
        for (std::bitset<8> binInst : buffer)
        {
            binInstructs.push_back(binInst);
        }
        const char *parsedInst = parseInstruction(binInstructs);
        printf("parsed Instruction: %s\n", parsedInst);
    }

    file.close();

    return 0;
}


// what is special about mov Ax, [75] ??? why won't it get encoded to binary or sth ? 

// why can we do mov Bx, [BP + 75], and not sth like [AX + BX + 7]

// what does mov Bx, [75] mean ? is the 76th byte of the process' memory space or what ? 

