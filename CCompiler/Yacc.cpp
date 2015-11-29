#include <list>
#include <stack>
#include "Yacc.h"
#include "Production.h"
using namespace std;
CYacc::CYacc(void)
{
	Init();
}


CYacc::~CYacc(void)
{
}

int CYacc::getProductionIndex(CProduction prod)
{
    for(int i=0;i<productionVec.size();++i)
    {
        if (productionVec[i].hasSameCore(prod))
        {
            return i;
        }
    }

    return -1;
}


vector<CProduction> CYacc::GetAfterItems(CProduction& lastLri)
{
    vector<CProduction> result;
    string nextElement = lastLri.nextElement();
    map<string, vector<CProduction>>::iterator nextIter = productionNameMap.find(nextElement);
    if (nextIter != productionNameMap.end())
    {
        result = nextIter->second;
    }

    return result;
}

vector<CProduction> CYacc::GetBeforeItems(CProduction& lastLri)
{
    vector<CProduction> result;
    string nextElement = lastLri.prevElement();
    map<string, vector<CProduction>>::iterator nextIter = productionNameMap.find(nextElement);
    if (nextIter != productionNameMap.end())
    {
        result = nextIter->second;
    }

    return result;
}

void CYacc::InitItem(CProduction& lastLri)
{

}

void CYacc::InitItems()
{
	for(int i=0;i<productionVec.size();++i)
	{
        InitItem(productionVec[i]);
	}
}

bool CYacc::isTerminal(string token)
{
    return (token == "$") || (terminalSet.find(token) != terminalSet.end());
}

bool CYacc::isNonTerminal(string token)
{
    return (nonterminalSet.find(token) != nonterminalSet.end());
}

vector<string> CYacc::getFirstSet(string token)
{
    vector<string> tokenVec;
    tokenVec.push_back(token);
    return getFirstSet(tokenVec);
}

vector<string> CYacc::getFirstSet(vector<string> tokenVec)
{
    return getFirstSet(tokenVec, 0);
}

vector<string> CYacc::getFirstSet(vector<string> tokenVec, int startIndex)
{
    vector<string> resultVec;
    if (startIndex >= tokenVec.size())
    {
        return resultVec;
    }

    if (tokenVec[startIndex] == "e" || tokenVec[startIndex] == "")
    {
        if (tokenVec.size() == startIndex + 1)
        {
            resultVec.push_back("e");
            return resultVec;
        }

        return getFirstSet(tokenVec, startIndex + 1);
    }
    else if(terminalSet.find(tokenVec[startIndex]) != terminalSet.end())
    {
        /// first set of a nonTerminalSet is itself.
        resultVec.push_back(tokenVec[startIndex]);
        return resultVec;
    }
    else if (nonterminalSet.find(tokenVec[startIndex]) != nonterminalSet.end())
    {
        vector<string> firstSetOfIthToken;
        map<string, bool> tokenExistMap;
        bool hasEmpty = false;
        for(int k=0;k<productionNameMap[tokenVec[startIndex]].size();++k)
        {
            vector<string> firstSetOfIthTokenTmp = getFirstSet(productionNameMap[tokenVec[startIndex]][k].tokens, 0);
            for(int j=0;j<firstSetOfIthTokenTmp.size();++j)
            {
                if(firstSetOfIthTokenTmp[j] == "e")
                {
                    hasEmpty = true;
                }
                tokenExistMap[firstSetOfIthTokenTmp[j]] = true;
            }
        }

        if (hasEmpty)
        {
            /// todo: check here to avoid recusive like:
            /// A-eA
            vector<string> firstSetOfIthTokenTmp2 = getFirstSet(tokenVec, 1+startIndex);
            for(int j=0;j<firstSetOfIthTokenTmp2.size();++j)
            {
                tokenExistMap[firstSetOfIthTokenTmp2[j]] = true;
            }
        }

        for(map<string, bool>::iterator iter = tokenExistMap.begin(); iter!= tokenExistMap.end();++iter)
        {
            resultVec.push_back(iter->first);
        }

        return resultVec;
    }
    
    return resultVec;
}

