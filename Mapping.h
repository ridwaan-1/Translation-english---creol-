#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

class Mapping {
    protected:
        vector<string> words_obt;
        string word;
        vector<string> sentences;

    public:
        Mapping();
        // Method to extract sentence from file
        vector<string> get_sentences(string filepath);
        // Method to remove all special characters in a sentence. for e.g: (. , ? ! -)
        string remove_specialcharacters(string sentence);
        // Method to check if sentence has a punctuation mark
        string sentence_check(string s);
        // // Method to split sentence into a vector of words
        vector<string> split_sentence(string s);
        ~Mapping();
}; 

Mapping::Mapping(){}

vector<string> Mapping::get_sentences(string filepath){

    sentences.clear();
    string sentence = "";

    ifstream file(filepath);
    while(!file.eof()) {

        getline(file, sentence);
        // Check if sentence has a punctuation mark
        sentence = sentence_check(sentence); 
        sentences.push_back(sentence);
    }

    file.close();
    return sentences;
}

string Mapping::sentence_check(string sent){
    char end_sentence = sent[sent.length() - 1];
    if (end_sentence!='.' && end_sentence!='?' && end_sentence!='!') {
        // Very important for splitting the sentence into words later.
        sent += '.';
    }
    return sent;
}

vector<string> Mapping::split_sentence(string s){ 
    words_obt.clear();   // remove any previous values
    word = "";  

    for ( char l:s ) {
        // Check if this character is an alphabet
        if ( isalpha(l)){
            word += tolower(l);
        } else {
            if (word!="") {
                word = (word=="ll") ? "will" : word; // For e.g: They'll -> They will
                word = (word=="s") ? "is" : word; // For e.g: There's -> There is
                word = (word=="ve") ? "have" : word;
                word = (word=="m") ? "am" : word;
                word = (word=="t") ? "not" : word;
                words_obt.push_back(word);
            }
            word = "";              
        }
    }

    return words_obt;
}

Mapping::~Mapping(){}