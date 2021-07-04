#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define L 1000001


//stack data structure
struct Stack{
	int top;
	unsigned capacity;
	double* array;
};

// create a stack
struct Stack *createStack( unsigned capacity ){
	struct Stack *stack = (struct Stack*)malloc(sizeof(struct Stack));
	if(!stack)
		return NULL;
	stack->top = -1;
	stack->capacity = capacity;
	stack->array = (double*) malloc(stack->capacity * sizeof(double));
	return stack;
}

double peek(struct Stack *stack){
	return stack->array[stack->top];
}

int isEmpty(struct Stack *stack){
	return stack->top == -1;
}

double pop(struct Stack *stack){
	if (!isEmpty(stack))
		return stack->array[stack->top--];
	return 'x';
}

void push(struct Stack *stack, char x){
	stack->array[++stack->top] = x;
}

void pushCalc(struct Stack *stack, double x){
	stack->array[++stack->top] = x;
}

int isOperand (char ch){
	 return isdigit(ch);
}

int precedence(char x){
	switch(x){
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		case '^':
			return 3;
	}
	return 0;	
}

double InfixtoPostfix(char* S, struct Stack *stack, int len){
	int j, i;
	char R[2*len];
	for(i = 0, j = -1; S[i]; i++){
		if(isOperand(S[i])){
			if(i == 0 || isOperand(S[i-1]) || R[i-1] == ' ')
				R[++j] = S[i];
			else{
				R[++j] = ' ';
				R[++j] = S[i];
			}	
		}
		
		else if(S[i] == '(')
			push(stack, S[i]);

		else if(S[i] == ')'){
			while(!isEmpty(stack) && peek(stack) != '('){
				if(isOperand(peek(stack))){
					if(R[j] == ' ')
						R[++j] = pop(stack);
					else{
						R[++j] = ' ';
						R[++j] = pop(stack);
					}
				}
				else{
					if(R[j] == ' ')
						R[++j] = pop(stack);
					else{
						R[++j] = ' ';
						R[++j] = pop(stack);
					}
				}
			}
			pop(stack);
		}
		else{ //operator
			R[++j] = ' ';
			while(!isEmpty(stack) && precedence(S[i]) <= precedence(peek(stack)))
				if(!isOperand(peek(stack))){
					if(R[j] == ' ')
						R[++j] = pop(stack);
					else{
						R[++j] = ' ';
						R[++j] = pop(stack);
					}	
				}
				else{
					if(R[j] == ' ')
						R[++j] = pop(stack);
					else{
						R[++j] = ' ';
						R[++j] = pop(stack);
					}	
				} 
			push(stack, S[i]);
		}
	}
	while(!isEmpty(stack)){
		if(!isOperand(peek(stack))){
			if(R[j] == ' ')
				pop(stack);
			else{	
				R[++j] = ' ';
				R[++j] = pop(stack);
			}
		}
		else{
			if(!isOperand(R[j]) && R[j] != ' '){
				R[++j] = ' ';
				R[++j] = pop(stack);
			}
			else R[++j] = pop(stack);
		}
	}
	R[++j] = '\0';
	free(stack);
	int leng = strlen(R);
	struct Stack *stackEval = createStack(leng);
	int idx;
	for(idx = 0; R[idx]; ++idx){
		if(R[idx] == ' ')
			continue;
		else if(isdigit(R[idx])){
			int fl = idx;
			int cntr = 0;
			while(isdigit(R[idx])){
				cntr++;
				idx++;
			}
			char tmp[cntr];
			strncpy(tmp, R+fl, cntr);
			tmp[cntr] = '\0';
			int val = atoi(tmp);
			double true_val = (double) val;
			idx--;
			pushCalc(stackEval, true_val);
		}
		else{
			double v1 = pop(stack);
			double v2 = pop(stack);
			switch (R[idx]){
				case '+': pushCalc(stack, v1+v2); break;
				case '-': pushCalc(stack, v2 - v1); break;
            	case '*': pushCalc(stack, v2 * v1); break;
            	case '/': pushCalc(stack, v2/v1); break;
			}
		}
	}
	double res = pop(stackEval);
	free(stackEval);
	return res;
}

int main(){
	char S[L];
	int flag_first = 0;
	while(scanf("%s", S) != EOF){
		if(flag_first != 0)
			printf("\n");
		int len = strlen(S);
		struct Stack *stack = createStack(len);
		double res = InfixtoPostfix(S, stack, len);
		printf("%0.15lf", res);
		flag_first = 1;
	}
}
