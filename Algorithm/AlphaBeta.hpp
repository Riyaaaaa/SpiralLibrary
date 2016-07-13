//
//  AlphaBeta.h
//  HyperReversi
//
//  Created by Atsumu Ono on 2016/06/09.
//
//

#ifndef AlphaBeta_h
#define AlphaBeta_h

#include<vector>
#include<algorithm>
#include"ReversiStream.h"
#include"../Container/Pair.hpp"

template<class Derived, class Field, class HandSelector, class Answer>
struct AlphaBetaState {
    typedef HandSelector HandSelector_t;
    typedef typename HandSelector::Hand_t Hand_t;
    typedef Field Field_t;
    typedef Answer Answer_t;
    
    AlphaBetaState(float alpha, float beta, bool isMyTurn, Hand_t hand):
    _alpha(alpha),
    _beta(beta),
    _isMyTurn(isMyTurn),
    _hand(hand),
    _eval(isMyTurn ? -1e6 : 1e6)
    {
        static_assert(std::is_same<decltype(std::declval<Derived>().getNextField(std::declval<Field>(), std::declval<Answer_t>())), Field>::value, "getNextField function is not defined");
        static_assert(std::is_same<decltype(std::declval<Derived>().getHands(std::declval<Field>())), std::vector<Answer_t>>::value, "getHands function is not defined");
        static_assert(std::is_same<decltype(std::declval<Derived>().calcEval(std::declval<Field>())), float>::value, "calcEval function is not defined");
    }
    
    bool isPruning(float eval) {
        if(_isMyTurn) {
            if(eval >= _beta) {
                return true;
            }
        }
        else {
            if(eval <= _alpha) {
                return true;
            }
        }
        return false;
    }
    
    void setEval(float eval) {
        if(_isMyTurn) {
            if(eval > _eval) {
                _eval = eval;
                _alpha = std::max(_alpha, _eval);
            }
        }
        else {
            if(eval < _eval) {
                _eval = eval;
                _beta = std::min(_beta, _eval);
            }
        }
    }
    
    float getEval() {
        return _eval;
    }
    
    float getAlpha() {
        return _alpha;
    }
    
    float getBeta() {
        return _beta;
    }
    
    Hand_t _hand;
    bool _isMyTurn;
    float _alpha, _beta;
    float _eval;
};

template<class FieldState>
class AlphaBeta {
public:
    typedef typename FieldState::HandSelector_t HandSelector;
    typedef typename FieldState::Field_t Field;
    typedef typename FieldState::Hand_t Hand;
    typedef typename FieldState::Answer_t Answer;
    
    static constexpr int SOAT_SHALLOW_DEPTH = 2;
    
    AlphaBeta(HandSelector selector):
    _selector(selector){
        
    }
    
    Answer operator()(const Field& field, int maxDepth) {
        std::vector<libspiral::Pair<Answer, float>> evalPriority;
        FieldState state(-1e6, 1e6, true, _selector(true));
        std::vector<Answer> nextHands;
        nextHands = state.getHands(field);
        
        for(auto && ans : nextHands) {
            float eval;
            auto nextField = state.getNextField(field, ans);
            
            eval = impl(nextField, -1e6, 1e6, 1, maxDepth);
            evalPriority.push_back(libspiral::make_pair(ans, eval));
        }
        
        if(maxDepth % 2 == 0) {
            std::sort(evalPriority.begin(), evalPriority.end(), libspiral::secondGreaterOrder{});
        }
        else {
            std::sort(evalPriority.begin(), evalPriority.end(), libspiral::secondLessOrder{});
        }
        
        return evalPriority.front().first;
    }
private:
    float impl(Field field, float alpha, float beta, int depth, int maxDepth) {
        FieldState state(alpha, beta, depth % 2 == 0, _selector(depth % 2 == 0));
        std::vector<Answer> nextHands = state.getHands(field);
        
        if(depth >= maxDepth) {
            return state.calcEval(field);
        }
        
        if(depth <= SOAT_SHALLOW_DEPTH) {
            nextHands = handsShallowSearchSort(field, state, nextHands);
        }
        
        for(auto ans: nextHands) {
            float eval;
            auto nextField = state.getNextField(field, ans);

            eval = impl(nextField, state.getAlpha(), state.getBeta(), depth + 1, maxDepth);

            if(state.isPruning(eval)) {
                return eval;
            }
            state.setEval(eval);
        }
        return state.getEval();
    }
    
    std::vector<Answer> handsShallowSearchSort(Field& field, FieldState& state, std::vector<Answer>& nextHands) {
        std::vector<Answer> sortedHands;
        sortedHands.reserve(nextHands.size());
        std::vector<libspiral::Pair<int, float>> sortIndexes(nextHands.size());
        for(int i = 0; i < nextHands.size(); i++) {
            auto nextField = state.getNextField(field, nextHands[i]);
            sortIndexes[i] = libspiral::make_pair(i, impl(nextField, state.getAlpha(), state.getBeta(), 0, 0));
        }
        
        std::sort(sortIndexes.begin(), sortIndexes.end(), libspiral::secondLessOrder());
        
        for(auto index : sortIndexes){
            sortedHands.push_back(nextHands[index.first]);
        }
        
        return sortedHands;
    }
    
    HandSelector _selector;
};

#endif /* AlphaBeta_h */
