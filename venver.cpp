#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <filesystem>

using namespace std;

int main(int argc, char *argv[]){

    string py_path;
    stringstream line;
    string vers;
    ifstream paths("py_paths.txt");
    map<string, string> versions;
    string v_name = "venv";

    while ( not paths.eof() ){
        
        if (not (paths >> vers) or not (paths >> py_path)){
            cout<<"Break"<<endl;
            break;
        }
        versions[vers] = py_path;

    }

    cout << "Versioni disponibili: ";
    for( auto i : versions){
        cout<<i.first<<"  ";
    }
    cout<<endl;
    
    if (argc > 1){
        string arg = argv[1];
        if (argc > 2){
            v_name = argv[2];
        }

        if(arg.find(R"(C:\)") != string::npos){
            py_path = argv[1];
            cout<<"Path impostata manualmente."<<endl;
        }else{
            if(versions.find(arg) != versions.end()){
                py_path = versions.find(arg) -> second;
                cout<<"Versione impostata"<<endl;
            }else{
                cout<<"Versione non trovata"<<endl;
            }
        }
        
        if(filesystem::exists(".\\" + v_name)){
            cout<<"La cartella \""+ v_name + "\" esiste. Sostituirla? (Y/n)";
            string res;
            cin >> res;
            
            if(res != "n"){
                string command = "del /F /Q " + v_name;
                system(command.c_str());
                cout<<"Generazione in corso..."<<endl;
                command = "python -m virtualenv -p=\"" + py_path + "\" " + v_name;
                system(command.c_str());
                cout<<"virtual enviroment creato."<<endl;
                return 0;
            }else{
                cout<<"Operazione abortita."<<endl;
                return 0;
            }
            

        }else{
            cout<<"Generazione in corso..."<<endl;
            string command = "python -m virtualenv -p=\"" + py_path + "\" " + v_name;
            system(command.c_str());
            cout<<"virtual enviroment creato."<<endl;
            return 0;
        }
    }else{
        cout<<"Argomenti insufficenti."<<endl;
    }
    return 0;
} 