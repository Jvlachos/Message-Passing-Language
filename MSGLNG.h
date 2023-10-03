#include <iostream>
#include <map>
#include <regex>
#include <functional>
#include <string>
#include <type_traits>
#include <any>

#include <vector>

using namespace std;
#define let auto
#define object  Let()
#define values (*(new Let()))+
#define key(x) (*(new Let(x)))
#define input(msg) Element().handle(msg)
#define ref(obj) Let().get_ref(obj)
#define func(arg) (*(new Let(arg)))-[&](Let& obj) 
#define lambda (*(new Element()))^[&](Let& obj)
#define self(_key_) get_self(#_key_,obj)
#define arg(_key_)  get_arg(#_key_,obj)
#define call(x) (*(new Let(x,0)))
#define eval(cond) evaluate(cond,obj)
#define eval_cond(eval_cond)  evaluate_cond(eval_cond,obj)
#define args_list get_args(obj)
#define none "\0"
#define nl "\n"




class Let;


 enum  class Type{
      _integer,
      _double,
      _string,
      _boolean,
      _function,
      _object,
      _none

   };
 

class Element{
   private:
  
   double double_val;
   string string_val;
   bool bool_val;
   Let *obj;
   Type type;
    function<any(Let& obj)> my_lambda;
   public:
    int int_val;
  
   

   Element(){
      int_val = 0;
      double_val = 0;
      string_val = '\0';
      bool_val = false;
      type = Type::_none;
   } 
  
   

   void set_val(int val);
   void set_val(double val);
   void set_val(string val);
   void set_val(bool val);
   void set_val(function<any(Let& obj)>f);
   void set_val(Let& obj);
   void set_type(Type type);
   void set_val(const char* val);
  
   Element& handle(string msg);
  
   void parse(string const& input);
   template<typename T> Element& operator =(T new_val);
   Element& operator=( Element &Element);
   friend ostream& operator<<(ostream& os ,const Element& it);
   Element& operator^(function<any(Let& obj)> f){
     this->my_lambda = f;
     this->set_type({Type::_function});
     return *this;
}

   operator int() const{
      return this->int_val;
   }
   operator double() const{
      return this->double_val;
   }       
   operator string() const{
      return this->string_val;
   }

    operator bool() const{
      return this->bool_val;
   }
    int operator+(int value){
      int ret = this->int_val + value;
      return ret;
   } 
   double operator+(double value){
      double ret = this->double_val + value;
      return ret;
   }

   string operator+(string value){
      string ret = this->string_val + value;
      return ret;
   }

   bool operator==(bool expr){
      
      return bool_val == expr;
   }

   bool operator == (double expr){
      return double_val == expr;
   }

   bool operator == (int expr){
      return int_val == expr;
   }

   bool operator == (string expr){
      return string_val == expr;
   }
  
   

   bool operator==(const Element& i){

      //cout<<"VAL 1 : "<<int_val<<" VAL 2 :"<<i.int_val<<nl;
      //cout<<"TYPE 1 : "<<static_cast<int>(type) <<" TYPE 2 :"<<static_cast<int>(i.get_type());    
  
      if( type == Type::_integer && i.get_type() == Type ::_integer){
       
       return int_val == i.int_val;
     }
     if(type == Type::_integer && i.get_type() == Type ::_double){
       return int_val == i.double_val;
     }
     if(type == Type::_double && i.get_type() == Type ::_integer){
       return double_val == i.int_val;
     }
     if(type == Type::_double && i.get_type() == Type ::_double){
       return double_val == i.double_val;
     }
     if(type == Type::_boolean && i.get_type()== Type::_boolean){
       return bool_val == i.bool_val;
        
     }else{
        cout<<"Warning operation == failed!"<<nl;
     }
     return errno;
   }
  


    int operator-(int value){
      int ret = this->int_val - value;
      return ret;
   } 
   double operator-(double value){
      double ret = this->double_val - value;
      return ret;
   }

   string operator-(string value){
     cout<<"Warning, - operator can't be used on strings"<<nl;
      return "\0";
   }
   

