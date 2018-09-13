//#include "parent.h"
//#include "Child.h"
#include "ChildSibling.h"

//void testParent();
//void testChild();
void testChildSibling();

void main() {
	//testParent();
	///testChild();
	testChildSibling();
	system("pause");
}

//void testParent() {
//	ParentTree tree = NULL;
//	
//	pt_init(&tree);
//	pt_create(tree);
//	pt_show(tree);
//	pt_queryParent(tree);
//	pt_queryChild(tree);
//	pt_destroy(tree);
//}
//void testChild() {
//	ChildTree tree = NULL;
//
//	ct_init(&tree);
//	ct_create(tree);
//	ct_show(tree);
//	ct_queryParent(tree);
//	ct_queryChild(tree);
//	ct_destroy(tree);
//}
void testChildSibling() {
	CSTree tree = NULL;
	char *str = "ABDG#H#I####CEJ##F###";
	//char *str = "AB#D##C##";

	cs_init(&tree);
	cs_create(&tree,&str);
	cs_show(tree);
}