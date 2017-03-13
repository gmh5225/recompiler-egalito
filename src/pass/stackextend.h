#ifndef EGALITO_PASS_STACKEXTEND_H
#define EGALITO_PASS_STACKEXTEND_H

#include <vector>
#include <map>
#include <set>
#include "chunkpass.h"
#include "analysis/controlflow.h"
#include "chunk/register.h"
#include "elf/reloc.h"

#ifdef ARCH_AARCH64
class FrameType {
private:
    size_t baseSize;    // local varible + callee-saved regs
    size_t outArgSize;
    Instruction *setBPInstr;
    std::vector<Instruction *> resetSPInstrs;
    std::vector<Instruction *> returnInstrs;
public:
    FrameType(Function *function);
    Instruction *getSetBPInstr() const { return setBPInstr; }
    std::vector<Instruction *> getResetSPInstrs() const { return resetSPInstrs; }
    std::vector<Instruction *> getReturnInstrs() const { return returnInstrs; }
    void dump();

private:
    size_t getFrameSize(Function *function);
};

class StackExtendPass : public ChunkPass {
private:
    size_t extendSize;
public:
    StackExtendPass(size_t extendSize) : extendSize(extendSize) {}
    virtual void visit(Module *module);
    virtual void visit(Function *function);
    virtual void visit(Block *block) {}
    virtual void visit(Instruction *instruction) {}
private:
    bool shouldApply(Function *function);
    void addExtendStack(Function *function, FrameType *frame);
    void addShrinkStack(Function *function, FrameType *frame);
    virtual void useStack(Function *function, FrameType *frame) {};
};


class AARCH64InstructionBinary {
private:
    std::vector<unsigned char> v;
public:
    AARCH64InstructionBinary(uint32_t bin)
        : v({static_cast<unsigned char>(bin >> 0  & 0xff),
             static_cast<unsigned char>(bin >> 8  & 0xff),
             static_cast<unsigned char>(bin >> 16 & 0xff),
             static_cast<unsigned char>(bin >> 24 & 0xff)}) {}
    std::vector<unsigned char> getVector() { return v; }
};
#endif

#endif
