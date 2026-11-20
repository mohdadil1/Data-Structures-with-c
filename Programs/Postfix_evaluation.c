/*
 * Application of Stack: Postfix Expression Evaluation
 * ---------------------------------------------------
 * Golden rule: scan the expression from left to right.
 *  - Operand  -> push it on the stack.
 *  - Operator -> pop two operands (first pop = operand 2, second pop =
 *                operand 1), apply the operator, push the result.
 * At the end, the only value on the stack is the answer.
 * Operands here are single digits.
 */
// Example: 3555/*+22^-   ->  4     (same as infix 3+5*(5/5)-2^2)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int value) {
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    stack[++top] = value;
}

int pop() {
    if (top == -1) {
        printf("Invalid postfix expression\n");
        exit(1);
    }
    return stack[top--];
}

int power(int base, int exp) {
    int result = 1;
    while (exp-- > 0)
        result *= base;
    return result;
}

int evaluatePostfix(const char *postfix) {
    int i, op1, op2;
    char c;
    top = -1;

    for (i = 0; postfix[i] != '\0'; i++) {
        c = postfix[i];
        if (c == ' ')
            continue;
        if (isdigit((unsigned char)c)) {
            push(c - '0');
        } else {
            op2 = pop();
            op1 = pop();
            switch (c) {
            case '+': push(op1 + op2); break;
            case '-': push(op1 - op2); break;
            case '*': push(op1 * op2); break;
            case '/': push(op1 / op2); break;
            case '^': push(power(op1, op2)); break;
            default:
                printf("Unknown operator %c\n", c);
                exit(1);
            }
        }
    }
    return pop();
}

int main() {
    char postfix[MAX];

    printf("3555/*+22^-   = %d\n", evaluatePostfix("3555/*+22^-"));
    printf("753*51^/+32-+ = %d\n", evaluatePostfix("753*51^/+32-+"));

    printf("\nEnter a postfix expression (single-digit operands): ");
    if (fgets(postfix, MAX, stdin) != NULL) {
        postfix[strcspn(postfix, "\n")] = '\0';
        printf("Result: %d\n", evaluatePostfix(postfix));
    }
    return 0;
}
