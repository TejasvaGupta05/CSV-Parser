#include<iostream>
#include<fstream>
#include<vector>
#include<variant>
#include<algorithm>
#include<iomanip> // Include iomanip for std::setw
using std::cout;
using Cell = std::variant<int, float, std::string>;
using Row = std::vector<Cell>;
using DataFrame = std::vector<Row>;

enum FieldType {
    INTEGER,
    STRING,
    FLOAT
};

int fieldcount=0;
int rowscount=0;

struct fieldstruct{
    FieldType key;
    std::string value;
    bool missingdata=false;
};

FieldType Ftypeidentifier(const std::string &value) {
    if (value.empty()) {
        return STRING; // Default to STRING for empty values
    }
    if (std::all_of(value.begin(), value.end(), ::isdigit)) {
        return INTEGER;
    }
    if (value.find('.') != std::string::npos && 
        std::all_of(value.begin(), value.end(), [](char c) { return ::isdigit(c) || c == '.'; })) {
        return FLOAT;
    }
    return STRING;
}

std::vector<fieldstruct> fieldsidentifier(std::ifstream &file){
    std::vector<fieldstruct> fields;
    std::string line;
    int pos=0,prevpos=0;
    fieldstruct field;
    std::string value;
    if(!file.is_open()){
        cout<<"File not found\n";
    }
    else{
        std::getline(file, line);
        std::getline(file, line);
        line+=',';
        for(char ch: line){
            if(ch==','){
                value.clear();
                fieldcount++;
                for(int i=prevpos; i<pos; i++){
                    value+=line[i];
                }
                field.key=Ftypeidentifier(value);
                field.value=value;
                fields.push_back(field);
                prevpos=pos+1;
            }
            pos++;
        }
        //move the file pointer to the start of the file
        file.clear();
        file.seekg(0, std::ios::beg);
        std::getline(file, line);
        line+=',';
        pos=0;
        prevpos=0;
        int j=0;
        for(char ch: line) {
            if (ch == ',') {
                value.clear();
                for (int i = prevpos; i < pos; i++) {
                    value += line[i];
                }
                fields[j].value = value;
                prevpos = pos + 1;
                j++;
            }
            pos++;
        }
    }
    return fields;
}

void datacounter(std::ifstream &file){
    std::string line;
    do
    {
        line.clear();
        std::getline(file,line);
        rowscount++;
    } while (!line.empty());
    rowscount--;
}

std::vector<fieldstruct> TrueFields;

DataFrame createDataFrame(std::ifstream &file) {
    DataFrame df;
    Row row;
    Cell cell;
    std::string line;
    std::string value;
    std::getline(file, line); // Skip the header line
    line.clear(); // Clear the line to prepare for reading data
    while(std::getline(file,line)){
        int pos=0,prevpos=0;
        int column = 0;
        line += ',';
        for(char ch : line){
            if(ch==','){
                value.clear();
                for(int i=prevpos; i<pos; i++){
                    value += line[i];
                }
                if (TrueFields[column].key == INTEGER) {
                    if(value.empty()) {
                        TrueFields[column].missingdata = true; 
                        cell = 0; // Default to 0 for empty integer values
                    } else {
                        try {
                            cell = std::stoi(value);
                        } catch (const std::invalid_argument&) {
                            cell = 0; // Handle invalid conversion gracefully
                        }
                    }
                } else if (TrueFields[column].key == FLOAT) {
                    if(value.empty()) {
                        TrueFields[column].missingdata = true;
                        cell = 0.0f; // Default to 0.0 for empty float values
                    } else {
                        try {
                            cell = std::stof(value);
                        } catch (const std::invalid_argument&) {
                            cell = 0.0f; // Handle invalid conversion gracefully
                        }
                    }
                } else {
                    if(value.empty()) {
                        TrueFields[column].missingdata = true;
                        cell = "NA"; // Default to empty string for empty string values
                    } else {
                        cell = value; // Store the string value directly
                    }
                }
                row.push_back(cell);
                column++;
                prevpos = pos + 1;
            }
            pos++;
        }
        df.push_back(row);
        row.clear();
        line.clear();
    }
    return df;
}



