#include "CSQueue.h"
/*
	男士和女士各排成一队,跳舞开始时,依次从男和女队头各出一人配对,
	若两队初始人数不一样,则长的那一队中未配对者等待下一只舞曲.
	写一算法模拟上述舞伴配对问题
*/
void show(Participant participant) {
	printf("姓名:%-6s,性别:%c\n",participant->name,participant->gender);
}
void showPartner(Participant MParticipant, Participant FParticipant,int group) {
	printf("第%d组:男士:%-6s,女士:%-6s\n", group,MParticipant->name, FParticipant->name);
}
void main() {
	Participant participants[10] = {NULL};
	char *names[10] = {"专家","二娃","鱿鱼","胖娃","小泉君","疯子","流氓","大爷","蒙蒙","袁大妈"};
	char genders[10] = { 'M', 'M', 'M', 'M', 'M', 'M', 'F', 'F', 'F', 'F' };
	for (int i = 0; i < 10; i++)
	{
		participants[i] = malloc(sizeof(struct Person));
		participants[i]->gender = genders[i];
		participants[i]->name = names[i];
	}
	
	CSQueue MQueue;
	init(&MQueue);
	CSQueue FQueue;
	init(&FQueue);

	for (int i = 0; i < 10; i++)
	{
		if (participants[i]->gender == 'F') {
			enQueue(&FQueue, participants[i]);
		}
		else {
			enQueue(&MQueue, participants[i]);
		}
	}

	printf("舞曲开始:\n");
	for (int i = 0;!isEmpty(MQueue) && !isEmpty(FQueue);i++)
	{
		showPartner(deQueue(&MQueue), deQueue(&FQueue),i+1);
	}
	if (!isEmpty(MQueue))
	{
		printf("下一首最先匹配的男士是:%s\n",getHead(MQueue)->name);
	}
	if (!isEmpty(FQueue))
	{
		printf("下一首最先匹配的女士是:%s\n", getHead(FQueue)->name);
	}
	system("pause");
}
