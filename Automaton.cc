/**
 * @file Automaton.cc
 * @author Pierre Viprey
 * @brief Management of automate
 * @version 1.0
 * @date 2021-12-19
 * 
 */
#include "Automaton.h"

namespace fa {
  /**
   * @brief remove a state from the automate and return the iterator to the following state.
   * 
   * @param state id of the state
   * @return std::optional<std::map<int, State>::iterator> (success)
   * @return std::nullopt (failure)
   */
  std::optional<std::map<int, State>::iterator> Automaton::betterRemoveState(int state){
    std::map<int, State>::iterator position = node.find(state);
    if (position != node.end()){
      auto ptr = node.erase(position);

      for(auto it = transition.begin(); it != transition.end(); ){
        if(it->first == state || it->second.target == state){
          it = transition.erase(it);
        }else{
          ++it;
        }
      }
      return ptr;
    }
    return std::nullopt;
  }

  /**
   * @brief remove a transition from the automate and return the iterator to the following state.
   * 
   * @param from the index of the origin of the transition
   * @param alpha the letter of the transition
   * @param to the index of the arrival of the transition
   * @return std::optional<std::multimap<int, Link>::iterator> (success)
   * @return std::nullopt (failure)
   */
  std::optional<std::multimap<int, Link>::iterator> Automaton::betterRemoveTransition(int from, char alpha, int to){
    auto position = this->transition.equal_range(from);
    for(auto &it = position.first; it != position.second; ){
      if(it->second.letter == alpha && it->second.target == to){
        return transition.erase(it);
      }
      ++it;
    }
    return std::nullopt;
  }

  /**
   * @brief find and return if there are transition by providing the origin and the letter only.
   * 
   * @param from id of the origin state
   * @param alpha letter
   * @return std::optional<std::set<int>> (success)
   * @return std::nullopt (failure)
   */
  std::optional<std::set<int>> Automaton::transitionBeginWith(int from, char alpha) const{
    std::set<int> rtn;
    auto position = this->transition.equal_range(from);
    for(auto i = position.first; i != position.second; i++){
      if(i->first == from && i->second.letter == alpha){
        rtn.insert(i->second.target);
      }
    }
    if(rtn.empty()){
      return std::nullopt;
    }
    return rtn;
  }

  /**
   * @brief research in depth of a final state in the automate.
   * 
   * @param actualNode the current state
   * @param knownNodes the already visited states
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::researchFinalStateInDepth(int actualNode, std::set<int>& knownNodes) const{
    knownNodes.insert(actualNode);
    if(this->isStateFinal(actualNode)){
      return true;
    }
    
    for(auto const &it: this->transition){
      if(it.first == actualNode){
        if(knownNodes.find(it.second.target) == knownNodes.end()){ //knownNodes.contains(it.second.target)
          if(this->researchFinalStateInDepth(it.second.target, knownNodes)){
            return true;
          }
        }
      }
    }
    return false;
  }

  /**
   * @brief list all the states reachable using a research by child.
   * 
   * @param actualNode the current state
   * @param knownNodes the already visited states
   */
  void Automaton::researchInDepth(int actualNode, std::set<int>& knownNodes) const{
    knownNodes.insert(actualNode);
    for(auto const &it: this->transition){
      if(it.first == actualNode){
        if(knownNodes.find(it.second.target) == knownNodes.end()){ //knownNodes.contains(it.second.target)
          this->researchInDepth(it.second.target, knownNodes);
        }
      }
    }
  }

  /**
   * @brief list all the states reachable using a research by parent.
   * 
   * @param actualNode the current state
   * @param knowNodes the already visited states
   */
  void Automaton::researchInSurface(int actualNode, std::set<int>& knowNodes) const{
    knowNodes.insert(actualNode);
    for(auto const &it: this->transition){
      if(it.second.target == actualNode){
        if(knowNodes.find(it.first) == knowNodes.end()){
          this->researchInSurface(it.first, knowNodes);
        }
      }
    }
  }

