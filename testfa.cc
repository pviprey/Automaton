#include "gtest/gtest.h"
#include "Automaton.h"


/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Those tests exist in order to verify the good implementation of the symbols *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

TEST(SYMBOL, Empty){
  fa::Automaton fa;
  EXPECT_FALSE(fa.isValid());
}

TEST(SYMBOL, AddEpsilon){
  fa::Automaton fa;
  EXPECT_FALSE(fa.addSymbol(fa::Epsilon));
  EXPECT_FALSE(fa.isValid());
}

TEST(SYMBOL, AddSymbol){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_FALSE(fa.isValid());
}

TEST(SYMBOL, AddExistingSymbol){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_FALSE(fa.addSymbol('a'));
  EXPECT_FALSE(fa.isValid());  
}

TEST(SYMBOL, RemoveSymbol){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.removeSymbol('a'));
  EXPECT_FALSE(fa.hasSymbol('a'));
  EXPECT_FALSE(fa.isValid());  
}

TEST(SYMBOL, RemoveUnknownSymbol){
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasSymbol('a'));
  EXPECT_FALSE(fa.removeSymbol('a'));
  EXPECT_FALSE(fa.hasSymbol('a'));
  EXPECT_FALSE(fa.isValid());
}

TEST(SYMBOL, AlreadyRemovedSymbol){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.removeSymbol('a'));
  EXPECT_FALSE(fa.removeSymbol('a'));
  EXPECT_FALSE(fa.hasSymbol('a'));
  EXPECT_FALSE(fa.isValid());
}

TEST(SYMBOL, HasSymbol){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_FALSE(fa.isValid());
}

TEST(SYMBOL, UnknownSymbol){
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasSymbol('a'));
  EXPECT_FALSE(fa.isValid());
}

TEST(SYMBOL, NotListedSymbol){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_FALSE(fa.hasSymbol('A'));
  EXPECT_FALSE(fa.isValid());  
}

TEST(SYMBOL, SizeEmpty){
  fa::Automaton fa;
  EXPECT_EQ(fa.countSymbols(),0u);  
}

TEST(SYMBOL, SizeRandom){
  fa::Automaton fa;
  srand (time(NULL));
  std::size_t random=rand()%10;
  for(std::size_t i=0; i<random; i++){
    char c='a'+i;
    EXPECT_TRUE(fa.addSymbol(c));
  }
  EXPECT_EQ(fa.countSymbols(),random);  
}


/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Those tests exist in order to verify the good implementation of the states  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

TEST(STATE, AddState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_FALSE(fa.isValid());  
}

TEST(STATE, AddRepetitiveState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_FALSE(fa.addState(0));
  EXPECT_FALSE(fa.isValid());  
}

TEST(STATE, AddNegativeState){
  fa::Automaton fa;
  EXPECT_FALSE(fa.addState(-1));
}

TEST(STATE, RemoveState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.removeState(0));
  EXPECT_FALSE(fa.hasState(0));
  EXPECT_FALSE(fa.isValid());   
}

TEST(STATE, RemoveUnknownState){
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeState(0));
  EXPECT_FALSE(fa.hasState(0));
  EXPECT_FALSE(fa.isValid()); 
}

TEST(STATE, HasState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.hasState(0));
  EXPECT_FALSE(fa.isValid());  
}

TEST(STATE, HasUnknownState){
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasState(0));
  EXPECT_FALSE(fa.isValid());
}

TEST(STATE, HasAnotherState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_FALSE(fa.hasState(1));
  EXPECT_FALSE(fa.isValid());
}

TEST(STATE, SizeZero){
  fa::Automaton fa;
  EXPECT_EQ(fa.countStates(), 0u);
}

TEST(STATE, SizeRandom){
  fa::Automaton fa;
  srand(time(NULL));
  std::size_t random=rand()%10;
  for(std::size_t i=0; i<random; i++){
    EXPECT_TRUE(fa.addState(i));
  }
  EXPECT_EQ(fa.countStates(),random);  
}

TEST(STATE, InitialState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));  
}

TEST(STATE, FinalState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));
}

TEST(STATE, NoInitialState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_FALSE(fa.isStateInitial(0));
}

TEST(STATE, NoFinalState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_FALSE(fa.isStateFinal(0));  
}


/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Those tests exist in order to verify the good implementation of the transitions *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

TEST(TRANSITION, AddEpsilonTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addTransition(0, fa::Epsilon, 0));
}

TEST(TRANSITION, AddTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
}

TEST(TRANSITION, AddRepetitiveTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_FALSE(fa.addTransition(0, 'a', 0));
}

TEST(TRANSITION, RemoveTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));  
  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.removeTransition(0, 'a', 0));
  EXPECT_FALSE(fa.hasTransition(0, 'a', 0));  
}

TEST(TRANSITION, RemoveStateWithTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));  
  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(1, 'b', 1));
  EXPECT_TRUE(fa.removeState(1));
  EXPECT_FALSE(fa.hasTransition(1, 'b', 1));
  EXPECT_FALSE(fa.hasTransition(0, 'a', 1));
}

TEST(TRANSITION, RemoveSymbolWithTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));  
  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'b', 1));
  EXPECT_TRUE(fa.removeSymbol('b'));
  EXPECT_FALSE(fa.hasTransition(1, 'b', 1));    
}

TEST(TRANSITION, RemoveUnknownTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_FALSE(fa.removeTransition(0, 'a', 0));
  EXPECT_FALSE(fa.hasTransition(0, 'a', 0));  
}

TEST(TRANSITION, RemoveTwiceTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.removeTransition(0, 'a', 0));  
  EXPECT_FALSE(fa.removeTransition(0, 'a', 0));  
}

TEST(TRANSITION, HasTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addState(0));  
  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.hasTransition(0, 'a', 0));  
}

TEST(TRANSITION, HasUnknownTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addState(0));  
  EXPECT_FALSE(fa.hasTransition(0, 'a', 0));  
}

TEST(TRANSITION, HasOtherTransitions){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_FALSE(fa.hasTransition(1, 'a', 1));
}

TEST(TRANSITION, SizeZero){
  fa::Automaton fa;
  EXPECT_EQ(fa.countTransitions(),0u);  
}

TEST(TRANSITION, SizeRandom){
  fa::Automaton fa;
  srand (time(NULL));
  std::size_t random=rand()%10;
  for(std::size_t i=0; i<random; i++){
    char c='a'+i;
    EXPECT_TRUE(fa.addSymbol(c));
    EXPECT_TRUE(fa.addState(i));
    EXPECT_TRUE(fa.addTransition(i, c, i));
  }
  EXPECT_EQ(fa.countTransitions(),random);  
}


/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Those tests exist in order to verify the good implementation of the prints  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

TEST(PRINT, PrettyPrint){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));  
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'a', 2));
  EXPECT_TRUE(fa.addTransition(0, 'a', 3));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 3));
  EXPECT_TRUE(fa.addTransition(2, 'b', 4));
  EXPECT_TRUE(fa.addTransition(3, 'a', 3));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  EXPECT_TRUE(fa.addTransition(4, 'a', 4));  

  /*std::ofstream file("test.txt");
  fa.prettyPrint(&file);*/
  fa.prettyPrint(std::cout);
}


/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Those tests exist in order to verify the good implementation of the property  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

TEST(PROPERTY, HasEpsilonTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));

  EXPECT_TRUE(fa.addState(0));
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.addState(1));
  fa.setStateFinal(0);

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, fa::Epsilon, 1));

  EXPECT_TRUE(fa.hasEpsilonTransition());
}

TEST(PROPERTY, HasNoEpsilonTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));

  EXPECT_TRUE(fa.addState(0));
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.addState(1));
  fa.setStateFinal(0);

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));

  EXPECT_FALSE(fa.hasEpsilonTransition());
}

TEST(PROPERTY, IsNotDeterministicNoInitial){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 0));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));

  EXPECT_FALSE(fa.isDeterministic());
}

TEST(PROPERTY, IsNotDeterministicMultipleInitials){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 0));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));

  EXPECT_FALSE(fa.isDeterministic());
}

TEST(PROPERTY, IsNotDeterministicSameTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));

  EXPECT_FALSE(fa.isDeterministic());
}

TEST(PROPERTY, IsNotDeterministicEpsilonTransition){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, fa::Epsilon, 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));

  EXPECT_FALSE(fa.isDeterministic());
}

TEST(PROPERTY, IsDeterministic){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 2));

  EXPECT_TRUE(fa.isDeterministic());
}

TEST(PROPERTY, IsNotComplete){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));

  EXPECT_FALSE(fa.isComplete());
}

TEST(PROPERTY, IsComplete){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 2));
  EXPECT_TRUE(fa.addTransition(2, 'a', 1));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));

  EXPECT_TRUE(fa.isComplete());
}

TEST(PROPERTY, IsVeryComplete){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 2));
  EXPECT_TRUE(fa.addTransition(2, 'a', 1));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));
  EXPECT_TRUE(fa.addTransition(2, 'a', 2));

  EXPECT_TRUE(fa.isComplete());
}

TEST(PROPERTY, MakeComplete){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 1));

  EXPECT_EQ(fa.countStates(), 3u);
  EXPECT_TRUE(fa.match("aaababababab"));
  EXPECT_FALSE(fa.match("aaababababaa"));

  fa::Automaton new_fa = fa::Automaton::createComplete(fa);

  EXPECT_TRUE(new_fa.isComplete());
  EXPECT_EQ(new_fa.countStates(), 4u);
  EXPECT_TRUE(new_fa.match("aaababababab"));
  EXPECT_FALSE(new_fa.match("aaababababaa"));
}

TEST(PROPERTY, MakeCompleteButAlreadyComplete){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 2));
  EXPECT_TRUE(fa.addTransition(2, 'a', 1));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));

  EXPECT_EQ(fa.countStates(), 3u);
  EXPECT_TRUE(fa.match("bbaabb"));
  EXPECT_TRUE(fa.match("bb"));

  fa::Automaton new_fa = fa::Automaton::createComplete(fa);

  EXPECT_TRUE(new_fa.isComplete());
  EXPECT_EQ(new_fa.countStates(), 3u);
  EXPECT_TRUE(new_fa.match("bbaabb"));
  EXPECT_TRUE(new_fa.match("bb"));

}

TEST(PROPERTY, MakeCompleteNoLinearValueNode){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(3));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(3);
  EXPECT_TRUE(fa.isStateFinal(3));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 3));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(3, 'b', 3));

  EXPECT_EQ(fa.countStates(), 3u);
  EXPECT_TRUE(fa.match("aaaaabab"));
  EXPECT_FALSE(fa.match("aaaaababa"));

  fa::Automaton new_fa = fa::Automaton::createComplete(fa);

  EXPECT_TRUE(new_fa.isComplete());
  EXPECT_EQ(new_fa.countStates(), 4u);
  EXPECT_TRUE(new_fa.match("aaaaabab"));
  EXPECT_FALSE(new_fa.match("aaaaababa"));
}

TEST(PROPERTY, MakeCompleteMaxInteger){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(INT_MAX));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(INT_MAX);
  EXPECT_TRUE(fa.isStateFinal(INT_MAX));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', INT_MAX));
  EXPECT_TRUE(fa.addTransition(1, 'b', INT_MAX));
  EXPECT_TRUE(fa.addTransition(INT_MAX, 'b', INT_MAX));

  EXPECT_EQ(fa.countStates(), 3u);
  EXPECT_TRUE(fa.match("aaaaabab"));
  EXPECT_FALSE(fa.match("aaaaababa"));

  fa::Automaton new_fa = fa::Automaton::createComplete(fa);

  EXPECT_TRUE(new_fa.isComplete());
  EXPECT_EQ(new_fa.countStates(), 4u);
  EXPECT_TRUE(new_fa.match("aaaaabab"));
  EXPECT_FALSE(new_fa.match("aaaaababa"));
}

