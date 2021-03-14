/**
 *   @file: zipcode.cc
 *   @author: Hunter Douglas
 *   @date: March 13th 2021
 *   @brief: inputing zipcodes and outputing zipcodes into lines
 */


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;


string getDigitCode (char);
int getCheckDigitValue(int);

int main(int argc, char const *argv[]) {
    
    
    //Variables needed for input file, line reading, and inputFilename
    string line;
    string inputFilename;
    string outputFilename;
    ifstream infile;
    ofstream outfile;

    //Output prompt and input inputFilename
    cout << "Please enter file name for input: ";
    cin >> inputFilename;

    //Output prompt and input outputFilename
    cout << "Please enter file name for output: ";
    cin >> outputFilename; 

    //Open output file in preparation to write to it
    outfile.open(outputFilename, fstream::out);

    //Open file from inputFilename given
    infile.open(inputFilename);

    //Iterate through file line by line to extract valid lines
    while (getline(infile, line)){
        
        outfile << left << setw(10) << line;
        
        //If the current line length is 5
        if (line.length() == 5){
            
            int lineSum = 0;
            
            //Boolean variable for indicating whether or not line is valid
            bool validLine = true;

            //Iterate through line 1 character at a time and ensure all 5 are digits
            for (int i = 0; i < line.length(); i++){
                
                char myChar = line[i]; 

                //If character is not equal to a digit (0-9), set validLine to false, add error to output string, and break out of the loop
                if (isdigit(myChar) == false){
                    
                    outfile << "Error: Code is invalid" << endl;
                    validLine = false;
                    break;
                }

                //Convert our digit to an integer and add it to the line sum (for checkDigit)
                int myInt = myChar - '0';                
                lineSum += myInt;
            }

            //If our line is a valid 5-digit zip code
            if (validLine == true){
                
                string outputBarCode;
              
                int checkDigit = getCheckDigitValue(lineSum);

                //For each of the 5 digits, get the proper barcode and add it to the output string
                for (int j = 0; j < line.length(); j++){
                    
                    outputBarCode += getDigitCode(line[j]);
                    outputBarCode += " ";
                }

               //Add checkdigit to the output string
                outputBarCode += getDigitCode('0' + checkDigit);

                //Output the string to the file
                outfile << outputBarCode << endl;
                
            }
        }

        else{
            //Output the error to the file
            outfile << "Error: zip code must be 5 digits" << endl;
        }

   }

    //Close the output file
    outfile.close();
    return 0;
}


string getDigitCode (char digit) {
    
    string digitcode;
    
    if (digit == '1'){
        digitcode = ":::||";
    }

    else if (digit == '2'){
        digitcode = "::|:|";
    }

    else if (digit == '3'){
        digitcode = "::||:";
    }

    else if (digit == '4'){
        digitcode = ":|::|";
    }

    else if (digit == '5'){
        digitcode = ":|:|:";
    }

    else if (digit == '6'){
        digitcode = ":||::";
    }

    else if (digit == '7'){
        digitcode = "|:::|";
    }

    else if (digit == '8'){
        digitcode = "|::|:";
    }

    else if (digit == '9'){
        digitcode = "|:|::";
    }

    else if (digit == '0'){
        digitcode = "||:::";
    }
  
    return digitcode;
}

int getCheckDigitValue(int sum){
    return (10 - (sum % 10));
}