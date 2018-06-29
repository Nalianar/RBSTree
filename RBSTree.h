#ifndef _RBSTREE_H_
#define _RBSTREE_H_


struct BSTree
{
	struct Node  
	{
		int key;
		int size=1;
		Node* parent;
		Node* left;
		Node* right;
		Node(int k) { key = k; left = right = parent = nullptr; size = 1; }
	};
	Node * m_pRoot;
};



BSTree * RBSTreeCreate();

bool RBSTreeHasKey(BSTree * pTree, int key);

int getsize(BSTree::Node* p);

void fixsize(BSTree::Node* p);

void RBSTreeInsert(BSTree * pTree, int key);

void RBSTreeRemoveKey(BSTree * pTree, int key);

int RBSTreeFindKey(BSTree * pTree, int key);

void RBSTreeDestroy(BSTree * pTree);

void RBSTreeRotateLeft(BSTree* pTree);

void RBSTreeRotateRight(BSTree* pTree);

int RBSTreeMinimum(const BSTree * pTree);

int RBSTreeMaximum(const BSTree * pTree);

void RBSTreeInsertRoot(BSTree* pTree, int key);

typedef void(*BSTreeWalkFunction) (const BSTree::Node & pTreeNode);

void RBSTreeSymmetricWalk(const BSTree * pTree, BSTreeWalkFunction _f);

void RBSTreeReverseWalk(const BSTree * pTree, BSTreeWalkFunction _f);

void RBSTreeDirectWalk(const BSTree * pTree, BSTreeWalkFunction _f);

void RBSTreePrint(const BSTree::Node & pTreeNode);

BSTree::Node * BSTreeInsert(BSTree::Node* pTreeNode, int key);

int RBSTreeHeight(BSTree * pTree);

#endif //  _RBSTREE_H_