TEST(PROPERTY, MakeCompleteNoNewState){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 1));

  EXPECT_EQ(fa.countStates(), 3u);
  EXPECT_FALSE(fa.match("aaababababab"));
  EXPECT_FALSE(fa.match("aaababababaa"));

  fa::Automaton new_fa = fa::Automaton::createComplete(fa);

  EXPECT_TRUE(new_fa.isComplete());
  EXPECT_EQ(new_fa.countStates(), 3u);
  EXPECT_FALSE(new_fa.match("aaababababab"));
  EXPECT_FALSE(new_fa.match("aaababababaa"));
}

TEST(PROPERTY, MakeMirrorSimple){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));  
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));

  EXPECT_TRUE(fa.match("aaab"));
  EXPECT_TRUE(fa.match("aaba"));
  EXPECT_TRUE(fa.match("abbb"));

  fa::Automaton new_fa = fa::Automaton::createMirror(fa);
  
  EXPECT_TRUE(new_fa.match("baaa"));
  EXPECT_TRUE(new_fa.match("abaa"));
  EXPECT_TRUE(new_fa.match("bbba"));
}

TEST(PROPERTY, MakeMirrorInitialIsFinal){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));  
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));

  EXPECT_TRUE(fa.match(""));
  EXPECT_TRUE(fa.match("aaaaab"));
  EXPECT_TRUE(fa.match("aababb"));
  EXPECT_TRUE(fa.match("abbbbb"));
  
  fa::Automaton new_fa = fa::Automaton::createMirror(fa);

  EXPECT_TRUE(new_fa.match(""));
  EXPECT_TRUE(new_fa.match("baaaaa"));
  EXPECT_TRUE(new_fa.match("bbabaa"));
  EXPECT_TRUE(new_fa.match("bbbbba"));
}


/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Those tests exist in order to verify if the language of the automate is empty *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

TEST(EMPTYNESS, LanguageisEmptyWithNoInitial){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
 
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));

  EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(EMPTYNESS, LanguageisEmptyWithNoFinal){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
 
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));  

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));

  EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(EMPTYNESS, LanguageisEmpty){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
 
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));  
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 0));
  EXPECT_TRUE(fa.addTransition(2, 'b', 1));

  EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(EMPTYNESS, LanguageisNotEmpty){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
 
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));  
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));

  EXPECT_FALSE(fa.isLanguageEmpty());
}

TEST(EMPTYNESS, AutomatonIsNotDeterministic){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
 
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 3));
  EXPECT_TRUE(fa.addTransition(1, 'a', 4));

  EXPECT_FALSE(fa.isLanguageEmpty());  
}


/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Those tests exist in order to verify if the automate has non accessible states  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

TEST(ACCESSIBLE, RemoveSimpleNonAccessibleNodes){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
 
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));  

  fa.removeNonAccessibleStates();
  EXPECT_EQ(fa.countStates(), 3u);
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_TRUE(fa.match("ab"));

}

TEST(ACCESSIBLE, RemoveFollowingNonAccessibleNodes){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));  
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));  
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));  
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));

  fa.removeNonAccessibleStates();
  EXPECT_EQ(fa.countStates(), 3u);
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_FALSE(fa.hasState(4));
  EXPECT_FALSE(fa.hasTransition(3, 'b', 4));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_TRUE(fa.match("ab"));
}

TEST(ACCESSIBLE, RemoveCircularNonAccessibleNodes){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));  
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));  
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  EXPECT_TRUE(fa.addTransition(4, 'b', 3));

  fa.removeNonAccessibleStates();
  EXPECT_EQ(fa.countStates(), 3u);
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_FALSE(fa.hasState(4));
  EXPECT_FALSE(fa.hasTransition(3, 'b', 4));
  EXPECT_FALSE(fa.hasTransition(4, 'b', 3));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_TRUE(fa.match("ab"));
}

TEST(ACCESSIBLE, RemoveSelfTargetingNonAccessibleNodes){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));  
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));
  EXPECT_TRUE(fa.addTransition(3, 'b', 3));

  fa.removeNonAccessibleStates();
  EXPECT_EQ(fa.countStates(), 3u);
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_FALSE(fa.hasTransition(3, 'b', 3));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_TRUE(fa.match("ab"));
}

TEST(ACCESSIBLE, RemoveNonAccessibleNodes){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));  
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));
  EXPECT_TRUE(fa.addTransition(3, 'b', 3));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));

  fa.removeNonAccessibleStates();
  EXPECT_EQ(fa.countStates(), 3u);
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_FALSE(fa.hasState(4));
  EXPECT_FALSE(fa.hasTransition(3, 'b', 4));
  EXPECT_FALSE(fa.hasTransition(3, 'b', 3));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_TRUE(fa.match("ab"));
}

TEST(ACCESSIBLE, RemoveAllNodes){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'a', 2));
  EXPECT_TRUE(fa.addTransition(3, 'b', 3));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));

  fa.removeNonAccessibleStates();
  EXPECT_TRUE(fa.isValid());
  EXPECT_FALSE(fa.hasTransition(0, 'a', 0));
  EXPECT_FALSE(fa.hasTransition(1, 'a', 2));
  EXPECT_FALSE(fa.hasTransition(2, 'a', 2));
  EXPECT_FALSE(fa.hasTransition(3, 'b', 3));
  EXPECT_FALSE(fa.hasTransition(3, 'b', 4));
}

TEST(ACCESSIBLE, RemoveAnyNonAccessibleNodes){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));

  fa.removeNonAccessibleStates();
  EXPECT_EQ(fa.countStates(), 3u);
  EXPECT_TRUE(fa.match("a"));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_TRUE(fa.match("ab"));
}


/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Those tests exist in order to verify if the automate has non co-accessible states *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

TEST(COACCESSIBLE, RemoveSimpleNonCoAccessibleNodes){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
 
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));  

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));  

  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(fa.countStates(), 3u);
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("ab"));
}

TEST(COACCESSIBLE, RemoveFollowingNonCoAccessibleNodes){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));  
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));  

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));  
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));

  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(fa.countStates(), 3u);
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_FALSE(fa.hasState(4));
  EXPECT_FALSE(fa.hasTransition(3, 'b', 4));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("ab"));
}

TEST(COACCESSIBLE, RemoveCircularNonCoAccessibleNodes){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));  
  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));  
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));  

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));  
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  EXPECT_TRUE(fa.addTransition(4, 'b', 3));

  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(fa.countStates(), 3u);
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_FALSE(fa.hasState(4));
  EXPECT_FALSE(fa.hasTransition(3, 'b', 4));
  EXPECT_FALSE(fa.hasTransition(4, 'b', 3));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("ab"));
}

TEST(COACCESSIBLE, RemoveSelfTargetingNonCoAccessibleNodes){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));  
  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));  
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2)); 

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));
  EXPECT_TRUE(fa.addTransition(3, 'b', 3));

  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(fa.countStates(), 3u);
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_FALSE(fa.hasTransition(3, 'b', 3));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("ab"));
}

TEST(COACCESSIBLE, RemoveNonCoAccessibleNodes){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));  
  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));  
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2)); 

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));
  EXPECT_TRUE(fa.addTransition(3, 'b', 3));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));

  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(fa.countStates(), 3u);
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_FALSE(fa.hasState(4));
  EXPECT_FALSE(fa.hasTransition(3, 'b', 4));
  EXPECT_FALSE(fa.hasTransition(3, 'b', 3));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("ab"));
}

TEST(COACCESSIBLE, RemoveAllNodes){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'a', 2));
  EXPECT_TRUE(fa.addTransition(3, 'b', 3));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));

  fa.removeNonCoAccessibleStates();
  EXPECT_TRUE(fa.isValid());
  EXPECT_FALSE(fa.hasTransition(0, 'a', 0));
  EXPECT_FALSE(fa.hasTransition(1, 'a', 2));
  EXPECT_FALSE(fa.hasTransition(2, 'a', 2));
  EXPECT_FALSE(fa.hasTransition(3, 'b', 3));
  EXPECT_FALSE(fa.hasTransition(3, 'b', 4));
}

TEST(COACCESSIBLE, RemoveAllNodesBcsNonAccesible){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));

  fa.removeNonCoAccessibleStates();
  EXPECT_TRUE(fa.isValid());
}

TEST(COACCESSIBLE, RemoveAnyNode){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));  

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'a', 2));

  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(fa.countStates(), 3u);
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("aaaaaaa"));
}


/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Those tests exist in order to verify the product of two automatons  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

TEST(PRODUITSYNCH, LeftAutomateHasEmptyLanguage){
  fa::Automaton left;
  EXPECT_TRUE(left.addSymbol('a'));
  EXPECT_TRUE(left.addSymbol('b'));
  
  EXPECT_TRUE(left.addState(0));
  EXPECT_TRUE(left.addState(1));
  EXPECT_TRUE(left.addState(2));
 
  left.setStateInitial(0);
  EXPECT_TRUE(left.isStateInitial(0));

  EXPECT_TRUE(left.addTransition(0, 'a', 0));
  EXPECT_TRUE(left.addTransition(0, 'b', 1));
  EXPECT_TRUE(left.addTransition(1, 'a', 2));
  EXPECT_TRUE(left.addTransition(0, 'b', 2));
  EXPECT_TRUE(left.addTransition(2, 'b', 2));
  EXPECT_TRUE(left.isLanguageEmpty());


  fa::Automaton right;
  EXPECT_TRUE(right.addSymbol('a'));
  EXPECT_TRUE(right.addSymbol('b'));
  
  EXPECT_TRUE(right.addState(0));
  EXPECT_TRUE(right.addState(1));
  EXPECT_TRUE(right.addState(2));
 
  right.setStateInitial(0);
  EXPECT_TRUE(right.isStateInitial(0));
  right.setStateFinal(2);
  EXPECT_TRUE(right.isStateFinal(2));

  EXPECT_TRUE(right.addTransition(0, 'a', 0));
  EXPECT_TRUE(right.addTransition(0, 'b', 1));
  EXPECT_TRUE(right.addTransition(1, 'a', 2));
  EXPECT_TRUE(right.addTransition(0, 'b', 2));
  EXPECT_TRUE(right.addTransition(2, 'b', 2));

  fa::Automaton new_fa = fa::Automaton::createProduct(left, right);
  EXPECT_TRUE(new_fa.isLanguageEmpty());
}

TEST(PRODUITSYNCH, RightAutomateHasEmptyLanguage){
  fa::Automaton left;
  EXPECT_TRUE(left.addSymbol('a'));
  EXPECT_TRUE(left.addSymbol('b'));
  
  EXPECT_TRUE(left.addState(0));
  EXPECT_TRUE(left.addState(1));
  EXPECT_TRUE(left.addState(2));
 
  left.setStateInitial(0);
  EXPECT_TRUE(left.isStateInitial(0));
  left.setStateFinal(2);
  EXPECT_TRUE(left.isStateFinal(2));

  EXPECT_TRUE(left.addTransition(0, 'a', 0));
  EXPECT_TRUE(left.addTransition(0, 'b', 1));
  EXPECT_TRUE(left.addTransition(1, 'a', 2));
  EXPECT_TRUE(left.addTransition(0, 'b', 2));
  EXPECT_TRUE(left.addTransition(2, 'b', 2));


  fa::Automaton right;
  EXPECT_TRUE(right.addSymbol('a'));
  EXPECT_TRUE(right.addSymbol('b'));
  
  EXPECT_TRUE(right.addState(0));
  EXPECT_TRUE(right.addState(1));
  EXPECT_TRUE(right.addState(2));
 
  right.setStateFinal(2);
  EXPECT_TRUE(right.isStateFinal(2));

  EXPECT_TRUE(right.addTransition(0, 'a', 0));
  EXPECT_TRUE(right.addTransition(0, 'b', 1));
  EXPECT_TRUE(right.addTransition(1, 'a', 2));
  EXPECT_TRUE(right.addTransition(0, 'b', 2));
  EXPECT_TRUE(right.addTransition(2, 'b', 2));
  EXPECT_TRUE(right.isLanguageEmpty());

  fa::Automaton new_fa = fa::Automaton::createProduct(left, right);
  EXPECT_TRUE(new_fa.isLanguageEmpty());  
}

