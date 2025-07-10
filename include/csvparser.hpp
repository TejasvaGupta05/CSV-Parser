#ifndef CSVPARSER_HPP
#define CSVPARSER_HPP
#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<variant>
#include<algorithm>
#include<iomanip>
using std::cout;
using Cell = std::variant<int, float, std::string>;
using Row = std::vector<Cell>;

extern char delimiters[];
enum FieldType {
    INTEGER,
    STRING,
    FLOAT
};
struct fieldstruct{
    FieldType key;
    std::string value;
    bool missingdata=false;
};

FieldType Ftypeidentifier(const std::string &value);
char delimiteridentifier(const std::string &line);

class DataFrame {
private:
    std::vector<fieldstruct> fieldsidentifier(std::ifstream &file, char delimiter=',');

    void datacounter(std::ifstream &file);

    void createDataFrame(std::ifstream &file, char delimiter=',');

public:
    std::vector<Row> data;
    std::vector<fieldstruct> TrueFields;
    int fieldcount = 0;
    int rowscount = 0;

    DataFrame();

    void reset();


    void read_csv(const std::string& filename, char delimiter = ',');
    
    void save(const std::string& filename);

    void change_value(std::string field_name, int row_index, const Cell& new_value);
    
    template<typename T>
    void get_column(std::vector<T>& x, const int index){
        if (index < 0 || index >= fieldcount) {
            cout << "Invalid column index.\n";
        }
        for (int i = 0; i < rowscount; ++i) {
            if (std::holds_alternative<T>(data[i][index])) {
                x.push_back(std::get<T>(data[i][index]));
            } else {
                cout << "Type mismatch in column " << index << ".\n";
            }
        }
    }
    
    void sort(int column_index, bool ascending = true);
    
    void print();

    void print_info();
};

#endif