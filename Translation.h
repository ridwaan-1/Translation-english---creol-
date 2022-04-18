#include <iostream>
#include <fstream>
#include <vector>
#include "Mapping.h"
using namespace std;

// using inheritance to make use of some methods in class Mapping
class Translation : public Mapping {
    private:
        vector<pair<string,int>> currentmappings;
    public:
        Translation();
        // Method to get mappings from file
        vector<pair<string,int>> get_mappings(string filepath);
        // Method to convert entire word to uppercase if word is not found in the mappings file
        string convert_uppercase(string w);
        // Method to format string. E.g:First letter of string in capital
        string format_string(string s, char p);
        // Method use to remove special char (. , " ? ! ) from string for comparison later
        vector<string> remove_specialcharacters(vector<string> d);
        // Methos to convert all charaters to lower case/
        string convert_tolower(string s);
        ~Translation();
};

Translation::Translation(){}

vector<pair<string,int>> Translation::get_mappings(string filepath){

    string e_word, c_word, frequency; 
    ifstream mapsandfreq_file(filepath);

    while(!mapsandfreq_file.eof()) {
        while (mapsandfreq_file >> e_word >> c_word >> frequency){
            currentmappings.push_back( {e_word + " " + c_word + ".", stoi(frequency)} );
        }
    }

    mapsandfreq_file.close();
    return currentmappings;
}

string Translation::convert_uppercase(string w) {
    string unfound_mappings = "";
    for (char c:w){
        unfound_mappings += toupper(c);
    }
    return unfound_mappings;
}

string Translation::format_string(string s, char p) {
    string formatted_sentence = "";
    formatted_sentence += toupper(s[0]);
    formatted_sentence += s.substr(1, s.length()-2) + p;
    return formatted_sentence;
}

vector<string> Translation::remove_specialcharacters(vector<string> d){
    string temp_word;
    vector<string> new_words;
    for (int i = 0; i < d.size(); ++i) {
        temp_word = "";  // Variable to temporarily store new string without special char
        for (char l:d[i]){
            if ((l >= 'a' && l <= 'z')) {
                temp_word += l;
            }
        }
        new_words.push_back(temp_word);
    }
    return new_words;
}

string Translation::convert_tolower(string s){
    for_each(s.begin(), s.end(), [](char & d) {
            d = tolower(d);
    });
    return s;
}

Translation::~Translation(){}