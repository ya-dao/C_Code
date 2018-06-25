#include "Huffman.h"
/*
	根据传入的值初始化这棵哈夫曼树,总的结点数为2N-1
	初始化一个由HuffmanTree指向的数组,里面是每个结点信息
*/
void initTree(HuffmanTree *tree, int *weights) {
	//具体数量必须单独括号计算乘完,3*2*2+1与3*(2*2+1)结果是不相同的
	//具体表现到malloc上就会出现堆已被破坏
	*tree = (HuffmanTree)malloc(sizeof(HuffmanNode) * (2 * N + 1));
	for (int i = 0; i < 2 * N + 1; i++)
	{
		if (i < N)
		{
			((*tree) + i)->weight = *(weights + i);
		}
		else {
			((*tree) + i)->weight = 0;
		}
		((*tree) + i)->leftChild = NULL;
		((*tree) + i)->rightChild = NULL;
		((*tree) + i)->parent = -1;
	}
}
/*
	总结点2N-1,减去N个叶结点,剩下N-1个结点待处理
	每次找出两个权值最小的结点,将其权值相加并当作一个新的结点处理,同时将它设置为这两个结点的父结点
*/
void createTree(HuffmanTree *tree) {
	int firstIndex = 0;
	int secondIndex = 0;
	for (int i = 0; i < N - 1; i++)
	{
		if (i == N - 2) {
			printf("");
		}
		selectMinimum(*tree, &firstIndex, &secondIndex);
		printf("first=%d,second=%d\n",(*tree + firstIndex)->weight, (*tree + secondIndex)->weight);
		(*tree + firstIndex)->parent = N + i;
		(*tree + secondIndex)->parent = N + i;
		(*tree + N + i)->weight = (*tree + firstIndex)->weight + (*tree + secondIndex)->weight;
		(*tree + N + i)->leftChild = (*tree + firstIndex);
		(*tree + N + i)->rightChild = (*tree + secondIndex);
	}
}
/*
	找出父结点为空的两个最小结点的下标
*/
void selectMinimum(HuffmanTree tree,int *firstIndex,int *secondIndex) {
	*firstIndex = 0;
	*secondIndex = 0;
	int isInit = 0;
	for (int i = 0; i < 2 * N - 1; i++)
	{
		if ((tree + i)->parent != -1)
		{
			continue;
		}
		else {
			if (0 == isInit) {
				*firstIndex = i;
				isInit++;
			}
			else if (1 == isInit) {
				*secondIndex = i;
				isInit++;
			}
			if ((tree + i)->weight != 0) {
				//不能用等于,如果新结点权值与之前结点权值相等会造成前面一个结点会被新结点覆盖
				if ((tree + i)->weight < (tree + *firstIndex)->weight)
				{
					//此时发现了一个比第一小的数更小的数,所以原来第一小的现在变成了第二小
					*secondIndex = *firstIndex;
					*firstIndex = i;
				}else if((tree + i)->weight < (tree + *secondIndex)->weight){
					//如果不小于第一小,还可能小于当前第二小的,需要单独判断
					*secondIndex = i;
				}
			}
		}
	}
}
void prefix(HuffmanTree tree) {
	if (tree == NULL)
	{
		return;
	}
	else {
		printf("%d ",tree->weight);
		prefix(tree->leftChild);
		prefix(tree->rightChild);
	}
}
/*
	按照左0右1编码
	code:这是一个指针数组,每个元素都存放对应结点的编码信息
	每个节点的编码长度必定小于n(即树深度小于n),原因:
		假设最坏情况下没有分支(即根结点只有一个儿子结点的情况),n个叶子结点会生成n-1个非叶子结点,
		由于每次挑选两个权值最小的结点,ceil((2n - 1) / 2)向上取整最多为n
	tree:该树的基准地址,每个结点的父结点下标都从该地址进行偏移
	currentNode:当前的结点,该结点获取到的父结点不能直接相对于它进行偏移
	code:当前编码存放的单元地址
*/
void encodeRecursive(HuffmanTree tree, HuffmanTree currentNode, char *code) {
	if (currentNode == NULL || currentNode->parent == -1) {
		return;
	}
	else {
		//tree的地址每次都在相对变化,而父结点的下标没有随着变化,直接加后面会导致越界
		HuffmanTree parent = tree + currentNode->parent;
		//不能比权值,否则左右孩子权值相等就尴尬了,直接比地址吧
		if (parent->leftChild == currentNode) {
			*code = LEFT;
		}
		else {
			*code = RIGHT;
		}
		code--;
		encodeRecursive(tree,parent,code);
	}
}
