#include "prefixToInfix.h"

#include <iostream>

void printQueue(std::queue<std::string> queue){

    std::cout << "queue: " << std::endl;

    while(!queue.empty()){
        std::cout << queue.front() << std::endl;

        queue.pop();
    }
}

bool isNumber(std::string string){

    if(string.empty()){
        return false;
    }

    int stringSize = string.size();

    if(stringSize > 1){
        if(string[0] == '-' || isdigit(string[0])){
            for(int i = 1; i<stringSize; i++){
                if(!isdigit(string[i])){
                    return false;
                }
            }
        }
        else{
            return false;
        }
    }
    else if(!isdigit(string[0])){
        return false;
    }

    return true;

}

std::string convertAndComputeHelper(std::queue<std::string>* queue){

    std::string operatoR = queue->front();

    queue->pop();

    if(queue->size() < 2){
        return "Error";
    }

    std::string secondElement = "";
    secondElement =  queue->front();
    std::string secondElementResult = secondElement;

    if(!(isNumber(secondElement))){

        secondElement = convertAndComputeHelper(queue);

        //If returned error
        if(secondElement == "Error"){
            return "Error";
        }

        secondElementResult = secondElement.substr(secondElement.find(" =") + 2); //stores result in variable to be used in stoi funciton later

        //Get computed eqn by finding everything before the space before the equals sign
        secondElement = "(" + secondElement.substr(0, secondElement.find(" =")) + ")";

    }
    // //If element in queue is not between 0 and 99 inclusive
    else if(stoi(secondElement) > 99 || stoi(secondElement) < 0){
        return "Error";
    }

    queue->pop();
    std::string thirdElement = queue->front();
    std::string thirdElementResult = thirdElement;

    if(!isNumber(thirdElement)){

        thirdElement = convertAndComputeHelper(queue);

        //If returned error
        if(thirdElement == "Error"){
            return "Error";
        }

        thirdElementResult = thirdElement.substr(thirdElement.find(" =") + 2);

        //Get computed eqn by finding everything before the space before the equals sign
        thirdElement = "(" + thirdElement.substr(0, thirdElement.find(" =")) + ")";

    }
    //If element in queue is not between 0 and 99 inclusive
    else if(stoi(thirdElement) > 99 || stoi(thirdElement) < 0){
        return "Error";
    }

    int intNumberOne = std::stoi(secondElementResult); //mySubstrFunction returns result without ")"
    int intNumberTwo = std::stoi(thirdElementResult);

    int result;
    
    switch (operatoR[0]){
        case '+':
            result = intNumberOne + intNumberTwo;
            break;
        case '-':
            result = intNumberOne - intNumberTwo;
            break;
        case '*':
            result = intNumberOne * intNumberTwo;
            break;
        case '/':
            result = intNumberOne / intNumberTwo;
            break;
    }

    return secondElement + " " + operatoR + " " + thirdElement + " = " + std::to_string(result);

}

std::string PrefixToInfix::convertAndCompute(std::queue<std::string> queue){

    std::queue<std::string>* newQueue = new std::queue<std::string>;

    *newQueue = queue;

    std::string output = convertAndComputeHelper(newQueue);

    if(newQueue->size() > 1){
        return "Error";
    }

    return output;

}