#include <random>
#include <fstream>
#include <iostream>
#include <cstdlib>

#include "haversine_algo.cpp"

void appendToJsonFile(std::ofstream &outfile, double &x0, double &y0, double &x1, double &y1)
{
    outfile << "{";
    outfile << std::fixed << std::setprecision(16) << "\"x0\":" << x0 << ",";
    // fprintf(outfile, "\"x0\":%.16f", x0);
    outfile << std::fixed << std::setprecision(16) << "\"y0\":" << y0 << ",";
    outfile << std::fixed << std::setprecision(16) << "\"x1\":" << x1 << ",";
    outfile << std::fixed << std::setprecision(16) << "\"y1\":" << y1;
    return;
}

void generate_harvesine_json_input(int &nCords, int &seed, std::vector<double> &results)
{
    const char *keyName = "pairs";

    std::mt19937 rn_gen(seed); // initialized a mersenne random no generator which generates higher quality random nos than rand()
    int rnx_min = -180, rnx_max = 180, rny_min = -90, rny_max = 90;

    std::uniform_real_distribution<> distrx(rnx_min, rnx_max);
    std::uniform_real_distribution<> distry(rny_min, rny_max);

    const char *fileName = "haversine_data.json";
    std::ofstream outfile(fileName);

    if (!outfile)
    {
        printf("error: could not create file: %s\n", fileName);
        exit(1);
    }
    outfile << "{\"" << keyName << "\":[" << std::endl;

    // double sum = 0;
    while (nCords)
    {
        double x0 = distrx(rn_gen);
        double y0 = distry(rn_gen);
        double x1 = distrx(rn_gen);
        double y1 = distry(rn_gen);
        results.push_back(ReferenceHaversine(x0, y0, x1, y1));
        // printf("%.10d")
        appendToJsonFile(outfile, x0, y0, x1, y1);
        if (nCords == 1)
            outfile << "}";
        else
            outfile << "},";
        nCords--;
    }
    outfile << "]}";
}

int main(int argv, char **argc)
{
    int nCords = atoi(argc[1]); // no of cordinates
    if (nCords > 2e7)
    {
        printf("file size too big :) to generate safely\n");
        return 1;
    }
    int seed = atoi(argc[2]); // seed for the marsenne random no generator
    std::vector<double> results;

    generate_harvesine_json_input(nCords, seed, results);

    double average = 0;
    std::size_t lenResults = results.size();
    for (int i = 0; i < lenResults; i++)
        average += results[i] / (lenResults * 1.0);
    printf("average = %.16f\n", average);

    // for (int i = 0; i < lenResults; i++)
    //     printf("%.16f\n", results[i]);

    return 0;
}