#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<time.h>

#define TABLE_MAX_SIZE 10
#define KEY_MAX_SIZE 8
#define KEY_TYPE int

typedef struct {
	int index;
	int key;
	int compareCount;
	int hashCode;
}Node;

typedef struct Table {
	Node nodes[TABLE_MAX_SIZE];
}*HashTable;

void initKey(int *keys);
int getHashCode(KEY_TYPE key);
int getConflictCode(KEY_TYPE key,int increasement);
void show(HashTable table);

void main() {
	KEY_TYPE keys[KEY_MAX_SIZE] = { 0 };
	HashTable table = (HashTable)malloc(sizeof(struct Table));
	initKey(keys);

	Node tempNode;
	for (int i = 0; i < TABLE_MAX_SIZE; i++)
	{
		tempNode = *((Node *)malloc(sizeof(Node) * TABLE_MAX_SIZE));
		tempNode.compareCount = 0;
		tempNode.hashCode = -1;
		tempNode.index = -1;
		tempNode.key = -1;
		table->nodes[i] = tempNode;
	}

	int hashCode = 0;
	for (int i = 0; i < KEY_MAX_SIZE; i++)
	{
		tempNode = *((Node *)malloc(sizeof(Node)));
		hashCode = getHashCode(keys[i]);
		table->nodes[hashCode].compareCount++;
		table->nodes[hashCode].hashCode = hashCode;
		table->nodes[hashCode].index = hashCode;
		table->nodes[hashCode].key = keys[i];

		for (int j = 1; table->nodes[hashCode].key != -1; j++) {
			hashCode = getConflictCode(keys[i], j);
			table->nodes[hashCode].compareCount++;
			table->nodes[hashCode].index = hashCode;
		}
		
	}
}
int getConflictCode(KEY_TYPE key, int increasement) {
	return (key + increasement) % TABLE_MAX_SIZE;
}
