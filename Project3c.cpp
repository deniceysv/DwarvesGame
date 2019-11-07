/* Author: Denice Veluz
Builds the fence
*/

#include <iostream>
#include "bot.h"
#include <cstdlib>
#include <cmath>
using namespace std;

const int MAX_ROWS = 40;
const int MAX_COLS = 40;
const int MAX_NUM = 10;

int ROWS; // global variables
int COLS;
int NUM;

bool atTheTop[MAX_NUM];
bool startedBuilding = false;

bool is_0_walking = false;
bool is_building_fence = false;

bool is_1building_fence = false;
bool is_1_walking = false;

bool is_2building_fence = false;
bool is_2_walking = false; //dwarf1

bool is_3building_fence = false;
bool is_3_walking = false; //dwarf1

bool is_4building_fence = false;
bool is_4_walking = false;

bool is_5building_fence = false;
bool is_5_walking = false; //dwarf1

int fencecount = 0;
/* onStart:
An Initialization procedure called at the start of the game.
You can use it to initialize certain global variables, or do
something else before the actual simulation starts.
Parameters:
    rows: number of rows
    cols: number of columns
    num:  number of dwarfs
    log:  a cout-like log */

void onStart(int rows, int cols, int num, std::ostream &log)
{
  log << "Start!" << endl; // Print a greeting message

  ROWS = rows; // Save values in global variables
  COLS = cols;
  NUM = num;
  for (int i = 0; i < MAX_NUM; i++)
  {
    atTheTop[i] = false;
  }
}

/* onAction:
A procedure called each time an idle dwarf is choosing
their next action.
Parameters:
    dwarf:   dwarf choosing an action
    day:     day (1+)
    hours:   number of hours in 24-hour format (0-23)
    minutes: number of minutes (0-59)
    log:     a cout-like log  */

bool isNextTo(Dwarf &dwarf, Place lookingfor)
{
  int r = dwarf.row();
  int c = dwarf.col();
  if (dwarf.look(r, c + 1) == lookingfor)
  {
    return true;
  }
  else if (dwarf.look(r, c - 1) == lookingfor)
  {
    return true;
  }
  else if (dwarf.look(r + 1, c) == lookingfor)
  {
    return true;
  }
  else if (dwarf.look(r - 1, c) == lookingfor)
  {
    return true;
  }
  return false;
}

//This function finds a spot (that is empty) next to a tree
void OtherTree(Dwarf &dwarf, int tree_r, int tree_c, ostream &log)
{

  if (dwarf.look(tree_r, tree_c + 1) == EMPTY) //dwarf will look for row & column and see if it empty
                                               //c+1 = a column to the right
  {
    dwarf.start_walk(tree_r, tree_c + 1); //if its empty, then walk to it
    return;
  }
  else if (dwarf.look(tree_r, tree_c - 1) == EMPTY)
  {
    dwarf.start_walk(tree_r, tree_c - 1);
    return;
  }
  else if (dwarf.look(tree_r + 1, tree_c) == EMPTY)
  {
    dwarf.start_walk(tree_r + 1, tree_c);
    return;
  }
  else if (dwarf.look(tree_r - 1, tree_c) == EMPTY)
  {
    dwarf.start_walk(tree_r - 1, tree_c);
    return;
  }
}
void ChopTree(Dwarf &dwarf, ostream &log)
{
  int r = dwarf.row();
  int c = dwarf.col();
  if (dwarf.look(r, c + 1) == PINE_TREE || dwarf.look(r, c + 1) == APPLE_TREE)
  {
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(EAST);
    return;
  }
  else if (dwarf.look(r, c - 1) == PINE_TREE || dwarf.look(r, c - 1) == APPLE_TREE)
  {
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(WEST);
    return;
  }
  else if (dwarf.look(r + 1, c) == PINE_TREE || dwarf.look(r + 1, c) == APPLE_TREE)
  {
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(SOUTH);
    return;
  }
  else if (dwarf.look(r - 1, c) == PINE_TREE || dwarf.look(r - 1, c) == APPLE_TREE)
  {
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(NORTH);
    return;
  }
}

