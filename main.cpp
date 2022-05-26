#include "prefixToInfix.h"

#include <string>
#include <iostream>
#include <queue>

int main(void){

    PrefixToInfix pti;

    std::string input;

    std::getline(std::cin, input);

    std::queue<std::string> queue;

    std::string currentTerm;

    //Puts space seperated input into a queue
    for(int i = 0; i<input.size(); i++){
        if(isdigit(input[i]) || input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/'){

            currentTerm = input[i];

            while(isdigit(input[i+1])){

                i++;

                currentTerm += input[i];
            }

            queue.push(currentTerm);
        }
    }

    std::cout << pti.convertAndCompute(queue) <<std::endl;

    return 0;
}