TEST(PRODUITSYNCH, AutomatesHaveNoMatchingAlphabet){
  fa::Automaton left;
  EXPECT_TRUE(left.addSymbol('a'));
  EXPECT_TRUE(left.addSymbol('b'));
  
  EXPECT_TRUE(left.addState(0));
  EXPECT_TRUE(left.addState(1));
  EXPECT_TRUE(left.addState(2));
 
  left.setStateInitial(0);
  EXPECT_TRUE(left.isStateInitial(0));
  left.setStateFinal(2);
  EXPECT_TRUE(left.isStateFinal(2));

  EXPECT_TRUE(left.addTransition(0, 'a', 0));
  EXPECT_TRUE(left.addTransition(0, 'b', 1));
  EXPECT_TRUE(left.addTransition(1, 'a', 2));
  EXPECT_TRUE(left.addTransition(0, 'b', 2));
  EXPECT_TRUE(left.addTransition(2, 'b', 2));


  fa::Automaton right;
  EXPECT_TRUE(right.addSymbol('c'));
  EXPECT_TRUE(right.addSymbol('d'));
  
  EXPECT_TRUE(right.addState(0));
  EXPECT_TRUE(right.addState(1));
  EXPECT_TRUE(right.addState(2));
 
  right.setStateInitial(0);
  EXPECT_TRUE(right.isStateInitial(0));
  right.setStateFinal(2);
  EXPECT_TRUE(right.isStateFinal(2));

  EXPECT_TRUE(right.addTransition(0, 'c', 0));
  EXPECT_TRUE(right.addTransition(0, 'c', 1));
  EXPECT_TRUE(right.addTransition(1, 'd', 2));
  EXPECT_TRUE(right.addTransition(0, 'd', 2));
  EXPECT_TRUE(right.addTransition(2, 'c', 2));

  fa::Automaton new_fa = fa::Automaton::createProduct(left, right);
}

TEST(PRODUITSYNCH, AutomatesAreNotDeterministic){
  fa::Automaton left;
  EXPECT_TRUE(left.addSymbol('a'));
  EXPECT_TRUE(left.addSymbol('b'));
  
  EXPECT_TRUE(left.addState(0));
  EXPECT_TRUE(left.addState(1));
  EXPECT_TRUE(left.addState(2));
 
  left.setStateInitial(0);
  EXPECT_TRUE(left.isStateInitial(0));
  left.setStateFinal(2);
  EXPECT_TRUE(left.isStateFinal(2));

  EXPECT_TRUE(left.addTransition(0, 'a', 1));
  EXPECT_TRUE(left.addTransition(0, 'b', 1));
  EXPECT_TRUE(left.addTransition(1, 'a', 2));
  EXPECT_TRUE(left.addTransition(0, 'b', 2));


  fa::Automaton right;
  EXPECT_TRUE(right.addSymbol('a'));
  EXPECT_TRUE(right.addSymbol('b'));
  
  EXPECT_TRUE(right.addState(0));
  EXPECT_TRUE(right.addState(1));
  EXPECT_TRUE(right.addState(2));
 
  right.setStateInitial(0);
  EXPECT_TRUE(right.isStateInitial(0));
  right.setStateFinal(2);
  EXPECT_TRUE(right.isStateFinal(2));

  EXPECT_TRUE(right.addTransition(0, 'b', 1));
  EXPECT_TRUE(right.addTransition(1, 'a', 0));
  EXPECT_TRUE(right.addTransition(1, 'a', 2));
  EXPECT_TRUE(right.addTransition(2, 'b', 2));

  fa::Automaton new_fa = fa::Automaton::createProduct(left, right);
  EXPECT_EQ(new_fa.countStates(), 5u);
  EXPECT_TRUE(new_fa.match("ba"));
}

TEST(PRODUITSYNCH, InitialsStatesAreFinals){
  fa::Automaton left;
  EXPECT_TRUE(left.addSymbol('a'));
  EXPECT_TRUE(left.addSymbol('b'));
  
  EXPECT_TRUE(left.addState(0));
  EXPECT_TRUE(left.addState(1));
  EXPECT_TRUE(left.addState(2));
 
  left.setStateInitial(0);
  EXPECT_TRUE(left.isStateInitial(0));
  left.setStateFinal(0);
  EXPECT_TRUE(left.isStateFinal(0));
  left.setStateFinal(2);
  EXPECT_TRUE(left.isStateFinal(2));

  EXPECT_TRUE(left.addTransition(0, 'a', 1));
  EXPECT_TRUE(left.addTransition(0, 'b', 1));
  EXPECT_TRUE(left.addTransition(1, 'a', 2));
  EXPECT_TRUE(left.addTransition(0, 'b', 2));


  fa::Automaton right;
  EXPECT_TRUE(right.addSymbol('a'));
  EXPECT_TRUE(right.addSymbol('b'));
  
  EXPECT_TRUE(right.addState(0));
  EXPECT_TRUE(right.addState(1));
  EXPECT_TRUE(right.addState(2));
 
  right.setStateInitial(0);
  EXPECT_TRUE(right.isStateInitial(0));
  right.setStateFinal(0);
  EXPECT_TRUE(right.isStateFinal(0));
  right.setStateFinal(2);
  EXPECT_TRUE(right.isStateFinal(2));

  EXPECT_TRUE(right.addTransition(0, 'a', 0));
  EXPECT_TRUE(right.addTransition(0, 'b', 1));
  EXPECT_TRUE(right.addTransition(1, 'a', 2));
  EXPECT_TRUE(right.addTransition(2, 'b', 2));

  fa::Automaton new_fa = fa::Automaton::createProduct(left, right);
  EXPECT_EQ(new_fa.countStates(), 6u);
  EXPECT_TRUE(new_fa.match(""));
  EXPECT_TRUE(new_fa.match("aa"));
  EXPECT_TRUE(new_fa.match("ba"));
}

TEST(PRODUITSYNCH, LinkToAlreadyExistingNode){
  fa::Automaton left;
  EXPECT_TRUE(left.addSymbol('a'));
  EXPECT_TRUE(left.addSymbol('b'));
  
  EXPECT_TRUE(left.addState(0));
  EXPECT_TRUE(left.addState(1));
  EXPECT_TRUE(left.addState(2));
 
  left.setStateInitial(0);
  EXPECT_TRUE(left.isStateInitial(0));
  left.setStateInitial(1);
  EXPECT_TRUE(left.isStateInitial(1));  
  left.setStateFinal(2);
  EXPECT_TRUE(left.isStateFinal(2));

  EXPECT_TRUE(left.addTransition(0, 'a', 2));
  EXPECT_TRUE(left.addTransition(1, 'b', 2));
  EXPECT_TRUE(left.addTransition(2, 'a', 1));


  fa::Automaton right;
  EXPECT_TRUE(right.addSymbol('a'));
  EXPECT_TRUE(right.addSymbol('b'));
  
  EXPECT_TRUE(right.addState(0));
  EXPECT_TRUE(right.addState(1));
  EXPECT_TRUE(right.addState(2));
 
  right.setStateInitial(0);
  EXPECT_TRUE(right.isStateInitial(0));
  right.setStateFinal(1);
  EXPECT_TRUE(right.isStateFinal(1));
  right.setStateFinal(2);
  EXPECT_TRUE(right.isStateFinal(2));

  EXPECT_TRUE(right.addTransition(0, 'a', 0));
  EXPECT_TRUE(right.addTransition(0, 'b', 1));
  EXPECT_TRUE(right.addTransition(1, 'b', 2));
  EXPECT_TRUE(right.addTransition(2, 'a', 2));

  fa::Automaton new_fa = fa::Automaton::createProduct(left, right);
  EXPECT_EQ(new_fa.countStates(), 4u);
  EXPECT_TRUE(new_fa.match("aab"));
  EXPECT_TRUE(new_fa.match("b"));
}

TEST(PRODUITSYNCH, AutomatesHaveMultipleInitialStates){
  fa::Automaton left;
  EXPECT_TRUE(left.addSymbol('a'));
  EXPECT_TRUE(left.addSymbol('b'));
  
  EXPECT_TRUE(left.addState(0));
  EXPECT_TRUE(left.addState(1));
  EXPECT_TRUE(left.addState(2));
  EXPECT_TRUE(left.addState(3));
 
  left.setStateInitial(0);
  EXPECT_TRUE(left.isStateInitial(0));
  left.setStateInitial(1);
  EXPECT_TRUE(left.isStateInitial(1));
  left.setStateFinal(3);
  EXPECT_TRUE(left.isStateFinal(3));

  EXPECT_TRUE(left.addTransition(0, 'a', 3));
  EXPECT_TRUE(left.addTransition(1, 'b', 2));
  EXPECT_TRUE(left.addTransition(2, 'a', 1));
  EXPECT_TRUE(left.addTransition(2, 'b', 3));


  fa::Automaton right;
  EXPECT_TRUE(right.addSymbol('a'));
  EXPECT_TRUE(right.addSymbol('b'));
  
  EXPECT_TRUE(right.addState(0));
  EXPECT_TRUE(right.addState(1));
  EXPECT_TRUE(right.addState(2));
 
  right.setStateInitial(0);
  EXPECT_TRUE(right.isStateInitial(0));
  right.setStateInitial(1);
  EXPECT_TRUE(right.isStateInitial(1));
  right.setStateFinal(2);
  EXPECT_TRUE(right.isStateFinal(2));

  EXPECT_TRUE(right.addTransition(0, 'a', 0));
  EXPECT_TRUE(right.addTransition(0, 'b', 1));
  EXPECT_TRUE(right.addTransition(1, 'b', 2));
  EXPECT_TRUE(right.addTransition(2, 'a', 2));

  fa::Automaton new_fa = fa::Automaton::createProduct(left, right);
  EXPECT_EQ(new_fa.countStates(), 9u);
  EXPECT_TRUE(new_fa.match("bb"));
}

TEST(PRODUITSYNCH, LanguageEmptyButAutomatonIsValid){
  fa::Automaton left;
  EXPECT_TRUE(left.addSymbol('a'));
  EXPECT_TRUE(left.addSymbol('b'));
  
  EXPECT_TRUE(left.addState(0));
  EXPECT_TRUE(left.addState(1));
  EXPECT_TRUE(left.addState(2));
 
  left.setStateInitial(0);
  EXPECT_TRUE(left.isStateInitial(0));
  left.setStateFinal(0);
  EXPECT_TRUE(left.isStateFinal(0));
  left.setStateFinal(2);
  EXPECT_TRUE(left.isStateFinal(2));

  EXPECT_TRUE(left.addTransition(0, 'a', 0));
  EXPECT_TRUE(left.addTransition(0, 'b', 1));
  EXPECT_TRUE(left.addTransition(1, 'a', 2));
  EXPECT_TRUE(left.addTransition(0, 'b', 2));
  EXPECT_TRUE(left.addTransition(2, 'b', 2));


  fa::Automaton right;
  EXPECT_TRUE(right.addSymbol('c'));
  EXPECT_TRUE(right.addSymbol('d'));
  
  EXPECT_TRUE(right.addState(0));
  EXPECT_TRUE(right.addState(1));
  EXPECT_TRUE(right.addState(2));
 
  right.setStateInitial(0);
  EXPECT_TRUE(right.isStateInitial(0));
  right.setStateFinal(0);
  EXPECT_TRUE(right.isStateFinal(0));
  right.setStateFinal(2);
  EXPECT_TRUE(right.isStateFinal(2));

  EXPECT_TRUE(right.addTransition(0, 'c', 0));
  EXPECT_TRUE(right.addTransition(0, 'c', 1));
  EXPECT_TRUE(right.addTransition(1, 'd', 2));
  EXPECT_TRUE(right.addTransition(0, 'd', 2));
  EXPECT_TRUE(right.addTransition(2, 'c', 2));

  fa::Automaton new_fa = fa::Automaton::createProduct(left, right);
  EXPECT_TRUE(new_fa.match(""));
}

