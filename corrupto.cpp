#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

void wobble(char* bytes, int len, int count, int amount, int wobbleVersion){
	int currCounter = 0;
	for(int i = 0; i < len; i++){
		if (currCounter >= count){
			currCounter = 0;
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
						cout << "Program Error";
				}
			}
		}else{
			currCounter++;
		}
	}
}

void shift(char* bytes, int len, int count, int amount, int shiftVersion){
	int currCounter = 0;
	char tempByte;
	for(int i = 0; i < len; i++){
		if (currCounter >= count){
			currCounter = 0;
			if (( i == 0 ) || ( i == (len-1) )){
				tempByte = bytes[len-1];
				bytes[len-1] = bytes[0];
				bytes[0] = tempByte;
			}else{
				switch (shiftVersion){
					case 0:
						tempByte = bytes[i+amount];
						bytes[i+amount] = bytes[i];
						bytes[i] = tempByte;
						break;
					default:
						cout << "Program Error";
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
					cout << "Program Error";
			}
		}else{
			currCounter++;
		}
	}
}

int main(int argc, char* argv[])
{
	//help:
	//command inFile outFile setting everynth changeamount

	size_t sz;

	int everyNth = stoi (argv[4],&sz);
	int changeAmount = stoi (argv[5],&sz);


	string in,out;
	in = (string) argv[1];
	out = (string) argv[2];

	ifstream inStream(in, ios::binary|ios::ate); //open file stream
	int length = (ifstream::pos_type) inStream.tellg(); //current stream position which is like the end of file so length is pos

	int corrCounter = length/everyNth; //real everynth so actually tricking user, TODO: stop tricking user

	char *fileBytes = new char[length]; //create char array for file bytes

	inStream.seekg(0, ios::beg);
	inStream.read(fileBytes, length); //read file bytes into char array

	inStream.close(); //close file as we adjust array as we dont need it anymore

	//apply correct corruption
	if ( ((string)argv[3]).find("wobble") != string::npos ){

		int version = 0;
		if (!( ((string)argv[3]).substr(6,2) == "" )){
			version = stoi( ((string)argv[3]).substr(6,2), &sz );
		}
		
		wobble(fileBytes, length, corrCounter, changeAmount, version);
	}else if( ((string)argv[3]).find("shift") != string::npos ){
		int version = 0;
		if (!( ((string)argv[3]).substr(5,2) == "" )){
			version = stoi( ((string)argv[3]).substr(5,2), &sz );
		}

		shift(fileBytes, length, corrCounter, changeAmount, version);
	}else if( ((string)argv[3]).find("adjust") != string::npos ){
		int version = 0;
		if (!( ((string)argv[3]).substr(6,2) == "" )){
			version = stoi( ((string)argv[3]).substr(6,2), &sz );
		}

		adjust(fileBytes, length, corrCounter, changeAmount, version);
	}else{
		cout << "Invalid Setting" << endl;
		return 0;
	}

	//info
	cout << "in: " << in << ", out: " << out << ", setting: " << (string)argv[3] << ", everyNth: " << everyNth << ", changeAmount: " << changeAmount << endl; //command line args
	cout << "length: " << length << endl;//output length

	ofstream(out, ios::binary).write(fileBytes, length); //write corrupted bytes to file
}
