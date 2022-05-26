#include "prefixToInfix.h"

#include <string>
#include <iostream>
#include <queue>

int main(void){

    PrefixToInfix pti;

    std::string input;

    std::getline(std::cin, input);

    std::queue<std::string> queue;

    std::string currentTerm = "";

    //Puts space seperated input into a queue
    for(int i = 0; i<input.size(); i++){

        while(input[i] != ' ' && input[i] != '\0'){ //If null character isn't there and there isn't a space before the end of the string, this loop will iterate into oblivion

            currentTerm.push_back(input[i]);

            i++;
        }

        queue.push(currentTerm);

        currentTerm = "";
    }

    std::cout << pti.convertAndCompute(queue) <<std::endl;

    return 0;
}