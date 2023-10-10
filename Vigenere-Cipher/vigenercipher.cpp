/*
Nama        : Raffanisa Kamila Z
NPM         : 140810210067
Deskripsi   : Tugas 5 Vigenere Cipher
*/

#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main(){
    int i, j, k, n, pilih;
    string s, key;
    bool loop = true;

    vector<vector<char> > a(26,vector<char>(26));
    k=0;
    n=26;
    for(i=0;i<n;i++){
        k=i;
        for(j=0;j<n;j++){
            a[i][j]='A'+k;
            k++;
            if(k==26)
                k=0;
        }
    }

    while(loop){
        cout << "\n\n________________________________________\n";
        cout << "     PROGRAM VIGENERE CIPHER        \n";
        cout << "__________________________________________\n";

        cout << "\nMENU";
        cout << "\n------\n";
        cout << "1. Enkripsi \n";
        cout << "2. Dekripsi \n";
        cout << "Pilih menu : ";
        cin >> pilih;
        cout << "__________________________________________\n";

        switch (pilih)
        {
            case 1: {
                cout<<"Masukkan plaintext    : ";
                cin>>s;
                cout<<"Masukkan kunci        : ";
                cin>>key;
                k=0;

                int mod = key.size();
                for(i=key.size();i<s.size();i++){
                    key+=key[k%mod];
                    k++;
                }

                string enkripsi;
                for(i=0;i<s.size();i++){
                    enkripsi+= a[s[i]-'A'][key[i]-'A'];
                }

                cout<<"Ciphertext            : "<<enkripsi<<'\n';
                break;
            }
                

            case 2: {
                cout<<"Masukkan ciphertext  : ";
                cin>>s;
                cout<<"Masukkan kunci       : ";
                cin>>key;
                k=0;

                for(i=key.size();i<s.size();i++){
                    key+=key[k];
                    k++;
                }

                string dekripsi;
                for(i=0;i<s.size();i++){
                    for(j=0;j<n;j++){
                        if(a[j][key[i]-'A']==s[i]){
                            dekripsi += 'A'+j;
                        }
                    }
                }
                cout<<"Plaintext            : "<<dekripsi<<'\n';
                break;
            }

        default:
            break;   
        }

        cout << "\nExit? (Y/N): ";
        char optionLoop;
        cin >> optionLoop;
        if (optionLoop == 'n' || optionLoop == 'N')
            loop = true;
        else
            loop = false;
    }
    return 0;
}