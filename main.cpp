#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Key
{
    int e;
    int n;
};

struct result 
{
  int u,v;
};

//function
int generate();
int pgcd(int a,int b);
Key generatK();
long long convert(int);
int indienn(int c,Key key);
result Euclide_e(int e,int phi);
void  encrypt(string file,Key key ,string &fileC);
void  dcrypt(string file,Key key,string &fileD);

int main() 
{
    char choice; string file,fileC,fileD; Key key;  bool  result;
     // Ask if encryption or decryption 
    cout << "Welome  "<<endl ;
    cout << "upload the file ( file location  ) "<<endl ;
    cin >> file; 
    cout << " you want to encrypt '1' or decrypt '2' "<<endl ;
    cout << " choose '1' or '2' please "<<endl ;
    cin >> choice ;
    
    switch(choice)
    {
      case('1'):
        cout <<"you want to generate a key '1' or you have one '0' !"<<endl ;
        cin >> result;
        if (result==true)
        {
        //generate a key 
          key=generatK();
        }
        else 
        {
          cout << "Enter your public  key" <<endl ;  
          cin >> key.e;
          cin >> key.n;
        }
        //aappel a la methode 
        encrypt(file,key,fileC);
        break;

      case('2') :
          
        cout << "Enter your secret  key" <<endl ;  
        cin >> key.e;
        cin >> key.n;
        //appel la méthode
        dcrypt(file,key,fileD);
        break ;
    }
}
int generate()
{
  int  p,i,cpt ; bool premier=false;
  while(premier==false )
  {
   p = rand() % 100 + 1;   //p in the range 1 to 100
   if(p <=1) 
        premier= false ;
   else { 
       cpt=0;
       for(i=2;i<=(p/2);i++)
       {
           if(p%i==0)    cpt+=1;
       }
       if (cpt==0) premier=true;
         }
  }
   return  p;
}

int pgcd(int a,int b)
{ 
if(b==0) return a;
else 
    { if(a>b)
      return pgcd(b,a%b);
      else 
      return pgcd(a,b%a);
    }
}

Key generatK()
{    Key key; result s;
    int p,q,n,e,phi,res;
    bool  quit;
    
    p=generate(); 
    q=generate();

    n=p*q;
    phi=(p-1)*(q-1);
    e=3;
    while(e<phi & quit==false)
    {
        res=pgcd(e,phi);
        if (res==1)
           { quit=true; }
        else {
             e+=1; }
    }
        key.e=e;
        key.n=n;
        cout << "the public key  ("<< e <<","<< n << ")" <<endl;
        s=Euclide_e(e,phi);
        cout << "the secret key  ("<<s.u<<"," << n << ")" <<endl;
    return key;
}

result Euclide_e(int e,int phi)
{
  result s; int  u0,u1,v0,v1,r0,r1,ri,vi,ui,qi;
  if(e>phi)
    {
     r0=e; u0=1; v0=0;
     r1=phi; u1=0; v1=1;
    }
  else 
   {
      r0=phi; u0=0; v0=1;
      r1=e; u1=1; v1=0;
   }
   ri=2;
   while(ri>1)
   {
     ri=r0%r1;
     qi=r0/r1;
     ui=u0-(qi*u1);
     vi=v0-(qi*v1);

     r0=r1;
     u0=u1;
     v0=v1;
     r1=ri;
     u1=ui;
     v1=vi;
   }
    s.u=ui;
    s.v=vi;
return s;
}

long long convert(int n) 
{
  long long bin = 0;
  int rem, i = 1;
  while (n!=0) 
  {
    rem = n % 2;
    n /= 2;
    bin += rem * i;
    i *= 10;
  }
  return bin;
}

int indienn(int c,Key key)
{
    long long bin; int v; string str;
    bin=convert(key.e);//convert key.e to binary 
    str= to_string(bin);
    v=1;
    for(int i=0;i<str.size();i++)
    {
      v=(v*v)%key.n;
      if (str[i] =='1' )
      {
          v=(v*c)%key.n;
      }
    }
  return v;  
}

void  encrypt(string file,Key key,string &fileC)
{
  char m; int c,mm;
    ifstream f (file);
    if (!f.is_open())
    {
         cout << "Unable to open the file for reading " << endl;
    }
    else
    {  
      ofstream fc ("fichC.txt");
      while(!f.eof())
     {
       f >> m;
       if(m!=' ')
       {  mm=int(m);
          c= indienn(mm,key);
         
             if (!fc.is_open())
                cout << "Unable to open the file for writing !" << endl;
             else
             {  
                fc << c << ' ';
               // To better visualise encryption 
             }
       }
     }
     cout << " your file has been properly encrypted " << endl;
    }
}

void  dcrypt(string file,Key key,string &fileD)
{
  string m; int c,cc; char d;
  ifstream f (file);
  if (!f.is_open())
   {
         cout << "Unable to open the file for reading " << endl;
   }
  else
   {
      ofstream fd ("fichD.txt");
      while(!f.eof())
     {
       f >> m; 
       cc=stoi(m); 
       c= indienn(cc,key);
       d=char(c);
       if (!fd.is_open())
                cout << "Unable to open the file for writing" << endl;
             else
             {  
                fd << d << ' '; // To better visualise encryption 
             }      
      }
      cout << " your file has been successfully decrypted " << endl;
    }
}
