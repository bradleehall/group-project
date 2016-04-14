/*
* GroupProject.h
*
*  Created on: Mar 28, 2014
*  Created on: Mar 28, 2014
*      Author: Dr. Booth
*/

#ifndef GroupProject_H_
#define GroupProject_H_
#include "GLUT_Plotter.h"


/*
This is a basic implementation, might move it out of header,
deconstructor must set pointers to null.
*/
class SplayNode {
private:
	int value;
	SplayNode *left, *right;
public:
	SplayNode();

	~SplayNode() {
		left = NULL;
		right = NULL;
	}
	SplayNode(int val)
	{
	    this->value = val;
	    this->left = this->right = NULL;
	}
	SplayNode(int val, SplayNode* l, SplayNode* r)
	{
        this->value = val;
        this->left = l;
        this->right = r;
	}

	SplayNode* getRight() {
		return right;
	}
	SplayNode* getLeft() {
		return left;
	}
	void setVal(int val) {
		value = val;
		return;
	}
};


class SplayTree {
private:
	SplayNode* root;
public:
	//right rotation, used with "locate value", really complicated
	//so here's some pseudocode, right rotation is basically the same
	//thing only opposite
	/*
	check right != null
	swap data between right child and this(value at top)
	save this->right as temp and modify this->right to equal temp-> right
	now save this->left as temp2
	set this->left to temp
	set temp->right to temp ->left
	set temp->left to temp2
	*/
	void RRotation(SplayNode* top);
	void LRotation(SplayNode* top);

	//you may or may not realize that double rotations are easy if you use
	//two single rotation function calls
	void RRRotation(SplayNode* top);
	void RLRotation(SplayNode* top);
	void LRRotation(SplayNode* top);
	void LLRotation(SplayNode* top);

	//return 0 if not found, 1 if found,
	//make ptr the address of the pointer you're using in the function call.
	//If the value is found, *ptr should point to it, if it's not found, let it.
	//point to the last valid node that isn't NULL
	//This can be done iteratively
	//it should also call "movetotop" (see below)
	bool FindValue(SplayNode **ptr);

	//everything hard we learned in class
	//this function recursively moves the value at ptr to target.
	//if target isn't found, call the function again with a different
	//target(at the place where ptr would be if it was in range of a
	//double rotation, keep in mind our rotates don't change the
	//address location of parents so it should be fine recursively)
	void MoveToTop(SplayNode *ptr, SplayNode* target);


	//basically a combination of findValue and movetotop with a short part where
	//you use the "new" operand
	void AddValue();
	void RemoveValue();

	//as of now I don't see anything else to add here except maybe a printpreorder
	//but if it's not required, this is where I'd like us to focus
};


class GroupProject {
private:
	GLUT_Plotter *g;
	int depth; //for spacing
public:
	//constructor
	GroupProject(GLUT_Plotter* g);

	//gets depth of tree
	int getDepth();

	//calculates depth of tree...it might be better to implement this in
	//Splay Tree
	int CalculateDepth();

	//Unless I'm forgetting something, the rest can be GUI
	//we haven't decided how the gui will work, but since we have
	//mouse capabilities, it might be cool to implement a system
	//where people could click on a value and get their options
	//at the bottom of the screen. In addition, we have to
	//be wary of having literal tonnes of values, i.e. you have
	//to scroll to see them all
	//with this being a possibility, it might just be better to use a simple
	//arrow key approach, I think we should talk about it.


	//Main GAIM FUNCTION
	void Play(void);
};

#endif /* GroupProject_H_ */