  /**
   * @brief find the intersection of two alphabets.
   * 
   * @param lhs first alphabet
   * @param rhs second alphabet
   * @return std::set<char> 
   */
  std::set<char> Automaton::createAlphabetProduct(const std::set<char>& lhs, const std::set<char>& rhs){
    std::set<char> product;
    for(auto const &it_lhs : lhs){
      for(auto const &it_rhs : rhs){
        if(it_lhs == it_rhs){
          product.insert(it_lhs);
        }
      }
    }
    return product;
  }

  /**
   * @brief return the lowest number available for a new state.
   * 
   * @return number (success)
   * @return -1 (failure) 
   */
  int Automaton::getNumberForNewNode() const{
    for(int number = 0; number < (int)this->countStates()+1; number++){
      if(!this->hasState(number)){
        return number;
      }
    }
    return -1;
  }
  
  /**
   * @brief return all the nodes that are found after itering through the automate followinf the word
   * The set is empty if there was no route available.
   * 
   * @param actualNode the current node
   * @param word the word to iterate through
   * @return std::set<int> 
   */
  std::set<int> Automaton::getLastNodesOfTheWord(int actualNode, const std::string& word) const{
    std::set<int> rtn;

    if(this->hasEpsilonTransition()){ //if the Automaton has an Epsilon transition inside
      auto position = this->transition.equal_range(actualNode);
      for(auto &it = position.first; it != position.second; it++){
        if(it->second.letter == fa::Epsilon && it->first != it->second.target){
          rtn.merge(this->getLastNodesOfTheWord(it->second.target, word));
        }
      }
    }

    if(word.begin() == word.end()){
      rtn.insert(actualNode);
      return rtn;
    }

    auto targettedNodes = this->transitionBeginWith(actualNode, *word.begin());
    if(targettedNodes.has_value()){
      for(auto const &it: targettedNodes.value()){
        rtn.merge(this->getLastNodesOfTheWord(it, word.substr(1)));
      }
    }
    return rtn;
  }

  /**
   * @brief remove the epsilon transitions from an automaton
   * 
   * @param actualNode the current node
   * @param knowNodes the already visited states
   */
  void Automaton::removeEpsilonTransition(int actualNode, std::set<int>& knownNodes){
    std::set<int> reachable;

    if(knownNodes.find(actualNode) == knownNodes.end()){
      knownNodes.insert(actualNode);

      auto position = transition.equal_range(actualNode);
      for(auto it = position.first; it != position.second; ){
        /* call back the function on every nodes visitable from the actual node */
        this->removeEpsilonTransition(it->second.target, knownNodes);
        
        /* look for an epsilon transition */
        if(it->second.letter == fa::Epsilon){

          /* find every nodes that are the target of the epsilon transition(s) */
          if(it->first != it->second.target){
            reachable.merge(this->getLastNodesOfTheWord(it->second.target, ""));
          }

          /* check if the target is final */
          if(this->isStateFinal(it->second.target)){
            this->setStateFinal(it->first);
          }

          /* remove the epsilon transition */
          it = this->betterRemoveTransition(it->first, it->second.letter, it->second.target).value();
        }else{
          it++;
        }
      }

      /* update the transitions to the nodes targetted by the epsilon transition(s) */
      for(auto const &node : reachable){
        auto position = this->transition.equal_range(node);
        for(auto &it = position.first; it != position.second; it++){
          if(it->second.letter != fa::Epsilon){
            this->addTransition(actualNode, it->second.letter, it->second.target);
          }
        }
      }

    }
  }

  /**
   * @brief Construct a new Automaton:: Automaton object
   * 
   */
  Automaton::Automaton(){
  }

