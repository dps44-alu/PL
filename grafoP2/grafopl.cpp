#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

unordered_set<string> terminales = {
    "id", "pari", "pard", "int", "float", "llavei", 
    "llaved", "asig", "pyc", "if", "opas", "numentero", "numreal"
};

unordered_set<string> noTerminales = {
    "Fun", "Tipo", "Bloque", "SInstr", "Instr", "E", "T"
};

unordered_map<string, vector<vector<string>>> reglas = {
    {"Fun",    {{"Tipo", "id", "pari", "pard", "Bloque"}}},
    {"Tipo",   {{"int"}, 
                {"float"}}},
    {"Bloque", {{"llavei", "SInstr", "llaved"}}},
    {"SInstr", {{"SInstr", "Instr"},
                {"Instr"}}},
    {"Instr",  {{"Bloque"}, 
                {"id", "asig", "E", "pyc"},
                {"if", "pari", "E", "pard", "Instr"},
                {"Tipo", "id", "pyc"}}},
    {"E",      {{"E", "opas", "T"},
                {"T"}}},
    {"T",      {{"numentero"}, 
                {"numreal"}, 
                {"id"}}}
};


vector<vector<vector<string>>> sol;


bool esNumero (const string& e)
{
    return all_of(e.begin(), e.end(), ::isdigit);
}

// Crea un bloque a partir de una linea
vector<vector<string>> crearBloque(const vector<string>& linea, const vector<vector<string>>& mas_lineas = {})
{
    // Crea el bloque y le añade la primera linea
    vector<vector<string>> bloque;
    bloque.push_back(linea);

    for (const auto& linea_extra : mas_lineas)
    {
        bloque.push_back(linea_extra);
    }

    for (int i = 0; i < bloque.size(); i++)
    {
        int pos = stoi(bloque[i][0]);   // to_int

        // Si la posición del punto está detrás del último elemento, sigue con la siguiente linea
        if (pos == bloque[i].size())
        {
            continue;
        }

        string a = bloque[i][pos];      // a es igual al elemento que tiene delante el punto

        // Si el elemento (a) es no terminal, amplia el bloque, sino continua con la siguiente linea
        if (noTerminales.find(a) != noTerminales.end())
        {
            for (const auto& regla : reglas)                    
            {  
                if (regla.first == a)                               // El primero de la regla es el no terminal
                {                             
                    for (const auto& secuencia : regla.second)      // Reglas del no terminal
                    {
                        vector<string> nueva_linea = {"2", a};                           // Se añade la nueva línea
                        for (const auto& simbolo : secuencia)  
                        {
                            nueva_linea.push_back(simbolo);               // Añadimos cada simbolo de la secuencia
                        }
                        if (linea.size() == 3 && linea[2] == "#")   // Comprueba q no sea sólo el elemento vacío
                        {
                            nueva_linea.pop_back();
                        }

                        // Si la linea ya está en el bloque, continua sin desarrollarla
                        bool repetida = false;
                        for (const auto& ln : bloque)
                        {
                            if (ln == nueva_linea)  repetida = true;
                        }
                        if (!repetida) bloque.push_back(nueva_linea);                    // Agregamos la nueva línea al bloque
                    }
                }
            }
        }
    }
    return bloque;
}

