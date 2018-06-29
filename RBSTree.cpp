

#include "RBSTree.h"

#include <stdlib.h>
#include <cassert>
#include <iostream>



BSTree * RBSTreeCreate()
{
	BSTree * pTree = new BSTree;
	pTree->m_pRoot = nullptr;
	return pTree;
}


BSTree::Node* RBSTreeFind(BSTree::Node* pTreeNode, int key) 
{
	
	if (!pTreeNode)
		return nullptr; 

	if (key == pTreeNode->key)
		return pTreeNode;
	if (key < pTreeNode->key)
		return RBSTreeFind(pTreeNode->left, key);
	else
		return RBSTreeFind(pTreeNode->right, key);
}


bool RBSTreeHasKey(BSTree * pTree, int key)
{
	BSTree::Node * pCurrrent = pTree->m_pRoot;
	return RBSTreeFind( pCurrrent,  key) != nullptr;
}


int RBSTreeFindKey(BSTree * pTree, int key)
{	
	BSTree::Node * pCurrent = pTree->m_pRoot;
	pCurrent = RBSTreeFind(pCurrent, key);;
	return pCurrent->key;
}


int getsize(BSTree::Node* pTreeNode) 
{
	if (!pTreeNode) 
		return 0;

	return pTreeNode->size;
}


void fixsize(BSTree::Node* pTreeNode) 
{
	pTreeNode->size = getsize(pTreeNode->left) + getsize(pTreeNode->right) + 1;
}


BSTree::Node* RBSTreeRotateRight(BSTree::Node* pTreeNode)
{
	BSTree::Node* qTreeNode = pTreeNode->left;

	if (!qTreeNode) 
		return pTreeNode;

	pTreeNode->left = qTreeNode->right;
	if (qTreeNode->right)
		qTreeNode->right->parent = pTreeNode;
	qTreeNode->right = pTreeNode;
	if (pTreeNode)
		pTreeNode->parent = qTreeNode;
	qTreeNode->size = pTreeNode->size;

	fixsize(pTreeNode);

	return qTreeNode;
}


void RBSTreeRotateRight(BSTree * pTree)
{
	pTree->m_pRoot = RBSTreeRotateRight(pTree->m_pRoot);
}


BSTree::Node* RBSTreeRotateLeft(BSTree::Node* qTreeNode) 
{
	BSTree::Node* pTreeNode = qTreeNode->right;

	if (!pTreeNode)
		return qTreeNode;

	qTreeNode->right = pTreeNode->left;
	if (pTreeNode->left)
		pTreeNode->left->parent = qTreeNode;
	pTreeNode->left = qTreeNode;
	if (qTreeNode)
		qTreeNode->parent = pTreeNode;
	pTreeNode->size = qTreeNode->size;

	fixsize(qTreeNode);

	return pTreeNode;
}


void RBSTreeRotateLeft(BSTree* pTree)
{
	pTree->m_pRoot = RBSTreeRotateLeft(pTree->m_pRoot);
}


BSTree::Node* RBSTreeInsertRoot(BSTree::Node* pTreeNode, int key) 
{
	if (!pTreeNode)
		return new BSTree::Node(key);

	if (key<pTreeNode->key)
	{
		pTreeNode->left = RBSTreeInsertRoot(pTreeNode->left, key);
		return RBSTreeRotateRight(pTreeNode);
	}
	else
	{
		pTreeNode->right = RBSTreeInsertRoot(pTreeNode->right, key);
		return RBSTreeRotateLeft(pTreeNode);
	}


}


void RBSTreeInsertRoot(BSTree* pTree, int key)
{
	pTree->m_pRoot = RBSTreeInsertRoot(pTree->m_pRoot, key);
}



BSTree::Node * RBSTreeInsert(BSTree::Node* pTreeNode, int key) 
{
	BSTree::Node * mParent = nullptr;

	if (!pTreeNode)
		return new BSTree::Node(key);

	if (rand() % (pTreeNode->size + 1) == 0)
		return RBSTreeInsertRoot(pTreeNode, key);

	if (pTreeNode->key > key)
	{
		mParent = pTreeNode;
		pTreeNode->left = RBSTreeInsert(pTreeNode->left, key);
	}
	else
	{
		mParent = pTreeNode;
		pTreeNode->right = RBSTreeInsert(pTreeNode->right, key);
	}

	fixsize(pTreeNode);

	if (pTreeNode->key > key)
	{
		pTreeNode->left->parent = mParent;
	}
	else
	{
		pTreeNode->right->parent = mParent;
	}

	return pTreeNode;
}


void RBSTreeInsert(BSTree * pTree, int key)
{
	pTree->m_pRoot = RBSTreeInsert(pTree->m_pRoot, key);
}


BSTree::Node * BSTreeInsert(BSTree::Node* pTreeNode, int key)
{
	BSTree::Node * mParent = nullptr;

	if (!pTreeNode)
		return new BSTree::Node(key);

	if (pTreeNode->key > key)
	{
		mParent = pTreeNode;
		pTreeNode->left = BSTreeInsert(pTreeNode->left, key);
	}
	else
	{
		mParent = pTreeNode;
		pTreeNode->right = BSTreeInsert(pTreeNode->right, key);
	}

	fixsize(pTreeNode);

	if (pTreeNode->key > key)
	{
		pTreeNode->left->parent = mParent;
	}
	else
	{
		pTreeNode->right->parent = mParent;
	}

	return pTreeNode;
}


