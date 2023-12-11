#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class hamming{
	public:
		string data; 
		int m , r = 0; 
		char * msg; 
		hamming(string data){
			this->data = data;
			reverse(data.begin(),data.end());
			m = data.size();
			int power = 1;

			while(power < (m + r + 1)){
				r++;
				power*=2;
			}
			msg = new char[m+r+1];
			int curr = 0;

			for(int i = 1 ; i <= m+r ; i++){
				if(i & (i-1)){
					msg[i] = data[curr++];
				}
				else msg[i] = 'n';
			}
			setRedundantBits();
		}
		void showmsg(){
			cout << "the data packet to be sent is : ";
			for(int i = m+r ; i >= 1 ; i--){
				cout << msg[i] << " ";
			}
			cout << endl;
		}
		void setRedundantBits(){
			
			int bit = 0;
			for(int i = 1 ; i <= m+r ; i*=2){
				int count = 0;
				for(int j = i+1 ; j<=m+r ; j++){
					if(j & (1 << bit)){
						if(msg[j] == '1') count++;        
					}
				}
				if(count & 1) msg[i] = '1';
				else msg[i] = '0';
				bit++;
			}
			showmsg();
		}
		void receiver(){
			string ans = "";
			int bit = 0;
			for(int i = 1 ; i <= m+r ; i*=2){
				int count = 0;
				for(int j = i+1 ; j<=m+r ; j++){
					if(j & (1 << bit)){
						if(msg[j] == '1') count++;
					}
				}
				if(count & 1){
					if(msg[i] == '1') ans.push_back('0');
					else ans.push_back('1');
				}
				else{
					if(msg[i]=='0') ans.push_back('0');
					else ans.push_back('1');
				}
				bit++;
			}
			if(ans.find('1') != string::npos){
				int power = 1;
				int wrongbit = 0;
				for(int i = 0 ; i < ans.size() ; i++){
					if(ans[i]=='1') wrongbit+=power;
					power*=2;
				}
				cout << "bit number " << wrongbit << " is wrong and having error " << endl;
			}
	
			else{
				cout << "correct data packet received " << endl;
			}
		}
};
int main(){
	string data = "1011001";
	hamming h(data);


	h.receiver();
	return 0;
}

