#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define TABLE_MAX_SIZE 10
#define KEY_MAX_SIZE 8
#define KEY_TYPE int
void initKey(int *keys);
int getHashCode(KEY_TYPE key);
void show(HashTable table);

typedef struct Hash{
	KEY_TYPE key;
	HashTable next;
}*HashTable;

void main() {
	int keys[KEY_MAX_SIZE] = { 0 };
	HashTable table[TABLE_MAX_SIZE] = { NULL };
	int hashCode = 0;
	initKeys(keys);
	for (int i = 0; i < KEY_MAX_SIZE; i++)
	{
		hashCode = getHashCode(keys[i]);
		HashTable node = (HashTable)malloc(sizeof(struct Hash));
		node->key = hashCode;
		node->next = table[hashCode];
		table[hashCode]->next = node;
	}

	system("pause");
}

void initKey(int *keys) {
	srand(time(NULL));
	for (int i = 0; i < KEY_MAX_SIZE; i++) {
		keys[i] = rand() % 50;
	}
}

int getHashCode(KEY_TYPE key) {
	return key % TABLE_MAX_SIZE;
}