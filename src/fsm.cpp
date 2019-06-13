#include "fsm.h"


FsmNode::FsmNode(int nodeId) {
	this->nodeId  = nodeId;
	this->onEnter = NULL;
}

FsmNode::FsmNode(int nodeId, StateEnterFunc func) {
	this->nodeId  = nodeId;
	this->onEnter = func;
}

Fsm::Fsm() {

}

Fsm::~Fsm() {
	// TODO: Go through each state and delete it
}

void Fsm::transitionTo(int state) {

}

void Fsm::transitionTo(int state, void *data) {

}

void Fsm::handleInput(int state, struct descriptor_data *d, const char *arg) {
	log_vfprintf("*fsm beep");

	FsmNode *currNode = this->getState(state);
	if(currNode == NULL) {
		log_vfprintf("[ FSM ] : ERROR : Invalid state found %d", state);
		return;
	}

	if(currNode->onEnter != NULL) {
		currNode->onEnter(this, d);
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
	return this->createState(state, NULL);
}

FsmNode *Fsm::createState(int state, StateEnterFunc func) {
	FsmNode *currNode = this->getState(state);
	if(currNode != NULL) {
		log_vfprintf("[ FSM ] : WARNING : Fsm node already exists, not overriding ! : %d", state);
		return currNode;
	}

	this->states[state] = new FsmNode(state, func);
}