   ///*
     int operator*(int value){
      int ret = this->int_val * value;
      return ret;
   } 
   double operator*(double value){
      double ret = this->double_val * value;
      return ret;
   }

   string operator*(string value){
      cout<<"Warning,* operator can't be used on strings"<<nl;
      return "\0";
   }
   
  double operator+(const Element& i){

     if( type == Type::_integer && i.get_type() == Type ::_integer){
       
       return int_val + i.int_val;
     }
     if(type == Type::_integer && i.get_type() == Type ::_double){
       return int_val + i.double_val;
     }
     if(type == Type::_double && i.get_type() == Type ::_integer){
       return double_val + i.int_val;
     }
     if(type == Type::_double && i.get_type() == Type ::_double){
       return double_val + i.double_val;
     }else if(type == Type::_boolean || i.get_type()== Type::_boolean){
        cout<<"Warning ,operation + failed!"<<nl;
        
     }
     return errno;
  }

  double operator-(const Element& i){
     int t_1,t_2;
     
     t_1 = static_cast<int>(this->get_type());
     t_2 = static_cast<int>(i.get_type());
     double val;
     if(t_1 == 0 && t_2 == 0){
       val = int_val - i.int_val;
     }
     if(t_1 == 0 && t_2 == 1){
       val = int_val - i.double_val;
     }
     if(t_1 == 1 && t_2 == 0){
       val =  double_val - i.int_val;
     }
     if(t_1 == 1 && t_2 == 1){
       val = double_val - i.double_val;
     }else{
        cout<<"Warning ,operation - failed!"<<nl;
        
     }
     
     return val;
  }
  double operator*(const Element &i){
     int t_1,t_2;
     t_1 = static_cast<int>(get_type());
     t_2 = static_cast<int>(i.get_type());
    
     if(t_1 == 0 && t_2 == 0){
       return int_val * i.int_val;
     }
     if(t_1 == 0 && t_2 == 1){
       return int_val * i.double_val;
     }
     if(t_1 == 1 && t_2 == 0){
       return double_val * i.int_val;
     }
     if(t_1 == 1 && t_2 == 1){
       return double_val * i.double_val;
     }else{
        cout<<"Warning ,operation * failed!"<<nl;
        
     }
     return errno;
  }

  double operator/(const Element &i){
     int t_1,t_2;
          cout<<"CALLED"<<nl;

     t_1 = static_cast<int>(this->get_type());
     t_2 = static_cast<int>(i.get_type());
     if(t_1 == 0 && t_2 == 0){
       return int_val / i.int_val;
     }
     if(t_1 == 0 && t_2 == 1){
       return int_val / i.double_val;
     }
     if(t_1 == 1 && t_2 == 0){
       return double_val / i.int_val;
     }
     if(t_1 == 1 && t_2 == 1){
       return double_val / i.double_val;
     }else{
        cout<<"Warning ,operation / failed!"<<nl;
        
     }
     return errno;

  }
 Type get_type()const{
   return this->type;
}

function<any(Let& obj)>get_func(){
   return this->my_lambda;
}

};


Element& Element::operator=(Element& Element){
  
   Type t = Element.type;
   switch (t)
   {
   case Type::_integer:
      this->set_val(Element.int_val);
      break;
   case Type::_double:
      this->set_val(Element.double_val);
      break;
   case Type::_string:
      this->set_val(Element.string_val);
      break;
   case Type::_boolean:
       this->set_val(Element.bool_val);
       break;
   case Type::_function:
       this->my_lambda = Element.my_lambda;
       break;
   case Type::_object:
       this->obj = Element.obj;    
       break;
   default:
      cout<<"Type Error"<<"\n";
      break;
   }

   return *this;
}

template<typename T> Element& Element::operator=(T new_val){
   this->set_val(new_val);
   
   return *this;
}



void Element::set_val(int val){
   this->type={Type::_integer};
   this->int_val = val;
}

void Element::set_val(double val){
   this->type={Type::_double};
   this->double_val = val;
}

void Element::set_val(string val){
   this->type={Type::_string};
   this->string_val = val;
}

