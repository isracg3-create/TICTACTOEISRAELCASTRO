#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

const int FILAS = 3;
const int COLUMNAS = 3;

struct Configuracion {
    char jugadorX = 'X';
    char jugadorO = 'O';
};

void inicializarTablero(vector<vector<char>>& tablero) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            tablero[i][j] = ' ';
        }
    }
}

void mostrarTablero(const vector<vector<char>>& tablero) {
    cout << "\n  1   2   3\n";
    cout << " -----------\n";
    for (int i = 0; i < FILAS; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < COLUMNAS; j++) {
            cout << tablero[i][j];
            if (j < COLUMNAS - 1) cout << " | ";
        }
        cout << "\n";
        if (i < FILAS - 1) {
            cout << "  ---------\n";
        }
    }
    cout << endl;
}

bool movimientoValido(const vector<vector<char>>& tablero, int fila, int columna) {
    return (fila >= 0 && fila < FILAS && 
            columna >= 0 && columna < COLUMNAS && 
            tablero[fila][columna] == ' ');
}

void hacerMovimiento(vector<vector<char>>& tablero, int fila, int columna, char jugador) {
    tablero[fila][columna] = jugador;
}

char verificarGanador(const vector<vector<char>>& tablero) {
    for (int i = 0; i < FILAS; i++) {
        if (tablero[i][0] != ' ' && tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2]) {
            return tablero[i][0];
        }
    }
    
    for (int j = 0; j < COLUMNAS; j++) {
        if (tablero[0][j] != ' ' && tablero[0][j] == tablero[1][j] && tablero[1][j] == tablero[2][j]) {
            return tablero[0][j];
        }
    }
    
    if (tablero[0][0] != ' ' && tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]) {
        return tablero[0][0];
    }
    if (tablero[0][2] != ' ' && tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0]) {
        return tablero[0][2];
    }
    
    return ' ';
}

bool tableroLleno(const vector<vector<char>>& tablero) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void movimientoCPU(vector<vector<char>>& tablero, char jugadorCPU) {
    char oponente = (jugadorCPU == 'X') ? 'O' : 'X';
    
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] == ' ') {
                tablero[i][j] = jugadorCPU;
                if (verificarGanador(tablero) == jugadorCPU) {
                    return;
                }
                tablero[i][j] = ' ';
            }
        }
    }
    
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] == ' ') {
                tablero[i][j] = oponente;
                if (verificarGanador(tablero) == oponente) {
                    tablero[i][j] = jugadorCPU;
                    return;
                }
                tablero[i][j] = ' ';
            }
        }
    }
    
    vector<pair<int, int>> disponibles;
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] == ' ') {
                disponibles.push_back(make_pair(i, j));
            }
        }
    }
    
    if (!disponibles.empty()) {
        int idx = rand() % disponibles.size();
        int fila = disponibles[idx].first;
        int columna = disponibles[idx].second;
        tablero[fila][columna] = jugadorCPU;
    }
}

void mostrarMenu() {
    cout << "=== TRES EN RAYA ===\n";
    cout << "1. VS Jugador\n";
    cout << "2. VS CPU\n";
    cout << "3. Acerca de\n";
    cout << "4. Salir\n";
    cout << "====================\n";
}

