#ifndef __fsm_h__
#define __fsm_h__
#include "structs.h"
#include <map>
#include <cstring>
using namespace std;

struct cmp_str
{
   bool operator()(char const *a, char const *b) const
   {
      return std::strcmp(a, b) < 0;
   }
};




class Fsm;
class FsmNode;
//class FsmEdge;

typedef void (*StateEnterFunc)      (Fsm *fsm, struct descriptor_data *d);
typedef void (*StateProcessFunc)    (Fsm *fsm, struct descriptor_data *d, const char *arg);
//typedef bool (*StateTransitionFunc) (Fsm *fsm, struct descriptor_data *d, int state, void *data);

#define FSM_STATE(name) void (name)(Fsm *fsm, struct descriptor_data *d)
#define FSM_INPUT(name) void (name)(Fsm *fsm, struct descriptor_data *d, const char *arg)

class FsmNode {
public:
	FsmNode(int nodeId);
	FsmNode(int nodeId, StateEnterFunc onEnter);
	FsmNode(int nodeId, StateEnterFunc onEnter, StateProcessFunc onInput);

	int nodeId;
	StateEnterFunc   onEnter;
	StateProcessFunc onInput;
private:
	map<char *, int, cmp_str> edges;
};

/*
class FsmEdge {

};
*/

class Fsm
{
public:
	Fsm();
	~Fsm();
	void transitionTo(int state, struct descriptor_data *d);
	void handleInput(int state, struct descriptor_data *d, const char *arg);

	FsmNode *getState(int state);
	FsmNode *createState(int state);
	FsmNode *createState(int state, StateEnterFunc onEnter);
	FsmNode *createState(int state, StateEnterFunc onEnter, StateProcessFunc onInput);
private:
	map<int, FsmNode *> states;
};

#endif