TEST(PRODUITSYNCH, EmptyProductButRemovesFinalStates) {
  fa::Automaton left;
  EXPECT_TRUE(left.addSymbol('a'));
  EXPECT_TRUE(left.addSymbol('b'));

  EXPECT_TRUE(left.addState(0));
  EXPECT_TRUE(left.addState(1));
  EXPECT_TRUE(left.addState(2));
  
  left.setStateInitial(0);
  EXPECT_TRUE(left.isStateInitial(0));
  left.setStateFinal(0);
  EXPECT_TRUE(left.isStateFinal(0));
  left.setStateFinal(2);
  EXPECT_TRUE(left.isStateFinal(2));
  
  EXPECT_TRUE(left.addTransition(0,'a',0));
  EXPECT_TRUE(left.addTransition(0,'b',1));
  EXPECT_TRUE(left.addTransition(0,'a',2));
  EXPECT_TRUE(left.addTransition(1,'b',2));

  fa::Automaton right;
  EXPECT_TRUE(right.addSymbol('a'));
  
  EXPECT_TRUE(right.addState(0));

  right.setStateInitial(0);
  EXPECT_TRUE(right.isStateInitial(0));
  right.setStateFinal(0);
  EXPECT_TRUE(right.isStateFinal(0));

  fa::Automaton product = fa::Automaton::createProduct(left,right);
  EXPECT_TRUE(product.isValid());
}

TEST(PRODUITSYNCH, IntersectionIsEmptyBecauseOfLeft){
  fa::Automaton left;
  EXPECT_TRUE(left.addSymbol('a'));
  EXPECT_TRUE(left.addSymbol('b'));
  
  EXPECT_TRUE(left.addState(0));
  EXPECT_TRUE(left.addState(1));
  EXPECT_TRUE(left.addState(2));
 
  left.setStateInitial(0);
  EXPECT_TRUE(left.isStateInitial(0));

  EXPECT_TRUE(left.addTransition(0, 'a', 0));
  EXPECT_TRUE(left.addTransition(0, 'b', 1));
  EXPECT_TRUE(left.addTransition(1, 'a', 2));
  EXPECT_TRUE(left.addTransition(0, 'b', 2));
  EXPECT_TRUE(left.addTransition(2, 'b', 2));
  EXPECT_TRUE(left.isLanguageEmpty());

  fa::Automaton right;
  EXPECT_TRUE(right.addSymbol('a'));
  EXPECT_TRUE(right.addSymbol('b'));
  
  EXPECT_TRUE(right.addState(0));
  EXPECT_TRUE(right.addState(1));
  EXPECT_TRUE(right.addState(2));
 
  right.setStateInitial(0);
  EXPECT_TRUE(right.isStateInitial(0));
  right.setStateFinal(2);
  EXPECT_TRUE(right.isStateFinal(2));

  EXPECT_TRUE(right.addTransition(0, 'a', 0));
  EXPECT_TRUE(right.addTransition(0, 'b', 1));
  EXPECT_TRUE(right.addTransition(1, 'a', 2));
  EXPECT_TRUE(right.addTransition(0, 'b', 2));
  EXPECT_TRUE(right.addTransition(2, 'b', 2));

  EXPECT_TRUE(left.hasEmptyIntersectionWith(right));
}

TEST(PRODUITSYNCH, IntersectionIsEmptyBecauseOfRight){
  fa::Automaton left;
  EXPECT_TRUE(left.addSymbol('a'));
  EXPECT_TRUE(left.addSymbol('b'));
  
  EXPECT_TRUE(left.addState(0));
  EXPECT_TRUE(left.addState(1));
  EXPECT_TRUE(left.addState(2));
 
  left.setStateInitial(0);
  EXPECT_TRUE(left.isStateInitial(0));
  left.setStateFinal(2);
  EXPECT_TRUE(left.isStateFinal(2));

  EXPECT_TRUE(left.addTransition(0, 'a', 0));
  EXPECT_TRUE(left.addTransition(0, 'b', 1));
  EXPECT_TRUE(left.addTransition(1, 'a', 2));
  EXPECT_TRUE(left.addTransition(0, 'b', 2));
  EXPECT_TRUE(left.addTransition(2, 'b', 2));


  fa::Automaton right;
  EXPECT_TRUE(right.addSymbol('a'));
  EXPECT_TRUE(right.addSymbol('b'));
  
  EXPECT_TRUE(right.addState(0));
  EXPECT_TRUE(right.addState(1));
  EXPECT_TRUE(right.addState(2));
 
  right.setStateFinal(2);
  EXPECT_TRUE(right.isStateFinal(2));

  EXPECT_TRUE(right.addTransition(0, 'a', 0));
  EXPECT_TRUE(right.addTransition(0, 'b', 1));
  EXPECT_TRUE(right.addTransition(1, 'a', 2));
  EXPECT_TRUE(right.addTransition(0, 'b', 2));
  EXPECT_TRUE(right.addTransition(2, 'b', 2));
  EXPECT_TRUE(right.isLanguageEmpty());

  EXPECT_TRUE(left.hasEmptyIntersectionWith(right));
}

TEST(PRODUITSYNCH, IntersectionIsEmptyBecauseOfAlphabet){
  fa::Automaton left;
  EXPECT_TRUE(left.addSymbol('a'));
  EXPECT_TRUE(left.addSymbol('b'));
  
  EXPECT_TRUE(left.addState(0));
  EXPECT_TRUE(left.addState(1));
  EXPECT_TRUE(left.addState(2));
 
  left.setStateInitial(0);
  EXPECT_TRUE(left.isStateInitial(0));
  left.setStateFinal(2);
  EXPECT_TRUE(left.isStateFinal(2));

  EXPECT_TRUE(left.addTransition(0, 'a', 0));
  EXPECT_TRUE(left.addTransition(0, 'b', 1));
  EXPECT_TRUE(left.addTransition(1, 'a', 2));
  EXPECT_TRUE(left.addTransition(0, 'b', 2));
  EXPECT_TRUE(left.addTransition(2, 'b', 2));


  fa::Automaton right;
  EXPECT_TRUE(right.addSymbol('c'));
  EXPECT_TRUE(right.addSymbol('d'));
  
  EXPECT_TRUE(right.addState(0));
  EXPECT_TRUE(right.addState(1));
  EXPECT_TRUE(right.addState(2));
 
  right.setStateInitial(0);
  EXPECT_TRUE(right.isStateInitial(0));
  right.setStateFinal(2);
  EXPECT_TRUE(right.isStateFinal(2));

  EXPECT_TRUE(right.addTransition(0, 'c', 0));
  EXPECT_TRUE(right.addTransition(0, 'c', 1));
  EXPECT_TRUE(right.addTransition(1, 'd', 2));
  EXPECT_TRUE(right.addTransition(0, 'd', 2));
  EXPECT_TRUE(right.addTransition(2, 'c', 2));

  EXPECT_TRUE(left.hasEmptyIntersectionWith(right));
}

TEST(PRODUITSYNCH, IntersectionIsNotEmpty){
  fa::Automaton left;
  EXPECT_TRUE(left.addSymbol('a'));
  EXPECT_TRUE(left.addSymbol('b'));
  
  EXPECT_TRUE(left.addState(0));
  EXPECT_TRUE(left.addState(1));
  EXPECT_TRUE(left.addState(2));
 
  left.setStateInitial(0);
  EXPECT_TRUE(left.isStateInitial(0));
  left.setStateFinal(0);
  EXPECT_TRUE(left.isStateFinal(0));
  left.setStateFinal(2);
  EXPECT_TRUE(left.isStateFinal(2));

  EXPECT_TRUE(left.addTransition(0, 'a', 1));
  EXPECT_TRUE(left.addTransition(0, 'b', 1));
  EXPECT_TRUE(left.addTransition(1, 'a', 2));
  EXPECT_TRUE(left.addTransition(0, 'b', 2));


  fa::Automaton right;
  EXPECT_TRUE(right.addSymbol('a'));
  EXPECT_TRUE(right.addSymbol('b'));
  
  EXPECT_TRUE(right.addState(0));
  EXPECT_TRUE(right.addState(1));
  EXPECT_TRUE(right.addState(2));
 
  right.setStateInitial(0);
  EXPECT_TRUE(right.isStateInitial(0));
  right.setStateFinal(0);
  EXPECT_TRUE(right.isStateFinal(0));
  right.setStateFinal(2);
  EXPECT_TRUE(right.isStateFinal(2));

  EXPECT_TRUE(right.addTransition(0, 'a', 0));
  EXPECT_TRUE(right.addTransition(0, 'b', 1));
  EXPECT_TRUE(right.addTransition(1, 'a', 2));
  EXPECT_TRUE(right.addTransition(2, 'b', 2));

  EXPECT_FALSE(left.hasEmptyIntersectionWith(right));
}

TEST(PRODUITSYNCH, IntersectionIsNotEmptyWithNonDeterministic) {
  fa::Automaton left;
  EXPECT_TRUE(left.addSymbol('a'));
  EXPECT_TRUE(left.addSymbol('b'));
  
  EXPECT_TRUE(left.addState(0));
  EXPECT_TRUE(left.addState(1));
  EXPECT_TRUE(left.addState(2));
 
  left.setStateInitial(0);
  EXPECT_TRUE(left.isStateInitial(0));
  left.setStateFinal(2);
  EXPECT_TRUE(left.isStateFinal(2));

  EXPECT_TRUE(left.addTransition(0, 'a', 1));
  EXPECT_TRUE(left.addTransition(0, 'b', 1));
  EXPECT_TRUE(left.addTransition(1, 'a', 2));
  EXPECT_TRUE(left.addTransition(0, 'b', 2));


  fa::Automaton right;
  EXPECT_TRUE(right.addSymbol('a'));
  EXPECT_TRUE(right.addSymbol('b'));
  
  EXPECT_TRUE(right.addState(0));
  EXPECT_TRUE(right.addState(1));
  EXPECT_TRUE(right.addState(2));
 
  right.setStateInitial(0);
  EXPECT_TRUE(right.isStateInitial(0));
  right.setStateFinal(2);
  EXPECT_TRUE(right.isStateFinal(2));

  EXPECT_TRUE(right.addTransition(0, 'b', 1));
  EXPECT_TRUE(right.addTransition(1, 'a', 0));
  EXPECT_TRUE(right.addTransition(1, 'a', 2));
  EXPECT_TRUE(right.addTransition(2, 'b', 2));

  EXPECT_FALSE(left.hasEmptyIntersectionWith(right));
}

TEST(PRODUITSYNCH, IntersectionPartiallySameAlphabet){
  fa::Automaton left;
  EXPECT_TRUE(left.addSymbol('a'));
  EXPECT_TRUE(left.addSymbol('b'));
  
  EXPECT_TRUE(left.addState(0));
  EXPECT_TRUE(left.addState(1));
  EXPECT_TRUE(left.addState(2));
 
  left.setStateInitial(0);
  EXPECT_TRUE(left.isStateInitial(0));
  left.setStateFinal(2);
  EXPECT_TRUE(left.isStateFinal(2));

  EXPECT_TRUE(left.addTransition(0, 'a', 0));
  EXPECT_TRUE(left.addTransition(0, 'b', 1));
  EXPECT_TRUE(left.addTransition(0, 'b', 2));
  EXPECT_TRUE(left.addTransition(1, 'a', 2));
  EXPECT_TRUE(left.addTransition(2, 'b', 2));


  fa::Automaton right;
  EXPECT_TRUE(right.addSymbol('b'));
  EXPECT_TRUE(right.addSymbol('c'));
  
  EXPECT_TRUE(right.addState(0));
  EXPECT_TRUE(right.addState(1));
  EXPECT_TRUE(right.addState(2));
 
  right.setStateInitial(0);
  EXPECT_TRUE(right.isStateInitial(0));
  right.setStateFinal(2);
  EXPECT_TRUE(right.isStateFinal(2));

  EXPECT_TRUE(right.addTransition(0, 'c', 0));
  EXPECT_TRUE(right.addTransition(0, 'b', 1));
  EXPECT_TRUE(right.addTransition(0, 'c', 2));
  EXPECT_TRUE(right.addTransition(1, 'b', 2));
  EXPECT_TRUE(right.addTransition(2, 'c', 2));

  EXPECT_FALSE(left.hasEmptyIntersectionWith(right));
  EXPECT_FALSE(right.hasEmptyIntersectionWith(left));
}


