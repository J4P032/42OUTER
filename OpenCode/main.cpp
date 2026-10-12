// Game of life en C++
#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

constexpr int ROWS = 20;
constexpr int COLS = 40;

using Board = std::vector<std::vector<bool>>;

// Rellena el tablero con valores aleatorios (true/false)
void randomizeBoard(Board& board) {
    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> dist(0, 1);
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            board[r][c] = (dist(rng) == 1);
        }
    }
}

// Dibuja el tablero: '#' para vivas, '.' para muertas
void drawBoard(const Board& board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            std::cout << (cell ? '#' : '.');
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

// Cuenta cuántos de los 8 vecinos de (r, c) están vivos
int countNeighbors(const std::vector<std::vector<bool>>& board, int r, int c) {
    int count = 0;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue; // no contar a la propia celda
            int nr = r + dr;
            int nc = c + dc;
            // Control de límites: filas 0..19, columnas 0..39
            if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS && board[nr][nc]) {
                ++count;
            }
        }
    }
    return count;
}

void clearScreen() {
    // Limpia la pantalla y mueve el cursor arriba a la izquierda
    std::cout << "\033[2J\033[1;1H";
}

// Genera el próximo tablero aplicando las reglas del Juego de la Vida
Board updateBoard(const Board& board) {
    Board next(ROWS, std::vector<bool>(COLS, false));
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            int neighbors = countNeighbors(board, r, c);
            if (board[r][c]) {
                // Sobrevive con 2 o 3 vecinos; muere por soledad o superpoblación
                next[r][c] = (neighbors == 2 || neighbors == 3);
            } else {
                // Nace si tiene exactamente 3 vecinos
                next[r][c] = (neighbors == 3);
            }
        }
    }
    return next;
}

int main() {
    Board board(ROWS, std::vector<bool>(COLS, false));
    randomizeBoard(board);

    while (true) {
        // 1. Dibujar el tablero
        drawBoard(board);
        // 2. Esperar 100 ms
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // 3. Limpiar la pantalla
        clearScreen();
        // 4. Actualizar el tablero
        board = updateBoard(board);
    }
    return 0;
}