void acercaDe() {
    cout << "\n" << string(50, '=') << "\n";
    cout << "          ACERCA DE TIC TAC TOE\n";
    cout << string(50, '=') << "\n\n";
    
    cout << "JUEGO: TIC TAC TOE (TRES EN RAYA)\n\n";
    
    cout << "DESCRIPCION:\n";
    cout << "Tic Tac Toe, también conocido como Tres en Raya, es un juego de\n";
    cout << "estrategia simple para dos jugadores. Se juega en una cuadrícula\n";
    cout << "de 3x3. El objetivo es ser el primero en formar una línea de tres\n";
    cout << "de tus símbolos (X o O) en horizontal, vertical o diagonal.\n\n";
    
    cout << "MODO DE JUEGO:\n";
    cout << "1. El juego comienza con un tablero vacío de 3x3 casillas.\n";
    cout << "2. Dos jugadores eligen su símbolo: uno será 'X' y el otro 'O'.\n";
    cout << "3. Los jugadores turnan para colocar su símbolo en una casilla vacía.\n";
    cout << "4. El jugador 'X' generalmente comienza la partida.\n";
    cout << "5. Los jugadores no pueden colocar su símbolo en una casilla ya ocupada.\n";
    cout << "6. El juego continúa por turnos hasta que un jugador gane o no\n";
    cout << "   queden más movimientos posibles.\n\n";
    
    cout << "FORMA DE GANAR:\n";
    cout << "Un jugador gana la partida si consigue alinear tres de sus símbolos en:\n";
    cout << "* Línea Horizontal: Las tres casillas de una misma fila\n";
    cout << "* Línea Vertical: Las tres casillas de una misma columna\n";
    cout << "* Línea Diagonal: Las tres casillas en diagonal (de esquina a esquina)\n\n";
    
    cout << "Si todas las casillas del tablero se llenan y ningún jugador ha\n";
    cout << "conseguido un tres en raya, el juego termina en EMPATE.\n\n";
    
    cout << string(50, '=') << "\n";
    cout << "      EJEMPLOS DE PARTIDAS DE TIC TAC TOE\n";
    cout << string(50, '=') << "\n\n";
    
    cout << "TABLERO VACIO:\n";
    cout << "     |     |     \n";
    cout << "  ---+---+---\n";
    cout << "     |     |     \n";
    cout << "  ---+---+---\n";
    cout << "     |     |     \n\n";
    
    cout << "PARTIDA EN CURSO:\n";
    cout << "     |     |     \n";
    cout << "  ---+---+---\n";
    cout << "     |  X  |  O  \n";
    cout << "  ---+---+---\n";
    cout << "  O  |     |  X  \n\n";
    
    cout << "VICTORIA POR LINEA HORIZONTAL (Jugador X gana):\n";
    cout << "  X  |  X  |  X  \n";
    cout << "  ---+---+---\n";
    cout << "  O  |  O  |     \n";
    cout << "  ---+---+---\n";
    cout << "     |     |  O  \n";
    cout << ">>> ¡EL JUGADOR 'X' HA GANADO! <<<\n\n";
    
    cout << "VICTORIA POR LINEA VERTICAL (Jugador O gana):\n";
    cout << "  O  |  X  |  X  \n";
    cout << "  ---+---+---\n";
    cout << "  O  |  X  |     \n";
    cout << "  ---+---+---\n";
    cout << "  O  |     |     \n";
    cout << ">>> ¡EL JUGADOR 'O' HA GANADO! <<<\n\n";
    
    cout << "VICTORIA POR LINEA DIAGONAL (Jugador X gana):\n";
    cout << "  X  |  O  |  O  \n";
    cout << "  ---+---+---\n";
    cout << "     |  X  |     \n";
    cout << "  ---+---+---\n";
    cout << "     |     |  X  \n";
    cout << ">>> ¡EL JUGADOR 'X' HA GANADO! <<<\n\n";
    
    cout << "PARTIDA EMPATADA (No hay ganador):\n";
    cout << "  X  |  O  |  X  \n";
    cout << "  ---+---+---\n";
    cout << "  X  |  X  |  O  \n";
    cout << "  ---+---+---\n";
    cout << "  O  |  X  |  O  \n";
    cout << ">>> ¡EMPATE! <<<\n\n";
    
    cout << string(50, '=') << "\n";
    cout << "          TIPS Y ESTRATEGIAS BASICAS\n";
    cout << string(50, '=') << "\n\n";
    
    cout << "* Ataque: Siempre busca oportunidades para crear dos líneas de\n";
    cout << "  tres en raya al mismo tiempo (una 'tenaza'). Tu oponente solo\n";
    cout << "  podrá bloquear una.\n\n";
    
    cout << "* Defensa: Si tu oponente tiene dos símbolos en línea, DEBES\n";
    cout << "  colocar el tuyo en la casilla restante para bloquearlo.\n\n";
    
    cout << "* Controla el Centro: Tomar la casilla central en uno de tus\n";
    cout << "  primeros movimientos te da una gran ventaja, ya que es parte\n";
    cout << "  de más líneas ganadoras.\n\n";
    
    cout << "* Ocupa una Esquina: Si no puedes tomar el centro, una esquina\n";
    cout << "  es la segunda mejor opción.\n\n";
    
    cout << "* Evita las Esquinas Opuestas: Si tu oponente tiene dos esquinas\n";
    cout << "  opuestas, colocar tu símbolo en un lateral puede evitar que\n";
    cout << "  te hagan una tenaza diagonal.\n\n";
    
    cout << string(50, '=') << "\n";
    cout << "                   CREDITOS\n";
    cout << string(50, '=') << "\n\n";
    
    cout << "Este proyecto fue desarrollado como parte de la formación\n";
    cout << "académica en la:\n\n";
    
    cout << "* Universidad Autónoma de Sinaloa\n";
    cout << "* Carrera: Ingeniería de Software, Modalidad Virtual\n";
    cout << "* Alumno: Israel Castro García\n";
    cout << "* Matrícula: 201-\n\n";
    
    cout << "Para más información visita:\n";
    cout << "https://tinyurl.com/2sza5y6k\n\n";
    
    cout << string(50, '=') << "\n";
}

