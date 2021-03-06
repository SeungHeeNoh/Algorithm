/*
	선형 조사법에서 탐색 키를 삭제하는 함수 hash_lp_delete(element item, element ht[])를 구현해보라.
*/

#include<stdio.h>

#define KEY_SIZE 20
#define TABLE_SIZE 11

typedef struct element{
	int value;
	int used;
	int full;
}element;

typedef struct HashTable{
	element table[TABLE_SIZE];
}HashTable;

void initTable(HashTable *ht){
	for(int i=0; i<TABLE_SIZE; i++){
		ht->table[i].value = -1;
		ht->table[i].used = ht->table[i].full = 0;
	}
}

void display(HashTable ht){
	for(int i=0; i<TABLE_SIZE; i++){
		printf("%d ", ht.table[i].value);
	}
	printf("\n");
}

int isEmpty(HashTable ht){
	int count=0;
	for(int i=0; i<TABLE_SIZE; i++){
		if(ht.table[i].full){
			count++;
		}
	}
	return count == 0;
}

int isFull(HashTable ht){
	int count = 0;

	for(int i=0; i<TABLE_SIZE; i++){
		if(ht.table[i].full){
			count++;
		}
	}
	return count==TABLE_SIZE;
}

void inputHashTable(HashTable *ht, element data){
	int step, hashKey;
	step = hashKey = data.value % 11;

	if(isFull(*ht)){
		printf("Table is Full.\n");
		return;
	}else{
		while(1){
			if (!ht->table[step].full){
				ht->table[step].value = data.value;
				ht->table[step].full = 1;
				ht->table[step].used = 1;
				break;
			} else {
				step =  ++step % TABLE_SIZE;
				if (step == hashKey) {
					printf("Table is Full.\n");
					return;
				}
			}
		}
		display(*ht);
	}
}

void deleteHashTable(HashTable *ht, element data){
	int step, hashKey;
	step = hashKey = data.value % 11;

	if(isEmpty(*ht)){
		printf("Table is Empty.\n");
		return;
	}else{
		while(1){
			if(ht->table[step].full && ht->table[step].value == data.value){
				ht->table[step].value = -1;
				ht->table[step].full = 0;
				printf("delete success : %d\n", data.value);
				break;
			}else{
				step = ++step % TABLE_SIZE;
				if (step == hashKey || !ht->table[step].used){
					printf("Data you want to delete is not exist in hashtable.\n");
					return;
				}
			}
		}
	}
}

int find(HashTable ht, int data){
	int step, hashKey, result = -1;
	step = hashKey = data % 11;

	while(1){
		if(ht.table[step].used && ht.table[step].value == data){
			result = step;
			break;
		}else{
			step = ++step % TABLE_SIZE;
			if (step == hashKey){
				return -1;
			}
		}
	}

	return result;
}

void search(HashTable ht, element data){
	if(isEmpty(ht)){
		printf("Table is Empty.\n");
	} else{
		int result = find(ht, data.value);
		if(result == -1) {
			printf("Data you are looking for is not exist in hashtable.\n");
		}else{
			printf("search success : %d\n", result);
		}
	}
}

void main(){
	int op;
	element temp;
	HashTable test1;
	initTable(&test1);

	do{
		printf("Enter the desired operation.(0=input, 1=delete, 2=search, 3=display, 4=exit.) ");
		scanf("%d", &op);
		switch (op){
		case 0:
			printf("Enter the key ");
			scanf("%d", &temp.value);
			inputHashTable(&test1, temp);
			break;
		case 1:
			printf("Enter the key ");
			scanf("%d", &temp.value);
			deleteHashTable(&test1, temp);
			break;
		case 2:
			printf("Enter the key ");
			scanf("%d", &temp.value);
			search(test1, temp);
			break;
		case 3:
			display(test1);
		}

	}while(op != 4);
}