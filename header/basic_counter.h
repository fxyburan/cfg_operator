//
// Created by vontroy on 18-4-21.
//

#ifndef CFG_BASIC_COUNTER_H
#define CFG_BASIC_COUNTER_H


struct BB_Counter : public ModulePass {
    static char ID;

    BlockProfiler() : ModulePass(ID) {
        initializeBlock ProfilerPass(*Registry::getPassRegistry());
    }

    virtual bool runOnModule(Module &M);
};  //end of function profiling pass

#endif //CFG_BASIC_COUNTER_H