  /**
   * @brief test if the automate is valid.
   * (ie: has at least one state and at least one symbol)
   * 
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::isValid() const {
    return (!alphabet.empty() && !node.empty());
  }

  /**
   * @brief add a symbol to the alphabet.
   * 
   * @param symbol the letter
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::addSymbol(char symbol){
    if(symbol == '\0'){
      return false;
    }
    if(isgraph(symbol)){
      auto rtn = alphabet.insert(symbol);
      return rtn.second;
    }
    return false;
  }

  /**
   * @brief remove a symbol to the alphabet.
   * 
   * @param symbol the letter
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::removeSymbol(char symbol){
    auto position = alphabet.find(symbol);
    if (position != alphabet.end()){
      alphabet.erase(position);

      for(auto it = transition.begin(); it != transition.end(); ){
        if(it->second.letter == symbol){
          it = transition.erase(it);
        }else{
          ++it;
        }
      }
      return true;
    }
    return false;
  }

  /**
   * @brief check if the alphabet contains the given symbol.
   * 
   * @param symbol the letter
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::hasSymbol(char symbol) const {
    return alphabet.find(symbol) != alphabet.end();
  }

  /**
   * @brief returns the number of symbol in the alphabet.
   * 
   * @return std::size_t 
   */
  std::size_t Automaton::countSymbols() const{
    return alphabet.size();
  }

  /**
   * @brief add a state to the automate.
   * 
   * @param state the index of the state
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::addState(int state){
    if(state >= 0){
      auto rtn = node.insert({state,{false, false}});
      return rtn.second;
    }
    return false;
  }

  /**
   * @brief remove a state of the automate.
   * 
   * @param state the index of the state
   * @return true 
   * @return false 
   */
  bool Automaton::removeState(int state){
    return betterRemoveState(state).has_value();
  }

  /**
   * @brief check if the automate contains the given state.
   * 
   * @param state the index of the state
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::hasState(int state) const{
    return node.find(state) != node.end();
  }

  /**
   * @brief returns the number of states in the automate.
   * 
   * @return std::size_t 
   */
  std::size_t Automaton::countStates() const{
    return node.size();
  }

  /**
   * @brief set the state as initial.
   * 
   * @param state the index of the state
   */
  void Automaton::setStateInitial(int state){
    auto position = node.find(state);
    if(position != node.end()){
      position->second.initial=true;
    }
  }

  /**
   * @brief check if the state is initial.
   * 
   * @param state the index of the state
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::isStateInitial(int state) const{
    auto position = node.find(state);
    if(position != node.end()){
      return position->second.initial;
    }
    return false;
  }

  /**
   * @brief set the state as final.
   * 
   * @param state the index of the state
   */
  void Automaton::setStateFinal(int state){
    auto position = node.find(state);
    if(position != node.end()){
      position->second.final=true;
    }    
  }

  /**
   * @brief check if the state is final.
   * 
   * @param state the index of the state
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::isStateFinal(int state) const{
    auto position = node.find(state);
    if(position != node.end()){
      return position->second.final;
    }
    return false;
  }

  /**
   * @brief add a transition to the automate.
   * 
   * @param from the index of the origin of the transition
   * @param alpha the letter of the transition
   * @param to the index of the arrival of the transition
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::addTransition(int from, char alpha, int to){
    if(from<0 || to<0 || (!isgraph(alpha) && alpha!=fa::Epsilon)){
      return false;
    }
    if(!hasState(from) || !hasState(to)){
      return false;
    }
    if(!hasSymbol(alpha) && alpha!=fa::Epsilon){
      return false;
    }

    if(hasTransition(from, alpha, to)){
      return false;
    }

    transition.insert({from,{alpha, to}});
    return true;
  }

  /**
   * @brief remove a transition of the automate.
   * 
   * @param from the index of the origin of the transition
   * @param alpha the letter of the transition
   * @param to the index of the arrival of the transition
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::removeTransition(int from, char alpha, int to){
    return betterRemoveTransition(from, alpha, to).has_value();
  }

  /**
   * @brief check if the automate has the given transition.
   * 
   * @param from the index of the origin of the transition
   * @param alpha the letter of the transition
   * @param to the index of the arrival of the transition
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::hasTransition(int from, char alpha, int to) const{
    auto position = this->transition.equal_range(from);
    for(auto &it = position.first; it != position.second; it++){
      if(it->first == from && it->second.letter == alpha && it->second.target == to){
        return true;
      }
    }
    return false;
  }
  
  /**
   * @brief returns the number of transition in the automate
   * 
   * @return std::size_t 
   */
  std::size_t Automaton::countTransitions() const{
    return transition.size();
  }

