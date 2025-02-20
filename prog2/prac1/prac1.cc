#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <cstring> // Para strcpy(), strcat() y strcmp()
#include <vector>
#include <cstdio>
#include <algorithm>



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

void playmatch(Team &home, Team &away){
    int homegoals = simulateGoals(home);
    int awaygoals = simulateGoals(away);

    if (homegoals>awaygoals){ // goals part
        home.points += 3;
        home.wins ++;
        away.losses ++;
    }
    else if (homegoals<awaygoals){
        away.points +=3;
        home.losses ++;
        away.wins ++;
    }
    else{
        home.points +=1;
        away.points +=1;
        home.draws ++;
        away.draws ++;
    }
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
        //cin.ignore();
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
            sprintf(teams[size].players[i].name, "%s-R%d", gname, i+1); 
        }
    }
}

void generateAllTeams(vector<Team> &teams, int &contador){
    teams.clear();
    unsigned int teamNum;
    do{
        cout << "Enter number of teams: ";
        cin >> teamNum;
        if (teamNum < 2 || teamNum > 20){
            error(ERR_NUM_TEAMS);
        }
    }while(teamNum < 2 || teamNum > 20);
    for (size_t i=0;i < teamNum;i++){
        teams.push_back(Team());
        sprintf(teams[i].name ,"Team_%zu", i);
        teams[i].wins = 0;
        teams[i].losses = 0;
        teams[i].draws = 0;
        teams[i].points = 0;
        for (int j = 0; j< kPLAYERS;j++){
            char gname[kTEAMNAME];
            strcpy(gname, teams[i].name); // ahora tiene el nombre de team
            snprintf(teams[i].players[j].name,sizeof(teams[i].players[j].name), "%s-R%d", gname, j+1); 
        }
    }
    contador += teamNum;
}

void addAllTeams(vector<Team> &teams, int &contador){
    unsigned char option;
    if (teams.size()> 0){
        do{
            cout << "Do you want to delete existing teams (y/n)?\n"<< endl;
            cin >> option;
            cin.ignore();
        }while(option != 'n' && option != 'y' && option != 'N' && option != 'Y');

        if (option == 'n' || option == 'N'){
            return;
        }
        else{
            generateAllTeams(teams, contador);
        }
        
    }
    else{
        generateAllTeams(teams, contador);
    }



}

int findTeam(vector<Team> teams, char searchedTeam[kMAXTEAMS]){
    int result = -1;
    for (size_t i = 0;i<teams.size();i++){
        if (strcmp(teams[i].name, searchedTeam) == 0){
            result = i;
        }
    }
    return result;
}

void deleteTeam(vector<Team> &teams){
    if (teams.size() == 0){
        error(ERR_NO_TEAMS);
        return;
    }
    else{
        cout << "Enter team name: ";
        char searchedTeam[kTEAMNAME];
        cin.getline(searchedTeam, kTEAMNAME); 
        if (searchedTeam[0] == '\0'){
            error(ERR_EMPTY);
            return;
        }
        int teamPos = findTeam(teams, searchedTeam); 
        if(teamPos == -1){ //if team doesnt exist 
            error(ERR_NOT_EXIST);
            return; 
        }
        else{
            teams.erase(teams.begin() + teamPos);
        }

    }
}

