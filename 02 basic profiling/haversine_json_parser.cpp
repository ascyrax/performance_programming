#include <fstream>
// #include <string>
#include <iostream>
#include <vector>
#include <stack>
// #include "nested_profiler.cpp"

#define UNIQUE_VAR2(A, B) A##B
#define UNIQUE_VAR(A, B) UNIQUE_VAR2(A, B)

#define PROFILER 1
#include "haversine_algo.cpp"

// static inline uint64_t rdtsc() // this is for x86 arch
// {
//     unsigned int lo, hi;
//     __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
//     return ((uint64_t)hi << 32) | lo;
// }

static inline uint64_t read_system_counter()
{ // this is for arm64 arch
    // std::string UNIQUE_VAR(Block, __LINE__) = __func__;
    // std::cout << Block20 << std::endl;
    uint64_t val;
    __asm__ volatile(
        "mrs %0, cntvct_el0"
        : "=r"(val));
    return val;
}

int main(int argCnt, char **args)
{
    // printf("__func__ = %s\n", __func__);
    BeginProfile();
    uint64_t start = read_system_counter();

    if (argCnt < 2)
    {
        printf("./haversine_json_parser [ haversine_data.json ]\n");
        printf("data.json filename needs to be provided :)\n");
        return 1;
    }
    char *fileName = args[1];
    uint64_t befFileOpen = read_system_counter();
    std::ifstream fileObj;
    {
        TimeBandwidth("open file",0);
        fileObj.open(fileName, std::ios::ate);
    }
    if (!fileObj)
    {
        printf("error: could not open file = %s\n", fileName);
        return 1;
    }
    std::streampos fileLen = fileObj.tellg();
    printf("fileLen = %lld\n", static_cast<long long>(fileLen));

    fileObj.seekg(0, std::ios::beg);

    std::vector<char> jsonData(fileLen);

    std::stack<char> st;
    std::vector<std::string> tokens;

    uint64_t befFileRead = read_system_counter();

    {
        TimeBandwidth("fileRead", fileLen);
        fileObj.read(jsonData.data(), fileLen);
    }
    // if (fileObj.read(jsonData.data(), fileLen))
    if (fileObj.good())
    {
        TimeBandwidth("file_parse", fileLen);
        std::string token;
        for (int i = 0; i < fileLen; i++)
        {

            if (jsonData[i] == '{' || jsonData[i] == '[')
            {
                st.push(jsonData[i]);
            }
            else if (jsonData[i] == '}' || jsonData[i] == ']')
            {
                if (st.empty() || (st.top() != jsonData[i] - 2))
                {
                    printf("error: bad format in the input json file: %s \n", fileName);
                    return 1;
                }
                st.pop();
                if (st.empty())
                {
                    printf("json parsing complete for file : %s :)\n", fileName);
                    break;
                }
                else
                {
                    // printf("data group no: %d read\n", i);
                    // parseCordinates();
                    if (token != "")
                        tokens.push_back(token);
                    token = "";
                }
            }
            else if (jsonData[i] == '\"')
            {
                if (st.top() == '\"')
                    st.pop();
                else
                    st.push('\"');
            }
            else if (jsonData[i] == 'p')
            {
                // check if the pairs property exist or not
                if (!(i + 4 < fileLen))
                {
                    printf("error: bad format in the input json file: %s \n", fileName);
                    return 1;
                }
                if (!(jsonData[i + 1] == 'a' && jsonData[i + 2] == 'i' && jsonData[i + 3] == 'r' && jsonData[i + 4] == 's'))
                {
                    printf("error: property PAIRS not found in the input json file : %s\n", fileName);
                    return 1;
                }
                else
                {
                    printf("PAIRS property found :)\n");
                    i = i + 4;
                }
            }
            else if (jsonData[i] == ':')
            {
                // add token to tokens
                if (token != "")
                    tokens.push_back(token);
                token = "";
            }
            else if (jsonData[i] == ',')
            {
                // add current
                if (token.size() && isnumber(token.back()))
                {
                    if (token != "")
                        tokens.push_back(token);
                    token = "";
                }
            }
            else if (isalnum(jsonData[i]) || jsonData[i] == '-' || jsonData[i] == '.')
            {
                if (jsonData[i] == ' ')
                    continue;
                token += jsonData[i];
            }
        }
        // std::cout << "tokens: \n";
        // for (std::string token : tokens)
        //     std::cout << token << std::endl;
    }
    // uint64_t afterFileRead = read_system_counter();
    {
        TimeBandwidth("fileClose", fileLen);
        fileObj.close();
    }
    // uint64_t afterFileClose = read_system_counter();

    std::vector<double> results;
    double x0, y0, x1, y1;
    // for (int i = 0; i < tokens.size(); i++)
    // {
    //     printf("i = %d, token[%d] =", i, i);
    //     std::cout << tokens[i] << std::endl;
    // }
    {
        TimeBandwidth("ReferenceHaversine", 8 * tokens.size() / 2);
        std::cout << 8 * tokens.size() / 2 << std::endl;
        for (int i = 0; i < tokens.size(); i += 8)
        {
            for (int j = i; j < i + 8; j += 2)
            {
                if (tokens[j] == "x0")
                {
                    x0 = std::stod(tokens[j + 1]);
                }
                else if (tokens[j] == "y0")
                {
                    y0 = std::stod(tokens[j + 1]);
                }
                else if (tokens[j] == "x1")
                {
                    x1 = std::stod(tokens[j + 1]);
                }
                else if (tokens[j] == "y1")
                {
                    y1 = std::stod(tokens[j + 1]);
                }
            }
            // std::cout << std::fixed << std::setprecision(16) << "x0: " << x0 << ", y0 : " << y0 << ", x1 : " << x1 << ", y1 : " << y1 << std::endl;
            results.push_back(ReferenceHaversine(x0, y0, x1, y1));
        }
    }
    // uint64_t afterCalculation = read_system_counter();

    std::size_t lenResults = results.size();
    double average = 0;
    // for (int i = 0; i < lenResults; i++)
    //     printf("%.16f\n", results[i]);

    for (int i = 0; i < lenResults; i++)
        average += results[i] / (lenResults * 1.0);
    printf("average = %.16f\n", average);

    // uint64_t end = read_system_counter();

    // std::cout << std::endl
    //           << "start: " << start << std::endl;
    // std::cout << (befFileOpen - start) << std::endl;
    // std::cout << "befFileOpen: " << befFileOpen << std::endl;
    // std::cout << (befFileRead - befFileOpen) << std::endl;
    // std::cout << "befFileRead: " << befFileRead << std::endl;
    // std::cout << (afterFileRead - befFileRead) << std::endl;
    // std::cout << "afterFileRead: " << afterFileRead << std::endl;
    // std::cout << afterFileClose - afterFileRead << std::endl;
    // std::cout << "afterFileClose: " << afterFileClose << std::endl;
    // std::cout << (afterCalculation - afterFileClose) << std::endl;
    // std::cout << "afterCalculation: " << afterCalculation << std::endl;
    // std::cout << end - afterCalculation << std::endl;
    // std::cout << "end: " << end << std::endl;
    // std::cout << std::endl
    //           << "Total Cycles: " << (end - start) << std::endl;

    EndAndPrintProfile();

    return 0;
}