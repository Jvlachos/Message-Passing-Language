#include "MSGLNG.h"

using namespace std;
int main() {
    let o1 = object [
        key("x") = -1,
        key("y") = -2,
        func("mid") { return (self(x) + self(y)) * 0.5f; },
        func("+") {
            return object [
                key("x") = self(x) + arg(x),
                key("y") = self(y) + arg(y)
            ];
        }
    ];
    
    let o12 = object[key("peos") =1 ,values 1,"2",4.3,true];
    cout <<"O12 "<<o12<<nl;
    let o2 = object;
    let o3 = object [ values 1, "2",true, -3.14  ];
    std::cout <<o1<< o3<<endl;
    let printf_impl = object [
        key("x") = -1,
        key("y") = -2,
        func("printf") {
            for (auto& v : args_list){
                std::cout << v << nl;
            }
            return none;
            }
    ];

     o3 = object [ call("printf"), values 1, "2", true, -3.14, func("mid") { return (self(x) + self(y))*0.5f; } ];
    
    printf_impl<<o3;
    o1["x"] = true;
    o3["2"] = false;

    
    cout<<endl<<o1<<o3<<endl;

    o1["y"] = o1["x"] + o1["y"];
    cout<<o1<<endl;
    let obj=object[values ref(o1),"2",o1];
    obj["1"]=input("1: ");
    cout<<obj<<endl;
     
    
    let connection = object[
        call("connect"),
        key("ip") = "1.1.1.1",
        key("bool") = true,
        key("port") = 5000,
        func("cond"){ return arg(port) == self(port);},
        func("success"){
            cout << arg(ip) << " connected to "
            << self(ip) << nl;
            return none;
        },
        func("failure"){
            cout << arg(ip) << " failed to connect to "
            << self(ip) << nl;
            return none;
        }
    ];

    let conn_impl = object[
        key("ip") = "127.0.0.1",
        key("port") = 3030,
        func("connect"){
            if(eval_cond("cond")){
                eval("success");
            }
            else
                eval("failure");
            return none;
        }
    ];

   conn_impl << connection;
    return 0;
}



