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
        std::vector<int>& getKeys();
        virtual bool isLeaf() const = 0;
    };
    
    class LeafNode : public Node {
    private:
        std::vector<int> csvPos;
        int neighbor;
    
    public:
        LeafNode(int line, int fatherLine, int nPts, int neighbor);
    
        bool isLeaf() const override;
        std::vector<int>& getCsvPos();
        int getNeighbor();
    };
    
    class InternalNode : public Node {
    private:
        std::vector<int> children;
    
    public:
        InternalNode(int line, int fatherLine, int nPts);
    
        bool isLeaf() const override;
        std::vector<int>& getChildren();
    };

#endif