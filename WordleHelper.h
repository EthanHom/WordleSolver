#ifndef WORDLE_HELPER_H
#define WORDLE_HELPER_H

#include <csetjmp>
#include <locale>
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

class WordleHelper{
 
    std::vector<std::string> allowed;
    std::vector<std::string> answers;

    std::vector<std::string> green;
    std::vector<std::string> yellow;
    std::vector<std::string> gray;


    bool contains(std::string word, char c){
        for (int i = 0; i < word.length(); i++){
            if (word[i] == c){
                return true;
            }
        }

        return false;
    }

public:
    WordleHelper(){
        std::string answersFile = "answers.txt";
        std::string allowedFile = "allowed.txt";

        std::fstream newfile;

        newfile.open(answersFile, std::ios::in);
        if (newfile.is_open()){
            std::string tp;
            
            while(getline(newfile, tp)){
                answers.push_back(tp);
            }
            newfile.close();
        }
        else {
            throw std::logic_error("Cant read file " + answersFile + ".");
        }

        newfile.open(allowedFile, std::ios::in);
        if (newfile.is_open()){
            std::string tp;
            
            while(getline(newfile, tp)){
                allowed.push_back(tp);
            }
            newfile.close();
        }
        else {
            throw std::logic_error("Cant read file " + allowedFile + ".");
        }
    }

    void addGreen(std::string feedback){
        if (feedback.size() != 5){
            throw std::logic_error("Green feedback must be exactly 5 characters");
        }
        if (std::any_of(feedback.begin(), feedback.end(), [](char c){
            return c != '_' && (c < 'a' || c > 'z');
        })){
            throw std::logic_error("Green feedback must contain only lowercase letters or underscores");
        }

        green.push_back(feedback);
    }

    void addYellow(std::string feedback){
        if (feedback.size() != 5){
            throw std::logic_error("Yellow feedback must be exactly 5 characters");
        }
        if (std::any_of(feedback.begin(), feedback.end(), [](char c){
            return c != '_' && (c < 'a' || c > 'z');
        })){
            throw std::logic_error("Yellow feedback must contain only lowercase letters or underscores");
        }

        yellow.push_back(feedback);
    }

    void addGray(std::string feedback){
        if (std::any_of(feedback.begin(), feedback.end(), [](char c){
            return c < 'a' && c > 'z';
        })){
            throw std::logic_error("Yellow feedback must contain only lowercase letters");
        }

        gray.push_back(feedback);
    }

    std::vector<std::string>possibleSolutions(){
        // Your code here...

        // eliminating all grays
        char cTemp;
        int iter = 0;
        for (int g = 0; g < gray[0].length(); g++){
            cTemp = gray[0][g];
            iter = 0;
            while (iter < answers.size()){
                if (answers[iter].find(cTemp) != std::string::npos){
                    answers.erase(answers.begin()+iter);
                } else {
                    iter++;
                }
            }
        }

        // yellow
        iter = 0;
        for (int g = 0; g < yellow[0].length(); g++){
            cTemp = yellow[0][g];
            iter = 0;
            while (iter < answers.size()){
                if (answers[iter].find(cTemp) == std::string::npos && cTemp != '_' || cTemp == answers[iter][g]){
                    answers.erase(answers.begin()+iter);
                } else {
                    iter++;
                }
            }
        }

        // green
        iter = 0;
        for (int g = 0; g < green[0].length(); g++){
            cTemp = green[0][g];
            iter = 0;
            while (iter < answers.size()){
                if (answers[iter][g] != cTemp && cTemp != '_'){
                    answers.erase(answers.begin()+iter);
                } else {
                    iter++;
                }
            }
        }

        
        return answers;
        // return {"these", "words", "there"};
    }

    std::vector<std::string> suggest(){
        // suggest function
        return {"bring", "words", "close"};
    }

    ~WordleHelper(){

    }

    friend struct WordleTester;

};

#endif