void HalftheDwarvesinTheGrid(Dwarf &dwarf, ostream &log, Place lookingfor)
{
  if (dwarf.name() >= 3)
  {
    for (int i = 0; i < ROWS; i++)
    {
      for (int j = 0; j < COLS / 2; j++)
      {
        if (dwarf.look(i, j) == lookingfor)
        {
          OtherTree(dwarf, i, j, log); //finds a space next to a tree to the dwarf to walk to it
          return;
        }
      }
    }
  }
  else
  {
    for (int i = 0; i < ROWS; i++)
    {
      for (int j = COLS / 2; j < COLS; j++)
      {
        if (dwarf.look(i, j) == lookingfor)
        {
          OtherTree(dwarf, i, j, log); //finds a space next to a tree to the dwarf to walk to it
          return;
        }
      }
    }
  }
}

void BuildTheFence(Dwarf &dwarf, ostream &log)
{
  if (dwarf.name() == 0)
  {
    if (is_0_walking == false)
    {
      if (is_building_fence == false)
      {
        if (dwarf.look(1, 1) == EMPTY)
        {
          is_0_walking = true;
          //log << "Walk" << endl;
          dwarf.start_walk(1, 1);
        }
        else
        {
          //log << "Chop" << endl;
          ChopTree(dwarf, log);
        }
      }
      else
      {
        is_0_walking = true;
        //log << "Walking1step" << endl;
        dwarf.start_walk(dwarf.row() + 1, 1);
      }
    }
    else
    {
      is_building_fence = true;
      is_0_walking = false;
      //log << "build" << endl;
      fencecount++;
      dwarf.start_build(NORTH);
    }
  }

  if (dwarf.name() == 1)
  {
    if (is_1_walking == false)
    {
      if (is_1building_fence == false)
      {
        if (dwarf.look(1, 2) == EMPTY)
        {
          is_1_walking = true;
          //log << "Walk" << endl;
          dwarf.start_walk(1, 2);
        }
        else
        {
          //log << "Chop" << endl;
          ChopTree(dwarf, log);
        }
      }
      else
      {
        is_1_walking = true;
        //log << "Walking1step" << endl;
        dwarf.start_walk(dwarf.row() + 1, 2);
      }
    }
    else
    {
      is_1building_fence = true;
      is_1_walking = false;
      // log << "build" << endl;
      fencecount++;
      dwarf.start_build(NORTH);
    }
  }

  if (dwarf.name() == 2)
  {
    if (is_2_walking == false)
    {
      if (is_2building_fence == false)
      {
        if (dwarf.look(1, 3) == EMPTY)
        {
          is_2_walking = true;
          //log << "Walk" << endl;
          dwarf.start_walk(1, 3);
        }
        else
        {
          //log << "Chop" << endl;
          ChopTree(dwarf, log);
        }
      }
      else
      {
        is_2_walking = true;
        //log << "Walking1step" << endl;
        dwarf.start_walk(dwarf.row() + 1, 3);
      }
    }
    else
    {
      is_2building_fence = true;
      is_2_walking = false;
      //log << "build" << endl;
      fencecount++;
      dwarf.start_build(NORTH);
    }
  }
  if (dwarf.name() == 3)
  {
    if (is_3_walking == false)
    {
      if (is_3building_fence == false)
      {
        if (dwarf.look(1, 4) == EMPTY)
        {
          is_3_walking = true;
          //log << "Walk" << endl;
          dwarf.start_walk(1, 4);
        }
        else
        {
          //log << "Chop" << endl;
          ChopTree(dwarf, log);
        }
      }
      else
      {
        is_3_walking = true;
        //log << "Walking1step" << endl;
        dwarf.start_walk(dwarf.row() + 1, 4);
      }
    }
    else
    {
      is_3building_fence = true;
      is_3_walking = false;
      //log << "build" << endl;
      fencecount++;
      dwarf.start_build(NORTH);
    }
  }

  if (dwarf.name() == 4)
  {
    if (is_4_walking == false)
    {
      if (is_4building_fence == false)
      {
        if (dwarf.look(1, 5) == EMPTY)
        {
          is_4_walking = true;
          //log << "Walk" << endl;
          dwarf.start_walk(1, 5);
        }
        else
        {
          //log << "Chop" << endl;
          ChopTree(dwarf, log);
        }
      }
      else
      {
        is_4_walking = true;
        //log << "Walking1step" << endl;
        dwarf.start_walk(dwarf.row() + 1, 5);
      }
    }
    else
    {
      is_4building_fence = true;
      is_4_walking = false;
      //log << "build" << endl;
      fencecount++;
      dwarf.start_build(NORTH);
    }
  }

  if (dwarf.name() == 5)
  {
    if (is_5_walking == false)
    {
      if (is_5building_fence == false)
      {
        if (dwarf.look(1, 6) == EMPTY)
        {
          is_5_walking = true;
          // log << "Walk" << endl;
          dwarf.start_walk(1, 6);
        }
        else
        {
          //log << "Chop" << endl;
          ChopTree(dwarf, log);
        }
      }
      else
      {
        is_5_walking = true;
        //log << "Walking1step" << endl;
        dwarf.start_walk(dwarf.row() + 1, 6);
      }
    }
    else
    {
      is_5building_fence = true;
      is_5_walking = false;
      //log << "build" << endl;
      fencecount++;
      dwarf.start_build(NORTH);
    }
  }
}