// Crea la solucion a partir de crear bloques, a partir de lineas que no encabecen ningún bloque
vector<vector<vector<string>>> analizador(const vector<vector<string>>& bloque)
{
    // Posición dentro de sol en donde se encuentra el bloque actual
    int sol_i = 0;
    for (const auto& bl : sol)
    {
        if (bl == bloque)   break;
        sol_i++;
    }

    // Posiciones de las lineas en el bloque que avanzan al mismo bloque
    vector<string> elementos;                   // Elementos que avanzamos y su posición en el bloque
    for (const auto& ln : bloque)
    {
        int pos = stoi(ln[0]);                   // pos señala al elemento que tiene el punto delante
        if (pos < ln.size())
        {
            elementos.push_back(ln[pos]);                // Guardamos el elemento que estamos avanzando
        }
    }

    // Elementos repetidos y posiciones de sus lineas en el bloque
    vector<pair<string, unordered_set<int>>> lineas_comunes;       // Posiciones de las lineas que evolucionan al mismo bloque
    for (int i = 0; i < elementos.size(); i++)
    {
        // Si el elemento ya ha sido encontrado, continua con el siguiente
        bool repetido = false;
        for (const auto& ln : lineas_comunes)
        {
            if (ln.first == elementos[i])
            {
                repetido = true;
            }
        }
        if (repetido)   continue;

        bool encontrado = false;
        for (int j = 0; j < elementos.size(); j++)
        {
            if (i != j)     // Si las posiciones son distintas, sino es el mismo elemento
            {
                if (elementos[i] == elementos[j])
                {
                    // Si no se ha encontrado el elemento, se añade con las posiciones donde se encuentra
                    if (!encontrado)
                    {
                        // Elemento que se repite, posiciones del bloque een las que está
                        lineas_comunes.push_back({elementos[i], {i, j}});
                        encontrado = true;
                    }
                    else
                    {
                        // Si no existe la posición, añadirla
                        lineas_comunes[lineas_comunes.size() - 1].second.insert(j);
                    }

                }
            }
        }
    }

    // Obtener las lineas que no se han desarrollado en otro bloque
    vector<vector<string>> lineas_no_hechas;    // Lineas del bloque que no están desarrolldas en otro bloque
    for (int i = 0; i < bloque.size(); i++)     // Para cada línea del bloque
    {
        int pos = stoi(bloque[i][0]);                   // pos señala al elemento que tiene el punto delante
        if (pos < bloque[i].size())                         // Si la línea no ha sido recorrida entera (3 -> 0, 1, 2)
        {
            // +1 a la posición del punto, ahora apunta al siguiente elemento
            if (esNumero(bloque[i].back())) sol[sol_i][i].pop_back();
            vector<string> linea = bloque[i];
            linea[0] = to_string(stoi(bloque[i][0]) + 1);

            bool hecho = false;
            for (int j = 0; j < sol.size(); j++)
            {
                for (int k = 0; k < sol[j].size(); k++)
                {
                    vector<string> linea_aux = sol[j][k];    // Primera linea del bloque

                    // Si el ultimo elemento de la linea es un número, eliminalo para poder comparalas
                    if (esNumero(linea_aux.back())) linea_aux.pop_back();

                    // Si la linea es igual a la linea de otro bloque, entonces esa linea ya se ha hecho
                    if (linea == linea_aux)
                    {
                        // Si el último elemento de la linea del bloque actual en la solución no es un número
                        if (!esNumero(bloque[i][bloque[i].size() - 1]))
                        {
                            // Añadir al final de la línea un puntero al bloque que la resuelve
                            sol[sol_i][i].push_back(to_string(j));
                        }
                        hecho = true;
                    }

                    // Sal del bucle si ya se ha encontrado
                    if (hecho)  break;
                }

                // Sal del bucle si ya se ha encontrado
                if (hecho)  break;
            }

            if (!hecho) lineas_no_hechas.push_back(linea);
        }
    }

    vector<vector<vector<string>>> bloques_nuevos;
    for (int a = 0; a < lineas_no_hechas.size(); a++)    // Para cada linea no hecha
    {
        // Lineas extras para crear el bloque
        vector<vector<string>> lineas_extra = {};

        // pos señala al elemento que tiene el punto delante
        // (el del bloque actual, no del elemento del que se hará un nuevo bloque)
        int pos = stoi(lineas_no_hechas[a][0]) - 1;
        vector<string> linea_aux = lineas_no_hechas[a];   // linea_aux es una linea no hecha

        // -1 al puntero que indica donde está el punto
        linea_aux[0] = to_string(pos);

        // Buscar la posición de la linea no hecha en el bloque
        int bloque_i = 0;
        for (const auto& li : bloque)   // Para cada linea del bloque
        {
            if (linea_aux == li)   break;   // Si la encuentras, deja de contar
            bloque_i++;
        }

        // Añade al final de la linea no hecha el puntero al bloque que la va a desarrollar,
        // que será el siguiente al actual último de la solución
        if (!esNumero(sol[sol_i][bloque_i].back()))
        {
            sol[sol_i][bloque_i].push_back(to_string(sol.size() + a));
        }
        else
        {
            // Si los números son distintos
            if (stoi(sol[sol_i][bloque_i].back()) != sol.size())
            {
                sol[sol_i][bloque_i].pop_back();
                sol[sol_i][bloque_i].push_back(to_string(sol.size()));
            }
        }

        // Comprobar si está en los repetidos
        for (const auto& elemento : lineas_comunes)
        {
            if (elemento.first == lineas_no_hechas[a][pos])
            {
                for (const auto& posicion : elemento.second)
                {
                    // Si la posicion no está ya añadida
                    if (posicion != bloque_i)
                    {
                        if (!esNumero(sol[sol_i][posicion].back()))
                        {
                            sol[sol_i][posicion].push_back(to_string(sol.size()));
                        }
                        else 
                        {
                            // Si los números son distintos
                            if (stoi(sol[sol_i][posicion].back()) != sol.size())
                            {
                                if (find(elemento.second.begin(), elemento.second.end(), bloque_i) != elemento.second.end())
                                {
                                    sol[sol_i][posicion].pop_back();
                                    sol[sol_i][posicion].push_back(to_string(sol.size()));
                                    sol[sol_i][posicion][0] = to_string(stoi(sol[sol_i][posicion][0]) + 1);
                                    lineas_extra.push_back(sol[sol_i][posicion]);
                                }
                            }
                        }

                        // Eliminarla de linias_no_hechas y añadirla en lineas extra
                        for (int i = 0; i < lineas_no_hechas.size(); i++)
                        {
                            // Se resta uno a la posición del punto para poder comparar
                            vector<string> linea_temp0 = bloque[posicion];  // Linea temporal para comparar
                            linea_temp0.pop_back();

                            // Se resta uno a la posición del punto para poder comparar
                            vector<string> linea_temp1 = lineas_no_hechas[i];  // Linea temporal para comparar
                            linea_temp1[0] = to_string(stoi(linea_temp1[0]) - 1);

                            if (linea_temp0 == linea_temp1)
                            {
                                if (!esNumero(sol[sol_i][posicion].back()))
                                {
                                    sol[sol_i][posicion].push_back(to_string(sol.size()));
                                }
                                // Si es número
                                /*
                                else 
                                {
                                    // Si los números son distintos
                                    if (stoi(sol[sol_i][posicion].back()) != sol.size())
                                    {
                                        sol[sol_i][posicion].pop_back();
                                        sol[sol_i][posicion].push_back(to_string(sol.size()));
                                    }
                                }
                                */
                                lineas_no_hechas.erase(lineas_no_hechas.begin() + i);   // Eliminarla de lineas_no_hechas

                                linea_temp1[0] = to_string(stoi(linea_temp1[0]) + 1);
                                lineas_extra.push_back(linea_temp1);   // Añadirla en lineas extra
                            }
                        }
                    }
                }
            }
        }

        // Se crea el bloque con la linea no hecha y se añade a bloques_nuevos y a la solución
        vector<vector<string>> b = crearBloque(lineas_no_hechas[a], lineas_extra);
        bloques_nuevos.push_back(b);
        //sol.push_back(b);
    }

    return bloques_nuevos;
}

