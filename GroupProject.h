/*
* GroupProject.h
*
*  Created on: Mar 28, 2014
*      Author: Dr. Booth
*/

#ifndef GroupProject_H_
#define GroupProject_H_
#include "GLUT_Plotter.h"


/*
This is a basic implementation, might move it out of header,
deconstructor must set pointers to null.
No, keep splay tree in the header since it's templated.  --Michael
*/
template <class Base>
class SplayNode
{
private:
	Base value;
	SplayNode *left, *right;
public:
	SplayNode()
	{
	    this->value = Base();
        this->left = this->right = NULL;
	}

	~SplayNode()
	{
		if(this->left)
        {
            delete this->left;
        }
        if(this->right)
        {
            delete this->right;
        }
        this->left = this->right = NULL;
	}

	SplayNode(const Base &val)
	{
	    this->value = val;
	    this->left = this->right = NULL;
	}

	SplayNode(const Base &val, SplayNode *l, SplayNode *r)
	{
        this->value = val;
        this->left = l;
        this->right = r;
	}

	SplayNode(SplayNode *l, SplayNode *r)
	{
	    this->value = Base();
	    this->left = l;
	    this->right = r;
	}

	SplayNode* getRight()
	{
		return this->right;
	}

	SplayNode* getLeft()
	{
		return this->left;
	}

	void setVal(const Base &val)
	{
		this->value = val;
		return;
	}

	const Base getVal()
	{
	    return this->value;
	}
};

template <class Base>
class SplayTree
{
private:
	SplayNode<Base>* root;
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
	SplayNode<Base>* RRotation(SplayNode<Base> *top)
	{
	    SplayNode<Base> *temp = top->getLeft();
	    top->left = temp->getRight();
	    temp->right = top;
	    return temp;
	}

	SplayNode<Base>* LRotation(SplayNode<Base> *top)
	{
        SplayNode<Base> *temp = top->getRight();
        top->right = temp->getLeft();
        temp->left = top;
        return temp;
	}

	//you may or may not realize that double rotations are easy if you use
	//two single rotation function calls
	//void RRRotation(SplayNode<Base> *top);
	//void RLRotation(SplayNode<Base> *top);
	//void LRRotation(SplayNode<Base> *top);
	//void LLRotation(SplayNode<Base> *top);

	//return 0 if not found, 1 if found,
	//make ptr the address of the pointer you're using in the function call.
	//If the value is found, *ptr should point to it, if it's not found, let it.
	//point to the last valid node that isn't NULL
	//This can be done iteratively
	//it should also call "movetotop" (see below)

	//bool FindValue(SplayNode<Base> **ptr);

	//everything hard we learned in class
	//this function recursively moves the value at ptr to target.
	//if target isn't found, call the function again with a different
	//target(at the place where ptr would be if it was in range of a
	//double rotation, keep in mind our rotates don't change the
	//address location of parents so it should be fine recursively)

	//void MoveToTop(SplayNode<Base> *ptr, SplayNode<Base> *target);

	SplayNode<Base>* splay(SplayNode<Base> *root, const Base &splayval)
	{
        if((!root) || (root->getVal() == splayval))
        {
            return root;
        }
        if(root->getVal() > splayval)
        {
            if(!(root->getLeft()))
            {
                return root;
            }
            if(root->getLeft->getVal() > splayval)
            {
                root->left->left = splay(root->getLeft()->getLeft(),
                                          splayval);
                root = RRotation(root);
            }
            else if(root->getLeft()->getVal() < splayval)
            {
                root->left->right = splay(root->getLeft()->getRight(),
                                           splayval);
                if(root->getLeft()->getRight())
                {
                    root->left = LRotation(root->getLeft());
                }
            }
            return((!(root->getLeft()))? root: RRotation(root));
        }
        else
        {
            if(!(root->getRight()))
            {
                return root;
            }
            if(root->getRight->getVal() > splayval)
            {
                root->right->left = splay(root->getRight()->getLeft(),
                                           splayval);
                if(root->getRight()->getLeft())
                {
                    root->right = RRotation(root->getRight());
                }
                else if(root->getRight()->getVal() < splayval)
                {
                    root->right->right = splay(root->getRight()->getRight(),
                                                splayval);
                    root = LRotation(root);
                }
                return((!(root->getRight()))? root: LRotation(root));
            }
        }
	}


	//basically a combination of findValue and movetotop with a short part where
	//you use the "new" operand
	void AddValue(SplayNode<Base> *root, const Base &newval)
	{
        if(!root)
        {
            root = new SplayNode<Base>(newval);
        }
        root = splay(root, newval);
        if(root->getVal() == newval)
        {
            return;
        }
        SplayNode<Base> *temp = new SplayNode<Base>(newval);
        if(root->getVal() > newval)
        {
            temp->right = root;
            temp->left = root->getLeft();
            root->left = NULL;
        }
        else
        {
            temp->left = root;
            temp->right = root->getRight();
            root->right = NULL;
        }
        return temp;
	}

	void RemoveValue(const Base &delval)
	{
	    if(!(root))
        {
            return;
        }
        this->root = splay(this->root, delval);
        if(delval == root->getVal())
        {
            if(!(this->root->getLeft()))
            {
                this->root = this->root->getRight();
            }
            else
            {
                SplayNode<Base> *temp = this->root->getRight();
                this->root = this->root->getLeft();
                splay(this->root, delval);
                this->root->getRight() = temp;
            }
        }
        else
        {
            cerr << "[error] Value " << delval << " not found" << endl;
        }
	}

	//as of now I don't see anything else to add here except maybe a
	//printpreorder but if it's not required, this is where I'd like us to focus
};


class GroupProject {
private:
	GLUT_Plotter *g;
	int depth; //for spacing
public:
	//constructor
	GroupProject(GLUT_Plotter* g);

	//destructor
	~GroupProject();

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
