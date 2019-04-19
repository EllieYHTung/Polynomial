//
//  main.cpp
//  Polynomial
//
//  Created by YunHua Tung on 2019/4/12.
//  Copyright © 2019 YunHua Tung. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Term{
public:
    int coef;
    int exp;
    Term(string _a){
        string _temp;
        if(_a.find("X^")!=string::npos){
            
        }else if(_a.find("X")!=string::npos){
            _a.append("^1");
        }else{
            _a.append("X^0");
        }
        
        for(string::iterator it=_a.begin();it<_a.end();++it){
            _temp.push_back(*it);
            if(*it=='X'||*it=='^'){
                _temp.pop_back();
            }
            if( *(it+1)=='X' ){
                if(*it=='+' || *it=='-'){
                    _temp.push_back('1');
                }
                coef=atoi(_temp.c_str());
                _temp.clear();
            }
            if((it+1)==_a.end()){
                exp=atoi(_temp.c_str());
                _temp.clear();
            }
        }
    }
    
};
class Polynomial{
public:
    
    Polynomial(string _a){
        trans2Poly(_a);
        sort_decending();
    }
    Polynomial* operator +(Polynomial _addent){
        vector<Term*>::iterator _it_origin=this->poly_expression.begin();
        vector<Term*>::iterator _it_origin_end=this->poly_expression.end();
        vector<Term*>::iterator _it_addent=_addent.poly_expression.begin();
        vector<Term*>::iterator _it_addent_end=_addent.poly_expression.end();
    
        while(_it_origin<=_it_origin_end && _it_addent<=_it_addent_end){
            if((**_it_origin).exp==(**_it_addent).exp){
                (**_it_origin).coef=(**_it_origin).coef+(**_it_addent).coef;
                _it_origin++;
                _it_addent++;
            }else if((**_it_origin).exp<(**_it_addent).exp){
                this->poly_expression.insert(_it_origin, (*_it_addent));
                _it_addent++;
            }else{
                _it_origin++;
                
            }
        }
        
        sort_decending();
        
        return this;
    }
    void print_polynomial(){
        string _string_to_print="";
        for(vector<Term*>::iterator vt=poly_expression.begin();vt<poly_expression.end();++vt){
            if((**vt).coef>0){
                _string_to_print=_string_to_print + "+" +to_string((**vt).coef)+"X^"+to_string((**vt).exp);
            }else if((**vt).coef<0){
                
                _string_to_print=_string_to_print +to_string((**vt).coef)+"X^"+to_string((**vt).exp);
            }else{
                continue;
            }
        }
        cout<<_string_to_print<<endl;
    }
    void sort_decending(){
        vector<Term*>::iterator i=this->poly_expression.begin();
        vector<Term*>::iterator end=this->poly_expression.end();
        for(i=i+1;i<end;++i){
            int temp_e=(**i).exp;
            int temp_c=(**i).coef;
            vector<Term*>::iterator j=(i-1);
            while((**j).exp < temp_e){
                (**(j+1)).coef=(**j).coef;
                (**(j+1)).exp=(**j).exp;
                if(j==this->poly_expression.begin()){
                    break;
                }
                j--;
            }
            if(j==this->poly_expression.begin() && (**j).exp < temp_e){
                (**(j)).coef=temp_c;
                (**(j)).exp=temp_e;
            }else{
                (**(j+1)).coef=temp_c;
                (**(j+1)).exp=temp_e;
            }
            
        }
        
    }
protected:
    vector<Term*> poly_expression;
    
    void trans2Poly(string _a){
        string _temp;
        for(string::iterator it=_a.begin();it<_a.end();++it){
            _temp.push_back(*it);
            if( *(it+1)=='+' || (((*(it+1)=='-') && (*it !='^')))|| (it+1)==_a.end()){
                poly_expression.push_back(new Term(_temp));
                _temp.clear();
                
            }
        }
        
    }
    
};

int main(int argc, const char * argv[]) {
    Polynomial a_poly=Polynomial("-10X^6+15X^8-7X^17-11X^-4-X-80");
    Polynomial b_poly=Polynomial("-9X^9-3X^8+7X^6-11X^4+1X+9");

    a_poly.operator +(b_poly);
    a_poly.print_polynomial();
    
    //    Polynomial ans_poly = a_poly + b_poly;
    //    ans_poly.description();
    return 0;
}