/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Those tests exist in order to verify the lecture in an automate *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

TEST(LECTURE, ReadStringEmpty){
  fa::Automaton fa;
  
  EXPECT_TRUE(fa.addSymbol('a'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 2));  
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));  
  EXPECT_TRUE(fa.addTransition(2, 'a', 0));  
  EXPECT_TRUE(fa.addTransition(2, 'a', 3));  
  EXPECT_TRUE(fa.addTransition(3, 'a', 3));  

  auto rtn = fa.readString("");
  EXPECT_EQ(rtn.size(), 1u);
}

TEST(LECTURE, ReadStringOnDeterministicAutomaton){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 3));
  EXPECT_TRUE(fa.addTransition(2, 'b', 4));
  EXPECT_TRUE(fa.addTransition(3, 'a', 3));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  EXPECT_TRUE(fa.addTransition(4, 'a', 4));  

  auto rtn = fa.readString("a");
  EXPECT_EQ(rtn.size(), 1u);
  EXPECT_TRUE(rtn.find(1) != rtn.end());

  rtn = fa.readString("bb");
  EXPECT_EQ(rtn.size(), 1u);
  EXPECT_TRUE(rtn.find(4) != rtn.end());
  
  rtn = fa.readString("aa");
  EXPECT_EQ(rtn.size(), 0u);

  rtn = fa.readString("c");
  EXPECT_EQ(rtn.size(), 0u);
}

TEST(LECTURE, ReadStringOnCompletAutomaton){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));

  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'a', 4));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 3));
  EXPECT_TRUE(fa.addTransition(1, 'b', 4));
  EXPECT_TRUE(fa.addTransition(1, 'b', 1));
  EXPECT_TRUE(fa.addTransition(2, 'a', 3));
  EXPECT_TRUE(fa.addTransition(2, 'b', 4));
  EXPECT_TRUE(fa.addTransition(3, 'a', 3));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  EXPECT_TRUE(fa.addTransition(4, 'a', 4));  
  EXPECT_TRUE(fa.addTransition(4, 'b', 3));  

  auto rtn = fa.readString("a");
  EXPECT_EQ(rtn.size(), 2u);
  EXPECT_TRUE(rtn.find(1) != rtn.end());
  EXPECT_TRUE(rtn.find(4) != rtn.end());

  rtn = fa.readString("aa");
  EXPECT_EQ(rtn.size(), 2u);
  EXPECT_TRUE(rtn.find(3) != rtn.end());  
  EXPECT_TRUE(rtn.find(4) != rtn.end());  

  rtn = fa.readString("ab");
  EXPECT_EQ(rtn.size(), 3u);
  EXPECT_TRUE(rtn.find(1) != rtn.end());
  EXPECT_TRUE(rtn.find(3) != rtn.end());  
  EXPECT_TRUE(rtn.find(4) != rtn.end());

  rtn = fa.readString("cab");
  EXPECT_EQ(rtn.size(), 0u);
}

TEST(LECTURE, ReadStringOnDeteriministeAndCompletAutomaton){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0)); 
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 3));
  EXPECT_TRUE(fa.addTransition(2, 'b', 4));
  EXPECT_TRUE(fa.addTransition(3, 'a', 3));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  EXPECT_TRUE(fa.addTransition(4, 'a', 4));
  EXPECT_TRUE(fa.addTransition(4, 'b', 2));

  auto rtn = fa.readString("a");
  EXPECT_EQ(rtn.size(), 1u);
  EXPECT_TRUE(rtn.find(1) != rtn.end());

  rtn = fa.readString("bb");
  EXPECT_EQ(rtn.size(), 1u);
  EXPECT_TRUE(rtn.find(4) != rtn.end());
  
  rtn = fa.readString("c");
  EXPECT_EQ(rtn.size(), 0u);
}

TEST(LECTURE, ReadStringOnAutomateWithTwoInitialState){
  fa::Automaton fa;
  
  EXPECT_TRUE(fa.addSymbol('a'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 2));  
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));  
  EXPECT_TRUE(fa.addTransition(2, 'a', 0));  
  EXPECT_TRUE(fa.addTransition(2, 'a', 3));  
  EXPECT_TRUE(fa.addTransition(3, 'a', 3));  

  auto rtn = fa.readString("");
  EXPECT_EQ(rtn.size(), 2u);
  EXPECT_TRUE(rtn.find(0) != rtn.end());
  EXPECT_TRUE(rtn.find(1) != rtn.end());

  rtn = fa.readString("a");
  EXPECT_EQ(rtn.size(), 1u);
  EXPECT_TRUE(rtn.find(2) != rtn.end());
  
  rtn = fa.readString("aa");
  EXPECT_EQ(rtn.size(), 2u);
  EXPECT_TRUE(rtn.find(0) != rtn.end());
  EXPECT_TRUE(rtn.find(3) != rtn.end());  
}

TEST(LECTURE, ReadStringOnAutomateWithNoInitialState){
  fa::Automaton fa;
  
  EXPECT_TRUE(fa.addSymbol('a'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));

  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 2));  
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));  
  EXPECT_TRUE(fa.addTransition(2, 'a', 0));  
  EXPECT_TRUE(fa.addTransition(2, 'a', 3));  
  EXPECT_TRUE(fa.addTransition(3, 'a', 3));  

  auto rtn = fa.readString("a");
  EXPECT_EQ(rtn.size(), 0u);
}

TEST(LECTURE, MatchOnDeterministicAutomaton){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 3));
  EXPECT_TRUE(fa.addTransition(2, 'b', 4));
  EXPECT_TRUE(fa.addTransition(3, 'a', 3));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  EXPECT_TRUE(fa.addTransition(4, 'a', 4));  

  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("bb"));
  
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_FALSE(fa.match("ba"));
  EXPECT_FALSE(fa.match("c"));
}

TEST(LECTURE, MatchOnCompletAutomaton){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));

  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'a', 4));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 3));
  EXPECT_TRUE(fa.addTransition(1, 'b', 4));
  EXPECT_TRUE(fa.addTransition(1, 'b', 1));
  EXPECT_TRUE(fa.addTransition(2, 'a', 3));
  EXPECT_TRUE(fa.addTransition(2, 'b', 4));
  EXPECT_TRUE(fa.addTransition(3, 'a', 3));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  EXPECT_TRUE(fa.addTransition(4, 'a', 4));  
  EXPECT_TRUE(fa.addTransition(4, 'b', 3));  

  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("abbab"));

  EXPECT_FALSE(fa.match("ba"));
  EXPECT_FALSE(fa.match("cab"));
}

TEST(LECTURE, MatchOnDeteriministAndCompletAutomaton){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0)); 
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 3));
  EXPECT_TRUE(fa.addTransition(2, 'b', 4));
  EXPECT_TRUE(fa.addTransition(3, 'a', 3));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  EXPECT_TRUE(fa.addTransition(4, 'a', 4));
  EXPECT_TRUE(fa.addTransition(4, 'b', 2));

  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("bb"));

  EXPECT_FALSE(fa.match("aa"));
  EXPECT_FALSE(fa.match("c"));
}


/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Those tests exist in order to test the determinisation of an automate *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

TEST(DETERMINIST, MakeDeterministic){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'a', 4));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 3));
  EXPECT_TRUE(fa.addTransition(1, 'b', 4));
  EXPECT_TRUE(fa.addTransition(1, 'b', 1));
  EXPECT_TRUE(fa.addTransition(2, 'a', 3));
  EXPECT_TRUE(fa.addTransition(2, 'b', 4));
  EXPECT_TRUE(fa.addTransition(3, 'a', 3));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  EXPECT_TRUE(fa.addTransition(4, 'a', 4));  
  EXPECT_TRUE(fa.addTransition(4, 'b', 3));  

  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("abba"));
  EXPECT_TRUE(fa.match("bb"));
  EXPECT_TRUE(fa.match("baaaaaaabaabb"));

  fa::Automaton deterministic = fa::Automaton::createDeterministic(fa);
  
  EXPECT_TRUE(deterministic.isDeterministic());
  EXPECT_EQ(deterministic.countStates(), 7u);
  EXPECT_TRUE(deterministic.match("a"));
  EXPECT_TRUE(deterministic.match("aa"));
  EXPECT_TRUE(deterministic.match("ab"));
  EXPECT_TRUE(deterministic.match("abba"));
  EXPECT_TRUE(deterministic.match("bb"));
  EXPECT_TRUE(deterministic.match("baaaaaaabaabb"));
}

TEST(DETERMINIST, MakeDeterministicWithNotCompleteAutomaton){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addSymbol('e'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'a', 4));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 3));
  EXPECT_TRUE(fa.addTransition(1, 'b', 4));
  EXPECT_TRUE(fa.addTransition(1, 'b', 1));
  EXPECT_TRUE(fa.addTransition(2, 'a', 3));
  EXPECT_TRUE(fa.addTransition(2, 'b', 4));
  EXPECT_TRUE(fa.addTransition(3, 'a', 3));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  EXPECT_TRUE(fa.addTransition(4, 'a', 4));  
  EXPECT_TRUE(fa.addTransition(4, 'b', 3));  

  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("abba"));
  EXPECT_TRUE(fa.match("bb"));
  EXPECT_TRUE(fa.match("baaaaaaabaabb"));

  fa::Automaton deterministic = fa::Automaton::createDeterministic(fa);
  
  EXPECT_TRUE(deterministic.isDeterministic());
  EXPECT_EQ(deterministic.countStates(), 7u);
  EXPECT_TRUE(deterministic.match("a"));
  EXPECT_TRUE(deterministic.match("aa"));
  EXPECT_TRUE(deterministic.match("ab"));
  EXPECT_TRUE(deterministic.match("abba"));
  EXPECT_TRUE(deterministic.match("bb"));
  EXPECT_TRUE(deterministic.match("baaaaaaabaabb"));  
}

TEST(DETERMINIST, MakeDeterministicWithMultipleInitialStates){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
 
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  EXPECT_TRUE(fa.addState(5));
  EXPECT_TRUE(fa.addState(6));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
  fa.setStateFinal(6);
  EXPECT_TRUE(fa.isStateFinal(6));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'a', 2));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(1, 'a', 5));
  EXPECT_TRUE(fa.addTransition(1, 'b', 5));
  EXPECT_TRUE(fa.addTransition(2, 'a', 0));
  EXPECT_TRUE(fa.addTransition(2, 'b', 4));
  EXPECT_TRUE(fa.addTransition(3, 'a', 3));
  EXPECT_TRUE(fa.addTransition(3, 'a', 5));
  EXPECT_TRUE(fa.addTransition(3, 'b', 6));
  EXPECT_TRUE(fa.addTransition(4, 'a', 6));
  EXPECT_TRUE(fa.addTransition(5, 'b', 6));

  EXPECT_TRUE(fa.match("aba"));
  EXPECT_TRUE(fa.match("bba"));
  EXPECT_TRUE(fa.match("aaaaabba"));
  EXPECT_TRUE(fa.match("aaaabaaba"));
  EXPECT_TRUE(fa.match("bb"));
  EXPECT_TRUE(fa.match("bab"));
  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("bb"));
  EXPECT_TRUE(fa.match("baaaaab"));

  fa::Automaton deterministic = fa::Automaton::createDeterministic(fa);
  
  EXPECT_TRUE(deterministic.isDeterministic());
  EXPECT_EQ(deterministic.countStates(), 15u);
  EXPECT_TRUE(deterministic.match("aba"));
  EXPECT_TRUE(deterministic.match("bba"));
  EXPECT_TRUE(deterministic.match("aaaaabba"));
  EXPECT_TRUE(deterministic.match("aaaabaaba"));
  EXPECT_TRUE(deterministic.match("bb"));
  EXPECT_TRUE(deterministic.match("bab"));
  EXPECT_TRUE(deterministic.match("ab"));
  EXPECT_TRUE(deterministic.match("bb"));
  EXPECT_TRUE(deterministic.match("baaaaab"));
}

