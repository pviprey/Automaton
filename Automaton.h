#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <cstddef>
#include <iosfwd>
#include <set>
#include <string>


#include <map>            // needed for the good working of std::map & std::multimap
#include <vector>         // needed for the good working of std::vector

#include <algorithm>      // std::find
#include <iostream>       // std::cout

#include <cassert>        // assert
#include <optional>       // optional
#include <climits>  // INT_MAX

namespace fa {
  constexpr char Epsilon = '\0';

  struct State{
    bool initial, final;
  };

  struct Link{
    char letter;
    int target;
  };

  class Automaton {
  public:
    /**
     * Build an empty automaton (no state, no transition).
     */
    Automaton();

    /**
     * Tell if an automaton is valid.
     *
     * A valid automaton has a non-empty set of states and a non-empty set of symbols
     */
    bool isValid() const;

    /**
     * Add a symbol to the automaton
     *
     * Epsilon is not a valid symbol.
     * Returns true if the symbol was effectively added
     */
    bool addSymbol(char symbol);

    /**
     * Remove a symbol from the automaton
     *
     * Returns true if the symbol was effectively removed
     */
    bool removeSymbol(char symbol);

    /**
     * Tell if the symbol is present in the automaton
     */
    bool hasSymbol(char symbol) const;

    /**
     * Count the number of symbols
     */
    std::size_t countSymbols() const;

    /**
     * Add a state to the automaton.
     *
     * By default, a newly added state is not initial and not final.
     * Returns true if the state was effectively added and false otherwise.
     */
    bool addState(int state);

    /**
     * Remove a state from the automaton.
     *
     * The transitions involving the state are also removed.
     * Returns true if the state was effectively removed and false otherwise.
     */
    bool removeState(int state);

    /**
     * Tell if the state is present in the automaton.
     */
    bool hasState(int state) const;

    /**
     * Compute the number of states.
     */
    std::size_t countStates() const;

    /**
     * Set the state initial.
     */
    void setStateInitial(int state);

    /**
     * Tell if the state is initial.
     */
    bool isStateInitial(int state) const;

    /**
     * Set the state final.
     */
    void setStateFinal(int state);

    /**
     * Tell if the state is final.
     */
    bool isStateFinal(int state) const;

    /**
     * Add a transition
     *
     * Returns true if the transition was effectively added and false otherwise.
     * If one of the state or the symbol does not exists, the transition is not added.
     */
    bool addTransition(int from, char alpha, int to);

    /**
     * Remove a transition
     *
     * Returns true if the transition was effectively removed and false otherwise.
     */
    bool removeTransition(int from, char alpha, int to);

    /**
     * Tell if a transition is present.
     */
    bool hasTransition(int from, char alpha, int to) const;

    /**
     * Compute the number of transitions.
     */
    std::size_t countTransitions() const;

    /**
     * Print the automaton in a friendly way
     */
    void prettyPrint(std::ostream& os) const;

    /**
     * Print the automaton with respect to the DOT specification
     */
    // void dotPrint(std::ostream& os) const;

    /**
     * Tell if the automaton has one or more epsilon-transition
     */
    bool hasEpsilonTransition() const;

    /**
     * Tell if the automaton is deterministic
     */
    bool isDeterministic() const;

    /**
     * Tell if the automaton is complete
     */
    bool isComplete() const;

    /**
     * Remove non-accessible states
     */
    void removeNonAccessibleStates();

    /**
     * Remove non-co-accessible states
     */
    void removeNonCoAccessibleStates();

    /**
     * Check if the language of the automaton is empty
     */
    bool isLanguageEmpty() const;

    /**
     * Tell if the intersection with another automaton is empty
     */
    bool hasEmptyIntersectionWith(const Automaton& other) const;

    /**
     * Read the string and compute the state set after traversing the automaton
     */
    std::set<int> readString(const std::string& word) const;

    /**
     * Tell if the word is in the language accepted by the automaton
     */
    bool match(const std::string& word) const;

    /**
     * Tell if the langage accepted by the automaton is included in the
     * language accepted by the other automaton
     */
    bool isIncludedIn(const Automaton& other) const;

    /**
     * Create a mirror automaton
     */
    static Automaton createMirror(const Automaton& automaton);

    /**
     * Create a complete automaton, if not already complete
     */
    static Automaton createComplete(const Automaton& automaton);

    /**
     * Create a complement automaton
     */
    static Automaton createComplement(const Automaton& automaton);

    /**
     * Create the product of two automata
     *
     * The product of two automata accept the intersection of the two languages.
     */
    static Automaton createProduct(const Automaton& lhs, const Automaton& rhs);

    /**
     * Create a deterministic automaton, if not already deterministic
     */
    static Automaton createDeterministic(const Automaton& other);

    /**
     * Create an equivalent minimal automaton with the Moore algorithm
     */
    static Automaton createMinimalMoore(const Automaton& other);

    /**
     * Create an equivalent minimal automaton with the Brzozowski algorithm
     */
    static Automaton createMinimalBrzozowski(const Automaton& other);

    /**
     * Create an equivalent automaton with the epsilon transition removed
     */
    static Automaton createWithoutEpsilon(const Automaton& automaton);
  
  private:
    /**
     * The structure of our automaton
     */
    std::set<char> alphabet;
    std::map<int, State> node;
    std::multimap<int, Link> transition;

    /**
     * A better removeState that allows iteration (consider using it over removeState)
     */
    std::optional<std::map<int, State>::iterator> betterRemoveState(int state);
    
    /**
     * A better removeTransition that allows iteration (consider using it over removeTransition)
     */
    std::optional<std::multimap<int, Link>::iterator> betterRemoveTransition(int from, char alpha, int to);
    
    /**
     * Find all the nodes targetted by a specific transition from a specific node
     */
    std::optional<std::set<int>> transitionBeginWith(int from, char alpha) const;

    /**
     * Check if there is any Final State reachable from the node
     */
    bool researchFinalStateInDepth(int actualNode, std::set<int>& knownNodes) const;
    
    /**
     * Store every node reachable from the node
     */    
    void researchInDepth(int actualNode, std::set<int>& knownNodes) const;
 
     /**
     * Store every node that can reach the node
     */
    void researchInSurface(int actualNode, std::set<int>& knownNodes) const;

    /**
     * Create the product of two alphabets
     */
    static std::set<char> createAlphabetProduct(const std::set<char>& lhs, const std::set<char>& rhs);

    /**
     * Find the lowest number available for a new node
     */
    int getNumberForNewNode() const;

    /**
     * Find the last node when itering with a word
     */
    std::set<int> getLastNodesOfTheWord(int actualNode, const std::string& word) const;
    
    /**
     * Remove the Epsilon Transition from an automaton
     */
    void removeEpsilonTransition(int actualNode, std::set<int>& knownNodes);
  };
}

#endif // AUTOMATON_H