  /**
   * @brief print the automate.
   * 
   * @param os the stream to input the automate
   */
  void Automaton::prettyPrint(std::ostream& os) const{
    /*  print of initial state(s) */
    os << "Initial states:" << std::endl;
    bool init=false;
    for(auto const &it : node){
      if(isStateInitial(it.first)){
        if(!init){
          os << "\t" << it.first;
          init=true;
        }else{
          os << "  " << it.first;
        }
      }
    }
    os << std::endl;


    /*  print of final state(s) */
    os << "Final states:" << std::endl;
    bool final=false;
    for(auto const &it : node){
      if(isStateFinal(it.first)){
        if(!final){
          os << "\t" << it.first;
          final=true;
        }else{
          os << "  " << it.first;
        }
      }
    }
    os << "\n" << std::endl;


    /*  print of transition(s) */
    os << "Transition:" << std::endl;
    std::set<int> nodeUsed;
    bool first = true;
    for(auto const &transi : transition){
      std::set<int>::iterator it = nodeUsed.find(transi.first);
      if(it == nodeUsed.end()){
        nodeUsed.insert(transi.first);
        if(!first){
          os << std::endl;
        }
        os << "\tFor state " << transi.first << ":" << std::endl;

        auto letter = this->transition.equal_range(transi.first);
        for(auto c = letter.first; c != letter.second; c++){
          os << "\t\t" << "--" << c->second.letter << "--> " << c->second.target << std::endl;
        }
        first = false;
      }
    }
  }

  // TODO void Automaton::dotPrint(std::ostream& os) const{}

  /**
   * @brief check if there are any transition with an epsilon.
   * 
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::hasEpsilonTransition() const{
    assert(isValid());

    for(auto it = transition.begin(); it != transition.end(); it++){
      if(it->second.letter == fa::Epsilon){
        return true;
      }
    }    

    return false;
  }

  /**
   * @brief check if the automate is deterministic.
   * (ie: every state has a set composed of unique transition for a given symbol)
   * 
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::isDeterministic() const{
    assert(isValid());
    
    /* if there are Epsilon transition */
    if(this->hasEpsilonTransition()){
      return false;
    }

    /* if there are multiple Initial state */
    bool oneInitial = false;
    for(auto const &it : node){
      if(this->isStateInitial(it.first)){
        if(!oneInitial){
          oneInitial = true;
        }else{
          return false;
        }
      }
    }
    if(!oneInitial){
      return false;
    }

    /* if there are multiple transition with the same origin and letter */
    for(auto const &it : transition){
      auto rtn = this->transitionBeginWith(it.first, it.second.letter);
      if(rtn.value().size() > 1){
        return false;
      }
    }

