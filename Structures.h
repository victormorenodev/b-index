#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <vector>

using namespace std;

enum class Instruction {
    INC,
    BUS,
    FLH,
    INVALID
};

class Operation {
    private:
        Instruction instruction;
        int x;

    public:
        Operation(Instruction o, int val);

        Instruction getInstruction() const;

        int getX() const;
    };

    enum class NodeType {
        INTERNAL,
        LEAF
    };

    
class Node {
    protected:
        int line;
        int fatherLine;
        std::vector<int> keys;
        NodeType type;
        int nPts;
    
    public:
        Node(int line, int fatherLine, int nPts, NodeType type);
        virtual ~Node();
    
        NodeType getType() const;
        const std::vector<int>& getKeys() const;
        virtual bool isLeaf() const = 0;
    };
    
    class LeafNode : public Node {
    private:
        std::vector<int> csvPos;
        int neighbor;
    
    public:
        LeafNode(int line, int fatherLine, int nPts, int neighbor);
    
        bool isLeaf() const override;
        const std::vector<int>& getCsvPos() const;
        int getNeighbor() const;
    };
    
    class InternalNode : public Node {
    private:
        std::vector<int> children;
    
    public:
        InternalNode(int line, int fatherLine, int nPts);
    
        bool isLeaf() const override;
        const std::vector<int>& getChildren() const;
    };

#endif