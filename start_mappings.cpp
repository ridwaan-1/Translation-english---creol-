
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
#include <string>
#include <map>
#include <iterator>
#include <fstream>
#include <algorithm>
#include "Mapping.h"

using namespace std;

// Function used to sort mappings in descending order
bool sortmappings(const pair<string, int> &a, 
                        const pair<string, int> &b)
{ return (a.second > b.second); } 


    // ********* CODE FOR MAPPINGS ********* //
int main()
{   
    Mapping maps; 

    const string ENG_DATASET_PATH = "Datasets/1000_English_A_040521.txt"; // File path to english dataset for mapping
    const string CR_DATASET_PATH = "Datasets/1000_KM_A_040521.txt"; // File path to creole dataset for mapping

    // Extract english sentences from file
    vector<string> eng_sentences;
    eng_sentences = maps.get_sentences(ENG_DATASET_PATH);

    // Extract english sentences from file
    vector<string> cr_sentences;
    cr_sentences = maps.get_sentences(CR_DATASET_PATH);

    // Vectors to store extracted words from sentences
    vector<string> eng_words;
    vector<string> cr_words;

    string mapping; // Variable to store mapping 

    // Maps to store mappings and their frequency
    map<string, int> mappings_obtained;
    map<string, int>::iterator itr;

    // Start Mapping English Words to Creole 
    for (int i=0; i<eng_sentences.size(); i++) {
        // All words are extracted and stored in their given vector
        eng_words = maps.split_sentence(eng_sentences[i]);
        cr_words = maps.split_sentence(cr_sentences[i]);

        for (string i : eng_words){
            for (string j : cr_words){
                mapping = i + " " + j + "."; // '.' is added to be able to split later for translation

                // Search for existing mapping
                itr = mappings_obtained.find(mapping); 
                if (itr != mappings_obtained.end())
                    itr->second ++; // If found then frequency is incremented
                else
                    mappings_obtained.insert( {mapping, 1} ); // New mapping is added to vector
            }
        }
    }

    // All mappings are added to a vector for sorting.
    vector<pair<string, int>> mappingsAndfreq;
    for (itr=mappings_obtained.begin(); itr!=mappings_obtained.end(); itr++) 
    {
        mappingsAndfreq.push_back(make_pair(itr->first, itr->second));
    }

    // All mappings are ordered in descending order
    sort(mappingsAndfreq.begin(), mappingsAndfreq.end(), sortmappings); 

    // Creating a new file to store mappings and their frequencies
    fstream mappings_file;
    mappings_file.open("mappings_file.txt"); 
    mappings_file << endl;
    for(int j=0; j<mappingsAndfreq.size(); j++){
        vector<string> w = maps.split_sentence(mappingsAndfreq[j].first);
        cout << w[0]<< "\t" << w[1] << "\t" << mappingsAndfreq[j].second << endl;  
        // Data is written to file in the format EnglishWord CreoleWord Frequency
        mappings_file << w[0]<< "\t" << w[1] << "\t" << mappingsAndfreq[j].second << endl;      
    }  

    mappings_file.close();

    return 0;
}