void CYacc::getFullState(YaccState& state)
{
    bool itemAdded = false;
    while(1)
    {
        //YaccState& state = gotoAction.stateVec[i];
        // for each production in the state
        vector<CProduction> tmpProduction = state.productionVec;
        for(int k=0;k<tmpProduction.size();++k)
        {
            vector<CProduction> nextProd= GetAfterItems(tmpProduction[k]);
            vector<string> tmpTokenSet;
            tmpTokenSet.push_back(tmpProduction[k].getTokenAfterNext());
            vector<string> tmpFirstSet =  getFirstSet(tmpTokenSet);
            bool hasEmptyItem = false;

            /// act means available coming tokens
            /// [A¡ú¦Á¡¤B¦Â,a]
            /// B¡ú¦Ã, 
            /// aCT = FIRST(¦Âa)
            /// ¦Â==¦Å, aCT = a
            /// ¦Â!=¦Å, act = FIRST(¦Â)
            /// todo: If FIRST(¦Â) = {a,b,¦Å}, there could be problem here.
            vector<string> aCT; //aCT means available coming token
            for(int i=0;i<tmpFirstSet.size();++i)
            {
                if (tmpFirstSet[i] == "e" || tmpFirstSet[i] == "" )
                {
                    hasEmptyItem = true;
                }
                else
                {
                    aCT.push_back(tmpFirstSet[i]);
                }
            }

            if (hasEmptyItem)
            {
                for(int j=0;j<tmpProduction[k].comingTokens.size();++j)
                {
                    aCT.push_back(tmpProduction[k].comingTokens[j]);
                }
            }

            vector<string> availableComingToken;
            //For A->.BC, add B->.EF to the current state
            //For A->B.C, add C->.MN to the current state
            for(int j=0;j<nextProd.size();++j)
            {
                nextProd[j].comingTokens = aCT;
                if (!state.hasItem(nextProd[j]))
                {
                    state.addItem(nextProd[j]);
                    itemAdded = true;
                }
            }
        }

        if (!itemAdded)
        {
            break;
            /// All items are updated in this state. Update the states to next
        }

        itemAdded = false;
    }
}

void CYacc::InitGotoTable()
{
    //vector<string> tokenVec;
    //tokenVec.push_back("e");
    //tokenVec.push_back("G");
    //vector<string> firstSet = getFirstSet(tokenVec);
    //for(int i=0;i<firstSet.size();++i)
    //{

    //    printf("%s ", firstSet[i].c_str());
    //}

    //printf("\n------------first set test done-----------------------------------\n");

    if (productionVec.size() <= 0)
    {
        return ;
    }

    class StateMove 
    {
    public :
        int prevState;
        string moveStr;
        YaccState state;

        StateMove(YaccState& yaccState)
        {
            prevState = -1;
            moveStr = "";
            state = yaccState;
        }

        StateMove(int prevS, const string& str, YaccState& yaccState)
        {
            prevState = prevS;
            moveStr = str;
            state = yaccState;
        }
    };

    gotoAction.clear();

    YaccState state;
    state.addItem(productionVec[0]);
    list<StateMove> stateList;
    StateMove stateMove(state);
    stateList.push_front(stateMove);

    while(stateList.size())
    {
        StateMove stateMove = stateList.front();
        stateList.pop_front();

        getFullState(stateMove.state);      //get CLOSURE(I) and add it to a list for looping
        int stateIndex = gotoAction.getStateIndex(stateMove.state);
        
        if(stateIndex == -1)
        {
            map<string, bool> tokenTaken;

            // for each state
            int currentStateIndex = gotoAction.addState(stateMove.state);
            for(int i=0;i<stateMove.state.productionVec.size();++i)
            {
                /// for each item in CLOSURE(I)
                /// A¡úBC¡¤, set reduce by A¡úBC in goto table

                if(stateMove.state.productionVec[i].isLastItem())
                {
                    /// has an Item which need reduce.
                    int index = getProductionIndex(stateMove.state.productionVec[i]);
                    if (index < 0)
                    {
                        printf("Error: invalid production\n");
                    }

                    for(int k=0;k<stateMove.state.productionVec[i].comingTokens.size();++k)
                    {
                        gotoAction.setGotoState(currentStateIndex, stateMove.state.productionVec[i].comingTokens[k], -(1+index));
                    }
                    
                    continue;
                }

                /// for each item in CLOSURE(I)
                /// A¡úB¡¤CE, add A¡úBC¡¤E to I` and we will get CLOSURE(I`) later.
                /// also consider A¡ú¡¤CF, add A¡úC¡¤F to I` and we will get CLOSURE(I`) later.
                /// Added A¡úC¡¤F and A¡úBC¡¤E because they share C to switch state.
                string nextToken = stateMove.state.productionVec[i].nextToken();
                 
                if (tokenTaken[nextToken])
                {
                    continue;
                }

                YaccState state;
                state.addItem(stateMove.state.productionVec[i].nextItem());

                for(int k=i+1;k<stateMove.state.productionVec.size();++k)
                {
                    if (stateMove.state.productionVec[k].nextToken() == nextToken)
                    {
                        CProduction prod = stateMove.state.productionVec[k].nextItem();
                        state.addItem(prod);
                    }                    
                }

                StateMove tmpStateMove(currentStateIndex, nextToken, state);
                stateList.push_back(tmpStateMove);
                tokenTaken[nextToken] = true;
            }

            if (stateMove.prevState != -1)
            {
                gotoAction.setGotoState(stateMove.prevState, stateMove.moveStr, currentStateIndex);

            }
        }
        else
        {
            gotoAction.setGotoState(stateMove.prevState, stateMove.moveStr, stateIndex);
        }
    }

    {
        /// Add $ action for G->S .

    }
}