void showTeams(vector<Team> teams){
    if (teams.size() == 0){
        error(ERR_NO_TEAMS);
        return;
    }
    else{
        bool loop = false;
        do{ //preguntar por nombre
            cout << "Enter team name: ";
            char searchedTeam[kTEAMNAME];
            cin.getline(searchedTeam, kTEAMNAME); 
            if (searchedTeam[0] == '\0'){ // show all
                for (size_t i = 0;i<teams.size();i++){
                    cout << "Name:"<< teams[i].name <<endl
                        << "Wins: "<< teams[i].wins <<endl
                        << "Losses: "<< teams[i].losses <<endl
                        << "Draws: "<< teams[i].draws << endl
                        << "Points: "<< teams[i].points <<endl;
                    for (int j = 0;j<kPLAYERS;j++){
                        char buffer[69];
                        sprintf(buffer, "%s: %d goals", teams[i].players[j].name, teams[i].players[j].goals);
                        cout << "" <<buffer<< endl;
                        }
                    }
                loop = true;
            }
            else if(findTeam(teams, searchedTeam) == -1){  // // caso de team no existe 
                error(ERR_NOT_EXIST);
            }    
            else{ // si que existe 
                int pos = findTeam(teams, searchedTeam);
                cout << "Name:"<< teams[pos].name <<endl
                        << "Wins: "<< teams[pos].wins <<endl
                        << "Losses: "<< teams[pos].losses <<endl
                        << "Draws: "<< teams[pos].draws << endl
                        << "Points: "<< teams[pos].points <<endl;
                    for (int j = 0;j<kPLAYERS;j++){
                        char buffer[69];
                        sprintf(buffer, "%s: %d goals", teams[pos].players[j].name, teams[pos].players[j].goals);
                        cout << "" <<buffer<< endl;
                        }
                loop = true;
            }
        }while(loop == false);
    }
}
void borrar_info(vector<Team> &teams){
    for (int i=0; i <= kMAXTEAMS; i++){
        teams[i].draws = 0;
        teams[i].losses = 0;
        teams[i].points = 0;
        teams[i].wins = 0;
        for (int j = 0; j< kPLAYERS;j++){
            teams[i].players[j].goals = 0;
            teams[i].players[j].best = false;
        }
    }
}

void playLeage(vector<Team> &teams){
    if (teams.size() <= 1){
        error(ERR_NUM_TEAMS);
        return;
    }
    else{
        borrar_info(teams);
        for (size_t i = 0;i< teams.size(); i++){// error aqui de teams size si delete teams en el medio
            for (size_t j = i+1; j < teams.size(); j++){
                unsigned int players_goals_before_match[5] = { teams[i].players[0].goals, teams[i].players[1].goals, teams[i].players[2].goals, teams[i].players[3].goals, teams[i].players[4].goals };
                unsigned int players_goals_before_match_enemy[5] = { teams[j].players[0].goals, teams[j].players[1].goals, teams[j].players[2].goals, teams[j].players[3].goals, teams[j].players[4].goals };
                playmatch(teams[i], teams[j]);
                for (int k = 0; k< kPLAYERS; k++){
                    if (players_goals_before_match[k] < teams[i].players[k].goals){
                        teams[i].players[k].best = true;
                        k=5;
                    }
                    if (players_goals_before_match_enemy[k] < teams[j].players[k].goals){
                        teams[j].players[k].best = true;
                        k=5;
                    }  
                }
            }
        }  
    }
}

void showStandings(vector<Team> teams){
    if (teams[1].points == 0){
        error(ERR_NO_LEAGUE);
    }
    else{
        vector<Team> sorted = teams;
        stable_sort(sorted.begin(), sorted.end(), [](const Team& a, const Team& b) {
        return a.points > b.points;
    });
        // print name|wins|draws|losses|points
        for (size_t i = 0; i < sorted.size(); i++){
            char team_stat[100];
            sprintf(team_stat ,"%s|%d|%d|%d|%d", sorted[i].name, sorted[i].wins, sorted[i].draws, sorted[i].losses, sorted[i].points);
            cout <<"" << team_stat <<endl;
        };

    }
}


// Función principal. Tendrás que añadir más código tuyo
int main(){
    int contador = 0;
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
                addAllTeams(teams, contador); // Llamar a la función "addAllTeams" para añadir todos los equipos de una vez
                break;
            case '3':
                deleteTeam(teams); // Llamar a la función "deleteTeam" para borrar un equipo
                break;
            case '4':
                showTeams(teams); // Llamar a la función "showTeams" para mostrar los datos de los equipos
                break;
            case '5': 
                playLeage(teams);// Llamar a la función "playLeague" para simular los resultados de la competición
                break;
            case '6':
                showStandings(teams); // Llamar a la función "showStandings" para mostrar la clasificación final
                break;
            case '7': // Llamar a la función "showBestPlayers" para mostrar los mejores jugadores de cada equipo
                break;
            case 'q': break;
            default: error(ERR_OPTION);
        }
    }while(option!='q');
}
