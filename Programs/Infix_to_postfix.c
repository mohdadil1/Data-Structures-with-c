/*
 * Application of Stack: Infix to Postfix Conversion
 * -------------------------------------------------
 * Scan the infix expression from left to right:
 *  - Operand            -> add it to the postfix expression.
 *  - '('                -> always push it on the stack.
 *  - ')'                -> pop operators to postfix until the first '('
 *                          is found, then discard the '('.
 *  - Operator           -> while the top of the stack has an operator of
 *                          higher (or equal, for left-associative) precedence,
 *                          pop it to postfix; then push the current operator.
 *                          '^' is right-associative.
 *  - End of expression  -> pop all remaining operators to postfix.
 */
// Example: A+B/C*D-E/(F+G)  ->  ABC/D*+EFG+/-
//          3+5*(5/5)-2^2    ->  3555/*+22^-
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1)
        return '\0';
    return stack[top--];
}

int isEmpty() {
    return top == -1;
}

int precedence(char op) {
    switch (op) {
    case '^': return 3;
    case '*':
    case '/': return 2;
    case '+':
    case '-': return 1;
    default:  return 0;     /* '(' has the lowest priority inside the stack */
    }
}

void infixToPostfix(const char *infix, char *postfix) {
    int i, j = 0;
    char c;
    top = -1;

    for (i = 0; infix[i] != '\0'; i++) {
        c = infix[i];
        if (c == ' ')
            continue;
        if (isalnum((unsigned char)c)) {
            postfix[j++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (!isEmpty() && stack[top] != '(')
                postfix[j++] = pop();
            pop();                              /* discard '(' */
        } else {                                /* operator */
            while (!isEmpty() &&
                   (precedence(stack[top]) > precedence(c) ||
                    (precedence(stack[top]) == precedence(c) && c != '^')))
                postfix[j++] = pop();
            push(c);
        }
    }
    while (!isEmpty())
        postfix[j++] = pop();
    postfix[j] = '\0';
}

int main() {
    char infix[MAX], postfix[MAX];

    infixToPostfix("A+B/C*D-E/(F+G)", postfix);
    printf("Infix: A+B/C*D-E/(F+G)    Postfix: %s\n", postfix);

    infixToPostfix("3+5*(5/5)-2^2", postfix);
    printf("Infix: 3+5*(5/5)-2^2      Postfix: %s\n", postfix);

    printf("\nEnter an infix expression: ");
    if (fgets(infix, MAX, stdin) != NULL) {
        infix[strcspn(infix, "\n")] = '\0';
        infixToPostfix(infix, postfix);
        printf("Postfix expression: %s\n", postfix);
    }
    return 0;
}
