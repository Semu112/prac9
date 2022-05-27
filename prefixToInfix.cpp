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

#define ERRORDESCRIPTIONS true

std::string convertAndComputeHelper(std::queue<std::string>* queue, char lastOperator){

    if(queue->empty()){
        if(ERRORDESCRIPTIONS){
            std::cout << "not enough numbers for operands" << std::endl;
        }
        return "Error";
    }

    std::string firstElement = queue->front();
    queue->pop();

    std::string LHS;

    //First element in a new call to convertAndComputeHelper should always be an operator
    if(isNumber(firstElement)){

        if(firstElement.size() > 2 || stoi(firstElement) < 0){
            if(ERRORDESCRIPTIONS){
                std::cout << "element out of bounds" << std::endl;
            }
            return "Error";
        }

        return firstElement + " = " + firstElement;

    }
    else{

        std::string strExpOne = convertAndComputeHelper(queue, firstElement[0]);
        std::string strExpTwo = convertAndComputeHelper(queue, firstElement[0]);

        if(strExpOne == "Error" || strExpTwo == "Error"){
            return "Error";
        }

        //Finds last number in returned expressions
        int itrOne = strExpOne.size();

        while(strExpOne[itrOne] != ' '){
            if(itrOne == 0){
                break;
            }

            itrOne--;
        }

        int itrTwo = strExpTwo.size();

        while(strExpTwo[itrTwo] != ' '){
            if(itrTwo == 0){
                break;
            }

            itrTwo--;
        }

        int intNumberOne = stoi(strExpOne.substr(itrOne));
        int intNumberTwo = stoi(strExpTwo.substr(itrTwo));

        //brackets not applied if * or / is immediately after + or - in prefix or if there are two of the same operators in a row
        //brackets applied if * / operators follow each other
        //brackets not applied unless + or - is immediately after * or /

        //brackets only applied if + - is immediately after * / in prefix
        //--- * + 5 6 7 will have brackets
        //--- * / 5 6 7 will not have brackets
        //--- / * 5 6 7 will not have brackets
        //--- * + - 5 6 7 8 will have brackets, (5-6+7)*8
        //--- * 5 + 6 7 will have brackets, 5*(6+7)

        bool brackets = false;
        if((lastOperator == '*' || lastOperator == '/') && (firstElement[0] == '+' || firstElement[0] == '-')){
            brackets = true;
        }

        int result;
        switch (firstElement[0]){
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
        default: //Default case checks if operator is not + - * or /
            if(ERRORDESCRIPTIONS){
                std::cout << "operatoR not + - / or *" << std::endl;
            }
            return "Error";
        }

        strExpOne = strExpOne.substr(0, strExpOne.find(" ="));
        strExpTwo = strExpTwo.substr(0, strExpTwo.find(" ="));

        std::string LHS = strExpOne + " " + firstElement + " " + strExpTwo;

        if(brackets){
            LHS = "(" + LHS + ")";
        }

        return LHS + " = " + std::to_string(result);

    }

    // queue->pop();

    // //If we get to the second element and the queue is empty, return error
    // if(queue->empty()){
    //     if(ERRORDESCRIPTIONS){
    //         std::cout << "queue is empty" << std::endl;
    //     }
    //     return "Error";
    // }

    // std::string secondElement = "";
    // secondElement =  queue->front();
    // std::string secondElementResult = secondElement;

    // //Need brackets is not as simple as having them only on + and minus. 5/6*7 can be interpreted as (5/6)*7 or 5/(6*7)
    // //Get computed eqn by finding everything before the space before the equals sign
    // // bool needsBrackets;
    // // if(operatoR == "+" || operatoR == "-"){
    // //     needsBrackets = true;;
    // // }
    // // else{
    // //     needsBrackets = false;;
    // // }

    // if(!(isNumber(secondElement))){

    //     secondElement = convertAndComputeHelper(queue);

    //     //If returned error
    //     if(secondElement == "Error"){
    //         return "Error";
    //     }

    //     secondElementResult = secondElement.substr(secondElement.find(" =") + 2); //stores result in variable to be used in stoi funciton later

    //     //Get computed eqn by finding everything before the space before the equals sign
    //     // if(needsBrackets){
    //         secondElement = "(" + secondElement.substr(0, secondElement.find(" =")) + ")";
    //     // }
    //     // else{
    //     //     secondElement = secondElement.substr(0, secondElement.find(" ="));
    //     // }

    // }
    // //If element in queue is not between 0 and 99 inclusive
    // else if(secondElement.size() > 2 || stoi(secondElement) < 0){
    //     if(ERRORDESCRIPTIONS){
    //         std::cout << "second element out of range" << std::endl;
    //     }
    //     return "Error";
    // }
    // else{
    //     queue->pop();
    // }

    // //If we get to the third element and the queue is empty, return error
    // if(queue->empty()){
    //     if(ERRORDESCRIPTIONS){
    //         std::cout << "queue is empty" << std::endl;
    //     }
    //     return "Error";
    // }

    // std::string thirdElement = queue->front();
    // std::string thirdElementResult = thirdElement;

    // if(!isNumber(thirdElement)){

    //     thirdElement = convertAndComputeHelper(queue);

    //     //If returned error
    //     if(thirdElement == "Error"){
    //         return "Error";
    //     }

    //     thirdElementResult = thirdElement.substr(thirdElement.find(" =") + 2);

    //     //Get computed eqn by finding everything before the space before the equals sign
    //     // if(needsBrackets){
    //         thirdElement = "(" + thirdElement.substr(0, thirdElement.find(" =")) + ")";
    //     // }
    //     // else{
    //     //     thirdElement = thirdElement.substr(0, thirdElement.find(" ="));
    //     // }

    // }
    // //If element in queue is not between 0 and 99 inclusive
    // else if(thirdElement.size() > 2 || stoi(thirdElement) < 0){
    //     if(ERRORDESCRIPTIONS){
    //         std::cout << "third element out of range" << std::endl;
    //     }
    //     return "Error";
    // }
    // else{
    //     queue->pop();
    // }

    // int intNumberOne = std::stoi(secondElementResult); //mySubstrFunction returns result without ")"
    // int intNumberTwo = std::stoi(thirdElementResult);

    // int result;

    // switch (firstElement[0]){
    //     case '+':
    //         result = intNumberOne + intNumberTwo;
    //         break;
    //     case '-':
    //         result = intNumberOne - intNumberTwo;
    //         break;
    //     case '*':
    //         result = intNumberOne * intNumberTwo;
    //         break;
    //     case '/':
    //         result = intNumberOne / intNumberTwo;
    //         break;
    //     default: //Default case checks if operator is not + - * or /
    //         if(ERRORDESCRIPTIONS){
    //             std::cout << "operatoR not + - / or *" << std::endl;
    //         }
    //         return "Error";
    // }

    // return secondElement + " " + firstElement + " " + thirdElement + " = " + std::to_string(result);

}

std::string PrefixToInfix::convertAndCompute(std::queue<std::string> queue){

    std::queue<std::string>* newQueue = new std::queue<std::string>;

    *newQueue = queue;

    std::string output = convertAndComputeHelper(newQueue, '?');

    if(newQueue->size() >= 1){
        if(ERRORDESCRIPTIONS){
            std::cout << "size of queue greater than 0 on finishing" << std::endl;
        }
        return "Error";
    }

    delete newQueue;

    return output;

}