TEST(DETERMINIST, MakeDeterministicWithInitialIsFinal){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addSymbol('c'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));

  EXPECT_TRUE(fa.addTransition(0, 'b', 0));
  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 3));
  EXPECT_TRUE(fa.addTransition(1, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'a', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 1));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));
  EXPECT_TRUE(fa.addTransition(2, 'c', 3));
  EXPECT_TRUE(fa.addTransition(3, 'a', 2));
  EXPECT_TRUE(fa.addTransition(3, 'a', 3));

  EXPECT_TRUE(fa.match(""));
  EXPECT_TRUE(fa.match("b"));
  EXPECT_TRUE(fa.match("baaaaa"));
  EXPECT_TRUE(fa.match("aabbbbaaab"));
  EXPECT_TRUE(fa.match("aacacacaba"));
  EXPECT_TRUE(fa.match("baba"));

  fa::Automaton deterministic = fa::Automaton::createDeterministic(fa);
  
  EXPECT_TRUE(deterministic.isDeterministic());
  EXPECT_EQ(deterministic.countStates(), 9u);
  EXPECT_TRUE(deterministic.match(""));
  EXPECT_TRUE(deterministic.match("b"));
  EXPECT_TRUE(deterministic.match("baaaaa"));
  EXPECT_TRUE(deterministic.match("aabbbbaaab"));
  EXPECT_TRUE(deterministic.match("aacacacaba"));
  EXPECT_TRUE(deterministic.match("baba"));
}

TEST(DETERMINIST, MakeDeterministicEmptyLanguage){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
 
  EXPECT_TRUE(fa.addState(0));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));

  EXPECT_TRUE(fa.match(""));

  fa::Automaton deterministic = fa::Automaton::createDeterministic(fa);

  EXPECT_TRUE(deterministic.isDeterministic());
  EXPECT_EQ(deterministic.countStates(), 1u);
  EXPECT_TRUE(deterministic.match(""));
}

TEST(DETERMINIST, MakeDeterministicButNoInitial){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
 
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));  
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));

  fa::Automaton deterministic = fa::Automaton::createDeterministic(fa);

  EXPECT_TRUE(deterministic.isDeterministic());
  EXPECT_EQ(deterministic.countStates(), 1u);
}

TEST(DETERMINIST, MakeDeterministicButNoFinal){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));  

  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 3));  
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));

  fa::Automaton deterministic = fa::Automaton::createDeterministic(fa);

  EXPECT_TRUE(deterministic.isDeterministic());
  EXPECT_EQ(deterministic.countStates(), 5u);
}

TEST(DETERMINIST, MakeDeterministicAlreadyDeterminist){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 1));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 3));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));
  EXPECT_TRUE(fa.addTransition(3, 'a', 3));
  EXPECT_TRUE(fa.addTransition(3, 'b', 3));


  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("b"));
  EXPECT_TRUE(fa.match("aaaaa"));
  EXPECT_TRUE(fa.match("bbbbb"));

  fa::Automaton deterministic = fa::Automaton::createDeterministic(fa);
  
  EXPECT_TRUE(deterministic.isDeterministic());
  EXPECT_EQ(deterministic.countStates(), 4u);
  EXPECT_TRUE(deterministic.match("a"));
  EXPECT_TRUE(deterministic.match("b"));
  EXPECT_TRUE(deterministic.match("aaaaa"));
  EXPECT_TRUE(deterministic.match("bbbbb"));
}


/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Those tests exist in order to test the complement of an automate  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

TEST(COMPLEMENT, MakeComplementFromNoInitial){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_TRUE(fa.addSymbol('d'));
 
  EXPECT_TRUE(fa.addState(0));

  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));

  EXPECT_FALSE(fa.match(""));
  EXPECT_FALSE(fa.match("a"));
  EXPECT_FALSE(fa.match("b"));
  EXPECT_FALSE(fa.match("c"));
  EXPECT_FALSE(fa.match("d"));

  fa::Automaton complement = fa::Automaton::createComplement(fa);

  EXPECT_TRUE(complement.isDeterministic());
  EXPECT_TRUE(complement.isComplete());
  EXPECT_TRUE(complement.match(""));  
  EXPECT_TRUE(complement.match("a"));
  EXPECT_TRUE(complement.match("b"));
  EXPECT_TRUE(complement.match("c"));
  EXPECT_TRUE(complement.match("d"));
}

TEST(COMPLEMENT, MakeComplementFromNoFinal){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
 
  EXPECT_TRUE(fa.addState(0));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));

  EXPECT_FALSE(fa.match(""));
  EXPECT_FALSE(fa.match("a"));

  fa::Automaton complement = fa::Automaton::createComplement(fa);

  EXPECT_TRUE(complement.isDeterministic());
  EXPECT_TRUE(complement.isComplete());
  EXPECT_TRUE(complement.match(""));  
  EXPECT_TRUE(complement.match("a"));
}

TEST(COMPLEMENT, MakeComplementFromEmptyLanguage){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
 
  EXPECT_TRUE(fa.addState(0));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));

  EXPECT_TRUE(fa.match(""));
  EXPECT_FALSE(fa.match("a"));

  fa::Automaton complement = fa::Automaton::createComplement(fa);

  EXPECT_TRUE(complement.isDeterministic());
  EXPECT_TRUE(complement.isComplete());
  EXPECT_FALSE(complement.match(""));  
  EXPECT_TRUE(complement.match("a"));
}

TEST(COMPLEMENT, MakeComplementFromCompletAutomaton){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 1));

  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("aaa"));
  EXPECT_FALSE(fa.match(""));

  fa::Automaton complement = fa::Automaton::createComplement(fa);

  EXPECT_TRUE(complement.isDeterministic());
  EXPECT_TRUE(complement.isComplete());
  EXPECT_FALSE(complement.match("a"));
  EXPECT_FALSE(complement.match("aaa"));
  EXPECT_TRUE(complement.match(""));
}

TEST(COMPLEMENT, MakeComplementFromDeterministicAutomaton){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b')); 

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 0));

  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("bbbba"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_FALSE(fa.match("b"));

  fa::Automaton complement = fa::Automaton::createComplement(fa);

  EXPECT_TRUE(complement.isDeterministic());
  EXPECT_TRUE(complement.isComplete());
  EXPECT_FALSE(complement.match("a"));
  EXPECT_FALSE(complement.match("bbbba"));
  EXPECT_TRUE(complement.match(""));
  EXPECT_TRUE(complement.match("b"));  
}

TEST(COMPLEMENT, MakeComplementFromCompletAndDeterministicAutomaton){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b')); 

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 1));
  EXPECT_TRUE(fa.addTransition(1, 'b', 1));
  EXPECT_TRUE(fa.addTransition(2, 'a', 1));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));

  EXPECT_TRUE(fa.isComplete());
  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_TRUE(fa.match("b"));
  EXPECT_TRUE(fa.match("bbbbb"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_FALSE(fa.match("aabbabab"));
  EXPECT_FALSE(fa.match("aaa"));
  EXPECT_FALSE(fa.match("bbbbba"));
  EXPECT_FALSE(fa.match("bbbbbbab"));

  fa::Automaton complement = fa::Automaton::createComplement(fa);

  EXPECT_TRUE(complement.isDeterministic());
  EXPECT_TRUE(complement.isComplete());
  EXPECT_FALSE(complement.match("b"));
  EXPECT_FALSE(complement.match("bbbbb"));
  EXPECT_TRUE(complement.match(""));
  EXPECT_TRUE(complement.match("aabbabab"));
  EXPECT_TRUE(complement.match("aaa"));
  EXPECT_TRUE(complement.match("bbbbba"));
  EXPECT_TRUE(complement.match("bbbbbbab"));
}

TEST(COMPLEMENT, MakeComplementFromComplement){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('e'));
  EXPECT_TRUE(fa.addSymbol('s'));
  EXPECT_TRUE(fa.addSymbol('t'));
  EXPECT_TRUE(fa.addSymbol('j'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addSymbol('l'));
  EXPECT_TRUE(fa.addSymbol('u'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  EXPECT_TRUE(fa.addState(5));
  EXPECT_TRUE(fa.addState(6));
  EXPECT_TRUE(fa.addState(7));
  EXPECT_TRUE(fa.addState(8));
  EXPECT_TRUE(fa.addState(9));
  EXPECT_TRUE(fa.addState(10));
  EXPECT_TRUE(fa.addState(11));
  EXPECT_TRUE(fa.addState(12));
  EXPECT_TRUE(fa.addState(13));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateInitial(13);
  EXPECT_TRUE(fa.isStateInitial(13));

  EXPECT_TRUE(fa.addTransition(0,'j',1));
  EXPECT_TRUE(fa.addTransition(1,'u',2));
  EXPECT_TRUE(fa.addTransition(2,'b',3));
  EXPECT_TRUE(fa.addTransition(3,'e',4));
  EXPECT_TRUE(fa.addTransition(4,'e',5));
  EXPECT_TRUE(fa.addTransition(5,'s',6));
  EXPECT_TRUE(fa.addTransition(6,'t',7));
  EXPECT_TRUE(fa.addTransition(7,'l',8));
  EXPECT_TRUE(fa.addTransition(8,'e',9));
  EXPECT_TRUE(fa.addTransition(9,'b',10));
  EXPECT_TRUE(fa.addTransition(10,'e',11));
  EXPECT_TRUE(fa.addTransition(11,'s',12));
  EXPECT_TRUE(fa.addTransition(12,'t',13));

  fa.match("jubeestlebest");

  fa::Automaton complement = fa::Automaton::createComplement(fa);
  fa::Automaton complementCarre = fa::Automaton::createComplement(complement);

  complementCarre.match("jubeestlebest");
}


/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Those tests exist in order to test if the language of an automaton is include in an other *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

TEST(INCLUDE, OnHimself){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.isIncludedIn(fa));
}

TEST(INCLUDE, OnHImselfButDeterministAndComplete){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  fa::Automaton complete = fa::Automaton::createComplete(fa);
  fa::Automaton other = fa::Automaton::createDeterministic(complete);

  EXPECT_TRUE(fa.isIncludedIn(other));
  EXPECT_TRUE(other.isIncludedIn(fa));
}

TEST(INCLUDE, BothLanguageAcceptEmpty){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 0));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  EXPECT_TRUE(fa.addTransition(4, 'a', 4));
  EXPECT_TRUE(fa.addTransition(4, 'b', 2));


  fa::Automaton other;
  
  EXPECT_TRUE(other.addSymbol('a'));
  EXPECT_TRUE(other.addSymbol('b'));

  EXPECT_TRUE(other.addState(0));

  other.setStateInitial(0);
  EXPECT_TRUE(other.isStateInitial(0));
  other.setStateFinal(0);
  EXPECT_TRUE(other.isStateFinal(0));


  EXPECT_FALSE(fa.isIncludedIn(other));
  EXPECT_TRUE(other.isIncludedIn(fa));
}

TEST(INCLUDE, OneLanguageIsEmptyButNotTheOther){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 0));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  EXPECT_TRUE(fa.addTransition(4, 'a', 4));
  EXPECT_TRUE(fa.addTransition(4, 'b', 2));


  fa::Automaton other;
  
  EXPECT_TRUE(other.addSymbol('a'));
  EXPECT_TRUE(other.addSymbol('b'));

  EXPECT_TRUE(other.addState(0));

  other.setStateInitial(0);
  EXPECT_TRUE(other.isStateInitial(0));
  other.setStateFinal(0);
  EXPECT_TRUE(other.isStateFinal(0));


  EXPECT_FALSE(fa.isIncludedIn(other));
  EXPECT_FALSE(other.isIncludedIn(fa));
}

