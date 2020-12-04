//============================================================================
// Name        : Day2_Part1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <ios>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include <regex>

using namespace std;
using Passport = std::map<string, string>;

using Passports = std::vector<Passport>;



void splitLineToKeyValues(Passport & passport, std::string line){
	std::istringstream iline(line);
	std::string word, key, value;
	while (!iline.eof()){
		iline >> word;
		key = word.substr(0, word.find(":"));
		value = word.substr(word.find(":") + 1, word.length());

		passport.insert(std::pair<string, string>(key, value));
	}
}

void splitPassports(Passports & p, std::istream & io) {
	io >> std::noskipws;

	std::string line{};
	int curPassport {0};

	if(p.size() == 0) p.push_back(Passport());
	while(!io.eof()){
		std::getline(io, line);
		if(line.compare("") == 0){
			p.push_back(Passport());
			curPassport++;
			continue;
		}
		splitLineToKeyValues(p.at(curPassport), line);
	}
}

bool validateHexcolor(string value){
	return std::regex_match (value, std::regex("^#[0-9a-fA-F]{6}$"));
}

bool validateEyeColor(string value){
	string regex {"^(amb|blu|brn|gry|grn|hzl|oth)$"};

	return std::regex_match (value, std::regex(regex));
}

bool validateId(string value ){
	return std::regex_match (value, std::regex("^0*[0-9]+$")) && value.size() == 9;
}

bool validateNum(string value, int bottom, int upper){
	int n = std::stoi(value);
	return n >= bottom && n <= upper;
}

bool validateHgt(string value, int bottomCm, int upperCm, int bottomIn, int upperIn){
	return std::regex_match (value, std::regex("^((1[5-8][0-9]|19[0-3])cm|(59|6[0-9]|7[0-6])in)$"));
}

bool ValidateValue(Passport & p){
	for(pair<string, string> v : p){
		cout << v.first << " : " << v.second << std::endl;
	}

	if(!validateNum(p.find("byr")->second, 1920, 2002)) return false;
	if(!validateNum(p.find("iyr")->second, 2010, 2020)) return false;
	if(!validateNum(p.find("eyr")->second, 2020, 2030)) return false;
	if(!validateHgt(p.find("hgt")->second, 150, 193, 56, 76)) return false;
	if(!validateHexcolor(p.find("hcl")->second)) return false;
	if(!validateEyeColor(p.find("ecl")->second)) return false;
	if(!validateId(p.find("pid")->second)) return false;
	return true;
}

bool passportValidate(Passport & p){
	std::vector<string> const required { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };

	std::vector<string> const optional { "cid" };

	for(string field : required){
		if(p.find(field) == end(p)) return false;
	}

	return ValidateValue(p);
}

int main() {
	std::ifstream file;
	file.open("input.txt");
	string line;
	std::vector<string> vec{};

	int count{0};

	Passports p{};
	if(file){
		splitPassports(p, file);

		std::for_each(begin(p), end(p), [&count](Passport passport){

			if(passportValidate(passport)){
					count++;
			}
		});
	}

	std::cout << "Matches found: " << count << std::endl;
}