bool IsThere(Dwarf &dwarf, Place lookingfor)
{
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      if (dwarf.look(i, j) == lookingfor)
      {
        return true;
      }
    }
  }
  return false;
}

int AppleTreeCounter(Dwarf &dwarf, Place lookingfor)
{
  int count = 0;
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      if (dwarf.look(i, j) == lookingfor)
      {
        count++;
      }
    }
  }
  return count;
}

void BuildAroundDwarf(Dwarf &dwarf, ostream &log)
{
  int r = dwarf.row();
  int c = dwarf.col();
  log << "protecting myself\n ";
  if (dwarf.look(r, c + 1) == EMPTY) //EAST
  {
    log << dwarf.name() << "- building east\n";
    dwarf.start_build(EAST);
  }
  else if (dwarf.look(r, c - 1) == EMPTY) //WEST
  {
    log << dwarf.name() << "- building west\n";
    dwarf.start_build(WEST);
  }
  else if (dwarf.look(r + 1, c) == EMPTY) //SOUTH
  {
    log << dwarf.name() << "- building SOUTH\n";
    dwarf.start_build(SOUTH);
  }
  else if (dwarf.look(r - 1, c) == EMPTY) //NORTH
  {
    log << dwarf.name() << "- buildingnorth\n";
    dwarf.start_build(NORTH);
  }
}

void DestroyFence(Dwarf &dwarf, ostream &log)
{

  int r = dwarf.row();
  int c = dwarf.col();

  if (dwarf.look(r, c + 1) == FENCE) //EAST
  {
    log << dwarf.name() << "DESTROY\n";
    dwarf.start_chop(EAST);
  }
  else if (dwarf.look(r, c - 1) == FENCE) //WEST
  {
    log << dwarf.name() << "DESTROY\n";
    dwarf.start_chop(WEST);
  }
  else if (dwarf.look(r + 1, c) == FENCE) //SOUTH
  {
    log << dwarf.name() << "DESTROY\n";
    dwarf.start_chop(SOUTH);
  }
  else if (dwarf.look(r - 1, c) == FENCE) //NORTH
  {
    log << dwarf.name() << "-DESTROY\n";
    dwarf.start_chop(NORTH);
  }
}

void Pick(Dwarf &dwarf, Place lookingfor)
{
  int r = dwarf.row();
  int c = dwarf.col();

  if (dwarf.look(r, c + 1) == lookingfor) //EAST
  {
    //log << dwarf.name() <<" applepick\n";
    dwarf.start_pick(EAST);
  }
  else if (dwarf.look(r, c - 1) == lookingfor) //WEST
  {
    //log << dwarf.name() <<"applepick\n";
    dwarf.start_pick(WEST);
  }
  else if (dwarf.look(r + 1, c) == lookingfor) //SOUTH
  {
    //log << dwarf.name() <<"applepick\n";
    dwarf.start_pick(SOUTH);
  }
  else if (dwarf.look(r - 1, c) == lookingfor) //NORTH
  {
    //log << dwarf.name() <<"applepick\n";
    dwarf.start_pick(NORTH);
  }
}

Loc closestThing(Dwarf &dwarf, Place whatIwant)
{
  Loc currentClosest;
  int currentMinDistance = 100000;
  for (int r = 0; r < ROWS; r++)
  {
    for (int c = 0; c < COLS; c++)
    {
      if (dwarf.look(r, c) == whatIwant)
      {
        int dis = abs(r - dwarf.row()) + abs(c - dwarf.col());
        if (dis < currentMinDistance)
        {
          currentClosest.r = r;
          currentClosest.c = c;
          currentMinDistance = dis;
        }
      }
    }
  }
  return currentClosest;
}

