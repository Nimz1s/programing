#include <iostream>
#include <cmath>
#include <string>
using namespace std;


string colectLetter(char letter) 
{   
    char let(letter);
    int getNum = let;
    string retBinar = "";


    int sizeOfBit = 8;
    while (getNum > 0) {
        if (getNum % 2 == 0) {
            retBinar = "0" + retBinar;
            sizeOfBit--;
        }
        else {
            retBinar = "1" + retBinar;
            sizeOfBit--;
        }
        getNum /= 2;
    }
    if (sizeOfBit == 1)
    {
        retBinar = "0" + retBinar;
    }


    return retBinar;
}
string* getSixBit(string fullBinaryNum, int &countBinaryNum, int &countEqualNum)
{
    int countRes = countBinaryNum % 6;

    switch (countRes)
    {
    case 1:
        fullBinaryNum = fullBinaryNum + "00000";
        countBinaryNum += 5;
        countEqualNum += 2;
        break;
    case 2:
        fullBinaryNum = fullBinaryNum + "0000";
        countBinaryNum += 4;
        countEqualNum += 2;
        break;
    case 3:
        fullBinaryNum = fullBinaryNum + "000";
        countBinaryNum += 3;
        countEqualNum += 1;
        break;
    case 4:
        fullBinaryNum = fullBinaryNum + "00";
        countBinaryNum += 2;
        countEqualNum += 1;
        break;
    case 5:
        fullBinaryNum = fullBinaryNum + "0";
        countBinaryNum += 1;
        break;
    }


    string* arrOfSixBit = new string[countBinaryNum / 6];
    int s = 0;
    for (int i = 0; i < countBinaryNum/6; i++, s += 6)
    {
        arrOfSixBit[i] = fullBinaryNum.substr(s, 6);
    }


    return arrOfSixBit;
}
int startCoder(string word)
{
    string fullBinaryNum;
    for (auto letter : word)
    {
        string ret = colectLetter(letter);
        fullBinaryNum = fullBinaryNum + ret;
    }


    int countBinary = 0;
    /*fullBinaryNum = fullBinaryNum + "00001010";*/
    for (auto count : fullBinaryNum)
    {
        countBinary += 1;
    }

    int countEqual = 0;
    string* arr = getSixBit(fullBinaryNum, countBinary, countEqual);
    int* arrNum = new int[countBinary / 6];
    for (int i = 0; i < countBinary / 6; i++)
    {
        int exponent = 5;
        int tenBit = 0;
        for (auto el1 : arr[i])
        {
            if (int(el1) == 49)
            {
                int t = 2;
                int one = 1;


                for (int i = exponent; i > 0; i--)
                {
                    one *= 2;
                }


                exponent--;
                tenBit += one;
            }
            else
            {
                exponent--;
            }
        }
        arrNum[i] = tenBit;
    }
    

    const string symbol = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    cout << "Ваше зашифроване слово: ";
    for (int i = 0; i < countBinary / 6; i++)
    {
        cout << symbol[arrNum[i]];
    }
    for (int i = 0; i < countEqual; i++)
    {
        cout << "=";
    }


    delete[] arr;
    delete[] arrNum;
    return 0;
}



string findBit(char letter, int &equal)
{
    const string symbol = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


    int letterNum = 0;
    char eq(61);
    for (auto letterBase64 : symbol)
    {
        if (letterBase64 == letter)
        {
            break;
        }
        letterNum++;
    }


    string retBinary = "";
    int sizeOfBit = 6;
    int letterToSixBit = 0;
    while(letterNum > 0)
    {
        if (letterNum % 2==0)
        {
            retBinary = "0" + retBinary;
            sizeOfBit--;
        }
        else
        {
            retBinary = "1" + retBinary;
            sizeOfBit--;
        }
        letterNum /= 2;
    }


    switch (sizeOfBit)
    {
    case -1:
        retBinary = "00000" + retBinary;
        break;
    case 1:
        retBinary = "0" + retBinary;
        break;
    case 2:
        retBinary = "00" + retBinary;
        break;
    case 3:
        retBinary = "000" + retBinary;
        break;
    case 4:
        retBinary = "0000" + retBinary;
        break;
    case 5:
        retBinary = "00000" + retBinary;
        break;
    }


    if (retBinary == "000001000000")
    {
        retBinary = "";
    }


    return retBinary;
}
int startDecoder(string word)
{
    int equal = 0;
    string fullBit;
    for (auto letter : word)
    {
        if (int(letter) == char(61))
        {
            equal += 1;
        }
        fullBit += findBit(letter, equal);

    }
    

    int elementWithEqual = 0;
    for(auto el : fullBit)
    {
        elementWithEqual++;
    }


    int s = 0;
    int SIZE = (elementWithEqual - (equal * 2)) / 8;
    string* arrOfEightBit = new string[SIZE];
    for (int i = 0; i < SIZE; i++, s += 8)
    {
        arrOfEightBit[i] = fullBit.substr(s, 8);
    }


    int* arrNum = new int[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        int exponent = 7;
        int sum = 0;
        for (int el : arrOfEightBit[i])
        {
            if (int(el) == 49)
            {
                int t = 2;
                int one = 1;


                for (int i = exponent; i > 0; i--)
                {
                    one *= 2;
                }


                exponent--;
                sum += one;
            }
            else
            {
                exponent--;
            }
            arrNum[i] = sum;
        }
    }


    cout << "Ваше розшифроване слово: ";
    for (int i = 0; i < SIZE; i++)
    {
        cout << char(arrNum[i]);
    }


    delete[] arrOfEightBit;
    delete[] arrNum;
    return 0;
}


int main()
{
    
    bool choice;
    cout << "1-кодер, 0-декодер" <<endl;
    cin >> choice;

    if (choice)
    {
        string word;
        cout << "Введіть слово: ";
        cin >> word;
        startCoder(word);
    }
    else
    {
        string word;
        cout << "Введіть слово: ";
        cin >> word;
        startDecoder(word);
    }
    
    
    
}