void CYacc::dump()
{
    printf("\n---------------terminal chars-----------\n");
    for(unordered_set<string>::iterator iter = terminalSet.begin(); iter != terminalSet.end();++iter)
    {
        printf("%s\n", iter->c_str());
    }
    printf("\n--------------------------------------------\n");
    gotoAction.dump();
    printf("\n--------------------------------------------\n");
}

void CYacc::processToken(CLex lex)
{
    //////////////////////////////////////////////////////////////////////////
    // Test here.
    vector<CToken> testTokenVec = lex.getTokenVec();
    testTokenVec.push_back(CToken::getEndToken());
    int tokenIndex = 0;
    stack<int> stateStack;
    stateStack.push(0);
    stack<string> tokenStack;
    while(1)
    {
        if (testTokenVec.size() == tokenIndex)
        {
            printf("Invalid token sequence\n");
            break;
        }

        /// todo: need to check if the coming token is in the comingTokenList of current production.
        string currentToken = testTokenVec[tokenIndex].toString();
        int action = gotoAction.getGotoState(stateStack.top(), currentToken);
        if (isTerminal(currentToken))
        {
            if (GotoAction::INVALID_ACTION == action)
            {
                printf("Error when reducing. Invalid tokens to reduce:%s\n", testTokenVec[tokenIndex].info().c_str());
                return;
            }
            else if (action > 0)
            {
                /// move in a token
                stateStack.push(action);
                tokenStack.push(currentToken);
                ++tokenIndex;  // take a token
            }
            else
            {
                action = -action;
                action -= 1;

                //if (action == 0)
                //{
                //    /// accept if all tokens were processed.
                //    if ((testTokenVec.size() == tokenIndex + 1) && testTokenVec[tokenIndex].toString() == "$")
                //    {
                //        printf("Accept\n");
                //        return ;
                //    }
                //    else
                //    {
                //        //printf("Error:%s\n", currentToken.c_str());
                //        printf("Error:%s\n", testTokenVec[tokenIndex].info().c_str());
                //        break;
                //    }
                //}
                //else
                {
                    /// reduce with action-th production.
                    int prodTokenCount = productionVec[action].tokens.size();
                    if (tokenStack.size() >= prodTokenCount)
                    {
                        for(int i=0;i<prodTokenCount;++i)
                        {
                            if (tokenStack.top() == productionVec[action].tokens[prodTokenCount - 1 - i])
                            {
                                tokenStack.pop();
                                stateStack.pop();
                            }
                            else
                            {
                                printf("Error when reducing. Invalid tokens to reduce:%s\n", testTokenVec[tokenIndex].info().c_str());
                                return;
                            }
                        }

                        tokenStack.push(productionVec[action].name);

                        if (tokenStack.size() == 1 && tokenStack.top() == "G" && stateStack.size() == 1 && stateStack.top() == 0)
                        {
                            printf("Accept\n");
                            return ;
                        }

                        int reduceAction = gotoAction.getGotoState(stateStack.top(), productionVec[action].name);
                        printf("%s\n", productionVec[action].toString().c_str());
                        stateStack.push(reduceAction);
                    }
                    else
                    {
                        printf("Error when reducing. Not enough token to reduced\n");
                    }
                }
            }
        }
        else
        {
            stateStack.pop();
            stateStack.push(action);
        }
    }
}

