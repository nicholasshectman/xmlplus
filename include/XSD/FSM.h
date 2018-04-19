// This file is part of XmlPlus package
// 
// Copyright (C)   2010-2013 Satya Prakash Tripathi
//
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE VERSION 3 as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU LESSER GENERAL PUBLIC LICENSE VERSION 3 for more details.
//
// You should have received a copy of the GNU LESSER GENERAL PUBLIC LICENSE VERSION 3
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef __FSM_BASE_H__
#define __FSM_BASE_H__

#include <iostream>
#include <sstream>
#include <map>
#include <list>
#include <vector>

#include "XPlus/AutoPtr.h"
#include "XPlus/XPlusObject.h"

namespace FSM
{

  const int FSM_INIT_STATE=0;
  typedef int (* StateTransAction)(int eventId, void *userData);

  struct Edge : public XPlus::XPlusObject
  {
    int stateId;
    int eventId;
    int nextStateId;

    Edge(int aStateId, int aEventId, int aNextStateId):
      XPlusObject("Edge"),
      stateId(aStateId),
      eventId(aEventId),
      nextStateId(aNextStateId)
    {
    }

    virtual ~Edge() {}
  };

  struct ActionEdge : public Edge
  {
    StateTransAction     preAction;
    StateTransAction     postAction;

    ActionEdge(int aStateId, int aEventId, int aNextStateId, 
        StateTransAction aPreAction=NULL, StateTransAction aPostAction=NULL):
      Edge(aStateId, aEventId, aNextStateId),
      preAction(aPreAction),
      postAction(aPostAction)
    {
    }

    virtual ~ActionEdge() {}
    void print() const {
      cout << "ActionEdge:  stateId= " << stateId
              << " eventId=" << eventId 
              << " nextStateId=" << nextStateId 
              << endl;
    }
  };
  typedef XPlus::AutoPtr<ActionEdge> ActionEdgePtr;
  typedef ActionEdge* ActionEdgeP;


  class FSMBase : public XPlus::XPlusObject 
  {
    public:

    FSMBase():
      XPlusObject("FSMBase")
    {}
    virtual ~FSMBase() {};
    virtual FSMBase* clone() const =0;
    virtual bool processEvent(int eventId)=0; 
    virtual bool isInFinalState()const =0;
    virtual bool isInitFinalState()const =0;
    virtual std::list<int> suggestNextEvents() const =0;
    virtual void print() const =0;
  };
  typedef XPlus::AutoPtr<FSMBase> FSMBasePtr;
  typedef FSMBase* FSMBaseP;


  class GraphFSM : public FSMBase 
  {
  protected:
    int                           _stateId;
    std::vector<int>                   _finalStates;
    std::map<int,std::list<ActionEdge> >    _stateTransMap;

    GraphFSM(const GraphFSM& gfsm):
      _stateId(gfsm.stateId()),
      _finalStates(gfsm.finalStates()),
      _stateTransMap(gfsm.stateTransMap())
    {
    }
    virtual ~GraphFSM() {}
    
    void init(std::vector<ActionEdge>& transitions, std::vector<int>& finalStates) ;
    ActionEdge* getTransitionForEvent(int eventId);

  public:
    inline int stateId() const { return _stateId; }
    inline const std::vector<int>& finalStates() const { return _finalStates; }
    inline const std::map<int,std::list<ActionEdge> >& stateTransMap() const { return _stateTransMap; }

    GraphFSM(std::vector<ActionEdge>& transitions, std::vector<int>& finalStates);
    virtual FSMBase* clone() const;
    virtual bool processEvent(int eventId); 
    virtual bool isInFinalState() const;
    virtual bool isInitFinalState() const;
    virtual std::list<int> suggestNextEvents() const;
    void print() const;
  };


  struct SEAEdge {
    int eventId;
    bool required;
    SEAEdge(int aEventId, bool isRequired=true):
      eventId(aEventId),
      required(isRequired)
    {
    }
    
    virtual ~SEAEdge() {}

    void print() const {
      cout << "SEAEdge:  eventId=" << eventId << " required=" << required << endl;
    }
  };

  // Single-state, Events-All(except optional)
  class SEAFSM : public FSMBase 
  {
  protected:
    // all possible events
    std::vector<SEAEdge>   _eventEdges;

    // eventId to eventReceived(bool) map
    std::map<int,bool>   _eventsReceived;

    bool isEventReceived(int eventId) const;

  public:

    SEAFSM(std::vector<SEAEdge>& eventArray);
    virtual ~SEAFSM() {};
    virtual FSMBase* clone() const;
    virtual bool processEvent(int eventId); 
    virtual bool isInitFinalState() const;
    virtual bool isInFinalState() const;
    virtual std::list<int> suggestNextEvents() const;
    void print() const;
  };

}

#endif

