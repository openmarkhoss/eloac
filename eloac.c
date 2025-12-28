/* =========================================================
   OFFLINE ASCII MATRIX AI (GREEN/BLACK TERMINAL)
   Target: Raspberry Pi 4B (4GB RAM)
   Language: C
   Mode: Local, Offline, Low-Res ASCII, Event-Driven
   ========================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <termios.h>

/* -------------------------
   TERMINAL CONTROL (ANSI)
   ------------------------- */
#define GREEN  "\033[32m"
#define BLACK  "\033[40m"
#define CLEAR  "\033[2J"
#define HOME   "\033[H"
#define RESET  "\033[0m"

/* -------------------------
   MODEL CONFIG
   ------------------------- */
#define INPUT_SIZE 3
float weights[INPUT_SIZE] = {0.2f, -0.1f, 0.05f};
float bias = 0.0f;

/* -------------------------
   RAW KEY INPUT (no enter)
   ------------------------- */
char get_keypress() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

/* -------------------------
   ASCII ANIMATION
   ------------------------- */
void ascii_bubble(char c) {
    printf(GREEN);
    printf("\n   .----.\n");
    printf("  |  %c   |\n", c);
    printf("   '----'\n");
    printf(RESET);
    usleep(30000);
}

/* -------------------------
   MATH CORE
   ------------------------- */
float sigmoid(float x) {
    return 1.0f / (1.0f + expf(-x));
}

float forward(float input[INPUT_SIZE]) {
    float sum = bias;
    for (int i = 0; i < INPUT_SIZE; i++)
        sum += input[i] * weights[i];
    return sigmoid(sum);
}

/* -------------------------
   UI DRAW
   ------------------------- */
void draw_ui() {
    printf(CLEAR HOME BLACK GREEN);
    printf("=====================================\n");
    printf("   ASCII MATRIX AI  (OFFLINE MODE)\n");
    printf("=====================================\n\n");
    printf(">> Give me a task or ask me something\n\n");
    printf("-------------------------------------\n");
    printf(RESET);
}

/* -------------------------
   ASCII RESPONSE FORMAT
   ------------------------- */
void ascii_response(const char *text) {
    printf(GREEN);
    printf("\n+-----------------------------------+\n");
    printf("| RESPONSE                          |\n");
    printf("+-----------------------------------+\n");
    printf("| %s\n", text);
    printf("+-----------------------------------+\n\n");
    printf(RESET);
}

/* -------------------------
   MAIN LOOP
   ------------------------- */
int main() {
    char input_buffer[128];
    int idx = 0;

    draw_ui();

    while (1) {
        char c = get_keypress();

        if (c == 3) break;           // CTRL+C
        if (c == '\n') {
            input_buffer[idx] = '\0';

            /* Dummy numeric interpretation (symbolic AI feel) */
            float fake_input[INPUT_SIZE] = {
                (float)(strlen(input_buffer) % 3),
                (float)(strlen(input_buffer) % 2),
                1.0f
            };

            float output = forward(fake_input);

            char response[128];
            snprintf(response, sizeof(response),
                     "INPUT_LEN=%lu | OUTPUT=%.3f",
                     strlen(input_buffer), output);

            ascii_response(response);
            idx = 0;
            memset(input_buffer, 0, sizeof(input_buffer));
            draw_ui();
        } else {
            if (idx < 120) {
                input_buffer[idx++] = c;
                ascii_bubble(c);
            }
        }
    }

    printf(RESET CLEAR);
    return 0;
}