BSTree::Node* RBSTreeJoinNode(BSTree::Node* pTreeNode, BSTree::Node* qTreeNode) 
{
	BSTree::Node * mParent = nullptr;

	if (!pTreeNode)
		return qTreeNode;

	if (!qTreeNode)
		return pTreeNode;

	if (rand() % (pTreeNode->size + qTreeNode->size) > pTreeNode->size)
	{
		
		pTreeNode->right = RBSTreeJoinNode(pTreeNode->right, qTreeNode);
		
		fixsize(pTreeNode);
		return pTreeNode;
	}
	else
	{
		
		qTreeNode->left = RBSTreeJoinNode(pTreeNode, qTreeNode->left);
		
		fixsize(qTreeNode);
		return qTreeNode;
	}
}



BSTree::Node* RBSTreeRemoveKey(BSTree::Node* pTreeNode, int key) 
{
	if (!pTreeNode)
		return pTreeNode;

	BSTree::Node * mParent = pTreeNode->parent;

	if (pTreeNode->key == key)
	{
		
		BSTree::Node* qTreeNode = RBSTreeJoinNode(pTreeNode->left, pTreeNode->right);
		delete pTreeNode;
		return qTreeNode;
	}
	else if (key < pTreeNode->key)
		pTreeNode->left = RBSTreeRemoveKey(pTreeNode->left, key);
	else
		pTreeNode->right = RBSTreeRemoveKey(pTreeNode->right, key);

	pTreeNode->parent = mParent;
	return pTreeNode;
}


void RBSTreeRemoveKey(BSTree * pTree, int key)
{
	BSTree::Node * pCurrent = RBSTreeRemoveKey(pTree->m_pRoot, key);
	pTree->m_pRoot = pCurrent;
}


void RBSTreeDestroy(BSTree::Node * pTreeNode)
{
	if (!pTreeNode)
		return;


	RBSTreeDestroy(pTreeNode->left);
	RBSTreeDestroy(pTreeNode->right);
	delete pTreeNode;
}


void RBSTreeDestroy(BSTree * pTree)
{
	if (!pTree->m_pRoot)
		return;

	RBSTreeDestroy(pTree->m_pRoot);
	delete pTree;
}


BSTree::Node * BSTreeMinimumNode(BSTree::Node * _pNode)
{
	assert(_pNode);

	BSTree::Node * pCurrent = _pNode;
	while (pCurrent && pCurrent->left)
		pCurrent = pCurrent->left;

	return pCurrent;
}


int RBSTreeMinimum(const BSTree * _tree)
{
	BSTree::Node * pMinimumNode = BSTreeMinimumNode(_tree->m_pRoot);
	return pMinimumNode->key;
}


int RBSTreeMaximum(const BSTree * _tree)
{
	assert(_tree->m_pRoot);

	const BSTree::Node * pCurrent = _tree->m_pRoot;
	while (pCurrent && pCurrent->right)
		pCurrent = pCurrent->right;

	return pCurrent->key;
}


void RBSTreePrint(const BSTree::Node & pTreeNode)
{
	std::cout << pTreeNode.key << ' ';
}


void RBSTreeSymmetricWalk(const BSTree::Node * pTreeNode, BSTreeWalkFunction _f)
{
	if (!pTreeNode)
		return;

	RBSTreeSymmetricWalk(pTreeNode->left, _f);
	(*_f)(*pTreeNode);
	RBSTreeSymmetricWalk(pTreeNode->right, _f);
}


void RBSTreeSymmetricWalk(const BSTree * pTree, BSTreeWalkFunction _f)
{
	RBSTreeSymmetricWalk(pTree->m_pRoot, _f);
}


void RBSTreeReverseWalk(const BSTree::Node * pTreeNode, BSTreeWalkFunction _f)
{
	if (!pTreeNode)
		return;

	RBSTreeReverseWalk(pTreeNode->left, _f);
	RBSTreeReverseWalk(pTreeNode->right, _f);
	(*_f)(*pTreeNode);
}


void RBSTreeReverseWalk(const BSTree * pTree, BSTreeWalkFunction _f)
{
	RBSTreeReverseWalk(pTree->m_pRoot, _f);
}


void RBSTreeDirectWalk(const BSTree::Node * pTreeNode, BSTreeWalkFunction _f)
{
	if (!pTreeNode)
		return;

	(*_f)(*pTreeNode);
	RBSTreeDirectWalk(pTreeNode->left, _f);
	RBSTreeDirectWalk(pTreeNode->right, _f);
}


void RBSTreeDirectWalk(const BSTree * pTree, BSTreeWalkFunction _f)
{
	RBSTreeDirectWalk(pTree->m_pRoot, _f);
}


int RBSTreeHeight(BSTree::Node * pTreeNode)
{
	
	if (!pTreeNode)
		return 0;

	int left = 1, right = 1;
	if (pTreeNode->left)
	{
		//pTree->m_pRoot = pTreeNode->left;
		left += RBSTreeHeight(pTreeNode->left);
	}
	if (pTreeNode->right)
	{
		//pTree->m_pRoot = pTreeNode->right;
		right += RBSTreeHeight(pTreeNode->right);
	}
	return (left > right ? left : right);
}


int RBSTreeHeight(BSTree * pTree)
{
	return RBSTreeHeight(pTree->m_pRoot);
}