TEST(INCLUDE, OtherHasNoInitial){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 0));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  EXPECT_TRUE(fa.addTransition(4, 'a', 4));
  EXPECT_TRUE(fa.addTransition(4, 'b', 2));


  fa::Automaton other;
  
  EXPECT_TRUE(other.addSymbol('a'));
  EXPECT_TRUE(other.addSymbol('b'));

  EXPECT_TRUE(other.addState(0));

  other.setStateFinal(0);
  EXPECT_TRUE(other.isStateFinal(0));


  EXPECT_FALSE(fa.isIncludedIn(other));
  EXPECT_TRUE(other.isIncludedIn(fa));
}

TEST(INCLUDE, OtherHasNoFinal){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 0));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  EXPECT_TRUE(fa.addTransition(4, 'a', 4));
  EXPECT_TRUE(fa.addTransition(4, 'b', 2));


  fa::Automaton other;
  
  EXPECT_TRUE(other.addSymbol('a'));
  EXPECT_TRUE(other.addSymbol('b'));

  EXPECT_TRUE(other.addState(0));

  other.setStateInitial(0);
  EXPECT_TRUE(other.isStateInitial(0));


  EXPECT_FALSE(fa.isIncludedIn(other));
  EXPECT_TRUE(other.isIncludedIn(fa));
}

TEST(INCLUDE, DifferentAlphabet){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));  
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 0));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  EXPECT_TRUE(fa.addTransition(4, 'a', 4));
  EXPECT_TRUE(fa.addTransition(4, 'b', 2));


  fa::Automaton other;
  
  EXPECT_TRUE(other.addSymbol('a'));

  EXPECT_TRUE(other.addState(0));

  other.setStateInitial(0);
  EXPECT_TRUE(other.isStateInitial(0));
  other.setStateFinal(0);
  EXPECT_TRUE(other.isStateFinal(0));

  EXPECT_TRUE(other.addTransition(0, 'a', 0));

  EXPECT_FALSE(fa.isIncludedIn(other));
  EXPECT_TRUE(other.isIncludedIn(fa));  
}


/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Those tests exist in order to test the create minimal using the Moore algorith  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

TEST(MOORE, MakeMinimal1){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  EXPECT_TRUE(fa.addState(5));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(3);
  EXPECT_TRUE(fa.isStateFinal(3));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 1));
  EXPECT_TRUE(fa.addTransition(2, 'b', 4));
  EXPECT_TRUE(fa.addTransition(3, 'a', 4));
  EXPECT_TRUE(fa.addTransition(3, 'b', 5));
  EXPECT_TRUE(fa.addTransition(4, 'a', 3));
  EXPECT_TRUE(fa.addTransition(4, 'b', 5));
  EXPECT_TRUE(fa.addTransition(5, 'a', 5));
  EXPECT_TRUE(fa.addTransition(5, 'b', 5));

  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("bb"));
  EXPECT_TRUE(fa.match("aba"));
  EXPECT_TRUE(fa.match("baaabaaa"));

  fa::Automaton minimalMoore = fa::Automaton::createMinimalMoore(fa);

  EXPECT_EQ(minimalMoore.countStates(), 4u);
  EXPECT_TRUE(minimalMoore.isDeterministic());
  EXPECT_TRUE(minimalMoore.match("ab"));
  EXPECT_TRUE(minimalMoore.match("bb"));
  EXPECT_TRUE(minimalMoore.match("aba"));
  EXPECT_TRUE(minimalMoore.match("baaabaaa"));  
}

TEST(MOORE, MakeMinimal2){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  EXPECT_TRUE(fa.addState(5));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));
  fa.setStateFinal(5);
  EXPECT_TRUE(fa.isStateFinal(5));

  EXPECT_TRUE(fa.addTransition(0, 'a', 5));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 4));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 5));
  EXPECT_TRUE(fa.addTransition(3, 'a', 3));
  EXPECT_TRUE(fa.addTransition(3, 'b', 0));
  EXPECT_TRUE(fa.addTransition(4, 'a', 1));
  EXPECT_TRUE(fa.addTransition(4, 'b', 2));
  EXPECT_TRUE(fa.addTransition(5, 'a', 5));
  EXPECT_TRUE(fa.addTransition(5, 'b', 4));

  EXPECT_TRUE(fa.match(""));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("bbb"));
  EXPECT_TRUE(fa.match("abbb"));

  fa::Automaton minimalMoore = fa::Automaton::createMinimalMoore(fa);

  EXPECT_EQ(minimalMoore.countStates(), 3u);
  EXPECT_TRUE(minimalMoore.isDeterministic());
  EXPECT_TRUE(minimalMoore.match(""));
  EXPECT_TRUE(minimalMoore.match("a"));
  EXPECT_TRUE(minimalMoore.match("bbb"));
  EXPECT_TRUE(minimalMoore.match("abbb"));  
}

TEST(MOORE, MakeMinimalAlreadyMinimal){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  EXPECT_TRUE(fa.addState(5));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(5);
  EXPECT_TRUE(fa.isStateFinal(5));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 4));
  EXPECT_TRUE(fa.addTransition(1, 'b', 5));
  EXPECT_TRUE(fa.addTransition(2, 'a', 0));
  EXPECT_TRUE(fa.addTransition(2, 'b', 0));
  EXPECT_TRUE(fa.addTransition(3, 'a', 5));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  EXPECT_TRUE(fa.addTransition(4, 'a', 3));
  EXPECT_TRUE(fa.addTransition(4, 'b', 5));
  EXPECT_TRUE(fa.addTransition(5, 'a', 3));
  EXPECT_TRUE(fa.addTransition(5, 'b', 4));

  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("bbab"));
  EXPECT_TRUE(fa.match("aaaa"));
  EXPECT_TRUE(fa.match("aaabbaa"));

  fa::Automaton minimalMoore = fa::Automaton::createMinimalMoore(fa);

  EXPECT_EQ(minimalMoore.countStates(), 6u);
  EXPECT_TRUE(minimalMoore.isDeterministic());
  EXPECT_TRUE(minimalMoore.match("ab"));
  EXPECT_TRUE(minimalMoore.match("bbab"));
  EXPECT_TRUE(minimalMoore.match("aaaa"));
  EXPECT_TRUE(minimalMoore.match("aaabbaa"));  
}

TEST(MOORE, MakeMinimalAlreadyMinimalNotComplete){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  //EXPECT_TRUE(fa.addState(4));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(3);
  EXPECT_TRUE(fa.isStateFinal(3));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  //EXPECT_TRUE(fa.addTransition(1, 'b', 4));
  EXPECT_TRUE(fa.addTransition(1, 'a', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 0));
  EXPECT_TRUE(fa.addTransition(2, 'b', 0));
  //EXPECT_TRUE(fa.addTransition(3, 'a', 4));
  //EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  //EXPECT_TRUE(fa.addTransition(4, 'a', 4));
  //EXPECT_TRUE(fa.addTransition(4, 'b', 4));

  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("bbbaaa"));
  EXPECT_TRUE(fa.match("bababbaa"));

  fa::Automaton minimalMoore = fa::Automaton::createMinimalMoore(fa);

  EXPECT_EQ(minimalMoore.countStates(), 5u);
  EXPECT_TRUE(minimalMoore.isDeterministic());
  EXPECT_TRUE(minimalMoore.isComplete());
  EXPECT_TRUE(minimalMoore.match("aa"));
  EXPECT_TRUE(minimalMoore.match("bbbaaa"));
  EXPECT_TRUE(minimalMoore.match("bababbaa"));
}

TEST(MOORE, MakeMinimal1NotAesthetic){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  EXPECT_TRUE(fa.addState(5));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(3);
  EXPECT_TRUE(fa.isStateFinal(3));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(5, 'b', 5));
  EXPECT_TRUE(fa.addTransition(4, 'b', 5));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(3, 'b', 5));
  EXPECT_TRUE(fa.addTransition(2, 'b', 4));
  EXPECT_TRUE(fa.addTransition(3, 'a', 4));
  EXPECT_TRUE(fa.addTransition(5, 'a', 5));
  EXPECT_TRUE(fa.addTransition(4, 'a', 3));

  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("bb"));
  EXPECT_TRUE(fa.match("aba"));
  EXPECT_TRUE(fa.match("baaabaaa"));

  fa::Automaton minimalMoore = fa::Automaton::createMinimalMoore(fa);

  EXPECT_EQ(minimalMoore.countStates(), 4u);
  EXPECT_TRUE(minimalMoore.isDeterministic());
  EXPECT_TRUE(minimalMoore.match("ab"));
  EXPECT_TRUE(minimalMoore.match("bb"));
  EXPECT_TRUE(minimalMoore.match("aba"));
  EXPECT_TRUE(minimalMoore.match("baaabaaa"));  
}

TEST(MOORE, NoInitialState) {
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
 
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));

  fa::Automaton minimalMoore = fa::Automaton::createMinimalMoore(fa);

  EXPECT_EQ(minimalMoore.countStates(),1u);
  EXPECT_TRUE(minimalMoore.isDeterministic());
  EXPECT_FALSE(minimalMoore.match("b"));
  EXPECT_FALSE(minimalMoore.match("ab"));
  EXPECT_FALSE(minimalMoore.match("babbbb"));
  EXPECT_FALSE(minimalMoore.match(""));
}

TEST(MOORE, NoFinalState) {
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
 
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));

  fa::Automaton minimalMoore = fa::Automaton::createMinimalBrzozowski(fa);

  EXPECT_EQ(minimalMoore.countStates(),1u);
  EXPECT_TRUE(minimalMoore.isDeterministic());
  EXPECT_FALSE(minimalMoore.match("b"));
  EXPECT_FALSE(minimalMoore.match("ab"));
  EXPECT_FALSE(minimalMoore.match("babbbb"));
  EXPECT_FALSE(minimalMoore.match(""));
}


/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Those tests exist in order to test the create minimal using the Brzozowski algorith *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

TEST(BRZOZOWSKI, MakeMinimal1){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  EXPECT_TRUE(fa.addState(5));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(3);
  EXPECT_TRUE(fa.isStateFinal(3));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 1));
  EXPECT_TRUE(fa.addTransition(2, 'b', 4));
  EXPECT_TRUE(fa.addTransition(3, 'a', 4));
  EXPECT_TRUE(fa.addTransition(3, 'b', 5));
  EXPECT_TRUE(fa.addTransition(4, 'a', 3));
  EXPECT_TRUE(fa.addTransition(4, 'b', 5));
  EXPECT_TRUE(fa.addTransition(5, 'a', 5));
  EXPECT_TRUE(fa.addTransition(5, 'b', 5));

  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("bb"));
  EXPECT_TRUE(fa.match("aba"));
  EXPECT_TRUE(fa.match("baaabaaa"));

  fa::Automaton minimalBrzozowski = fa::Automaton::createMinimalBrzozowski(fa);

  EXPECT_EQ(minimalBrzozowski.countStates(), 4u);
  EXPECT_TRUE(minimalBrzozowski.isDeterministic());
  EXPECT_TRUE(minimalBrzozowski.isComplete());
  EXPECT_TRUE(minimalBrzozowski.match("ab"));
  EXPECT_TRUE(minimalBrzozowski.match("bb"));
  EXPECT_TRUE(minimalBrzozowski.match("aba"));
  EXPECT_TRUE(minimalBrzozowski.match("baaabaaa"));  
}

