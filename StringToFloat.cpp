#include <iostream>
#include <math.h>
#include <cmath>
#include <cfloat>

using namespace std;

enum State {START, DONE, GOT_SIGN, GOT_DIGIT, GOT_DECIMAL, GOT_DECIMAL_DIGIT, GOT_EXP_SIGN, GOT_EXP, GOT_EXP_DIGIT };
float stringToFloat(const char input[]){
	State s = START;
	float result = 0;
	int i = 0;
	int sign = 1;
	int DecimalVal = -1;
	int expSign = 1;
	int expVal = 0;
	char character = input[i];
	int number = input[i] - '0';

	if (character == '\0'){
		return NAN;
	}

	while (s != DONE){

		switch(s) {

		case START:
			if ((character == '-') || (character == '+')) {
				s = GOT_SIGN;
			}

			else if ((number >= 0) && (number <= 9)) {
				s = GOT_DIGIT;
			}

			else if (character == '.'){
				s = GOT_DECIMAL;
			}

			else {
				return NAN;
			}

			break;

		case GOT_SIGN:
			
			if (character == '+') {
				sign = 1;
			}

			else if (character == '-'){	
				sign = -1;
			}

			i++;
			character = input[i];
			number = input[i] - '0';

			if ((number >= 0) && (number <= 9)){
				s = GOT_DIGIT;
			}

			else if (character == '.'){
				s = GOT_DECIMAL;
			}

			else {
				return NAN;
			}

			break;

		case GOT_DIGIT:
				
			if (result > (FLT_MAX/10 - number)) {
				return INFINITY;
			}

			if (result < ((-1*FLT_MAX)/10 - number)){
				return -INFINITY;
			} 

			result = (result*10) + number;

			if (input[i+1] == '\0'){
				result = result * sign;
			}

			i++;
			character = input[i];
			number = input[i] - '0';

			if ((number >= 0) && (number <= 9)){
				s = GOT_DIGIT;
			}

			else if (character == '.'){
				s = GOT_DECIMAL;
			}
			
			else if ((character =='e') || (character == 'E')){
				s = GOT_EXP;
			}

			else if (character == '\0'){
				return result;
			}

			else {
				return NAN;
			}

			break;

		case GOT_DECIMAL:

			result = result + 0.0;
			i++;
			character = input[i];
			number = input[i] - '0';

			if ((number >= 0) && (number <= 9)){
				s = GOT_DECIMAL_DIGIT;
			}

			else if ((character == '-') || (character == '+')){
				s = GOT_EXP_SIGN;
			}

			else {
				return NAN;
			}

			break;

		case GOT_DECIMAL_DIGIT:

			result = result + (number * (pow(10, DecimalVal)));
			DecimalVal = DecimalVal - 1;
			
			if (input[i+1] == '\0'){
				result = result * sign;
			}

			i++;
			character = input[i];
			number = input[i] - '0';


			if ((number >= 0) && (number <= 9)){
				s = GOT_DECIMAL_DIGIT;
			}

			else if ((character =='e') || (character == 'E')){
				s = GOT_EXP;
			}

			else if (character == '\0'){
				return result;
			}

			else {
				return NAN;
			}

			break;

		case GOT_EXP_SIGN:

			if (character == '+') {
			
				i++;
				character = input[i];
				number = input[i] - '0';
			
				if ((number >= 0) && (number <= 9)){
					s = GOT_EXP_DIGIT;
				}

				else {
					return NAN;
				}
			}

			else if (character == '-'){
			
				expSign = -1;
				i++;
				character = input[i];
				number = input[i] - '0';
			
				if ((number >= 0) && (number <= 9)){
					s = GOT_EXP_DIGIT;
				}

				else {
					return NAN;
				}
			}

			else {
				return NAN;
			}

			break;


		case GOT_EXP:

			i++;
			character = input[i];
			number = input[i] - '0';

			if ((number >= 0) && (number <= 9)){
				s = GOT_EXP_DIGIT;
			}
			
			else if ((character == '-') || (character == '+')) {
				s = GOT_EXP_SIGN;
			}

			else {
				return NAN;
			}

			break;

		case GOT_EXP_DIGIT:
			
			if (expVal*expSign < 0){
				result = sign * result * (pow(10, expVal));
				if (result > (FLT_MAX/10 - number)) {
					result = 0;
					return result;
				}
			}
			
			if (expVal*expSign > 0){
				result = sign * result * (pow(10, expVal));
				if (result > (FLT_MAX/10 - number)) {
					return INFINITY;
				}
			}
			
			if (input[i+1] != '\0') {
				expVal = expVal*10 + number;
				if (expVal > (FLT_MAX/10 - number)) {
					if (expVal*expSign < 0){
						result = 0;
						return result;
					}
					else if (expVal*expSign > 0){
						result = INFINITY;
						return result;
					}
				}
				i++;
			}

			else if (input[i+1] == '\0'){
				expVal = (expVal*10 + number) * expSign;
				result = (result * (pow(10, expVal))) * sign;	
				i++;
			}

			character = input[i];
			number = input[i] - '0';

			if ((number >= 0) && (number <= 9)){
				s = GOT_EXP_DIGIT;
			}

			else if (character == '\0'){
				s = DONE;
			}

			else {
				return NAN;
			}

			break;

		case DONE:
			break;

		default:
			return NAN;

		}
	}

	return result;
}