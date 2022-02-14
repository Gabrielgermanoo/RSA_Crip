//Projeto de Criptografia RSA - Matemática Discreta
//Alunos: Adonys Henrique, Aryel Amaral, Gabriel Lucas, Victor Alexandre

#include<bits/stdc++.h> 
#define ll long long 
using namespace std;
int escolha;
ll p,q,e,n,chaven,chavee,fi;
string mensagem,mensageme,mensagemd,mm;
vector<ll> msg;
ll inv(ll a, ll b, ll & x, ll & y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    ll x1, y1;
    ll d = inv(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}


long long mod(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)    
            res = res * a % m; 
        a = a * a % m;
        b >>= 1; 
    }
    return res;
}


void encriptar(){//encripta a mensagem
    for(auto a: mensagem){
        if(a==' '){
            ll b = 28;
            b = mod(b,chavee,chaven);
            ll k = b;
            mm+=to_string(k)+' ';
            msg.push_back(b);
        }else{
            ll b =  a - 0;
            b-=63;
            b = mod(b,chavee,chaven);
            ll k = b;
            mm+=to_string(k)+' ';
            msg.push_back(b);
        }
    }
    return;
}


void desencriptar(){
    fi = (p-1)*(q-1);
    n = p*q;
    ll x,y;
    inv(e,fi,x,y);
    ll d = (x % fi + fi)% fi;
    for(auto k : msg){
        ll b = mod(k,d,n);
        if(b==28){
            mensagemd +=' ';
        }else{
            mensagemd += (char)(b+63);
        }
    }
    return;
}


int main(){
    cout<<"Criptografia RSA - Matematica Discreta\n";
    while(true){
        cout<<"Insira '1' para gerar uma chave publica, '2' para encriptar uma mensagem ou '3' para desencriptar uma mensagem. Insira '0' para sair do programa.";
        cin>>escolha;
        if(escolha == 1){
            cout<<"Insira o numero primo 'p':";
            cin>>p;
            cout<<"Insira o numero primo 'q':";
            cin>>q;
            cout<<"Insira o expoente 'e':";
            cin>>e;
            n = p*q;
            ofstream out("chave_publica.txt");
            out<<"("<<n<<","<<e<<")";
            out.close();
            cout<<"Chave publica gerada com sucesso, verifique em chave_publica.txt"<<endl;
        }
        else if(escolha == 2){
            cout<<"Insira a mensagem que sera criptografada: ";
            cin.ignore();
            getline(cin,mensagem);
            cout<<"Insira a chave publica gerada anteriormente: ";
            cin>>chaven>>chavee;
            encriptar();
            ofstream out("mensagem_encriptada.txt");
            out<<"Mensagem Encriptada: "<<mm;
            out.close();
            cout<<"Mensagem encriptada gerada com sucesso, verifique em mensagem_encriptada.txt"<<endl;
        }
        else if(escolha == 3){ 
            cout<<"Insira o numero primo 'p':";
            cin>>p;
            cout<<"Insira o numero primo 'q':";
            cin>>q;
            cout<<"Insira o expoente 'e': ";
            cin>>e;
            desencriptar();
            ofstream out("mensagem_desencripatada.txt");
            out<<"Mensagem Desencriptada: "<<mensagemd;
            out.close();
            cout<<"Gerada a mensagem desencriptada, verifique em mensagem_desencripatada.txt"<<endl;
        }
        else if(escolha == 0){
            return 0;
        }
        else{ 
            cout<<"Valor inserido invalido.\n";
        }
    }
    return 0;
}