//Sorting algorithm for the data
void sort_df(DataFrame& df, int column_index, bool ascending = true) {
    if (column_index < 0 || column_index >= fieldcount) {
        cout << "Invalid column index.\n";
        return;
    }
    
    std::sort(df.begin(), df.end(), [column_index, ascending](const Row& a, const Row& b) {
        const Cell& cell_a = a[column_index];
        const Cell& cell_b = b[column_index];
        
        if (std::holds_alternative<int>(cell_a) && std::holds_alternative<int>(cell_b)) {
            return ascending ? std::get<int>(cell_a) < std::get<int>(cell_b)
                             : std::get<int>(cell_a) > std::get<int>(cell_b);
        } else if (std::holds_alternative<float>(cell_a) && std::holds_alternative<float>(cell_b)) {
            return ascending ? std::get<float>(cell_a) < std::get<float>(cell_b)
                             : std::get<float>(cell_a) > std::get<float>(cell_b);
        } else {
            return ascending ? std::get<std::string>(cell_a) < std::get<std::string>(cell_b)
                             : std::get<std::string>(cell_a) > std::get<std::string>(cell_b);
        }
    });
}

void terminal_df_print(const DataFrame& df) {
    std::string value;
    FieldType key;
    int maxlen[fieldcount]= {0};
    // Calculate max width for each column
    for(int i=0; i<fieldcount; i++){
        key = TrueFields[i].key;
        if (key == INTEGER) {
            for (int j = 0; j < rowscount; j++) {
                value = std::to_string(std::get<int>(df[j][i]));
                if (value.length() > maxlen[i]) maxlen[i] = value.length();
            }
        } else if (key == FLOAT) {
            for (int j = 0; j < rowscount; j++) {   
                value = std::to_string(std::get<float>(df[j][i]));
                value.erase(value.find_last_not_of('0') + 1, std::string::npos);
                if (!value.empty() && value.back() == '.') value.pop_back();
                if (value.length() > maxlen[i]) maxlen[i] = value.length();
            }
        } else {
            for (int j = 0; j < rowscount; j++) {
                value = std::get<std::string>(df[j][i]);
                if (value.length() > maxlen[i]) maxlen[i] = value.length();
            }
        }
    }
    for(int i=0; i<fieldcount; i++){
        if(TrueFields[i].value.length() > maxlen[i]){
            maxlen[i] = TrueFields[i].value.length();
        }
    }

    cout << "\n+";
    for(int i=0; i<fieldcount; i++){
        cout << std::string(maxlen[i]+2, '-') << "+";
    }
    cout << "\n";
    // Print header
    cout << "|";
    for(int i=0; i<fieldcount; i++){
        cout << " " << std::left << std::setw(maxlen[i]) << TrueFields[i].value << " |";
    }
    cout << "\n";

    // Print separator
    cout << "+";
    for(int i=0; i<fieldcount; i++){
        cout << std::string(maxlen[i]+2, '-') << "+";
    }
    cout << "\n";

    // Print data rows
    for(int j=0; j<rowscount; j++){
        cout << "|";
        for(int i=0; i<fieldcount; i++){
            key = TrueFields[i].key;
            if (key == INTEGER) {
                value = std::to_string(std::get<int>(df[j][i]));
            } else if (key == FLOAT) {
                value = std::to_string(std::get<float>(df[j][i]));
                value.erase(value.find_last_not_of('0') + 1, std::string::npos);
                if (!value.empty() && value.back() == '.') value.pop_back();
            } else {
                value = std::get<std::string>(df[j][i]);
            }
            cout << " " << std::left << std::setw(maxlen[i]) << value << " |";
        }
        cout << "\n";
    }
    cout << "+";
    for(int i=0; i<fieldcount; i++){
        cout << std::string(maxlen[i]+2, '-') << "+";
    }
    
    cout << "\n";
}

int main(){
    std::ifstream file("data2.csv");
    TrueFields = fieldsidentifier(file);
    datacounter(file);
    file.clear();
    file.seekg(0, std::ios::beg);
    DataFrame df = createDataFrame(file);    
    cout << "\nDataFrame with field types:\n";
    //sort_df(df, 2, true); 
    terminal_df_print(df);
    //printing TrueField information
    // cout << "\nField Information:\n";
    // for(int i=0; i<fieldcount; i++){
    //     cout << "Field " << i+1 << ": " << TrueFields[i].value 
    //          << " (Type: " << (TrueFields[i].key == INTEGER ? "INTEGER" : 
    //                          TrueFields[i].key == FLOAT ? "FLOAT" : "STRING") 
    //          << ", Missing Data: " << (TrueFields[i].missingdata ? "Yes" : "No") << ")\n";
    // }
}