void desarrollar_bloque ()
{
    for (int i = 0; i < sol.size(); i++)
    {
        vector<vector<vector<string>>> bloques_nuevos = analizador(sol[i]);

        for (const auto& b : bloques_nuevos)
        {
            sol.push_back(b);
        }
    }
}

void imprimir()
{
    ofstream file("sol2.txt");

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo para escribir." << endl;
        exit;
    }

    int i = 0;
    for (const auto& b : sol)
    {
        i++;
        file << "I-" << i - 1 << endl;

        for (const auto& l : b)
        {
            int j = 0;
            for (const auto& e : l)
            {
                if (j > 0) {
                    if (esNumero(e))
                    {
                        file << "\t___ I-";
                    }
                    file << e << " ";
                    if (j == 1) {
                        file << "-> ";
                    }
                    if (j == stoi(l[0]) - 1) {
                        file << "* ";
                    }
                }
                j++;
            }
            file << endl;
        }
        file << endl;
    }
} 

int main()
{
    // Posición del punto, NoTerminal de la izquierda, cadena de la derecha (1 ... n-1), posición de sol donde se desarrola
    vector<string> linea = {"2", "X", "Fun"};

    // Se crea el bloque a partir de la linea y se añade a la solución
    vector<vector<string>> bloque = crearBloque(linea);
    sol.push_back(bloque);

    desarrollar_bloque();

    imprimir();

    return 0;
}