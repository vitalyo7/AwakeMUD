#ifndef __chargen_h__
#define __chargen_h__

#include "fsm.h"

//extern const char *pc_race_types[];
class Chargen
{
public:
	Chargen();
	~Chargen();
	void create_parse(struct descriptor_data *d, const char *arg);
private:
	Fsm chargenFsm;
};

#endif