TEST(BRZOZOWSKI, MakeMinimal2){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  EXPECT_TRUE(fa.addState(5));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(0);
  EXPECT_TRUE(fa.isStateFinal(0));
  fa.setStateFinal(5);
  EXPECT_TRUE(fa.isStateFinal(5));

  EXPECT_TRUE(fa.addTransition(0, 'a', 5));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 4));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 5));
  EXPECT_TRUE(fa.addTransition(3, 'a', 3));
  EXPECT_TRUE(fa.addTransition(3, 'b', 0));
  EXPECT_TRUE(fa.addTransition(4, 'a', 1));
  EXPECT_TRUE(fa.addTransition(4, 'b', 2));
  EXPECT_TRUE(fa.addTransition(5, 'a', 5));
  EXPECT_TRUE(fa.addTransition(5, 'b', 4));

  EXPECT_TRUE(fa.match(""));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("bbb"));
  EXPECT_TRUE(fa.match("abbb"));

  fa::Automaton minimalBrzozowski = fa::Automaton::createMinimalBrzozowski(fa);

  EXPECT_EQ(minimalBrzozowski.countStates(), 3u);
  EXPECT_TRUE(minimalBrzozowski.isDeterministic());
  EXPECT_TRUE(minimalBrzozowski.isComplete());
  EXPECT_TRUE(minimalBrzozowski.match(""));
  EXPECT_TRUE(minimalBrzozowski.match("a"));
  EXPECT_TRUE(minimalBrzozowski.match("bbb"));
  EXPECT_TRUE(minimalBrzozowski.match("abbb"));  
}

TEST(BRZOZOWSKI, MakeMinimalAlreadyMinimal){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.addState(4));
  EXPECT_TRUE(fa.addState(5));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(5);
  EXPECT_TRUE(fa.isStateFinal(5));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 4));
  EXPECT_TRUE(fa.addTransition(1, 'b', 5));
  EXPECT_TRUE(fa.addTransition(2, 'a', 0));
  EXPECT_TRUE(fa.addTransition(2, 'b', 0));
  EXPECT_TRUE(fa.addTransition(3, 'a', 5));
  EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  EXPECT_TRUE(fa.addTransition(4, 'a', 3));
  EXPECT_TRUE(fa.addTransition(4, 'b', 5));
  EXPECT_TRUE(fa.addTransition(5, 'a', 3));
  EXPECT_TRUE(fa.addTransition(5, 'b', 4));

  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("bbab"));
  EXPECT_TRUE(fa.match("aaaa"));
  EXPECT_TRUE(fa.match("aaabbaa"));

  fa::Automaton minimalBrzozowski = fa::Automaton::createMinimalBrzozowski(fa);

  EXPECT_EQ(minimalBrzozowski.countStates(), 6u);
  EXPECT_TRUE(minimalBrzozowski.isDeterministic());
  EXPECT_TRUE(minimalBrzozowski.isComplete());
  EXPECT_TRUE(minimalBrzozowski.match("ab"));
  EXPECT_TRUE(minimalBrzozowski.match("bbab"));
  EXPECT_TRUE(minimalBrzozowski.match("aaaa"));
  EXPECT_TRUE(minimalBrzozowski.match("aaabbaa"));  
}

TEST(BRZOZOWSKI, MakeMinimalAlreadyMinimalNotComplete){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  //EXPECT_TRUE(fa.addState(4));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(3);
  EXPECT_TRUE(fa.isStateFinal(3));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  //EXPECT_TRUE(fa.addTransition(1, 'b', 4));
  EXPECT_TRUE(fa.addTransition(1, 'a', 3));
  EXPECT_TRUE(fa.addTransition(2, 'a', 0));
  EXPECT_TRUE(fa.addTransition(2, 'b', 0));
  //EXPECT_TRUE(fa.addTransition(3, 'a', 4));
  //EXPECT_TRUE(fa.addTransition(3, 'b', 4));
  //EXPECT_TRUE(fa.addTransition(4, 'a', 4));
  //EXPECT_TRUE(fa.addTransition(4, 'b', 4));

  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("bbbaaa"));
  EXPECT_TRUE(fa.match("bababbaa"));

  fa::Automaton minimalBrzozowski = fa::Automaton::createMinimalBrzozowski(fa);

  EXPECT_EQ(minimalBrzozowski.countStates(), 5u);
  EXPECT_TRUE(minimalBrzozowski.isDeterministic());
  EXPECT_TRUE(minimalBrzozowski.isComplete());
  EXPECT_TRUE(minimalBrzozowski.match("aa"));
  EXPECT_TRUE(minimalBrzozowski.match("bbbaaa"));
  EXPECT_TRUE(minimalBrzozowski.match("bababbaa"));
}

TEST(BRZOZOWSKI, MakeMinimal1NotAesthetic){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(8));
  EXPECT_TRUE(fa.addState(4));
  EXPECT_TRUE(fa.addState(5));

  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(8);
  EXPECT_TRUE(fa.isStateFinal(8));
  fa.setStateFinal(4);
  EXPECT_TRUE(fa.isStateFinal(4));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(5, 'b', 5));
  EXPECT_TRUE(fa.addTransition(4, 'b', 5));
  EXPECT_TRUE(fa.addTransition(1, 'b', 8));
  EXPECT_TRUE(fa.addTransition(2, 'a', 1));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(8, 'b', 5));
  EXPECT_TRUE(fa.addTransition(2, 'b', 4));
  EXPECT_TRUE(fa.addTransition(8, 'a', 4));
  EXPECT_TRUE(fa.addTransition(5, 'a', 5));
  EXPECT_TRUE(fa.addTransition(4, 'a', 8));

  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("bb"));
  EXPECT_TRUE(fa.match("aba"));
  EXPECT_TRUE(fa.match("baaabaaa"));

  fa::Automaton minimalBrzozowski = fa::Automaton::createMinimalBrzozowski(fa);

  EXPECT_EQ(minimalBrzozowski.countStates(), 4u);
  EXPECT_TRUE(minimalBrzozowski.isDeterministic());
  EXPECT_TRUE(minimalBrzozowski.isComplete());
  EXPECT_TRUE(minimalBrzozowski.match("ab"));
  EXPECT_TRUE(minimalBrzozowski.match("bb"));
  EXPECT_TRUE(minimalBrzozowski.match("aba"));
  EXPECT_TRUE(minimalBrzozowski.match("baaabaaa"));  
}

TEST(BRZOZOWSKI, NoInitialState) {
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
 
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));

  fa::Automaton minimalBrzozowski = fa::Automaton::createMinimalBrzozowski(fa);

  EXPECT_EQ(minimalBrzozowski.countStates(),1u);
  EXPECT_TRUE(minimalBrzozowski.isDeterministic());
  EXPECT_FALSE(minimalBrzozowski.match("b"));
  EXPECT_FALSE(minimalBrzozowski.match("ab"));
  EXPECT_FALSE(minimalBrzozowski.match("babbbb"));
  EXPECT_FALSE(minimalBrzozowski.match(""));
}

TEST(BRZOZOWSKI, NoFinalState) {
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
 
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, 'b', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(2, 'b', 2));

  fa::Automaton minimalBrzozowski = fa::Automaton::createMinimalBrzozowski(fa);

  EXPECT_EQ(minimalBrzozowski.countStates(),1u);
  EXPECT_TRUE(minimalBrzozowski.isDeterministic());
  EXPECT_FALSE(minimalBrzozowski.match("b"));
  EXPECT_FALSE(minimalBrzozowski.match("ab"));
  EXPECT_FALSE(minimalBrzozowski.match("babbbb"));
  EXPECT_FALSE(minimalBrzozowski.match(""));
}


/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Those tests exist in order to test the good implementation of the bonus *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

#if 0

TEST(EPSILON, RemoveEpsilonTransition){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, fa::Epsilon, 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 1));
  EXPECT_TRUE(fa.addTransition(2, 'a', 2));

  EXPECT_TRUE(fa.hasEpsilonTransition());
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("b"));
  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("abaaaa"));

  fa::Automaton fa_no_epsilon = fa::Automaton::createWithoutEpsilon(fa);
  
  EXPECT_FALSE(fa_no_epsilon.hasEpsilonTransition());
  EXPECT_TRUE(fa_no_epsilon.isDeterministic());
  EXPECT_EQ(fa_no_epsilon.countStates(), 3u);
  EXPECT_TRUE(fa_no_epsilon.match("a"));
  EXPECT_TRUE(fa_no_epsilon.match("b"));
  EXPECT_TRUE(fa_no_epsilon.match("baaaa"));
}

TEST(EPSILON, RemoveConsecutiveEpsilonTransitions){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_TRUE(fa.addSymbol('d'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 0));
  EXPECT_TRUE(fa.addTransition(0, fa::Epsilon, 1));
  EXPECT_TRUE(fa.addTransition(1, 'b', 1));
  EXPECT_TRUE(fa.addTransition(1, fa::Epsilon, 2));
  EXPECT_TRUE(fa.addTransition(2, 'c', 2));


  EXPECT_TRUE(fa.hasEpsilonTransition());
  EXPECT_TRUE(fa.match(""));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("b"));
  EXPECT_TRUE(fa.match("c"));
  EXPECT_TRUE(fa.match("aaaccc"));
  EXPECT_TRUE(fa.match("aabbcc"));
  EXPECT_TRUE(fa.match("bbbccc"));

  fa::Automaton fa_no_epsilon = fa::Automaton::createWithoutEpsilon(fa);

  EXPECT_FALSE(fa_no_epsilon.hasEpsilonTransition());
  EXPECT_TRUE(fa_no_epsilon.isDeterministic());
  EXPECT_EQ(fa_no_epsilon.countStates(), 3u);
  EXPECT_TRUE(fa_no_epsilon.match(""));
  EXPECT_TRUE(fa_no_epsilon.match("a"));
  EXPECT_TRUE(fa_no_epsilon.match("b"));
  EXPECT_TRUE(fa_no_epsilon.match("c"));
  EXPECT_TRUE(fa_no_epsilon.match("aaaccc"));
  EXPECT_TRUE(fa_no_epsilon.match("aabbcc"));
  EXPECT_TRUE(fa_no_epsilon.match("bbbccc"));
}

TEST(EPSILON, RemoveHorribleEpsilonTransition){
  fa::Automaton fa;

  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));

  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, fa::Epsilon, 1));
  EXPECT_TRUE(fa.addTransition(1, 'b', 2));
  EXPECT_TRUE(fa.addTransition(2, 'a', 2));

  EXPECT_TRUE(fa.hasEpsilonTransition());
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("b"));
  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("abaaaa"));

  fa::Automaton fa_no_epsilon = fa::Automaton::createWithoutEpsilon(fa);
    
  EXPECT_FALSE(fa_no_epsilon.hasEpsilonTransition());
  EXPECT_TRUE(fa_no_epsilon.isDeterministic());
  EXPECT_TRUE(fa_no_epsilon.match("a"));
  EXPECT_TRUE(fa_no_epsilon.match("b"));
  EXPECT_TRUE(fa_no_epsilon.match("ab"));
  EXPECT_TRUE(fa_no_epsilon.match("abaaaa"));
}

TEST(EPSILON, RemoveEpsilonTransitionAlreadyRemoved){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addState(0));
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isStateInitial(0));
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isStateFinal(2));

  EXPECT_TRUE(fa.addTransition(0, 'a', 1));
  EXPECT_TRUE(fa.addTransition(0, 'b', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 2));
  EXPECT_TRUE(fa.addTransition(2, 'a', 2));

  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("b"));
  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("abaaaa"));

  fa::Automaton fa_no_epsilon = fa::Automaton::createWithoutEpsilon(fa);
    
  EXPECT_FALSE(fa_no_epsilon.hasEpsilonTransition());
  EXPECT_TRUE(fa_no_epsilon.isDeterministic());
  EXPECT_TRUE(fa_no_epsilon.match("a"));
  EXPECT_TRUE(fa_no_epsilon.match("b"));
  EXPECT_TRUE(fa_no_epsilon.match("ab"));
  EXPECT_TRUE(fa_no_epsilon.match("abaaaa"));
}

#endif

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