void Element::set_val(const char* val){
   string s(val);
   this->type={Type::_string};
   this->string_val = s;
}

void Element::set_val(bool val){
   this->type={Type::_boolean};
   this->bool_val = val;
}

void Element::set_val(function<any(Let& obj)>f){
   this->type={Type::_function};
   this->my_lambda = f;
}

void Element::set_val(Let& obj){
   this->type={Type::_object};
   this->obj = &obj;
}

void Element::set_type(Type type){
   this->type = type;
}


 Element& Element::handle(string msg){
      string val;
      cout<<msg;
      cin >> val;
      parse(val);
      return *this;

   }

void Element::parse(string const& input) {
    static const regex doubleRegex{ R"([+\-]?(?:0|[1-9]\d*)(?:\.\d*)?(?:[eE][+\-]?\d+)?)" };
    static const regex intRegex{ R"(\d+)"};

    if (regex_match(input, intRegex)){
        istringstream inputStream(input);
        int i;
        inputStream >> i;
        this->set_val(i);
    }
    else if (regex_match(input, doubleRegex)) {
        istringstream inputStream(input);
        double d;
        inputStream >> d;
        this->set_val(d);
    }
    
    else {
        string s = input;
         
        if(s == "true"){
           this->set_val(true);
        }else if(s == "false"){
           this->set_val(false);
        }else{
           this->set_val(s);
        }
    }
}


ostream& operator<<(ostream& os ,const Element& it){
   Type t = it.type;
  
   switch (t)
   {
   case Type::_integer:
      os<<it.int_val;
      break;
   case Type::_double:
      os<<it.double_val;
      break;
   case Type::_string:
      os<<it.string_val;
      break;
   case Type::_boolean:
       os<<boolalpha<<it.bool_val;
       break;
    case Type::_function:
      //int i =any_cast<int>(it.my_lambda());
     
     // it.my_lambda();
      os<<"function";
      break;
    case Type::_object:
      
      os<<it.obj;
      break;            
   default:
      os<<"Error\n";
      break;
   }

   return os;
   
}

class Let{
   private:
   int index = -1;
   map<string,Element>data;
   string id;
   Let *ref = nullptr;
   Let  *receiver;
   Let *sender;
   string to_call;
   public:
   
   Let(){
      
      id = '\0';
      receiver = nullptr;
      sender = nullptr;
      to_call = '\0';
   }

   Let(string to_call,int flag){
      this->to_call = to_call;
   }

   Let(string id){
      this->id = id;
   }

   void add_to_map(const string key,const int value);
   void add_to_map(const string key,const double value);
   void add_to_map(const string key,const string value);
   void add_to_map(const string key,const bool value);
   void add_to_map(const string key,const char *value);
   void add_to_map(const string key,Let& obj);
   void add_to_map(const string key,const function<any(Let& obj)> func);
   void print();
   Let& get_sender(){
      return *(this->sender);
   }
   Let& get_receiver(){
      return *(this->receiver);
   }

   map<string,Element>get_map(){
      return this->data;
   }
   template<typename T> Let& operator=(T value);
   friend ostream& operator<<(ostream& os,const Let &l);
   Let& get_ref(Let l);
   Let& operator-(function<any(Let& obj)> func_){
       Element Element;
       if(func_ == nullptr){
          throw runtime_error("func is null");
       }
       
       Element.set_val(func_);
       data.insert({this->id,Element});
       return *this;
   }
   


   Let& operator=(Element& Element){
 
      this->data.insert({this->id,Element});
      return *this;
   }

   Element& operator[](const char* str){
      string s(str);
      map<string,Element>::iterator it;
      it =  this->data.find(s);
      return it->second;
      
   }

   Let& operator[]( Let& l){
      
      this->data.insert(l.data.begin(),l.data.end());
      this->index = l.index;
      this->id = l.id;
      this->to_call = l.to_call;
      return *this;
       
   } 

    Let& operator,(Let& l){
       
        this->data.insert(l.data.begin(),l.data.end());
       this->id = l.id;
       this->index = l.index;
       return *this;
   }

