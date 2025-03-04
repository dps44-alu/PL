#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

unordered_set<string> terminales = {
    "int", "float", "pari", "pard", "coma", "amp", 
    "llavei", "llaved", "asig", "pyc", "if", "opas", 
    "numerero", "numreal", "id"
};

unordered_set<string> noTerminales = {
    "Fun", "Tipo", "Args", "LArgs", "MasArgs", "A", 
    "Var", "Bloque", "SInstr", "SInstrp", "Instr", 
    "Init", "E", "Ep", "T"
};

unordered_map<string, vector<vector<string>>> reglas = {
    {"Fun",    {{"Tipo", "id", "Args", "Bloque"}}},
    {"Tipo",   {{"int"}, 
                {"float"}}},
    {"Args",   {{"pari", "LArgs", "pard"}}},            
    {"LArgs",  {{"A", "MasArgs"}, 
                {"#"}}},
    {"MasArgs",{{"coma", "A", "MasArgs"},
                {"#"}}},
    {"A",      {{"Tipo", "Var"}}},
    {"Var",    {{"amp", "id"},
                {"id"}}},
    {"Bloque", {{"llavei", "SInstr", "llaved"}}},
    {"SInstr", {{"Instr", "SInstrp"}}},
    {"SInstrp",{{"Instr", "SInstrp"}, 
                {"#"}}},
    {"Instr",  {{"Bloque"}, 
                {"id", "asig", "E", "pyc"},
                {"if", "pari", "E", "pard", "Instr"},
                {"Tipo", "id", "Init"}}},
    {"Init",   {{"pyc"},
                {"asig", "E", "pyc"}}},
    {"E",      {{"T", "Ep"}}},
    {"Ep",     {{"opas", "T", "Ep"}, 
                {"#"}}},
    {"T",      {{"numerero"}, 
                {"numreal"}, 
                {"id"}}}
};



vector<vector<string>> crearBloque(vector<string>& linea)
{
    vector<vector<string>> bloque;
    bloque.push_back(linea);

    int i = 0;
    while (i < bloque.size())
    {
        int pos = stoi(bloque[i][0]);   // to_int

        if (pos == bloque[i].size())
        {
            i++;
            continue;
        }

        string a = bloque[i][pos];

        if (noTerminales.find(a) != noTerminales.end())             // Es no terminal
        {
            for (const auto& regla : reglas)                    
            {  
                if (regla.first == a)                               // El primero de la regla es el no terminal
                {                             
                    for (const auto& secuencia : regla.second)      // Reglas del no terminal
                    {
                        linea = {"2", a};                           // Se añade la nueva línea
                        for (const auto& simbolo : secuencia)  
                        {
                            linea.push_back(simbolo);               // Añadimos cada simbolo de la secuencia
                        }
                        if (linea.size() == 3 && linea[2] == "#")   // Comprueba q no sea sólo el elemento vacío
                        {
                            linea.pop_back();
                        }
                        bloque.push_back(linea);                    // Agregamos la nueva línea al bloque
                    }
                }
            }
        }
        i++;
    }
    return bloque;
}

void analizador(vector<vector<vector<string>>>& sol, vector<string>& linea)
{
    vector<vector<string>> bloque = crearBloque(linea);
    sol.push_back(bloque);

    for (int i = 0; i < bloque.size(); i++)             // Para cada línea del bloque
    {
        int pos = stoi(bloque[i][0]);                   // pos es la posición del puntero
        if (pos != bloque[i].size())                    // Si la línea no ha sido recorrida entera
        {
            linea = bloque[i];
            linea[0] = to_string(stoi(bloque[i][0]) + 1);

            bool hecho = false;
            for (const auto& b : sol)
            {
                if (linea == b[0])
                {
                    hecho = true;
                }
            }

            if (!hecho) analizador(sol, linea);
        }
    }
}

void imprimir(const vector<vector<vector<string>>>& sol)
{
    ofstream file("sol.txt");

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo para escribir." << endl;
        exit;
    }

    for (int i = 0; i < sol.size(); i++)
    {
        file << "I-" << i + 1 << endl;

        for (int j = 0; j < sol[i].size(); j++)
        {   
            for (int k = 1; k < sol[i][j].size(); k++)
            {
                file << sol[i][j][k] << " ";
                if (k == 1)
                {
                    file << "-> ";
                }
                if (k == stoi(sol[i][j][0]) - 1)
                {
                    file << "· ";
                }
            }
            file << endl;
        }
        file << endl;
    }
} 

int main()
{
    vector<vector<vector<string>>> sol;
    vector<string> linea = {"2", "X", "Fun"};              // Posición del punto, NoTerminal de la izquierda, cadena de la derecha (1 ... n-1)

    analizador(sol, linea);

    imprimir(sol);

    return 0;
}