    return true;
  }

  /**
   * @brief check if the automate is complete.
   * (ie: every state has at least one transition of every symbol in the alphabet)
   * 
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::isComplete() const{
    assert(isValid());

    /* store everytime we find a new pair of 'origin, letter' */
    std::set<std::pair<int, char>> complete;
    for(auto const &it : transition){
      complete.insert(std::make_pair(it.first, it.second.letter));
    }

    /* test if we have every possibility of 'origin, letter' */
    return complete.size() == node.size()*alphabet.size();
  }

  /**
   * @brief create a complete automate from a given automate
   * 
   * @param automaton the automate
   * @return Automaton 
   */
  Automaton Automaton::createComplete(const Automaton& automaton){
    assert(automaton.isValid());

    if(automaton.isComplete()){
      return automaton;
    }

    /* create a new automaton and add a sink state */
    fa::Automaton new_automaton = automaton;
    bool sink_used = false;
    int sink = new_automaton.getNumberForNewNode();
    new_automaton.addState(sink);

    /*
     * iterate throught the nodes and create a transition
     * with the letter missing to the sink state          
     */
    for(auto const &it : new_automaton.node){
      for(auto const &symbol : new_automaton.alphabet){
        if(!new_automaton.transitionBeginWith(it.first, symbol).has_value()){
          std::set<int> knownNodes;
          if(!new_automaton.researchFinalStateInDepth(it.first, knownNodes)){
            new_automaton.addTransition(it.first, symbol, it.first);
          }else{
            sink_used = true;
            new_automaton.addTransition(it.first, symbol, sink);
          }
        }
      }
    }

    if(!sink_used){
      new_automaton.removeState(sink);
    }
    return new_automaton;
  }

  /**
   * @brief create the complement of the automate
   * 
   * @param automaton the automate
   * @return Automaton 
   */
  Automaton Automaton::createComplement(const Automaton& automaton){
    assert(automaton.isValid());

    /* create a deterministic finite automaton (DFA) of the original automaton */
    fa::Automaton deterministic = fa::Automaton::createDeterministic(automaton);
    fa::Automaton dfa = fa::Automaton::createComplete(deterministic);

    /* create the complement of DFA and initialize the alphabet */
    fa::Automaton complement;
    complement.alphabet = dfa.alphabet;

    /* initialize the nodes*/
    for(auto &it : dfa.node){
      complement.addState(it.first);
      if(dfa.isStateInitial(it.first)){
        complement.setStateInitial(it.first);
      }
      if(!dfa.isStateFinal(it.first)){
        complement.setStateFinal(it.first);
      }
    }
    
    /*initialize the transitions */
    complement.transition = dfa.transition;

    return complement;
  }

  /**
   * @brief create a mirror automaton from a given automate
   * 
   * @param automaton the automate
   * @return Automaton 
   */
  Automaton Automaton::createMirror(const Automaton& automaton){
    assert(automaton.isValid());

    /* create the mirror of the automaton and initialize the alphabet */
    fa::Automaton mirror;
    mirror.alphabet = automaton.alphabet;

    /* initialize the nodes */
    for(auto const &it : automaton.node){
      mirror.addState(it.first);
      if(automaton.isStateInitial(it.first)){
        mirror.setStateFinal(it.first);
      }
      if(automaton.isStateFinal(it.first)){
        mirror.setStateInitial(it.first);
      }
    }

    /* initialize the transitions */
    for(auto const &it : automaton.transition){
      mirror.addTransition(it.second.target, it.second.letter, it.first);
    }

    return mirror;
  }

  /**
   * @brief check if the automate only recognize the empty language
   * (ie: you can't create any word)
   * 
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::isLanguageEmpty() const{
    assert(this->isValid());

    /* test if we have at least one final and one initial node */
    bool hasFinal = false;
    bool hasInitial = false;
    for(auto const &it : node){
      if(isStateFinal(it.first)){
        hasFinal = true;
      }
      if(isStateInitial(it.first)){
        hasInitial = true;
      }
    }
    if(hasInitial==false || hasFinal==false){
      return true;
    }

    /* search if we can reach a final state from an initial node */
    std::set<int> knownNodes;
    for(auto const &it : node){
      if(this->isStateInitial(it.first)){
        if(this->researchFinalStateInDepth(it.first, knownNodes)){
          return false;
        }
      }
    }
    return true;
  }

  /**
   * @brief remove the non accessible states from an automate
   * 
   */
  void Automaton::removeNonAccessibleStates(){
    assert(this->isValid());

    /* store every nodes reachable from a initial node */
    std::set<int> knownNodes;
    for(auto const &it : node){
      if(this->isStateInitial(it.first)){
        this->researchInDepth(it.first, knownNodes);
      }
    }

    /* remove every nodes (and their transitions) that weren't stored before */
    for(auto it = node.begin(); it != node.end(); ){
      if(knownNodes.find(it->first) == knownNodes.end()){
        it = betterRemoveState(it->first).value();
      }else{
        ++it;
      }
    }

    /* make the automaton valid if needed */
    if(!this->isValid()){
      this->addState(42);
      this->setStateInitial(42);
      this->addSymbol('q');
    }
  }

  /**
   * @brief remove the non co-accessible states from an automate
   * 
   */
  void Automaton::removeNonCoAccessibleStates(){
    assert(this->isValid());

    /* store every nodes that can reach a final node */
    std::set<int> knownNodes;
    for(auto const &it : node){
      if(this->isStateFinal(it.first)){
        this->researchInSurface(it.first, knownNodes);
      }
    }

    /* remove every nodes (and their transitions) that weren't stored before */
    for(auto it = node.begin(); it != node.end(); ){
      if(knownNodes.find(it->first) == knownNodes.end()){
        it = betterRemoveState(it->first).value();
      }else{
        ++it;
      }
    }

    /* make the automaton valid if needed */
    if(!this->isValid()){
      this->addState(42);
      this->setStateInitial(42);
      this->addSymbol('q');
    }
  }

  /**
   * @brief create the synchronise product of two automates
   * 
   * @param lhs the first automate
   * @param rhs the second automate
   * @return Automaton 
   */
  Automaton Automaton::createProduct(const Automaton& lhs, const Automaton& rhs){
    assert(lhs.isValid());
    assert(rhs.isValid());

    /* create the product of the automaton and initialize the alphabet */
    fa::Automaton product;
    product.alphabet = fa::Automaton::createAlphabetProduct(lhs.alphabet, rhs.alphabet);
    
    /* initialize the nodes */
    std::map<std::pair<int, int>, int> nodes;
    int n=0;
    for(auto const &it_lhs : lhs.node){
      if(lhs.isStateInitial(it_lhs.first)){
        for(auto const &it_rhs : rhs.node){
          if(rhs.isStateInitial(it_rhs.first)){
            nodes[std::make_pair(it_lhs.first, it_rhs.first)] = n;
            product.addState(n);
            product.setStateInitial(n);
            if(lhs.isStateFinal(it_lhs.first) && rhs.isStateFinal(it_rhs.first)){
              product.setStateFinal(n);
            }
            n++;
          }
        }
      }
    }

    /* initialize the transitions */
    for(auto const &it : nodes){
      for(auto const &letter : product.alphabet){
        auto rtn_lhs=lhs.transitionBeginWith(it.first.first, letter);
        auto rtn_rhs=rhs.transitionBeginWith(it.first.second, letter);

        if(rtn_lhs.has_value() && rtn_rhs.has_value()){
          for(int node_lhs : rtn_lhs.value()){
            for(int node_rhs : rtn_rhs.value()){
              auto key = nodes.find(std::pair<int, int>(node_lhs, node_rhs));
              if(key == nodes.end()){    //si le noeud n'existe pas, on l'ajoute et on lui assigne un id
                nodes[std::make_pair(node_lhs, node_rhs)] = n;
                product.addState(n);
                product.addTransition(it.second, letter, n);
                if(lhs.isStateFinal(node_lhs) && rhs.isStateFinal(node_rhs)){
                  product.setStateFinal(n);
                }
                n++;
              }else{    //sinon on récupère son id
                product.addTransition(it.second, letter, key->second);
              }
            }
          }
        }
      }
    }

    /* make the automaton valid if needed */
    if(!product.isValid()){
      if(product.countStates() == 0){
        fa::Automaton new_product;
        product=new_product;
        product.addState(42);
        product.setStateInitial(42);
      }
      if(product.countSymbols() == 0){
        product.addSymbol('z');
      }
    }

    return product;
  }

  /**
   * @brief check if the intersection of two automates is empty
   * 
   * @param other the second automate
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::hasEmptyIntersectionWith(const Automaton& other) const{
    assert(this->isValid());
    assert(other.isValid());

    fa::Automaton fa = createProduct(*(this), other);
    return fa.isLanguageEmpty();
  }

  /**
   * @brief navigate through the automate to read the word
   * 
   * @param word the word to pass
   * @return std::set<int> the last node after iterring through the automate
   */
  std::set<int> Automaton::readString(const std::string& word) const{
    assert(this->isValid());

    std::set<int> rtn;
    for(auto const &it : this->node){
      if(this->isStateInitial(it.first)){
        rtn.merge(this->getLastNodesOfTheWord(it.first, word));
      }
    }

    return rtn;
  }

  /**
   * @brief check if the word is in the language of the automate
   * 
   * @param word the word to pass
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::match(const std::string& word) const{
    std::set<int> nodes = readString(word);

    for(auto node : nodes){
      if(this->isStateFinal(node)){
        return true;
      }
    }

    return false;
  }

  /**
   * @brief create the deterministic version of the automate
   * 
   * @param automaton the automate
   * @return Automaton 
   */
  Automaton Automaton::createDeterministic(const Automaton& automaton){
    assert(automaton.isValid());

    if(automaton.isDeterministic()){
      return automaton;
    }
    /* create the deterministic version of the automaton and initialize the alphabet */
    fa::Automaton deterministic;
    deterministic.alphabet = automaton.alphabet;

    /* initialize the initial nodes */
    std::map<int, std::set<int>> nodes;
    bool isFinal = false;
    int n = 0;
    std::set<int> initial;
    for(auto const &it : automaton.node){
      if(automaton.isStateInitial(it.first)){
        initial.insert(it.first);
        if(!isFinal && automaton.isStateFinal(it.first)){
          isFinal = true;
        }
      }
    }
    nodes[n] = initial;
    deterministic.addState(n);
    if(isFinal){
      deterministic.setStateFinal(n);
    }
    deterministic.setStateInitial(n++);

    /* initialize the nodes */
    for(auto &it : nodes){
      for(char letter : deterministic.alphabet){
        std::set<int> new_nodes;
        isFinal = false;
        for(auto &node : it.second){
          /* store the older nodes that are the target of the given transition */
          auto target = automaton.transitionBeginWith(node, letter);
          if(target.has_value()){
            new_nodes.merge(target.value());
          }
        }

        if(new_nodes.size() > 0){
          std::map<int, std::set<int>>::iterator key;
          /* find the key matching all the older nodes*/
          for(key = nodes.begin(); key != nodes.end(); ++key){
            if (key->second == new_nodes){
              break;
            }
          }

          /* initialize the transitions */
          if(key != nodes.end()){     //if the key exist create a transition toward the node associated
            deterministic.addTransition(it.first, letter, key->first);
          }else{      //if the key doesn't exist create the node, the transition and find if it is final
            nodes[n] = new_nodes;
            deterministic.addState(n);
            for(auto finalNode = new_nodes.begin(); !isFinal && finalNode != new_nodes.end(); finalNode++){
              if(automaton.isStateFinal(*finalNode)){
                deterministic.setStateFinal(n);
              }
            }
            deterministic.addTransition(it.first, letter, n++);
          }
        }
      }
    }

    /* make the automaton valid if needed */
    if(!deterministic.isValid()){
      fa::Automaton new_deterministic;
      deterministic=new_deterministic;
      deterministic.addState(42);
      deterministic.setStateInitial(42);
      deterministic.addSymbol('q');
    }

    return deterministic;
  }

  /**
   * @brief check if the language of an automate is include in another one.
   * 
   * @param other the other automate
   * @return true (success)
   * @return false (failure)
   */
  bool Automaton::isIncludedIn(const Automaton& other) const{
    assert(this->isValid());
    assert(other.isValid());

    fa::Automaton _other = other;
    if(this->alphabet != other.alphabet){
      for(auto const letter : this->alphabet){
        if(!_other.hasSymbol(letter)){
          _other.addSymbol(letter);
        }
      }
    }

    return this->hasEmptyIntersectionWith(fa::Automaton::createComplement(_other));
  }

  /**
   * @brief create the minimal version of the automate using the Moore algorithm
   * 
   * @param automaton the automate
   * @return Automaton 
   */
  Automaton Automaton::createMinimalMoore(const Automaton& automaton){
    assert(automaton.isValid());

    /* create a deterministic finite automaton (DFA) of the original automaton */
    fa::Automaton deterministic = fa::Automaton::createDeterministic(automaton);
    fa::Automaton dfa = fa::Automaton::createComplete(deterministic);
    dfa.removeNonAccessibleStates();

    /* create the minimal of DFA and initialize the alphabet */
    fa::Automaton minimal;
    minimal.alphabet = dfa.alphabet;

    /* initialize the nodes*/
    std::map<int, int> moore, mooreBis; //array to store the number of an original node with a new node
    for(auto from : dfa.node){
      if(dfa.isStateFinal(from.first)){
        moore[from.first] = 2;  //final nodes
      }else{
        moore[from.first] = 1;  //other nodes
      }
    }


    //<new node, <<letter, new node target>*, result node>
    std::map<std::pair<int, std::vector<std::pair<char, int>>>, int> transitions;
    do{
      int n=1;
      transitions.clear();
      mooreBis = moore;

      for(auto from : dfa.node){
        /* store the transitions for a given node */
        std::pair<int, std::vector<std::pair<char, int>>> key;
        key.first = mooreBis[from.first];
        auto rtn = dfa.transition.equal_range(from.first);
        for(auto const letter : dfa.alphabet){
          for(auto it = rtn.first; it != rtn.second; it++){
            if(it->second.letter == letter){
              key.second.push_back(std::make_pair(letter, mooreBis[it->second.target]));
            }
          }
        }

        std::map<std::pair<int, std::vector<std::pair<char, int>>>, int>::iterator it;
        /* find the iterator matching the key */
        for(it = transitions.begin(); it != transitions.end(); it++){
          if(it->first == key){
            break;
          }
        }

        if(it != transitions.end()){      //if the iterator exist set to the node associated
          moore[from.first] = it->second;
        }else{      //if the iterator doesn't exist create the transition and update the node associated
          transitions[key] = n;
          moore[from.first] = n++;
        }
      }
    }while(mooreBis != moore);

    /* set the nodes*/
    for(auto const node : moore){
      minimal.addState(node.second);
      if(dfa.isStateInitial(node.first)){
        minimal.setStateInitial(node.second);
      }

      if(dfa.isStateFinal(node.first)){
        minimal.setStateFinal(node.second);
      }
    }

    /*set the transitions */
    for(auto const trans : transitions){
      for(auto const target : trans.first.second){
        minimal.addTransition(trans.first.first, target.first, target.second);
      }
    }

    return minimal;
  }

  /**
   * @brief create the minimal version of the automate using the Brzozowski algorithm
   * 
   * @param automaton the automate
   * @return Automaton 
   */
  Automaton Automaton::createMinimalBrzozowski(const Automaton& automaton){
    assert(automaton.isValid());

    fa::Automaton mirrored = fa::Automaton::createMirror(automaton);
    fa::Automaton deterministicMirror = fa::Automaton::createDeterministic(mirrored);

    fa::Automaton mirroredbis = fa::Automaton::createMirror(deterministicMirror);
    fa::Automaton minimal = fa::Automaton::createDeterministic(mirroredbis);
    
    return fa::Automaton::createComplete(minimal);
  }
  


  /**
   * @brief remove the epsilon transitions of the automate
   * 
   * @param automaton the automate
   * @return Automaton 
   */
  Automaton Automaton::createWithoutEpsilon(const Automaton& automaton){
    assert(automaton.isValid());

    /* create the automaton without epsilon*/
    fa::Automaton automaton_no_epsilon = automaton;
    std::set<int> knownNodes;

    if(automaton_no_epsilon.hasEpsilonTransition()){
      for(const auto &initial : automaton_no_epsilon.node){
        if(automaton_no_epsilon.isStateInitial(initial.first)){
          automaton_no_epsilon.removeEpsilonTransition(initial.first, knownNodes);
        }
      }
    }

    return automaton_no_epsilon;
  }
}