   Let& operator=(Let& l){
       this->to_call = l.to_call;
       this->data.insert(l.data.begin(),l.data.end());
       return *this;
   }
   
  
   template<typename T> Let& operator,(T value){
      
        this->index++;
       string key = to_string(this->index);
       this->add_to_map(key,value);
       //cout<<"Operator , called with value :"<<value<<" index is :"<<this->index<<"\n";
       
       return *this;
   }

   template<typename T> Let& operator+(T value){
       
       this->index++;
       string key = to_string(this->index);
       this->add_to_map(key,value);
       //cout<<"Operator + called with value :"<<value<< " index is :"<<this->index<<"\n";
 
       return *this;
   }

    void operator<<(Let& s){
      this->receiver = this;
      this->sender = &s;
      auto it = receiver->data.find(sender->to_call);
    
      if(it == data.end() ){
         throw runtime_error("Element does not exist!");
      }
     
      function<any(Let& obj)>to_call = it->second.get_func();
      to_call(*receiver);
      
   }

   

};

void Let::add_to_map(const string key ,const int value){
   Element i; 
   i.set_val(value);  
   data.insert({key,i});
}

void Let::add_to_map(const string key ,const double value){
   Element i= Element();
   i.set_val(value);
   data.insert({key,i});
}


void Let::add_to_map(const string key ,const bool value){
   Element i = Element();
   i.set_val(value);
   data.insert({key,i});
}

void Let::add_to_map(const string key,const char* value){
   Element i = Element();
   i.set_val(value);
   data.insert({key,i});
}

void Let::add_to_map(const string key,const function<any(Let& obj)> func){
   Element i = Element();
   i.set_val(func);
   i.set_type({Type::_function});
   data.insert({key,i});
}

void Let::add_to_map(const string key,Let& obj){
   Element i = Element();
   i.set_val(obj);
   data.insert({key,i});
}

ostream& operator<<(ostream &os , Let& l){
   cout<<"object [";
   for(const auto & element : l.get_map()){
      os<<"KEY :"<<element.first<<" "<<"VALUE :"<<element.second<<",";
   }
   os<<"]"<<"\n";
   return os;
}

void Let::print(){
     cout<<"object [";
   for(const auto & element : this->data){
      cout<<"KEY :"<<element.first<<" "<<"VALUE :"<<element.second<<",";
   }
   cout<<"]"<<"\n";
  

}

template<typename T> Let& Let::operator=(T value){
      
      this->add_to_map(this->id,value);
      return *this;
}


Let& Let::get_ref(Let l){
      ref = &l;
      return *ref;
   }

Element&  get_self(string key,Let& obj){
  
    Let *rec = &obj.get_receiver();
    //cout<<"REC VALUE : "<<rec->get_map().at(key).int_val;
    return  rec->get_map().at(key);
   
    
   
}

Element& get_arg(string key,Let& obj){
   Let *send =  &obj.get_sender();
   //cout<<"SEND VALUE : "<<send->get_map().at(key).int_val;
   return send->get_map().at(key);
   
  
   
}

void evaluate(string key,Let& l){
   Let* send = &l.get_sender();
   Let* rec = &l.get_receiver();
   
   if(!send){
     
      throw runtime_error("ERROR OBJECT NULL\n");
   }
 
  
   function<any(Let& obj)>to_call = send->get_map().at(key).get_func();
   to_call(*rec);
   
}

bool evaluate_cond(string cond,Let& l){
   Let* send = &l.get_sender();
   Let* rec = &l.get_receiver();
   
   if(!send){
     
      throw runtime_error("ERROR OBJECT NULL\n");
   }
   
 
   function<any(Let& obj)>to_call = send->get_map().at(cond).get_func();
   return any_cast<bool> (to_call(*rec));
   
}

vector<Element> get_args(Let& obj){
   Let* send = &obj.get_sender();
   vector<Element> args ;
   map<string,Element> map = send->get_map();
   for(auto &it : map){
       args.push_back(it.second);
   }
   return args;

}


   
