//
// Created by vontroy on 18-4-21.
//

#include <iostream>
#include "../header/basic_counter.h"
#include "../header/cfg_graph.h"
#include "../header/graph_edge.h"

char BB_Counter::ID = 0;
INITIALIZE_PASS(BB_Counter,
"insert-block-profiling",
"Insert instrumentation for profiling", false, false )

ModulePass *llvm::createBB_CounterPass() { return new BB_Counter(); }


static RegisterPass <BlockProfilerPass> Y("insert-block-profiling",
                                          "Insert instrumentation for block profiling");

void counter_init(std::vector<graph_edge> *graphEdges) {
    unsigned int n, m;
    std::cin >> n >> m;
    //init
    std::vector<std::vector<int>> graph;
    graph.resize(m);
    for (int i = 0; i < m; ++i) {
        graph[i].resize(m);
    }

    //input graph
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        graph[x][y] = 1;
    }

    cfg_graph cfgGraph(graph);
    cfgGraph.cfg_preprocessing(&graphEdges);
    cfgGraph.dag_operator(&graphEdges);
}

bool edgeIsMarked() {
    return true;
}

bool BB_Counter::runOnModule(Module &M) {
    Function *Main = M.getFunction("main");
    if (Main == 0) {
        errs() << " WARING: cannot insert block profiling into a module"
               << " with no main function. \n";
        return false; // no main, no instrumentation, and no modify
    }

    unsigned NumBlocks = 0;
    for (Module::iterator I = M.begin(), E = M.end(); I != E; ++I)
        NumBlocks += I->size();

    Type *ATy = ArrayType::get(Type::getInt32Ty(M.getContext()), NumBlocks);
    GlobalVariable *Counters =
            new GlobalVariable(M, ATy, false, GlobalValue::InternalLinkage,
                               Constant::getNullValue(ATy), "BlockProCounters");

//Instrument all of the blocks
    unsigned i = 0;
    std::vector<graph_edge> graphEdges;

    counter_init(&graphEdges);

    for (Module::iterator I = M.begin(), E = M.end(); I != E; ++I) {
        for (Function::iterator BB = I->begin(), E = I->end(); BB != E; ++BB)
            //Insert counter at the start of the block
            if (edgeIsMarked()) {
                IncrementCounterInBlock(BB, i++, Counters);
            }
    }

    //add the initialization call to main
    InsertProfilingInitCall(Main, "llvm_start_block_profiling", Counters);
    return true;
}

