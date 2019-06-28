#include "fsm.h"


FsmNode::FsmNode(int nodeId) {
	this->nodeId  = nodeId;
	this->onEnter = NULL;
	this->onInput = NULL;
}

FsmNode::FsmNode(int nodeId, StateEnterFunc onEnter) {
	this->nodeId  = nodeId;
	this->onEnter = onEnter;
	this->onInput = NULL;
}

FsmNode::FsmNode(int nodeId, StateEnterFunc onEnter, StateProcessFunc onInput) {
	this->nodeId  = nodeId;
	this->onEnter = onEnter;
	this->onInput = onInput;
}

Fsm::Fsm() {

}

Fsm::~Fsm() {
	// TODO: Go through each state and delete it
}

void Fsm::transitionTo(int state, struct descriptor_data *d) {
	FsmNode *nextState = this->getState(state);
	if(nextState == NULL) {
		log_vfprintf("[ FSM ] : ERROR : Invalid state found %d", state);
		return;
	}

	if(nextState->onEnter != NULL) {
		nextState->onEnter(this, d);
	}
}

void Fsm::handleInput(int state, struct descriptor_data *d, const char *arg) {
	log_vfprintf("*fsm beep");

	FsmNode *currNode = this->getState(state);
	if(currNode == NULL) {
		log_vfprintf("[ FSM ] : ERROR : Invalid state found %d", state);
		return;
	}

	if(currNode->onInput != NULL) {
		currNode->onInput(this, d, arg);
	}
}

FsmNode *Fsm::getState(int state) {
	map<int, FsmNode *>::iterator it;

	// Check if we are in the right state
	FsmNode *currNode = NULL;
	it = this->states.find(state);
	if ( it == this->states.end() ) {
	  // not found
	} else {
		currNode = it->second;
	}

	return currNode;
}

FsmNode *Fsm::createState(int state) {
	// Create a new node
	return this->createState(state, NULL, NULL);
}

FsmNode *Fsm::createState(int state, StateEnterFunc onEnter) {
	return this->createState(state, onEnter, NULL);
}

FsmNode *Fsm::createState(int state, StateEnterFunc onEnter, StateProcessFunc onInput) {
	FsmNode *currNode = this->getState(state);
	if(currNode != NULL) {
		log_vfprintf("[ FSM ] : WARNING : Fsm node already exists, not overriding ! : %d", state);
		return currNode;
	}

	this->states[state] = new FsmNode(state, onEnter, onInput);
}
