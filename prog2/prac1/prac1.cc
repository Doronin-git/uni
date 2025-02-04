#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <cstring> // Para strcpy(), strcat() y strcmp()
#include <vector>
#include <cstdio>



using namespace std;

const int kTEAMNAME=40; // Máximo tamaño del nombre de un equipo
const int kPLAYERNAME=50; // Máximo tamaño del nombre de un jugador
const int kPLAYERS=5; // Número de jugadores por equipo
const int kMAXTEAMS=20; // Número máximo de equipos
const int kMINTEAMS=2; // Número mínimo de equipos

// Registro para los jugadores
struct Player{
    char name[kPLAYERNAME];
    unsigned int goals;
    bool best;
};

// Registro para los equipos
struct Team{
    unsigned int id;
    char name[kTEAMNAME];
    unsigned int wins;
    unsigned int losses;
    unsigned int draws;
    unsigned int points;
    Player players[kPLAYERS];
};

// Tipos de error posibles
enum Error{
    ERR_EMPTY,
    ERR_MAX_TEAMS,
    ERR_NO_LEAGUE,
    ERR_NO_TEAMS,
    ERR_NOT_EXIST,
    ERR_NUM_TEAMS,
    ERR_OPTION
};

/* Función que muestra los mensajes de error
e: tipo de error a mostrar
return: nada
*/
void error(Error e){
    switch(e){
        case ERR_EMPTY: cout << "ERROR: empty string" << endl;
            break;
        case ERR_MAX_TEAMS: cout << "ERROR: maximum number of teams reached" << endl;
            break;
        case ERR_NO_LEAGUE: cout << "ERROR: there are no standings" << endl;
            break;
        case ERR_NO_TEAMS: cout << "ERROR: there are no teams" << endl;
            break;
        case ERR_NOT_EXIST: cout << "ERROR: team does not exist" << endl;
            break;
        case ERR_NUM_TEAMS: cout << "ERROR: wrong number of teams" << endl;
            break;
        case ERR_OPTION: cout << "ERROR: wrong option" << endl;
    }
}

/* Función que simula los goles marcados por los jugadores
team: equipo para el que vamos a simular los goles marcados
return: número de goles totales del equipo
*/
int simulateGoals(Team &team){
    int goals=0;
    
    for(int i=0;i<kPLAYERS;i++){
        int goal=rand()%2; // Genera 0 o 1 (máximo un gol por robot en cada partido)
        team.players[i].goals+=goal;
        goals+=goal;
    }

    return goals;
}

/* Función que muestra el menú de opciones
return: nada
*/
void showMenu(){
    cout << "1- Add team" << endl
         << "2- Add all teams" << endl
         << "3- Delete team" << endl
         << "4- Show teams" << endl
         << "5- Play league" << endl
         << "6- Show standings" << endl
         << "7- Show best players" << endl
         << "q- Quit" << endl
         << "Option: ";
}

void addTeam(vector<Team>& teams){
    if (teams.size() >= kMAXTEAMS){
        error(ERR_MAX_TEAMS);
        return;
    }
    else {
        teams.push_back(Team());
        int size = teams.size() -1;
        teams[size].id = size;
        cout << "Enter team name: ";
        char buffer[kTEAMNAME];
        cin.getline(buffer, kTEAMNAME);
        if (buffer[0] == '\0'){
            sprintf(teams[size].name ,"Team_%d", size);
        }
        else {
            strcpy(teams[size].name , buffer);
        }
        // wins, losses, draws y points
        teams[size].wins = 0;
        teams[size].losses = 0;
        teams[size].draws = 0;
        teams[size].points = 0;

        for (int i = 0; i< kPLAYERS;i++){
            char gname[kTEAMNAME];
            strcpy(gname, teams[size].name); // ahora tiene el nombre de team
            sprintf(teams[size].players[i].name, "%s-R%d", gname, i); 
        }
    }
}

void generateAllTeams(vector<Team> &teams){
    teams.clear();
    unsigned int teamNum;
    do{
        cout << "Enter number of teams: ";
        cin >> teamNum;
        if (teamNum < 2 || teamNum > 20){
            error(ERR_NUM_TEAMS);
        }
    }while(teamNum < 2 || teamNum > 20);
    for (int i=0;i < teamNum;i++){
        teams.push_back(Team());
        sprintf(teams[i].name ,"Team_%d", i);
        teams[i].wins = 0;
        teams[i].losses = 0;
        teams[i].draws = 0;
        teams[i].points = 0;
        for (int j = 0; j< kPLAYERS;j++){
            char gname[kTEAMNAME];
            strcpy(gname, teams[i].name); // ahora tiene el nombre de team
            sprintf(teams[i].players[j].name, "%s-R%d", gname, j); 
        }
    }
}

void addAllTeams(vector<Team> &teams){
    unsigned char option;
    if (teams.size()> 0){
        do{
            cout << "Do you want to delete existing teams (y/n)?"<< endl;
            cin >> option;
            cin.ignore();
        }while(option != 'n' || option != 'y');

        if (option == 'n'){
            return;
        }
        else{
            generateAllTeams(teams);
        }
        
    }
    else{
        generateAllTeams(teams);
    }



}

// Función principal. Tendrás que añadir más código tuyo
int main(){
    char option;
    vector<Team> teams;
    srand(888); // Fija la semilla del generador de números aleatorios. ¡NO TOCAR!
    do{
        showMenu();
        cin >> option;
        cin.ignore(); // Para evitar que el salto de línea se quede en el buffer de teclado y luego pueda dar problemas si usas "getline"
        
        switch(option){
            case '1':
                addTeam(teams);
                break;
            case '2':
                addAllTeams(teams); // Llamar a la función "addAllTeams" para añadir todos los equipos de una vez
                break;
            case '3': // Llamar a la función "deleteTeam" para borrar un equipo
                break;
            case '4': // Llamar a la función "showTeams" para mostrar los datos de los equipos
                break;
            case '5': // Llamar a la función "playLeague" para simular los resultados de la competición
                break;
            case '6': // Llamar a la función "showStandings" para mostrar la clasificación final
                break;
            case '7': // Llamar a la función "showBestPlayers" para mostrar los mejores jugadores de cada equipo
                break;
            case 'q': break;
            default: error(ERR_OPTION);
        }
    }while(option!='q');
}
