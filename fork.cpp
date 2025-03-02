#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void processRectangle() {
    double length, width;
    printf("Enter the rectangle's length and width: ");
    if (scanf("%lf %lf", &length, &width) != 2) {
        fprintf(stderr, "Invalid input! Please enter two numbers.\n");
        exit(1);
    }
    double area = length * width;
    printf("Rectangle area = %.2f\n", area);
}

void processTriangle() {
    double base, height;
    printf("Enter the triangle's base and height : ");
    if (scanf("%lf %lf", &base, &height) != 2) {
        fprintf(stderr, "Invalid input! Please enter two numbers.\n");
        exit(1);
    }
    double area = 0.5 * base * height;
    printf("Triangle area = %.2f\n", area);
}

int main() {
    pid_t pid = fork(); 

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        processTriangle();
        exit(0);
    } else {
        processRectangle();
        wait(NULL);
    }

    return 0;
}
