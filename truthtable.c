#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void printtable(int **table, int row, int column, int input);
int not(int input1);
int and(int input1, int input2);
int or(int input1, int input2);
int nand(int input1, int input2);
int nor(int input1, int input2);
int xor(int input1, int input2);
int findindex(char **variable, char *string, int column);
int varlen(char **variable);
int mbinarytodecimal(char **vmux, char **variable, int **table, int index, int selector);
int dbinarytodecimal(char **vard, char **variable, int **table, int index, int counter);

int main(int argn, char** argv){
        if(argn != 2){
                return 0;
        }
        FILE* fp;
        fp = fopen(argv[1], "r");
        if(fp == NULL){
                return 0;
        }
        char* word = malloc(16*sizeof(char));
        int numofinput;
        fscanf(fp,"INPUT %d",&numofinput);
        int i, j;
        int rows = pow(2, numofinput);
        char **variable = malloc(100*sizeof(char*));
        for(i = 0; i < 100; i++){
                variable[i]=(char*)malloc(16*sizeof(char));
        }
	char **vmux = malloc(100*sizeof(char*));
	for(i = 0; i < 100; i++){
		vmux[i] = (char*)malloc(16*sizeof(char));
	}
	char **vard = malloc(100*sizeof(char*));
	for(i = 0; i < 100; i++){
		vard[i] = (char*)malloc(16*sizeof(char));
	}
	strcpy(variable[0], "0");
	strcpy(variable[1], "1");

        for(i = 0; i < numofinput; i++){
                fscanf(fp, " %s", word);
                if(strcmp(word, ":") != 0){
                        strcpy(variable[i+2], word);
                }else{
                        fscanf(fp, " %s", word);
                        strcpy(variable[i+2], word);
                }
        }
        int numofoutput;
        fscanf(fp, " OUTPUT %d", &numofoutput);
        for(i = numofinput; i < numofinput+numofoutput; i++){
                fscanf(fp, " %s", word);
                if(strcmp(word, ":") != 0){
                        strcpy(variable[i+2], word);
                
                }else{
                        fscanf(fp, " %s", word);
                        strcpy(variable[i+2], word);
                
                }
        }
	int** table = malloc(rows * sizeof(int*));
        for(i = 0; i < rows; i++){
                table[i]=(int*)malloc((100)*sizeof(int));
        }
        int count = rows;
        int num = 0;
	
	for(i = 0; i < rows; i++){
		table[i][0] = 0;
	}
	for(i = 0; i < rows; i++){
		table[i][1] = 1;
	}

        for(i = 2; i < numofinput+2; i++){
		count = count/2;
                for(j = 0; j < rows; j++){
                        for(num = 0; num < count; num++){
                        	if(j < count){
                            		table[j][i] = 0;
					j++;
				}else if(table[j-count][i] == 0){
                                       	table[j][i] = 1;
					j++;
                	        }else if(table[j-count][i] == 1){
                   	                table[j][i] = 0;
					j++;
                               	 };
                        }
			j--;	
                }
        }
	int index1;
        int index2;
        int index3;
        int k;
        while(fscanf(fp," %s",word) == 1){
	        if(strcmp(word, "NOT") == 0){
                        fscanf(fp, " %s", word);
                        index1 = findindex(variable, word, varlen(variable));
                        fscanf(fp, " %s", word);
                        if(strcmp(word, ":") == 0){
                                fscanf(fp, " %s", word);
                        }
                        index2 = findindex(variable, word, varlen(variable));
                        if(index2 == 500){
                                strcpy(variable[varlen(variable)], word);
                        }
                        index2 = findindex(variable, word, varlen(variable));
                        for(k = 0; k < rows; k++){
                                table[k][index2] = not(table[k][index1]);
                        }
                }else if(strcmp(word, "PASS") == 0 ){
			fscanf(fp, " %s", word);
                        index1 = findindex(variable, word, varlen(variable));
                        fscanf(fp, " %s", word);
                        if(strcmp(word, ":") == 0){
                                fscanf(fp, " %s", word);
                        }
                        index2 = findindex(variable, word, varlen(variable));
                        if(index2 == 500){
                                strcpy(variable[varlen(variable)], word);
                        }
                        index2 = findindex(variable, word, varlen(variable));
                        for(k = 0; k < rows; k++){
                                table[k][index2] = table[k][index1];
                        }
		}else if(strcmp(word, "AND") == 0){
			fscanf(fp, " %s", word);
                        index1 = findindex(variable, word, varlen(variable));
                        fscanf(fp, " %s", word);
                        index2 = findindex(variable, word, varlen(variable));
                        fscanf(fp, " %s", word);
                        if(strcmp(word, ":") == 0){
                                fscanf(fp, " %s", word);
                        }
                        index3 = findindex(variable, word, varlen(variable));
                        if(index3 == 500){
                                strcpy(variable[varlen(variable)], word);
                        }
                        index3 = findindex(variable, word, varlen(variable));
                        for(k = 0; k < rows; k++){
                                table[k][index3] = and(table[k][index1], table[k][index2]);
                        }
                }else if(strcmp(word, "OR") == 0){
                        fscanf(fp, " %s", word);
                        index1 = findindex(variable, word, varlen(variable));
                        fscanf(fp, " %s", word);
                        index2 = findindex(variable, word, varlen(variable));
                        fscanf(fp, " %s", word);
                        if(strcmp(word, ":") == 0){
                                fscanf(fp, " %s", word);
                        }
                        index3 = findindex(variable, word, varlen(variable));
                        if(index3 == 500){
                                strcpy(variable[varlen(variable)], word);
                        }
                        index3 = findindex(variable, word, varlen(variable));
                        for(k = 0; k < rows; k++){
                                table[k][index3] = or(table[k][index1], table[k][index2]);
                        }	
		}else if(strcmp(word, "NAND") == 0){
                        fscanf(fp, " %s", word);
                        index1 = findindex(variable, word, varlen(variable));
                        fscanf(fp, " %s", word);
                        index2 = findindex(variable, word, varlen(variable));
                        fscanf(fp, " %s", word);
                        if(strcmp(word, ":") == 0){
                                fscanf(fp, " %s", word);
                        }
                        index3 = findindex(variable, word, varlen(variable));
                        if(index3 == 500){
                                strcpy(variable[varlen(variable)], word);
                        }
                        index3 = findindex(variable, word, varlen(variable));
                        for(k = 0; k < rows; k++){
                                table[k][index3] = nand(table[k][index1], table[k][index2]);
                        }
               	
		}else if(strcmp(word, "NOR") == 0){
               		fscanf(fp, " %s", word);
                        index1 = findindex(variable, word, varlen(variable));
                        fscanf(fp, " %s", word);
                        index2 = findindex(variable, word, varlen(variable));
                        fscanf(fp, " %s", word);
                        if(strcmp(word, ":") == 0){
                                fscanf(fp, " %s", word);
                        }
                        index3 = findindex(variable, word, varlen(variable));
                        if(index3 == 500){
                                strcpy(variable[varlen(variable)], word);
                        }
                        index3 = findindex(variable, word, varlen(variable));
                        for(k = 0; k < rows; k++){
                                table[k][index3] = nor(table[k][index1], table[k][index2]);
                        }
		}else if(strcmp(word, "XOR") == 0){
			fscanf(fp, " %s", word);
                        index1 = findindex(variable, word, varlen(variable));
                        fscanf(fp, " %s", word);
                        index2 = findindex(variable, word, varlen(variable));
                        fscanf(fp, " %s", word);
                        if(strcmp(word, ":") == 0){
                                fscanf(fp, " %s", word);
                        }
                        index3 = findindex(variable, word, varlen(variable));
                        if(index3 == 500){
                                strcpy(variable[varlen(variable)], word);
                        }
                        index3 = findindex(variable, word, varlen(variable));
                        for(k = 0; k < rows; k++){
                                table[k][index3] = xor(table[k][index1], table[k][index2]);
                        }
		}else if(strcmp(word, "MULTIPLEXER") == 0){
			int selector;
                        fscanf(fp, " %d", &selector);
			int inputs = pow(2, selector);
			for(i = 0; i < inputs+selector; i++){
				fscanf(fp, " %s", word);
				if(strcmp(word, ":") == 0){
					fscanf(fp, " %s", word);
				}
				strcpy(vmux[i], word);
			}
			fscanf(fp, " %s", word);
			if(strcmp(word, ":") == 0){
				fscanf(fp, " %s", word);
			}
			index1 = findindex(variable, word, varlen(variable));
			if(index1 == 500){
				strcpy(variable[varlen(variable)], word);
			}
			index1 = findindex(variable, word, varlen(variable));
			for(k = 0; k < rows; k++){
				/* OUT[i] = Decimal_Selectors at i */
				int whatinput = mbinarytodecimal(vmux, variable, table, k, selector);
				int tempval = findindex(variable, vmux[whatinput], varlen(variable));
				table[k][index1] = table[k][tempval];
			}
		}else if(strcmp(word, "DECODER") == 0){
			int input = 0;
			fscanf(fp, " %d", &input);
			int output = pow(2, input);
			for(i = 0; i < input+output; i++){
				fscanf(fp, " %s", word);
				if(strcmp(word, ":") == 0){
					fscanf(fp, " %s", word);
				}
				strcpy(vard[i], word);
			}
			for(i = 0; i < rows; i++){
				int deci = dbinarytodecimal(vard, variable, table, i, input);
				index1 = findindex(variable, vard[deci+input], varlen(variable));
				if(index1 == 500){
					strcpy(variable[varlen(variable)], vard[deci+input]);
				}
				index1 = findindex(variable, vard[deci+input], varlen(variable));
				table[i][index1] = 1;
			}


		}


	}
        fclose(fp);
        int column = numofinput + numofoutput;
	printtable(table, rows, column, numofinput);
        free(word);
	int size = varlen(variable);
	int size2 = varlen(vmux);
	int size3 = varlen(vard);
        for (i = 0; i < size; i++){
                char* temp = variable[i];
		free(temp);
        }
        for (i = 0; i < rows; i++){
                int* temp = table[i];
                free(temp);
        }
	for (i = 0; i < size2; i++){
		char* temp = vmux[i];
		free(temp);
	}
	for(i = 0; i < size3; i++){
		char* temp = vard[i];
		free(temp);
	}
        return 0;
}