void buildIt(Dwarf &dwarf)
{
  if (!atTheTop[dwarf.name()])
  {
    dwarf.start_walk(1, dwarf.name()+4);
    if (dwarf.row() == 1 && dwarf.col() == dwarf.name()+4)
    {
      atTheTop[dwarf.name()] = true;
    }
  }
  else
  {
    if (dwarf.look(dwarf.row() - 1, dwarf.col()) == FENCE)
    {
      dwarf.start_walk(dwarf.row() + 1, dwarf.col());
    }
    else if (dwarf.look(dwarf.row() - 1, dwarf.col()) == EMPTY)
    {
      dwarf.start_build(NORTH);
    }
  }
}

void WalkToEmptySpotNear(Dwarf &dwarf, Loc theSpot)
{
  if (dwarf.look(theSpot.r + 1, theSpot.c) == EMPTY)
  {
    dwarf.start_walk(theSpot.r + 1, theSpot.c);
  }
  else if (dwarf.look(theSpot.r - 1, theSpot.c) == EMPTY)
  {
    dwarf.start_walk(theSpot.r - 1, theSpot.c);
  }
  else if (dwarf.look(theSpot.r, theSpot.c + 1) == EMPTY)
  {
    dwarf.start_walk(theSpot.r, theSpot.c + 1);
  }
  else if (dwarf.look(theSpot.r, theSpot.c - 1) == EMPTY)
  {
    dwarf.start_walk(theSpot.r, theSpot.c - 1);
  }
}

void onAction(Dwarf &dwarf, int day, int hours, int minutes, ostream &log)
{
  int r = dwarf.row();
  int c = dwarf.col();
  bool daytime = (hours >= 6 && hours <= 16);

  if (daytime)
  {
    log << "DAY TIME\n";
    if (isNextTo(dwarf, FENCE) && !startedBuilding){
      DestroyFence(dwarf, log);
      return;
    }
    else if (isNextTo(dwarf, PUMPKIN)){
      Pick(dwarf, PUMPKIN);
      return;
    }
    else if (IsThere(dwarf, PUMPKIN)){
      HalftheDwarvesinTheGrid(dwarf, log, PUMPKIN);
      return;
    }
     else if (day == 7 && dwarf.lumber() > 150)
    {
      buildIt(dwarf);
      startedBuilding = true;
      return;
    }
    else if (day == 6)
    {
      if (isNextTo(dwarf, APPLE_TREE))
      {
        ChopTree(dwarf, log);
        return;
      }
      else if (!isNextTo(dwarf, APPLE_TREE) && IsThere(dwarf, APPLE_TREE))
      {
        Loc closestAppleTree = closestThing(dwarf, APPLE_TREE);
        WalkToEmptySpotNear(dwarf, closestAppleTree);
        return;
      }
    }
    else if (isNextTo(dwarf, PINE_TREE))
    {
      ChopTree(dwarf, log);
      return;
    }

    else if (IsThere(dwarf, PINE_TREE))
    {
      HalftheDwarvesinTheGrid(dwarf, log, PINE_TREE);
      return;
    }
    else if (isNextTo(dwarf, APPLE_TREE))
    {
      Pick(dwarf, APPLE_TREE);
      return;
    }
   
    else if (IsThere(dwarf, APPLE_TREE))
    {
      HalftheDwarvesinTheGrid(dwarf, log, APPLE_TREE);
      return;
    }
  }
  else
  {
    log << "NIGHT TIME\n";
    if(day == 7 )
      BuildAroundDwarf(dwarf,log);
    if(IsThere(dwarf,ZOMBIE)) {
      BuildAroundDwarf(dwarf, log);
    }
    if (!isNextTo(dwarf, APPLE_TREE) && IsThere(dwarf, APPLE_TREE))
    {
      Loc closestAppleTree = closestThing(dwarf, APPLE_TREE);
      WalkToEmptySpotNear(dwarf, closestAppleTree);
      return;
    }
    else
    {
      BuildAroundDwarf(dwarf, log);
      Pick(dwarf, APPLE_TREE);
      return;
    }
  }
}