//////////////////////////////////////////////////////////////////////////
///Initialize the goto table of LR(0) ?
//void CYacc::InitGotoTable()
//{
//    if (productionVec.size() <= 0)
//    {
//        return ;
//    }
//
//    class StateMove 
//    {
//    public :
//        int prevState;
//        string moveStr;
//        YaccState state;
//
//        StateMove(YaccState& yaccState)
//        {
//            prevState = -1;
//            moveStr = "";
//            state = yaccState;
//        }
//
//        StateMove(int prevS, const string& str, YaccState& yaccState)
//        {
//            prevState = prevS;
//            moveStr = str;
//            state = yaccState;
//        }
//    };
//
//    gotoAction.clear();
//
//    YaccState state;
//    state.addItem(productionVec[0]);
//    list<StateMove> stateList;
//    StateMove stateMove(state);
//    stateList.push_front(stateMove);
//
//    while(stateList.size())
//    {
//        StateMove stateMove = stateList.front();
//        stateList.pop_front();
//
//        getFullState(stateMove.state);
//        int stateIndex = gotoAction.getStateIndex(stateMove.state);
//
//        if(stateIndex == -1)
//        {
//            map<string, bool> tokenTaken;
//
//            // for each state
//            int currentStateIndex = gotoAction.addState(stateMove.state);
//            for(int i=0;i<stateMove.state.productionVec.size();++i)
//            {
//                if(stateMove.state.productionVec[i].isLastItem())
//                {
//                    continue;
//                }
//
//                string nextToken = stateMove.state.productionVec[i].nextToken();
//
//                if (tokenTaken[nextToken])
//                {
//                    continue;
//                }
//
//                YaccState state;
//                state.addItem(stateMove.state.productionVec[i].nextItem());
//
//                for(int k=i+1;k<stateMove.state.productionVec.size();++k)
//                {
//                    if (stateMove.state.productionVec[k].nextToken() == nextToken)
//                    {
//                        CProduction prod = stateMove.state.productionVec[k].nextItem();
//                        state.addItem(prod);
//                    }                    
//                }
//
//                StateMove tmpStateMove(currentStateIndex, nextToken, state);
//                stateList.push_back(tmpStateMove);
//                tokenTaken[nextToken] = true;
//            }
//
//            if (stateMove.prevState != -1)
//            {
//                gotoAction.setGotoState(stateMove.prevState, stateMove.moveStr, currentStateIndex);
//            }
//        }
//        else
//        {
//            gotoAction.setGotoState(stateMove.prevState, stateMove.moveStr, stateIndex);
//        }
//    }
//
//    gotoAction.dump();
//}

void CYacc::Init()
{
	InitProduction();
	InitItems();

    InitGotoTable();
}


