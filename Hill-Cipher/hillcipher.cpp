/*
Nama        : Raffanisa Kamila Zikri
NPM         : 1408102167
Deskripsi   : Tugas 3 Praktikum Kriptografi (Hill Cipher Enkripsi, Dekripsi dan Mencari Kunci)
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int invMod(int a, int m){
    a = a % m;
    for (int x = -m; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return 0;
}

void cofactorMatrix(vector<vector<int> > &a, vector<vector<int> > &temp, int p, int q, int n){
    int i = 0, j = 0;
    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++){
            if (row != p && col != q){
                temp[i][j++] = a[row][col];
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int detMatrix(vector<vector<int> > &a, int n, int N){
    int D = 0;
    if (n == 1)
        return a[0][0];
    vector<vector<int> > temp(N, vector<int>(N));
    int sign = 1;
    for (int f = 0; f < n; f++){
        cofactorMatrix(a, temp, 0, f, n);
        D += sign * a[0][f] * detMatrix(temp, n - 1, N);
        sign = -sign;
    }
    return D;
}

void adjMatrix(vector<vector<int> > &a, vector<vector<int> > &adj, int N){
    if (N == 1){
        adj[0][0] = 1;
        return;
    }
    int sign = 1;
    vector<vector<int> > temp(N, vector<int>(N));
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cofactorMatrix(a, temp, i, j, N);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign) * (detMatrix(temp, N - 1, N));
        }
    }
}

bool inverse(vector<vector<int> > &a, vector<vector<int> > &inv, int N){
    int det = detMatrix(a, N, N);
    if (det == 0){
        return false;
    }
    int invDet = invMod(det, 26);
    vector<vector<int> > adj(N, vector<int>(N));
    adjMatrix(a, adj, N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            inv[i][j] = (adj[i][j] * invDet) % 26;
    return true;
}

string enkripsi(string text, int size, vector<vector<int> > key){
    string result = "";
    int temp = (size - text.size() % size) % size;

    for (int i = 0; i < temp; i++){
        text += 'x';
    }

    int k = 0;
    while (k < text.size()){
        for (int i = 0; i < size; i++){
            int sum = 0;
            int temp = k;

            for (int j = 0; j < size; j++){
                if (isupper(text[temp])){
                    sum += (key[i][j] % 26 * (text[temp++] - 'A') % 26) % 26;
                }
                else{
                    sum += (key[i][j] % 26 * (text[temp++] - 'a') % 26) % 26;
                }
                sum = sum % 26;
            }
            result += (sum + 'A');
        }
        k += size;
    }
    return result;
}

string dekripsi(string ciphertext, vector<vector<int> > a, vector<vector<int> > inv, int n){
    if (inverse(a, inv, n)){
        int k = 0;
        string dekripsi;
        while (k < ciphertext.size()){
            for (int i = 0; i < n; i++){
                int sum = 0;
                int temp = k;
                for (int j = 0; j < n; j++){
                    if (isupper(ciphertext[temp])){
                        sum += ((inv[i][j] + 26) % 26 * (ciphertext[temp++] - 'A') % 26) % 26;
                    }
                    else{
                        sum += ((inv[i][j] + 26) % 26 * (ciphertext[temp++] - 'a') % 26) % 26;
                    }
                    sum = sum % 26;
                }
                dekripsi += (sum + 'A');
            }
            k += n;
        }

        int f = dekripsi.size() - 1;
        while (dekripsi[f] == 'x'){
            f--;
        }

        return dekripsi;
    }
    return "xx Inversi Kunci Matriks Tidak Ada xx";
}

void printMatrix(vector<vector<int> > matrix, int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

int main(){
    string text, ciphertext, plaintext;
    int option, num, size, count;
    bool loop = true;

    while (loop){
        cout << "\n\n[       PROGRAM HILL CIPHER        ]\n\n";
        cout << "\nUkuran Matriks Key: ";
        cin >> size;

        vector<vector<int> > key(size, vector<int>(size));
        vector<vector<int> > adj(size, vector<int>(size));
        vector<vector<int> > inv(size, vector<int>(size));
        vector<vector<int> > c(size, vector<int>(size));
        vector<vector<int> > p(size, vector<int>(size));

		cout << "\nMENU\n\n";
        cout << "1. Enkripsi \n";
        cout << "2. Dekripsi \n";
        cout << "3. Cari Key \n";
        cout << "Masukan nomor yang dipilih : ";
        cin >> num;
        cout << "___________________________________\n";

        switch (num){
        case 1:
            cout << "\nMasukan Kunci Matriks " << size << "x" << size << ": \n";
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    cout << "[" << i << "][" << j << "]: ";
                    cin >> key[i][j];
                }
            }

            cin.ignore();
			cout << "__________________________________\n";
            cout << "\nMasukan Plaintext: ";
            getline(cin, text);
            cout << "__________________________________\n";

            ciphertext = enkripsi(text, size, key);

            cout << "Hasil Enkripsi: " << ciphertext << '\n';
            break;
		
        case 2:
            cout << "\nMasukan Kunci Matriks " << size << "x" << size << ": \n";
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    cout << "[" << i << "][" << j << "]: ";
                    cin >> key[i][j];
                }
            }

            cin.ignore();
			cout << "__________________________________\n";
            cout << "\nMasukan Ciphertext: ";
            getline(cin, text);
			cout << "__________________________________\n";

            plaintext = dekripsi(text, key, inv, size);

            cout << "Hasil Dekripsi: " << plaintext << '\n';
            break;

        case 3:
            cin.ignore();
            cout << "\nMasukan Plaintext: ";
            getline(cin, plaintext);

            cout << "Masukan Ciphertext: ";
            getline(cin, ciphertext);
			cout << "__________________________________\n";

            count = 0;
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    if (isupper(ciphertext[count])){
                        c[j][i] = ciphertext[count] - 'A';
                    }
                    else{
                        c[j][i] = ciphertext[count] - 'a';
                    }

                    if (isupper(plaintext[count])){
                        p[j][i] = plaintext[count] - 'A';
                    }
                    else{
                        p[j][i] = plaintext[count] - 'a';
                    }
                    count++;
                }
            }

            inverse(p, inv, size);

            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    key[i][j] = 0;

                    for (int k = 0; k < size; k++)
                        key[i][j] = key[i][j] + (c[i][k] * inv[k][j]);
                    key[i][j] %= 26;

                    if (key[i][j] < 0)
                        key[i][j] = 26 + key[i][j];
                }
            }

            cout << "\nKunci Hill Cipher: \n";
            printMatrix(key, size);
            break;
        default:
            break;
        }

        cout << "\nKeluar? (y/n): ";
        char optionLoop;
        cin >> optionLoop;
        if (optionLoop == 'n' || optionLoop == 'N')
            loop = true;
        else
            loop = false;
    }
    return 0;
}
