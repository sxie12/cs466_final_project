#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

const int NUM = 5;

string str_table[2];
const string sizes[2] = {"6x6", "7x7"};
const int m[2] = {6, 7};
const int n[2] = {6, 7};

int main() {
    str_table[0] = "\\begin{center}\n\\begin{tabular}{|c||c|c|c|c|}\n\\hline\n";
    str_table[0] += "Matrix & Skeleton & Brute force & SPhyR & Number of solutions \\\\\n\\hline\\hline\n";
    str_table[1] = str_table[0];
    string tmp, pre, line;
    int sol_sk, sol_bf;
    for (int j = 0; j < 2; ++j) {
        for (int i = 1; i <= NUM; ++i) {
            sol_sk = sol_bf = 0;
            ifstream filename("input_run_" + sizes[j] + "_" + to_string(i) + ".txt");
            if (filename.is_open()) {
                str_table[j] += "$\\begin{pmatrix}\n";
                filename >> tmp;
                filename >> tmp;
                for (int a = 0; a < m[j]; ++a) {
                    for (int b = 0; b < n[j]; ++b) {
                        filename >> tmp;
                        str_table[j] += tmp + " ";
                        if (b == n[j] - 1) str_table[j] += "\\\\\n";
                        else str_table[j] += "& ";
                    }
                }
                str_table[j] += "\\end{pmatrix}$\n & ";
                filename.close();
            } else {
                cout << "Cannot open input file\n";
            }

            ifstream skeleton("output_run_" + sizes[j] + "_" + to_string(i) + "_skeleton.txt");
            if (skeleton.is_open()) {
                while (getline(skeleton, line)) {
                    if (!line.length()) ++sol_sk;
                    pre = line;
                }
                stringstream ss(pre);
                ss >> tmp;
                ss >> tmp;
                ss >> tmp;
                str_table[j] += tmp + " & ";
                skeleton.close();
            } else {
                cout << "Cannot open skeleton\n";
            }

            ifstream brute("output_run_" + sizes[j] + "_" + to_string(i) + "_brute_force.txt");
            if (brute.is_open()) {
                while (getline(brute, line)) {
                    if (!line.length()) ++sol_bf;
                    pre = line;
                }
                stringstream ss2(pre);
                ss2 >> tmp;
                ss2 >> tmp;
                ss2 >> tmp;
                str_table[j] += tmp + " & ";
                brute.close();
            } else {
                cout << "Cannot open brute force\n";
            }

            ifstream sphyr("output_run_" + sizes[j] + "_" + to_string(i) + "_sphyr.txt");
            if (sphyr.is_open()) {
                while (getline(sphyr, line)) {
                    if (line[0] == 'E') {
                        stringstream ss3(line);
                        ss3 >> tmp;
                        ss3 >> tmp;
                        ss3 >> tmp;
                        break;
                    }
                }
                str_table[j] += tmp + " & ";
                sphyr.close();
            } else {
                cout << "Cannot open sphyr\n";
            }

            assert(sol_sk == sol_bf);
            str_table[j] += to_string(sol_sk) + " \\\\\n\\hline\n";
        }
    }
    str_table[0] += "\\end{tabular}\n\\end{center}\n";
    str_table[1] += "\\end{tabular}\n\\end{center}\n";
    cout << str_table[0] << "\n\n\n" << str_table[1] << "\n";

    return 0;
}