/*
 #include <iostream>
 #include <string>
 #include <vector>
 using namespace std;
 
 class term{
 public:
 term(string poly_str){
 
 string _temp;
 
 bool is_exp = false;
 for(string::iterator it=poly_str.begin();it!=poly_str.end(); ++it){
 
 _temp.push_back(*it);
 
 if(*it == 'X') {
 _temp.pop_back();
 coef = atoi(_temp.c_str());
 exp = 1;
 _temp.clear();
 }
 else if (*it == '^') {
 _temp.pop_back();
 is_exp = true;
 }
 else if (it+1==poly_str.end()) {
 if (is_exp==true) {
 exp = atoi(_temp.c_str());
 _temp.clear();
 }
 else {
 coef = atoi(_temp.c_str());
 _temp.clear();
 }
 
 }
 }
 
 cout<<poly_str<<endl;
 cout<<"coef="<<coef<<endl;
 cout<<"exp="<<exp<<endl<<endl;
 }
 term(int _coef, int _exp){
 coef=_coef;
 exp=_exp;
 }
 public:
 int coef;
 int exp;
 
 };
 
 class polynomial{
 public:
 vector<term*> poly_items;
 polynomial(string _a){
 trans2Poly(_a);
 
 }
 
 friend polynomial operator+(const polynomial& lhs, const polynomial& rhs) {
 polynomial result = lhs;
 polynomial temp = rhs;
 
 
 vector<term*>::iterator begin = temp.poly_items.begin();
 vector<term*>::iterator end = temp.poly_items.end();
 vector<term*>::iterator it;
 for(it=begin ; it!=end ; it++){
 vector<term*>::iterator result_begin = result.poly_items.begin();
 vector<term*>::iterator result_end = result.poly_items.end();
 vector<term*>::iterator result_it;
 bool found = false;
 for(result_it=result_begin ; result_it!=result_end ; result_it++){
 if ((**result_it).exp==(**it).exp) {
 (**result_it).coef = (**result_it).coef + (**it).coef;
 found = true;
 break;
 }
 }
 
 if (false==found) {
 result.poly_items.push_back(*it);
 }
 
 }
 
 return result;
 }
 
 void description() {
 string description = "";
 
 vector<term*>::iterator begin = poly_items.begin();
 vector<term*>::iterator end = poly_items.end();
 vector<term*>::iterator it;
 for(it=begin ; it!=end ; it++){
 if ((**it).coef==0) {
 continue;
 }
 if ((**it).coef>0) {
 description = description + "+" + std::to_string((**it).coef) + "X^" + std::to_string((**it).exp);
 }
 else {
 description = description + std::to_string((**it).coef) + "X^" + std::to_string((**it).exp);
 }
 }
 
 cout<<description<<endl;
 }
 
 protected:
 void trans2Poly(string _a){
 
 string _temp;
 
 string sign_str = "+";
 for(string::iterator it=_a.begin();it!=_a.end(); ++it){
 
 _temp.push_back(*it);
 
 if(*it == '+' || *it =='-') {
 _temp.pop_back();
 poly_items.push_back(new term(sign_str + _temp));
 _temp.clear();
 sign_str = *it;
 }
 else if (it+1==_a.end()) {
 poly_items.push_back(new term(sign_str + _temp));
 _temp.clear();
 }
 }
 }
 
 static term poly_array[1000];
 static int free_index;
 };
 
 int main(int argc, const char * argv[]) {
 
 polynomial a_poly=polynomial("10X^9+15X^8-7X^7-11X^4+2X-8");
 a_poly.description();
 polynomial b_poly=polynomial("-9X^9-3X^8+7X^6-11X^4+1X+8");
 polynomial ans_poly = a_poly + b_poly;
 ans_poly.description();
 return 0;
 }
*/
/*
 using namespace std;
 #include <iostream>
 #define MaxTerms 10
 char compare(int a, int b){
 char result;
 if(a>b)
 result='>';
 else if(a<b)
 result='<';
 else
 result='=';
 return result;
 }
 
 class Polynomial;
 class term{
 friend Polynomial;
 private:
 float coef;
 int exp;
 };
 class Polynomial{
 private:
 static term termArray[MaxTerms];
 static int free;
 int Start, Finish;
 void NewTerm(float, int);
 Polynomial Add(Polynomial);
 
 };
 term Polynomial::termArray[MaxTerms];
 int Polynomial::free=0;
 void Polynomial::NewTerm(float c, int e){
 if(free>=MaxTerms){
 cerr<<"Too many terms in polynomials"<<endl;
 }
 termArray[free].coef=c;
 termArray[free].exp=e;
 free++;
 }
 Polynomial Polynomial::Add(Polynomial B){
 Polynomial C;
 int a=Start;
 int b=B.Start;
 C.Start=free;
 float c;
 while((a<Finish)&&(b<=B.Finish)){
 switch(compare(termArray[a].exp,termArray[b].exp)){
 case '=':
 c=termArray[a].coef+termArray[b].coef;
 if(c)
 NewTerm(c, termArray[a].exp);
 a++;
 b++;
 break;
 case '<':
 NewTerm(termArray[b].coef,termArray[b].exp);
 b++;
 case '>':
 NewTerm(termArray[a].coef,termArray[a].exp);
 a++;
 }
 }
 
 for(;a<=Finish;a++)
 NewTerm(termArray[a].coef,termArray[a].exp);
 for(;b<=B.Finish;b++)
 NewTerm(termArray[b].coef,termArray[b].exp);
 C.Finish=free-1;
 return C;
 }
 
 int main(int argc, const char * argv[]) {
 
 return 0;
 }
 */
