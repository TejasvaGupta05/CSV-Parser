#include "../include/csvparser.hpp"

int main() {
    DataFrame df;
    df.read_csv("data.csv");
    df.print();
    df.print_info();
    return 0;
}