void printtable(int **table, int row, int column, int input){
	int i, j;
	for(i = 0; i < row; i++){
                for(j = 2; j < column+2; j++){
                        if(j == 2){
                                printf("%d", table[i][j]);
                        }else if(j == input+2){
                                printf(" | %d", table[i][j]);
                        }else{
                                printf(" %d", table[i][j]);
                        }
                }
                printf("\n");
        }
	return;
}

int not(int input1){
        if(input1 == 0){
                return 1;
        }
        return 0;
}

int and(int input1, int input2){
        if(input1 == 1 && input2 == 1){
                return 1;
        }
        return 0;
}

int or(int input1, int input2){
        if(input1 == 1){
                return 1;
        }else if(input2 == 1){
		return 1;
	}
	return 0;
}

int nand(int input1, int input2){
        int num = and(input1, input2);
        if(num == 0){
                return 1;
        }
        return 0;
}

int nor(int input1, int input2){
        int num = or(input1, input2);
        if(num == 0){
                return 1;
        }
        return 0;
}

int xor(int input1, int input2){
        if(input1 == input2){
                return 0;
        }else{
                return 1;
        }
        return 0;
}

int findindex(char **variable, char *string, int column){
        int i = 0;
        for (i = 0; i < column; i++){
                if (strcmp(variable[i], string) == 0){
                	return i;
        	}
        }
        return 500;
}

int varlen(char **variable){
	int count = 0;
	int i = 0;
	while(strlen(variable[i]) != 0){
		count++;
		i++;
	}
	return count;
}

int mbinarytodecimal(char **vmux, char **variable, int **table, int index, int selector){
	int decimal = 0;
	int place = pow(2, selector);
	int size = varlen(vmux);
	int i;
	int count = selector-1;
	for(i = place; i < size; i++){
		int intemp = findindex(variable, vmux[i], varlen(variable));
		int temp = table[index][intemp];
		decimal = decimal + temp*pow(2, count);
		count--;
	}
	return decimal;
}

int dbinarytodecimal(char **vard, char **variable, int **table, int index, int counter){
	int decimal = 0;
	int i;
	int count = counter-1;
	for(i = 0; i < counter; i++){
		int intemp = findindex(variable, vard[i], varlen(variable));
		int temp = table[index][intemp];
		decimal = decimal + temp*pow(2, count);
		count--;
	}
	return decimal;
}
