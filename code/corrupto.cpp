#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>



using namespace std;

bool randomEveryTime = false;

void wobble(char* bytes, int len, int count, int amount, int wobbleVersion){
	int currCounter = 0;
	for(int i = 0; i < len; i++){
		if (currCounter >= count){
			currCounter = 0;
			if (randomEveryTime){ count = (rand()%(len-(2-1)))+2; }
			if ( i == 0){
				bytes[i] += bytes[i+amount];
			}else if ( i == (len-1)){
				bytes[i] += bytes[i-amount];
			}else{
				switch (wobbleVersion){
					case 0:
						bytes[i] += bytes[i+amount];
						bytes[i] -= bytes[i-amount];
						break;
					case 1:
						bytes[i] -= bytes[i+amount];
						bytes[i] += bytes[i-amount];
						break;
					case 2:
						bytes[i] += bytes[i+amount];
						bytes[i] += bytes[i-amount];
						break;
					case 3:
						bytes[i] -= bytes[i+amount];
						bytes[i] -= bytes[i-amount];
						break;
					case 4:
						bytes[i] *= bytes[i+amount];
						bytes[i] /= bytes[i-amount];
						break;
					case 5:
						bytes[i] /= bytes[i+amount];
						bytes[i] *= bytes[i-amount];
						break;
					case 6:
						bytes[i] *= bytes[i+amount];
						bytes[i] *= bytes[i-amount];
						break;
					case 7:
						bytes[i] /= bytes[i+amount];
						bytes[i] /= bytes[i-amount];
						break;
					default:
						cout << "\e[1mProgram Error\e[0m" << endl;
						exit (EXIT_FAILURE);
				}
			}
		}else{
			currCounter++;
		}
	}
}

void swap(char* bytes, int len, int count, int amount, int swapVersion){
	int currCounter = 0;
	char tempByte;
	for(int i = 0; i < len; i++){
		if (currCounter >= count){
			currCounter = 0;
			if (randomEveryTime){ count = (rand()%(len-(2-1)))+2; }
			if (( i == 0 ) || ( i == (len-1) )){
				tempByte = bytes[len-1];
				bytes[len-1] = bytes[0];
				bytes[0] = tempByte;
			}else{
				switch (swapVersion){
					case 0:
						tempByte = bytes[i+amount];
						bytes[i+amount] = bytes[i];
						bytes[i] = tempByte;
						break;
					case 1:
						tempByte = bytes[i-amount];
						bytes[i-amount] = bytes[i];
						bytes[i] = tempByte;
						break;
					default:
						cout << "\e[1mProgram Error\e[0m" << endl;
						exit (EXIT_FAILURE);
				}
			}
		}else{
			currCounter++;
		}
	}
}

void adjust(char* bytes, int len, int count, int amount, int adjustVersion){
	int currCounter = 0;
	char tempByte;
	for(int i = 0; i < len; i++){
		if (currCounter >= count){
			currCounter = 0;
			if (randomEveryTime){ count = (rand()%(len-(2-1)))+2; }
			switch (adjustVersion){
				case 0:
					bytes[i] += amount;
					break;
				case 1:
					bytes[i] *= amount;
					break;
				case 2:
					bytes[i] /= amount;
					break;
				default:
					cout << "\e[1mProgram Error\e[0m" << endl;
					exit (EXIT_FAILURE);
			}
		}else{
			currCounter++;
		}
	}
}

void fswap(char* bytes, char* bytes2, int len, int len2, int count, int amount, int adjustVersion){
	int currCounter = 0;
	int i2=0;
	char tempByte;
	for(int i = 0; i < len; i++){
		if (currCounter >= count){
			currCounter = 0;
			if (randomEveryTime){ count = (rand()%(len-(2-1)))+2; }
			switch (adjustVersion){
				case 0:
					bytes[i] = bytes2[i2];
					break;
				default:
					cout << "\e[1mProgram Error\e[0m" << endl;
					exit (EXIT_FAILURE);
			}
		}else{
			currCounter++;
			if (i2 > len2){
				i2=0;
			}else{
				i2++;
			}
		}
	}
}

