#include "json/json.h"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
int main()
{
    // ifstream ifs("~/Desktop/Automatic_bench_options/env/config.json");
    ifstream ifs("../env/config.json");
    const static string dir  = "../env/config.json";
  Json::Value val(dir);
    Json::Reader reader;
    Json::Value obj;
    bool iff = reader.parse(ifs, obj); // reader can also read strings
    if(iff == false) cout << "fail" << endl;

    cout << obj["HPL"] << endl;
    cout << obj["HPL"]["mpirun"] << endl;
    cout << obj["test1"] << endl;
    cout << obj["test1"].asString() << endl;


  cout << val["HPL"]["mpirun"] << endl;



}