void pausa() {
    cout << "\nPresiona Enter para continuar...";
    cin.ignore();
    cin.get();
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    Configuracion config;
    bool ejecutando = true;
    
    while (ejecutando) {
        mostrarMenu();
        
        int opcion;
        cout << "Opcion: ";
        cin >> opcion;
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (opcion) {
            case 1: {
                vector<vector<char>> tablero(FILAS, vector<char>(COLUMNAS, ' '));
                char jugador = config.jugadorX;
                bool activo = true;
                
                inicializarTablero(tablero);
                
                while (activo) {
                    mostrarTablero(tablero);
                    
                    int f, c;
                    cout << "Jugador " << jugador << " (fila columna): ";
                    cin >> f >> c;
                    
                    if (!cin) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    
                    f--; c--;
                    
                    if (movimientoValido(tablero, f, c)) {
                        hacerMovimiento(tablero, f, c, jugador);
                        
                        char ganador = verificarGanador(tablero);
                        if (ganador != ' ') {
                            mostrarTablero(tablero);
                            cout << "¡Gana " << ganador << "!\n";
                            activo = false;
                        } else if (tableroLleno(tablero)) {
                            mostrarTablero(tablero);
                            cout << "¡Empate!\n";
                            activo = false;
                        } else {
                            jugador = (jugador == config.jugadorX) ? config.jugadorO : config.jugadorX;
                        }
                    }
                }
                pausa();
                break;
            }
            
            case 2: {
                vector<vector<char>> tablero(FILAS, vector<char>(COLUMNAS, ' '));
                char humano = config.jugadorX;
                char cpu = config.jugadorO;
                bool activo = true;
                
                inicializarTablero(tablero);
                
                while (activo) {
                    mostrarTablero(tablero);
                    
                    int f, c;
                    cout << "Tu turno " << humano << " (fila columna): ";
                    cin >> f >> c;
                    
                    if (!cin) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    
                    f--; c--;
                    
                    if (movimientoValido(tablero, f, c)) {
                        hacerMovimiento(tablero, f, c, humano);
                        
                        char ganador = verificarGanador(tablero);
                        if (ganador != ' ') {
                            mostrarTablero(tablero);
                            cout << (ganador == humano ? "¡Ganaste!\n" : "¡CPU gana!\n");
                            activo = false;
                            break;
                        } else if (tableroLleno(tablero)) {
                            mostrarTablero(tablero);
                            cout << "¡Empate!\n";
                            activo = false;
                            break;
                        }
                        
                        cout << "CPU pensando...\n";
                        movimientoCPU(tablero, cpu);
                        
                        ganador = verificarGanador(tablero);
                        if (ganador != ' ') {
                            mostrarTablero(tablero);
                            cout << (ganador == humano ? "¡Ganaste!\n" : "¡CPU gana!\n");
                            activo = false;
                        } else if (tableroLleno(tablero)) {
                            mostrarTablero(tablero);
                            cout << "¡Empate!\n";
                            activo = false;
                        }
                    }
                }
                pausa();
                break;
            }
            
            case 3:
                acercaDe();
                pausa();
                break;
                
            case 4:
                ejecutando = false;
                cout << "¡ADIOS!\n";
                break;
                
            default:
                cout << "Opcion invalida\n";
                break;
        }
    }
    
    return 0;
}
// https://github.com/isracg3-create/TICTACTOEISRAELCASTRO