int main(int argc, char* argv[])
{
	//help:
	//command inFile outFile setting everynth changeamount everynthType [seed]

	size_t sz;

	int everyNth;
	int changeAmount;

	unsigned int seed = time(NULL);

	int argsGiven[7];
	//TODO: look into why last element in array is really big for the moment though this works :)
	for (int i = 0; i < 7; i++){
		argsGiven[i] = 0;
	}

	string in,in2,out,setting,everyNthSetting;

	if ( (argc-1)%2 != 0){
		cout << "\e[1mProgram Error\e[0m" << endl;
		exit(EXIT_FAILURE); //each argument should have a thing in front e.g (-i in.nes) they come in pairs
	}

	int argCount = 1;
	for (int i = 0; i < ((argc-1)/2); i++){
		if ( ((string)argv[argCount]).substr(0,1) != "-"){
			cout << "\e[1mProgram Error\e[0m" << endl;
			exit(EXIT_FAILURE);
		}
		switch ( ((string)argv[argCount])[1] ){
			case 'i':
				cout << "\e[1mIN\e[0m" << ", ";
				argsGiven[0]++;
				if (argsGiven[0] > 1){
					if (!(argsGiven[0] > 2)){
						in2 = ((string)argv[argCount+1]);
					}else{
						cout << "\e[1mToo Many Files Supplied\e[0m" << endl;
						exit(EXIT_FAILURE);
					}
				}else{
					in = ((string)argv[argCount+1]);
				}
				break;
			case 'o':
				cout << "\e[1mOUT\e[0m" << ", ";
				argsGiven[1]++;
				out = ((string)argv[argCount+1]);
				break;
			case 's':
				cout << "\e[1mSETTING\e[0m" << ", ";
				argsGiven[2]++;
				setting = ((string)argv[argCount+1]);
				break;
			case 'n':
				cout << "\e[1mEVERY NTH\e[0m" << ", ";
				argsGiven[3]++;
				everyNth = stoi(((string)argv[argCount+1]));
				break;
			case 'a':
				cout << "\e[1mCHANGE AMOUNT\e[0m" << ", ";
				argsGiven[4]++;
				changeAmount = stoi(((string)argv[argCount+1]));
				break;
			case 'x':
				cout << "\e[1mEVERY NTH TYPE\e[0m" << ", ";
				argsGiven[5]++;
				everyNthSetting = ((string)argv[argCount+1]);
				break;
			case 'r':
				cout << "\e[1mSEED\e[0m" << ", ";
				argsGiven[6]++;
				seed = stoi(((string)argv[argCount+1]));
				break;
			default:
				cout << "\e[1mUnrecognised Command\e[0m" << endl;
				exit(EXIT_FAILURE);
		}
		argCount+=2;
	}

	cout << endl;

	for (int i = 1; i < 5; i++){
		if (argsGiven[i] != 1){
			cout << "\e[1mMinimum Arguments Not Met\e[0m" << endl;
			exit(EXIT_FAILURE);
		}
	}

	if (argsGiven[0] == 0){
		cout << "\e[1mNeed Input File\e[0m" << endl;
		exit(EXIT_FAILURE);
	}

	cout << "TEST" << endl;

	ifstream inStream(in, ios::binary|ios::ate); //open file stream
	int length = (ifstream::pos_type) inStream.tellg(); //current stream position which is like the end of file so length is pos

	int corrCounter = everyNth;

	//TODO: update output where if rando every dont print everynth maybe print N/A?
	if (argc >= 7){
		if ( everyNthSetting == "divide" ){ corrCounter = length/everyNth; }
		//TODO: add max option to command line
		else if ( everyNthSetting == "random" ){ srand(seed); corrCounter = (rand()%(length-(2-1)))+2; }
		else if ( everyNthSetting == "randomrepeat" ){ srand(seed); corrCounter = (rand()%(length-(2-1)))+2; randomEveryTime = true; }
	}

	char *fileBytes = new char[length]; //create char array for file bytes

	inStream.seekg(0, ios::beg);
	inStream.read(fileBytes, length); //read file bytes into char array

	inStream.close(); //close file as we adjust array as we dont need it anymore

	cout << "TEST2" << endl;

	//apply correct corruption
	if ( setting.find("wobble") != string::npos ){
		int version = 0;
		if (!( setting.substr(6,2) == "" )){
			version = stoi( setting.substr(6,2), &sz );
			cout << version << endl;
		}
		
		wobble(fileBytes, length, corrCounter, changeAmount, version);
	}else if( setting.find("swap") != string::npos ){
		int version = 0;
		if (!( setting.substr(5,2) == "" )){
			version = stoi( setting.substr(5,2), &sz );
		}

		swap(fileBytes, length, corrCounter, changeAmount, version);
	}else if( setting.find("adjust") != string::npos ){
		int version = 0;
		if (!( setting.substr(6,2) == "" )){
			version = stoi( setting.substr(6,2), &sz );
		}

		adjust(fileBytes, length, corrCounter, changeAmount, version);
	}else if( setting.find("fswap") != string::npos ){ //file swap
		int version = 0;
		if (!( setting.substr(5,2) == "" )){
			version = stoi( setting.substr(5,2), &sz );
		}

		if ( argsGiven[0] != 2 ){
			cout << "\e[1mYou Can Only Specify Two Input Files\e[0m" << endl;
			exit(EXIT_FAILURE);
		}

		cout << "SUBTEST1" << endl;
		cout << in2 << endl;
		ifstream inStream2(in2, ios::binary|ios::ate);
		cout << "SUBTEST2" << endl;
		int length2 = (ifstream::pos_type) inStream2.tellg();
		cout << "SUBTEST3" << endl;
		cout << length2 << endl;

		char *fileBytes2 = new char[length2]; //create char array for file bytes
		cout << "SUBTEST4" << endl;

		inStream2.seekg(0, ios::beg);
		cout << "SUBTEST5" << endl;
		inStream2.read(fileBytes2, length2); //read file bytes into char array
		cout << "SUBTEST6" << endl;

		inStream2.close(); //close file as we adjust array as we dont need it anymore
		cout << "SUBTEST7" << endl;


		

		fswap(fileBytes, fileBytes2, length, length2, corrCounter, changeAmount, version);
	}else{
		cout << "\e[1mProgram Error\e[0m" << endl;
		return 0;
	}

	cout << "TEST3" << endl;

	//info

	cout << "in: " << in << ", out: " << out << ", setting: " << (string)argv[3];
	
	if (!(randomEveryTime)){ cout << ", everyNth: " << everyNth; }

	cout << ", changeAmount: " << changeAmount << endl;

	cout << " WAGAMAMA " << corrCounter << endl;

	cout << "length: " << length << endl;

	if ( (string)argv[6] == "random" ){
		cout << "seed: " << seed << endl;
	}

	ofstream(out, ios::binary).write(fileBytes, length); //write corrupted bytes to file
}
