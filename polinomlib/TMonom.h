#pragma once
#include <sstream>
#include <string>

struct TMonom
{
	double coef; 
	int index; 

	TMonom() {
		coef = 0;
		index = 0;
	}

    TMonom(std::string str) {
        coef = 0;
        index = 0;
        int degX = 0, degY = 0, degZ = 0;


        std::stringstream ss(str);
        std::string token;


        std::getline(ss, token, 'x');
        if (token.find('y') != std::string::npos || token.find('z') != std::string::npos) {
            std::stringstream temp_ss(token);
            std::getline(temp_ss, token, 'y');
            if (token.find('z') != std::string::npos) {
                std::stringstream temp2_ss(token);
                std::getline(temp2_ss, token, 'z');
                coef = std::stod(token);
                if (temp2_ss.peek() == '^') {
                    temp2_ss.ignore();
                    std::getline(temp2_ss, token);
                    degZ = std::stoi(token);
                }
            }
            else {
                coef = std::stod(token);
                if (temp_ss.peek() == '^') {
                    temp_ss.ignore();
                    std::getline(temp_ss, token);
                    degY = std::stoi(token);
                }
            }
        }
        else {
            coef = std::stod(token);
            if (ss.peek() == '^') {
                ss.ignore();
                std::getline(ss, token, 'y');
                degX = std::stoi(token);
            }
        }

        if (ss.peek() == '^') {
            ss.ignore();
            std::getline(ss, token, 'z');
            degY = std::stoi(token);
        }

        if (ss.peek() == '^') {
            ss.ignore();
            std::getline(ss, token);
            degZ = std::stoi(token);
        }


        if (degX > 9 || degY > 9 || degZ > 9 || degX < 0 || degY < 0 || degZ < 0) {
            throw std::out_of_range("0 <= Degree <= 9");
        }


        index += degX * 100;
        index += degY * 10;
        index += degZ;
    }

	TMonom(double coef, int degX, int degY, int degZ) {
		this->coef = coef;
		this->index = 0;
		if (degX > 9 || degY > 9 || degZ > 9 || degX < 0 || degY < 0 || degZ < 0) {
			throw std::out_of_range("0 <= Degree <= 9");
		}
		index += degX * 100;
		index += degY * 10;
		index += degZ;
	}

	void SetCoef(double cval) { coef = cval; }
	double GetCoef(void) { return coef; }

	void SetIndex(int ival) { index = ival; }
	int GetIndex(void) { return index; }

	bool operator==(const TMonom& other) const {
		return coef == other.coef && index == other.index;
	}

    bool operator!=(const TMonom& other) const {
        return !(*this == other);
    }

	bool operator>(const TMonom& other) {
		if (index == 0 || other.index == 0) {
			throw std::invalid_argument("Cannot compare with zero index");
		}
		return index > other.index;
	}

	bool operator<(const TMonom& other) {
		if (index == 0 || other.index == 0) {
			throw std::invalid_argument("Cannot compare with zero index");
		}
		return index < other.index;
	}
};