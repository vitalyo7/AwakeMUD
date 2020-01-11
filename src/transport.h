//  file: transport.h
//  author: Andrew Hynek
//  purpose: contains defines and structs for transportation system
//  Copyright (c) 1998 by Andrew Hynek

#ifndef _transport_h_
#define _transport_h_

#define ELEVATOR_FILE     "etc/elevator"

#define FIRST_CAB         600
#define LAST_CAB          610
#define FIRST_PORTCAB	  650
#define LAST_PORTCAB	  660

#define CMD_TAXI_NONE          0
#define CMD_TAXI_DEST          1
#define CMD_TAXI_YES           2
#define CMD_TAXI_NO            3

#define ACT_AWAIT_CMD     0
#define ACT_REPLY_DEST    1
#define ACT_AWAIT_YESNO   2
#define ACT_REPLY_NOTOK   3
#define ACT_REPLY_TOOBAD  4
#define ACT_DRIVING       5

#define ELEVATOR_BUTTON_VNUM 41
#define ELEVATOR_PANEL_VNUM  42

#define TAXI_DEST_TYPE_AREA_OF_TOWN               0
#define TAXI_DEST_TYPE_CORPORATE_PARK             1
#define TAXI_DEST_TYPE_TOURIST_ATTRACTION         2
#define TAXI_DEST_TYPE_TRANSPORTATION             3
#define TAXI_DEST_TYPE_RESTAURANTS_AND_NIGHTCLUBS 4
#define TAXI_DEST_TYPE_SHOPPING                   5
#define TAXI_DEST_TYPE_ACCOMMODATIONS             6
#define TAXI_DEST_TYPE_HOSPITALS                  7
#define NUM_TAXI_DEST_TYPES                       8

struct taxi_dest_type
{
  const char *title_string;
  const char *entry_color_string;
};

struct dest_data
{
  const char *keyword, *str;
  vnum_t vnum;
  unsigned int type;
  bool enabled;
};

struct floor_data
{
  vnum_t vnum;
  vnum_t shaft_vnum;
  sh_int doors;
};

struct elevator_data
{
  vnum_t room;
  sh_int columns, time_left, dir, num_floors, start_floor;
  struct floor_data *floor;
  long destination;
  bool is_moving;
  elevator_data() :
      floor(NULL), destination(0), is_moving(FALSE)
  {}
}
;

#endif
