
//     ________________________________________________________
//    |  SURNAME Othername: IBRAHIM Muhammad Ridwaan Husayn    |
//    |  Student ID: 2011945                                   |
//    |  Programme: BSc (Hons) Computer Science L1, Group A    |
//    |  Module: Computer Programming, ICT 1017Y               |
//    |  Date: 01 June 2021                                    |  
//    |________________________________________________________|
//      * PROGRAM STRUCTURE: THERE ARE 2 DIFFERENT PROGRAMS ONE FOR MAPPINGS(start_mappings.cpp) AND ONE FOR TRANSLATION(translate.cpp)
//      * MAPPINGS AND TRANSLATIONS HAVE BEEN COMPLETED
//      * TOTAL NUMBER OF MAPPINGS -> 40,118
//      * NUMBER OF CORRECTLY TRANSLATED SENTENCES -> 2 (ACCURACY 0.2%)
//      * NUMBER OF NEARLY SAME TRANSLATED SENTENCES -> 34 (ONLY ONE WORD DIFFERENCE FROM MANUALLY TRANSLATED SENTENCE)
//      * HOW PROGRAM CAN BE IMPROVED:
//          1. A seperate file for common english word like he, she, the etc... should be created to improve the mappings
//          2. Codes should be able to recognise if sentence is a question or not because different sentence type have different translation.



#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Translation.h"

using namespace std;

    // ********* CODE FOR TRANSLATION ********* //
int main() {
    // Get Mappingse
    Translation translate;

    // Get all mappings from the mappings file
    vector<pair<string,int>> mappings;
    const string MAPPINGS_FILEPATH = "mappings_file.txt";
    mappings = translate.get_mappings(MAPPINGS_FILEPATH);
    
    // Get sentence to translate
    vector<string> new_engsentences;
    const string ENGTESTDATA_PATH = "Test_Datasets/1000_English_A_110521_Test.txt"; // file path to english test data
    new_engsentences = translate.get_sentences(ENGTESTDATA_PATH);

    // Vector to store translated sentence
    vector<string> tranlated_sentences;
    string current_tsentence = "";
    vector<string> words;
    bool mapping_found;
    // Extract word from english sentence and search for matching mappings
    for (int i=0; i<new_engsentences.size(); i++){
        words = translate.split_sentence(new_engsentences[i]);
        char punctuation_mark = new_engsentences[i][new_engsentences[i].length()-1];
        current_tsentence = "";
        for (string w:words) {
            mapping_found = 0;
            string z, zc;
            bool f = 0;
            ifstream vc("common_words.txt");
            while (vc >> z >> zc) {
                if (w==z) {
                    current_tsentence += zc + " ";
                    f = 1;
                }
            }
            if (!f) {
                for (int j=0; j<mappings.size(); j++){
                    vector<string> e_map = translate.split_sentence(mappings[j].first);
                    if (w==e_map[0] && mappings[j].second>1){
                        current_tsentence += e_map[1] + " ";
                        mapping_found = 1;
                        break;
                    }
                }
                if (!mapping_found) {         
                    current_tsentence += translate.convert_uppercase(w) + " ";
                }
            }
        }
        current_tsentence = translate.format_string(current_tsentence, punctuation_mark);
        tranlated_sentences.push_back(current_tsentence);
    }

    fstream translated_sent;
    translated_sent.open("translated_creole.txt");
    for (int i=0; i<tranlated_sentences.size(); i++){
        cout << "(" << i+1 << ") " << new_engsentences[i] << " --> " << tranlated_sentences[i] << endl;
        translated_sent << tranlated_sentences[i] << endl;
    }

    vector<string> cr_text = translate.get_sentences("Test_Datasets/1000_KM_A_110521_Test.txt"); // path to creole test data
    vector<string> translated_cr_text = translate.get_sentences("translated_creole.txt"); // path to translated creole sentence
    vector<vector<string>> correct_translations;
    vector<vector<string>> nearly_correct_translations;

    for (int i=0; i<cr_text.size(); i++) {
        string temp = cr_text[i];
        temp = translate.convert_tolower(temp);         
        vector<string> test_words = translate.split_sentence(temp);
        test_words = translate.remove_specialcharacters(test_words);

        temp = translated_cr_text[i];
        temp = translate.convert_tolower(temp);         
        vector<string> translated_words = translate.split_sentence(temp);
        translated_words = translate.remove_specialcharacters(translated_words);

        int count = 0;
        for (int y=0; y<test_words.size(); y++) {
            if (test_words[y] == translated_words[y]) {
                count++;
            }
        }

        if (count==translated_words.size()) {
            correct_translations.push_back({new_engsentences[i], cr_text[i], translated_cr_text[i]});

        }else if (count>=test_words.size()-1) {
            nearly_correct_translations.push_back({new_engsentences[i], cr_text[i], translated_cr_text[i]});
        }
    }
    cout << "\n*************************************************************" << endl;
    cout << "               ****     CORRECT TRANSLATIONS      ****\n" << endl;
    for (int i=0; i<correct_translations.size(); i++) {
        cout << "                   English Sentence: " << correct_translations[i][0] << endl;
        cout << "Manually Translated Creole Sentence: " << correct_translations[i][1] << endl;
        cout << "         Translated Creole Sentence: " << correct_translations[i][2] << endl << endl;
    }
    cout << "\n*************************************************************" << endl;
    cout << "            ****     NEARLY CORRECT TRANSLATIONS      ****\n" << endl;
    for (int i=0; i<nearly_correct_translations.size(); i++) {
        cout << "                   English Sentence: " << nearly_correct_translations[i][0] << endl;
        cout << "Manually Translated Creole Sentence: " << nearly_correct_translations[i][1] << endl;
        cout << "         Translated Creole Sentence: " << nearly_correct_translations[i][2] << endl << endl;
    }
}