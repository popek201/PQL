/*
 * PQL.cpp
 *
 *  Created on: 29 mar 2016
 *      Author: Popek
 */


#include "PQL.h"
#include "tree_util.hh"
#include "PQLNode.h"
#include "PQLTree.h"
#include "../QueryPreProcessor.h"

using namespace std;

PQL::PQL() {
	// TODO Auto-generated constructor stub
}

PQL::~PQL() {
	// TODO Auto-generated destructor stub
}

int main(int argc, char** args) {

	// DRZEWO PQL
	/*
	tree<tree_node_<PQLNode>>::iterator iter;
	PQLTree* tree;
	tree = tree->getInstance();
	PQLNode* node;
	tree_node_<PQLNode>* treeNode;

	// assign a; select a such that parent(a,2) and follows*(_,a);

	node = new QueryNode();
	treeNode = new tree_node_<PQLNode>(*node);
	iter = tree->appendRoot(*treeNode);

	node = new ResultMainNode();
	treeNode = new tree_node_<PQLNode>(*node);
	iter = tree->appendChild(iter, *treeNode);

	node = new ResultNode(new Field("assign", "a", false, false, false));
	treeNode = new tree_node_<PQLNode>(*node);
	iter = tree->appendChild(iter, *treeNode);

	iter = tree->getRoot();

	node = new SuchMainNode();
	treeNode = new tree_node_<PQLNode>(*node);
	iter = tree->appendChild(iter, *treeNode);

	node = new SuchNode("parent", new Field("assign", "a", false, false, false), new Field("constant", "2", false, false, false), false);
	treeNode = new tree_node_<PQLNode>(*node);
	iter = tree->appendChild(iter, *treeNode);

	node = new SuchNode("follows", new Field("all", "_", false, false, false), new Field("assign", "a", false, false, false), true);
	treeNode = new tree_node_<PQLNode>(*node);
	iter = tree->appendSibling(iter, *treeNode);

	tree->printTree();
	*/


	//string a = "assign a, a2; prog_line p; select a, p.procname such that parent(a,2) and follows*(\"ala\",a2) such that uses(_,p) such that modifies*(2,p);";
	//string a = "assign a; select a such that follows(a,\"a\") such that parent(a,a);";
	string a = "assign a; select a such that modifies(a,\"2\");";

	cout << "**** ZAPYTANIE **************************************************" << endl;
	cout << a << endl << endl;

	cout << "**** DRZEWO *****************************************************" << endl;
	QueryPreProcessor* que = new QueryPreProcessor();
	que->parseQuery(a);

	tree<tree_node_<PQLNode>>::iterator iter;
	PQLTree* tree = que->getTree();
	tree->printTree();

	cout << endl;
	cout << "**** KONIEC *****************************************************" << endl;

	//cout << tree->getRoot()->data.type << endl;

	//PQLNode p = tree->getRoot()->data;
	//cout << typename;
	//cout << endl;
	//ResultNode q = static_cast<ResultNode>(tree->getRoot()->first_child->first_child->data.type);
	//q.getField()->printField();

	return 0;
}