bool CYacc::InitProduction()
{
    /// use 'e' as empty token.

    static char * syntax[] = {
        "G->S",
    	"S->CElement S",
        "S->CElement",
    	"CElement->DefineVariable", 
        "CElement->DefineMethod", 
    	"DefineVariable->TYPE ID_LIST ;", 
        "ID_LIST->ID_ITEM , ID_LIST",
        "ID_LIST->ID_ITEM",
        "ID_ITEM->id", 
        "ID_ITEM->id = Expression", 
        //"DefineVariable->TYPE id = num ;", 
        //"DefineVariable->TYPE id = Expression ;", 
    	"DefineMethod->TYPE id ( TYPE_ARG_LIST ) { METHOD_BODY }",
        "DefineMethod->TYPE id ( TYPE_ARG_LIST ) { }",
    	"DefineMethod->TYPE id ( ) { METHOD_BODY }",
        "DefineMethod->TYPE id ( ) { }",
        "METHOD_BODY->Statements", 
        "Statements->Statement Statements", 
        "Statements->Statement", 
        "Statement->{ Statements }", 
        "Statement->DefineVariable",
        "Statement->MethodCall ;",
        "Statement->for ( Expression ; Expression ; Expression ) Statement",
        "Statement->while ( Expression ) Statement",
        "Statement->do Statement while ( Expression ) ;",
        "MethodCall->id ( )", 
        "MethodCall->id ( ARG_LIST )", 
        "Statement->Expression ;",
        //"MethodCall->id ( ) ;", 
        //"MethodCall->id ( ARG ) ;", 
        //"MethodCall->id ( ARG ARG ) ;", 
        //"MethodCall->id ( ARG ARG ARG ) ;", 
        //"ARG->id",
        //"ARG->num",
        "Expression->Expression_ + Expression",
        "Expression->Expression_ - Expression",
        "Expression->Expression_ = Expression",
        //"Expression->Expression_ >= Expression",
        //"Expression->Expression_ <= Expression",
        //"Expression->Expression_ == Expression",
        //"Expression->Expression_ != Expression",
        "Expression->( Expression )",
        "Expression->Expression_",
        "Expression_->( Expression )",
        "Expression_->VAL",
        "Expression_->VAL * Expression_",
        "Expression_->VAL / Expression_",
        "VAL->MethodCall",
        "VAL->id",
        "VAL->num",
        "TYPE->int",
        "TYPE->double",
        "TYPE->float",
        "TYPE->short",

        "ARG_LIST->ARG , ARG_LIST",
        "ARG_LIST->ARG",
        "ARG->VAL",
        "TYPE_ARG_LIST->TYPE_ARG , TYPE_ARG_LIST",
        "TYPE_ARG_LIST->TYPE_ARG",
        "TYPE_ARG->TYPE id",
       };


    //static char * syntax[] = {
    //    "G->E", 
    //    "E->E + T", 
    //    "E->T", 
    //    "T->T * F", 
    //    "T->F", 
    //    "F->( E )", 
    //    "F->id"
    //};

    //static char * syntax[] = {
    //    "G->A", 
    //    "A->B C D id E",
    //    "B->main",
    //    "B->e",
    //    "C->exp",
    //    "C->e",
    //    "D->stat",
    //    "D->e",
    //    "E->for",
    //    "E->e",
    //};

    for(int i=0;i<sizeof(syntax)/sizeof(syntax[0]);++i)
    {
        CProduction production;
        production.FromString(syntax[i]);
        production.BuildLRItems();

        if (production.name == "G")
        {
            production.comingTokens.push_back("$");
        }

        if (production.tokens.size()>0 && production.tokens[0] == production.name)
        {
            /// L-Recursive grammer
            printf("ERROR at: %s %d\n", __FUNCTION__, __LINE__);
            return false;
        }

        productionVec.push_back(production);
        productionNameMap[production.name].push_back(production);
    }


    for(int i=0;i<productionVec.size();++i)
    {
        nonterminalSet.insert(productionVec[i].name);
    }

    for(int i=0;i<productionVec.size();++i)
    {
        for(int k=0;k<productionVec[i].tokens.size();++k)
        {
            std::unordered_set<string>::iterator iter = nonterminalSet.find(productionVec[i].tokens[k]);
            if (iter!= nonterminalSet.end())
            {
                firstSet.push_back(*iter);
            }
            else
            {
                terminalSet.insert(productionVec[i].tokens[k]);
            }
        }
    }

    return true;
}
